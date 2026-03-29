/* exec.c — AST interpreter / execution pass.
 *
 * Walks the AST and executes each statement, using the global symtab
 * (which was populated with type information by semantic_check) to
 * store and retrieve runtime values.
 *
 * For declarations, exec sets the runtime value.
 * For updates, exec checks const-ness and sets the new value.
 * For print (bolo), exec evaluates the expression and writes to stdout.
 * For conditionals, exec evaluates bindings against actual variable values
 * and runs the first matching branch (or the else block).
 */
#include "ast.h"
#include "symtab.h"
#include "functab.h"
#include "value.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Forward declarations */
static EvalVal exec_expr(AstExpr* e);
static void    exec_stmts(AstNode* list);

/* ================================================================
   Return value mechanism (for function calls)
   ================================================================ */
static EvalVal g_return_val = { T_UNKNOWN, {0}, 0 };
static int     g_returning  = 0;
static int     g_breaking   = 0;  /* set by thamo (break) inside a loop */
static int     g_continuing = 0;  /* set by agao (continue) inside a loop */

/* ================================================================
   Expression evaluator
   Returns an EvalVal.  For string results the caller owns the copy
   only when owns_str == 1.
   ================================================================ */
static EvalVal exec_expr(AstExpr* e) {
  if (!e) return eval_unknown();

  switch (e->kind) {
    case EXPR_INT_LIT:   return eval_int(e->as.ival);
    case EXPR_FLOAT_LIT: return eval_float(e->as.fval);
    case EXPR_BOOL_LIT:  return eval_bool(e->as.bval);
    case EXPR_STR_LIT:   return eval_str_copy(e->as.sval);

    case EXPR_ID: {
      Symbol* s = symtab_lookup(e->as.sval);
      if (!s) {
        /* Should have been caught by semantic; just return unknown */
        return eval_unknown();
      }
      if (s->type == T_STR) {
        /* Return a non-owned reference into the symtab's storage */
        EvalVal ev;
        ev.type      = T_STR;
        ev.val.s     = s->val.s;
        ev.owns_str  = 0;
        return ev;
      }
      EvalVal ev;
      ev.type     = s->type;
      ev.val      = s->val;
      ev.owns_str = 0;
      return ev;
    }

    case EXPR_CALL: {
      FuncDef* f = functab_lookup(e->as.call.name);
      if (!f) {
        fprintf(stderr, "RUNTIME_ERROR: undefined function '%s'\n", e->as.call.name);
        return eval_unknown();
      }
      /* Evaluate arguments before pushing scope */
      EvalVal* args = (EvalVal*)malloc(e->as.call.argc * sizeof(EvalVal));
      for (int i = 0; i < e->as.call.argc; i++)
        args[i] = exec_expr(e->as.call.args[i]);
      /* Push scope and declare parameters */
      symtab_push_scope();
      for (int i = 0; i < f->param_count; i++) {
        symtab_declare(f->params[i].name, f->params[i].type, 0, 1, 0);
        symtab_set_value(f->params[i].name, f->params[i].type,
                         (i < e->as.call.argc) ? args[i].val : (Value){0});
      }
      for (int i = 0; i < e->as.call.argc; i++) eval_free(&args[i]);
      free(args);
      /* Execute body */
      int saved_returning = g_returning;
      EvalVal saved_retval = g_return_val;
      g_returning = 0;
      g_return_val = eval_unknown();
      exec_stmts(f->body);
      EvalVal result = g_return_val;
      g_return_val = saved_retval;
      g_returning  = saved_returning;
      symtab_pop_scope();
      return result;
    }

    case EXPR_BINOP: {
      EvalVal lv = exec_expr(e->as.binop.left);
      EvalVal rv = exec_expr(e->as.binop.right);
      EvalVal result;

      if (lv.type == T_INT && rv.type == T_INT) {
        switch (e->as.binop.op) {
          case BINOP_ADD: result = eval_int(lv.val.i + rv.val.i); break;
          case BINOP_SUB: result = eval_int(lv.val.i - rv.val.i); break;
          case BINOP_MUL: result = eval_int(lv.val.i * rv.val.i); break;
          case BINOP_DIV:
            if (rv.val.i == 0) {
              fprintf(stderr, "RUNTIME_ERROR: division by zero\n");
              result = eval_int(0);
            } else {
              result = eval_int(lv.val.i / rv.val.i);
            }
            break;
          default: result = eval_unknown(); break;
        }
      } else if ((lv.type == T_FLOAT || lv.type == T_INT) &&
                 (rv.type == T_FLOAT || rv.type == T_INT)) {
        double ld = (lv.type == T_INT) ? (double)lv.val.i : lv.val.f;
        double rd = (rv.type == T_INT) ? (double)rv.val.i : rv.val.f;
        switch (e->as.binop.op) {
          case BINOP_ADD: result = eval_float(ld + rd); break;
          case BINOP_SUB: result = eval_float(ld - rd); break;
          case BINOP_MUL: result = eval_float(ld * rd); break;
          case BINOP_DIV:
            if (rd == 0.0) {
              fprintf(stderr, "RUNTIME_ERROR: division by zero\n");
              result = eval_float(0.0);
            } else {
              result = eval_float(ld / rd);
            }
            break;
          default: result = eval_unknown(); break;
        }
      } else {
        result = eval_unknown();
      }
      eval_free(&lv);
      eval_free(&rv);
      return result;
    }
  }
  return eval_unknown();
}

