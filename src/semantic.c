/* semantic.c — Semantic analysis pass.
 *
 * Walks the AST and validates:
 *   - type correctness of all declarations, updates, casts, print exprs
 *   - that conditionals reference declared variables and group sizes match
 *
 * As a side-effect, every successfully validated declaration is registered
 * with the global symtab, making it available to the TAC and exec passes.
 *
 * Returns the number of semantic errors found (0 = clean programme).
 */
#include "semantic.h"
#include "symtab.h"
#include "functab.h"
#include "value.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

/* ================================================================
   Error bookkeeping
   ================================================================ */
static int  sem_errors         = 0;
static int  g_prescan          = 0;   /* 1 during function pre-scan pass */
static Type g_current_ret_type = T_UNKNOWN; /* return type of enclosing func */

static void sem_err(int line, const char* fmt, ...) {
  sem_errors++;
  fprintf(stderr, "SEM_ERROR at line %d: ", line);
  va_list ap;
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);
  fprintf(stderr, "\n");
}

/* ================================================================
   Expression type inference
   Used both for type-checking and for determining the result type
   of a sub-expression.  Reports errors on the way.
   ================================================================ */
static Type sem_check_expr(AstExpr* e, int line) {
  if (!e) return T_UNKNOWN;
  switch (e->kind) {
    case EXPR_INT_LIT:   return T_INT;
    case EXPR_FLOAT_LIT: return T_FLOAT;
    case EXPR_BOOL_LIT:  return T_BOOL;
    case EXPR_STR_LIT:   return T_STR;

    case EXPR_ID: {
      Symbol* s = symtab_lookup(e->as.sval);
      if (!s) {
        sem_err(line, "Use of undeclared variable '%s'", e->as.sval);
        return T_UNKNOWN;
      }
      return s->type;
    }

    case EXPR_BINOP: {
      Type lt = sem_check_expr(e->as.binop.left,  line);
      Type rt = sem_check_expr(e->as.binop.right, line);
      if (lt == T_UNKNOWN || rt == T_UNKNOWN) return T_UNKNOWN;
      /* Integer arithmetic */
      if (lt == T_INT && rt == T_INT) return T_INT;
      /* Mixed / float arithmetic */
      if ((lt == T_INT || lt == T_FLOAT) && (rt == T_INT || rt == T_FLOAT))
        return T_FLOAT;
      /* String concatenation is not supported */
      sem_err(line, "Invalid types for arithmetic operator (%s, %s)",
              type_name(lt), type_name(rt));
      return T_UNKNOWN;
    }

    case EXPR_CALL: {
      FuncDef* f = functab_lookup(e->as.call.name);
      if (!f) {
        sem_err(line, "Call to undefined function '%s'", e->as.call.name);
        return T_UNKNOWN;
      }
      if (e->as.call.argc != f->param_count) {
        sem_err(line, "Function '%s' expects %d argument(s), got %d",
                e->as.call.name, f->param_count, e->as.call.argc);
      } else {
        for (int i = 0; i < e->as.call.argc; i++) {
          Type at = sem_check_expr(e->as.call.args[i], line);
          if (at != T_UNKNOWN && at != f->params[i].type) {
            sem_err(line,
                    "Argument %d to '%s': expected %s, got %s",
                    i + 1, e->as.call.name,
                    type_name(f->params[i].type), type_name(at));
          }
        }
      }
      return f->return_type;
    }
  }
  return T_UNKNOWN;
}

/* ================================================================
   Forward declaration for recursive use
   ================================================================ */
static void sem_check_list(AstNode* list);

/* ================================================================
   Declaration helpers
   ================================================================ */

/*
 * Validate and register a declaration in the global symtab.
 * For const decls with a literal value the value is stored immediately
 * so downstream read-only passes (tac.c) can access it.
 */
static void sem_check_decl(AstNode* n) {
  char*   id         = n->as.decl.id;
  Type    decl_type  = n->as.decl.declared_type;
  AstExpr* val_expr  = n->as.decl.value;
  int      is_const  = n->as.decl.is_const;

  /* If there is an initialiser, check that its type matches the declared type.
     Special case: INT 0/1 may be used to initialise a BOOL variable. */
  if (val_expr) {
    Type expr_type = sem_check_expr(val_expr, n->line);
    if (expr_type != T_UNKNOWN) {
      int ok = (expr_type == decl_type)
            || (decl_type == T_BOOL && expr_type == T_INT);
      if (!ok) {
        sem_err(n->line,
                "Type mismatch in declaration of '%s' (expected %s, got %s)",
                id, type_name(decl_type), type_name(expr_type));
      }
    }
  }

  /* Register in symtab */
  if (!symtab_declare(id, decl_type, is_const, (val_expr != NULL), n->line)) {
    sem_err(n->line, "Redeclaration of variable '%s'", id);
  }
}