/* ================================================================
   Conditional evaluation helper
   Compare actual symtab value against an expected EvalVal using op.
   Returns 1 if the condition holds.
   ================================================================ */
static int compare_vals(const Value* actual, const Value* expected,
                         Type t, CondOp op) {
  if (op == CONDOP_SKIP) return 1;

  switch (t) {
    case T_INT:
      switch (op) {
        case CONDOP_GE:  return actual->i >= expected->i;
        case CONDOP_LE:  return actual->i <= expected->i;
        case CONDOP_EQ:  return actual->i == expected->i;
        case CONDOP_NEQ: return actual->i != expected->i;
        case CONDOP_GT:  return actual->i >  expected->i;
        case CONDOP_LT:  return actual->i <  expected->i;
        default: return 0;
      }
    case T_FLOAT:
      switch (op) {
        case CONDOP_GE:  return actual->f >= expected->f;
        case CONDOP_LE:  return actual->f <= expected->f;
        case CONDOP_EQ:  return actual->f == expected->f;
        case CONDOP_NEQ: return actual->f != expected->f;
        case CONDOP_GT:  return actual->f >  expected->f;
        case CONDOP_LT:  return actual->f <  expected->f;
        default: return 0;
      }
    case T_BOOL:
      switch (op) {
        case CONDOP_EQ:  return actual->b == expected->b;
        case CONDOP_NEQ: return actual->b != expected->b;
        default: return 0;
      }
    case T_STR:
      if (!actual->s || !expected->s) return 0;
      switch (op) {
        case CONDOP_EQ:  return strcmp(actual->s, expected->s) == 0;
        case CONDOP_NEQ: return strcmp(actual->s, expected->s) != 0;
        default: return 0;
      }
    default:
      return 0;
  }
}

/*
 * Try to match a single cond_block against the current runtime state.
 * If any group matches, execute the block and return 1.
 * Otherwise return 0.
 */
static int exec_cond_block(AstCondBlock* cb) {
  /* Evaluate all binding expected values */
  EvalVal* expected = (EvalVal*)malloc(cb->bind_count * sizeof(EvalVal));
  for (int b = 0; b < cb->bind_count; b++) {
    expected[b] = exec_expr(cb->binds[b].expr);
  }

  int matched = 0;

  /* Check each group (OR across groups) */
  for (int g = 0; g < cb->group_count && !matched; g++) {
    AstCondGroup* grp = &cb->groups[g];
    int group_ok = 1;

    for (int b = 0; b < cb->bind_count && b < grp->count; b++) {
      Symbol* s = symtab_lookup(cb->binds[b].id);
      if (!s) { group_ok = 0; break; }
      if (!compare_vals(&s->val, &expected[b].val, s->type, grp->ops[b])) {
        group_ok = 0;
        break;
      }
    }

    if (group_ok) {
      matched = 1;
      exec_stmts(cb->block);
    }
  }

  for (int b = 0; b < cb->bind_count; b++) eval_free(&expected[b]);
  free(expected);
  return matched;
}

/* ================================================================
   Statement executors
   ================================================================ */

static void exec_decl(AstNode* n) {
  /* Declare the symbol at runtime — needed for function-local variables
     whose scope was created then popped during the semantic pass. */
  symtab_declare(n->as.decl.id, n->as.decl.declared_type,
                 n->as.decl.is_const, (n->as.decl.value != NULL), n->line);

  if (!n->as.decl.value) return;   /* khaali — keep symtab default */

  EvalVal ev = exec_expr(n->as.decl.value);
  Type decl_t = n->as.decl.declared_type;

  /* Handle INT-to-BOOL coercion */
  if (decl_t == T_BOOL && ev.type == T_INT) {
    Value bv; bv.b = (ev.val.i != 0);
    symtab_set_value(n->as.decl.id, T_BOOL, bv);
    eval_free(&ev);
    return;
  }

  symtab_set_value(n->as.decl.id, ev.type, ev.val);
  eval_free(&ev);
}

static void exec_update(AstNode* n) {
  Symbol* s = symtab_lookup(n->as.upd.id);
  if (!s) return;
  if (s->is_const) {
    fprintf(stderr,
            "RUNTIME_ERROR: cannot update constant (pakka) '%s'\n",
            n->as.upd.id);
    return;
  }
  EvalVal ev = exec_expr(n->as.upd.value);
  symtab_set_value(n->as.upd.id, ev.type, ev.val);
  eval_free(&ev);
}

static void exec_cast(AstNode* n) {
  EvalVal src = exec_expr(n->as.cast.value);
  EvalVal casted;
  if (!cast_value(&src, n->as.cast.cast_type, &casted)) {
    fprintf(stderr,
            "RUNTIME_ERROR: cannot cast %s to %s for '%s'\n",
            type_name(src.type), type_name(n->as.cast.cast_type),
            n->as.cast.id);
    eval_free(&src);
    return;
  }
  eval_free(&src);
  /* Declare at runtime if this is a new variable (cast_decl) */
  if (!n->as.cast.is_update)
    symtab_declare(n->as.cast.id, n->as.cast.declared_type, 0, 1, n->line);
  symtab_set_value(n->as.cast.id, casted.type, casted.val);
  eval_free(&casted);
}

static void exec_print(AstNode* n) {
  EvalVal ev = exec_expr(n->as.print_expr);
  switch (ev.type) {
    case T_INT:   printf("%ld\n",  ev.val.i);                      break;
    case T_FLOAT: printf("%g\n",   ev.val.f);                      break;
    case T_BOOL:  printf("%d\n",   ev.val.b);                      break;
    case T_STR:   printf("%s\n",   ev.val.s ? ev.val.s : "");      break;
    default:      printf("<unknown>\n");                            break;
  }
  eval_free(&ev);
}

static void exec_cond_chain(AstNode* n) {
  int matched = 0;
  for (int bi = 0; bi < n->as.cond.block_count && !matched; bi++) {
    matched = exec_cond_block(n->as.cond.blocks[bi]);
  }
  if (!matched && n->as.cond.else_block) {
    exec_stmts(n->as.cond.else_block);
  }
}