/* ================================================================
   Update checks
   ================================================================ */
static void sem_check_update(AstNode* n) {
  char*    id       = n->as.upd.id;
  AstExpr* val_expr = n->as.upd.value;

  Symbol* s = symtab_lookup(id);
  if (!s) {
    sem_err(n->line, "Update of undeclared variable '%s'", id);
    return;
  }
  if (s->is_const) {
    sem_err(n->line, "Cannot update constant (pakka) variable '%s'", id);
    return;
  }
  Type expr_type = sem_check_expr(val_expr, n->line);
  if (expr_type != T_UNKNOWN && expr_type != s->type) {
    sem_err(n->line,
            "Type mismatch in update of '%s' (expected %s, got %s)",
            id, type_name(s->type), type_name(expr_type));
  }
}

/* ================================================================
   Cast checks
   ================================================================ */
static void sem_check_cast(AstNode* n) {
  char*    id        = n->as.cast.id;
  Type     cast_type = n->as.cast.cast_type;
  AstExpr* val_expr  = n->as.cast.value;

  if (!n->as.cast.is_update) {
    /* cast_decl: banaw T rakho ID -> T */
    Type decl_type = n->as.cast.declared_type;
    if (cast_type != decl_type) {
      sem_err(n->line,
              "Cast type and declared type must match for '%s' "
              "(banaw %s but declared %s)",
              id, type_name(cast_type), type_name(decl_type));
    }
    sem_check_expr(val_expr, n->line);   /* validate source expr */
    if (!symtab_declare(id, decl_type, 0, 1, n->line)) {
      sem_err(n->line, "Redeclaration of variable '%s'", id);
    }
  } else {
    /* cast_update: banaw T bodlao ID */
    Symbol* s = symtab_lookup(id);
    if (!s) {
      sem_err(n->line, "Update of undeclared variable '%s'", id);
      return;
    }
    if (s->is_const) {
      sem_err(n->line,
              "Cannot update constant (pakka) variable '%s'", id);
      return;
    }
    if (cast_type != s->type) {
      sem_err(n->line,
              "Cast type must match variable type for '%s' "
              "(banaw %s but var is %s)",
              id, type_name(cast_type), type_name(s->type));
    }
    sem_check_expr(val_expr, n->line);
  }
}

/* ================================================================
   Conditional chain checks
   ================================================================ */
static void sem_check_cond(AstNode* n) {
  for (int bi = 0; bi < n->as.cond.block_count; bi++) {
    AstCondBlock* cb = n->as.cond.blocks[bi];

    /* Validate each binding: variable must be declared and
       binding expression type must match the variable's type. */
    for (int b = 0; b < cb->bind_count; b++) {
      const char* var_name = cb->binds[b].id;
      Symbol* s = symtab_lookup(var_name);
      if (!s) {
        sem_err(n->line,
                "Binding uses undeclared variable '%s'", var_name);
      } else {
        Type expected_t = sem_check_expr(cb->binds[b].expr, n->line);
        if (expected_t != T_UNKNOWN && expected_t != s->type) {
          sem_err(n->line,
                  "Type mismatch in binding for '%s' (expected %s, got %s)",
                  var_name, type_name(s->type), type_name(expected_t));
        }
      }
    }

    /* Validate each group: item count must match binding count,
       and empty groups [] are only allowed as the else clause. */
    for (int g = 0; g < cb->group_count; g++) {
      int op_count = cb->groups[g].count;
      if (op_count == 0) {
        sem_err(n->line,
                "Empty [] is reserved for ELSE only "
                "(not allowed in IF/ELSEIF groups)");
      } else if (op_count != cb->bind_count) {
        sem_err(n->line,
                "Condition items count (%d) does not match "
                "bindings count (%d)",
                op_count, cb->bind_count);
      }
    }

    /* Recurse into the conditional body */
    sem_check_list(cb->block);
  }

  /* Recurse into the else block (if present) */
  sem_check_list(n->as.cond.else_block);
}

/* ================================================================
   Single-node dispatcher
   ================================================================ */