static void exec_loop(AstNode* n) {
  char* v = n->as.loop.var;
  /* Declare new variable if needed */
  if (n->as.loop.is_new)
    symtab_declare(v, n->as.loop.new_type, 0, 1, n->line);
  Symbol* s = symtab_lookup(v);
  if (!s) return;

  if (n->as.loop.step == LOOP_STOP) {
    /* thamo as loop_ctrl: run body once */
    exec_stmts(n->as.loop.body);
    g_breaking = 0;  /* consume any break from inside */
    return;
  }
  /* Set initial value */
  EvalVal iv = exec_expr(n->as.loop.init_expr);
  symtab_set_value(v, iv.type, iv.val); eval_free(&iv);

  /* Evaluate end value once */
  EvalVal ev = exec_expr(n->as.loop.end_expr);

  for (;;) {
    /* Check loop condition */
    s = symtab_lookup(v);
    if (!s) break;
    int cont;
    if (n->as.loop.step == LOOP_INC) {
      if (s->type == T_INT)   cont = (s->val.i <= ev.val.i);
      else                    cont = (s->val.f <= ev.val.f);
    } else if (n->as.loop.step == LOOP_DEC) {
      if (s->type == T_INT)   cont = (s->val.i >= ev.val.i);
      else                    cont = (s->val.f >= ev.val.f);
    } else { /* LOOP_CUSTOM */
      char op = n->as.loop.step_op;
      if (op == '+' || op == '*') {
        if (s->type == T_INT)   cont = (s->val.i <= ev.val.i);
        else                    cont = (s->val.f <= ev.val.f);
      } else {
        if (s->type == T_INT)   cont = (s->val.i >= ev.val.i);
        else                    cont = (s->val.f >= ev.val.f);
      }
    }
    if (!cont) break;
    exec_stmts(n->as.loop.body);
    if (g_returning) break;
    if (g_breaking)   { g_breaking   = 0; break; }  /* thamo break stmt */
    if (g_continuing) { g_continuing = 0; }          /* agao continue: fall through to advance */
    /* Advance */
    s = symtab_lookup(v);
    if (!s) break;
    Value nv = s->val;
    if (n->as.loop.step == LOOP_INC) {
      if (s->type == T_INT) nv.i += 1;
      else                  nv.f += 1.0;
    } else if (n->as.loop.step == LOOP_DEC) {
      if (s->type == T_INT) nv.i -= 1;
      else                  nv.f -= 1.0;
    } else { /* LOOP_CUSTOM */
      EvalVal sv = exec_expr(n->as.loop.step_expr);
      char op = n->as.loop.step_op;
      if (s->type == T_INT) {
        long sv_i = (sv.type == T_INT) ? sv.val.i : (long)sv.val.f;
        switch (op) {
          case '+': nv.i += sv_i; break;
          case '-': nv.i -= sv_i; break;
          case '*': nv.i *= sv_i; break;
          case '/': if (sv_i != 0) nv.i /= sv_i; break;
        }
      } else {
        double sv_f = (sv.type == T_FLOAT) ? sv.val.f : (double)sv.val.i;
        switch (op) {
          case '+': nv.f += sv_f; break;
          case '-': nv.f -= sv_f; break;
          case '*': nv.f *= sv_f; break;
          case '/': if (sv_f != 0.0) nv.f /= sv_f; break;
        }
      }
      eval_free(&sv);
    }
    symtab_set_value(v, s->type, nv);
  }
  eval_free(&ev);
}

static void exec_func_def(AstNode* n) {
  /* Function signatures were registered during the semantic prescan pass.
     Nothing to do here — the body is executed at call sites via EXPR_CALL.
     Guard against the rare case where semantic was skipped. */
  if (functab_lookup(n->as.func.name)) return;
  int pc = n->as.func.param_count;
  FuncParamNode* pcopy = NULL;
  if (pc > 0) {
    pcopy = (FuncParamNode*)malloc(pc * sizeof(FuncParamNode));
    for (int i = 0; i < pc; i++) {
      pcopy[i].name = strdup(n->as.func.params[i].name);
      pcopy[i].type = n->as.func.params[i].type;
    }
  }
  functab_register(n->as.func.name, n->as.func.return_type,
                    pcopy, pc, n->as.func.body);
}

/* ================================================================
   Statement dispatcher
   ================================================================ */
static void exec_stmt(AstNode* n) {
  if (!n) return;
  switch (n->kind) {
    case STMT_DECL:
    case STMT_CONST_DECL:
      exec_decl(n);
      break;

    case STMT_DEFAULT_DECL:
    case STMT_CONST_DEFAULT:
      /* Declare at runtime so function-local khaali vars exist in symtab. */
      symtab_declare(n->as.decl.id, n->as.decl.declared_type,
                     n->as.decl.is_const, 0, n->line);
      break;

    case STMT_UPDATE:
      exec_update(n);
      break;

    case STMT_CAST_DECL:
    case STMT_CAST_UPDATE:
      exec_cast(n);
      break;

    case STMT_PRINT:
      exec_print(n);
      break;

    case STMT_COND_CHAIN:
      exec_cond_chain(n);
      break;

    case STMT_LOOP:
      exec_loop(n);
      break;

    case STMT_FUNC_DEF:
      exec_func_def(n);
      break;

    case STMT_RETURN:
      eval_free(&g_return_val);
      g_return_val = n->as.ret.expr ? exec_expr(n->as.ret.expr) : eval_unknown();
      g_returning  = 1;
      break;

    case STMT_BREAK:
      g_breaking = 1;
      break;

    case STMT_CONTINUE:
      g_continuing = 1;
      break;
  }
}

static void exec_stmts(AstNode* list) {
  for (AstNode* n = list; n && !g_returning && !g_breaking && !g_continuing; n = n->next)
    exec_stmt(n);
}

/* ================================================================
   Public entry point
   ================================================================ */
void exec_program(AstNode* root) {
  exec_stmts(root);
}