static void sem_check_node(AstNode* n) {
  if (!n) return;

  /* ---- Prescan pass: register function signatures only ---- */
  if (g_prescan) {
    if (n->kind == STMT_FUNC_DEF) {
      int pc = n->as.func.param_count;
      FuncParamNode* pcopy = NULL;
      if (pc > 0) {
        pcopy = (FuncParamNode*)malloc(pc * sizeof(FuncParamNode));
        for (int i = 0; i < pc; i++) {
          pcopy[i].name = strdup(n->as.func.params[i].name);
          pcopy[i].type = n->as.func.params[i].type;
        }
      }
      if (!functab_register(n->as.func.name, n->as.func.return_type,
                             pcopy, pc, n->as.func.body))
        sem_err(n->line, "Redefinition of function '%s'", n->as.func.name);
    }
    return;  /* skip all other node types during prescan */
  }

  switch (n->kind) {
    case STMT_DECL:
    case STMT_CONST_DECL:
      sem_check_decl(n);
      break;

    case STMT_DEFAULT_DECL:
    case STMT_CONST_DEFAULT:
      /* No expression to check; just register the symbol. */
      if (!symtab_declare(n->as.decl.id, n->as.decl.declared_type,
                          n->as.decl.is_const, 0, n->line)) {
        sem_err(n->line, "Redeclaration of variable '%s'", n->as.decl.id);
      }
      break;

    case STMT_UPDATE:
      sem_check_update(n);
      break;

    case STMT_CAST_DECL:
    case STMT_CAST_UPDATE:
      sem_check_cast(n);
      break;

    case STMT_PRINT:
      /* Any type is printable; just validate the expression. */
      sem_check_expr(n->as.print_expr, n->line);
      break;

    case STMT_COND_CHAIN:
      sem_check_cond(n);
      break;

    case STMT_LOOP: {
      char* v  = n->as.loop.var;
      char* ev = n->as.loop.end_var;
      char* cv = n->as.loop.ctrl_var;

      /* Issue 2: loop init var and end var must be the same */
      if (ev && strcmp(v, ev) != 0)
        sem_err(n->line,
                "Loop end variable '%s' must match init variable '%s'",
                ev, v);

      /* Issue 3: loop control variable must match the loop variable */
      if (n->as.loop.step != LOOP_STOP && cv && strcmp(v, cv) != 0)
        sem_err(n->line,
                "Loop control variable '%s' must match loop variable '%s'",
                cv, v);

      /* Declare loop variable if new */
      Type lt;
      if (n->as.loop.is_new) {
        lt = n->as.loop.new_type;
        if (!symtab_declare(v, lt, 0, 1, n->line))
          sem_err(n->line, "Redeclaration of loop variable '%s'", v);
      } else {
        Symbol* s = symtab_lookup(v);
        if (!s) { sem_err(n->line, "Loop uses undeclared variable '%s'", v); break; }
        lt = s->type;
      }
      /* Check init and end expression types */
      Type it = sem_check_expr(n->as.loop.init_expr, n->line);
      Type et = sem_check_expr(n->as.loop.end_expr,  n->line);
      if (it != T_UNKNOWN && it != lt)
        sem_err(n->line, "Loop init type mismatch for '%s' (expected %s, got %s)",
                v, type_name(lt), type_name(it));
      if (et != T_UNKNOWN && et != lt)
        sem_err(n->line, "Loop end type mismatch for '%s' (expected %s, got %s)",
                v, type_name(lt), type_name(et));
      /* Check body */
      sem_check_list(n->as.loop.body);
      break;
    }

    case STMT_FUNC_DEF: {
      /* Function was already registered in the prescan pass.
         Here we only validate the body with proper param scope and
         track the declared return type for STMT_RETURN checks. */
      int pc = n->as.func.param_count;
      Type saved_ret     = g_current_ret_type;
      g_current_ret_type = n->as.func.return_type;
      symtab_push_scope();
      for (int i = 0; i < pc; i++)
        symtab_declare(n->as.func.params[i].name,
                       n->as.func.params[i].type, 0, 1, n->line);
      sem_check_list(n->as.func.body);
      symtab_pop_scope();
      g_current_ret_type = saved_ret;
      break;
    }

    case STMT_RETURN: {
      /* Issue 1: return expression type must match the declared return type */
      if (n->as.ret.expr) {
        Type rt = sem_check_expr(n->as.ret.expr, n->line);
        if (rt != T_UNKNOWN && g_current_ret_type != T_UNKNOWN) {
          int ok = (rt == g_current_ret_type)
                || (g_current_ret_type == T_FLOAT && rt == T_INT); /* coerce */
          if (!ok)
            sem_err(n->line,
                    "Return type mismatch: function declares %s but returns %s",
                    type_name(g_current_ret_type), type_name(rt));
        }
      }
      break;
    }
  }
}

/* ================================================================
   List walker
   ================================================================ */
static void sem_check_list(AstNode* list) {
  for (AstNode* n = list; n; n = n->next)
    sem_check_node(n);
}

/* ================================================================
   Public entry point
   ================================================================ */
int semantic_check(AstNode* root) {
  sem_errors = 0;

  /* Pass 1: register all top-level function signatures.
     This allows forward function calls (call before definition). */
  g_prescan = 1;
  sem_check_list(root);
  g_prescan = 0;

  /* Pass 2: full type-checking pass */
  sem_check_list(root);

  return sem_errors;
}
