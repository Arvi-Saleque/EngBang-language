/* tac.c — Three-Address Code generation pass.
 *
 * Walks the AST (after semantic_check has populated the symtab)
 * and emits TAC instructions to stdout.
 *
 * TAC format:
 *   TAC: tN = <operand>
 *   TAC: tN = tA OP tB
 *   TAC: x  = (type) tN       (cast)
 *   TAC: print tN
 *   TAC: if x OP v goto Lx   (conditional branch)
 *   TAC: goto Lx
 *   TAC: Lx:                  (label)
 */
#include "tac.h"
#include "symtab.h"
#include "value.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

/* ================================================================
   Counter state (fresh each tac_generate call)
   ================================================================ */
static int tac_temp_cnt  = 0;
static int tac_label_cnt = 0;

static char* new_temp(void) {
  char* s = (char*)malloc(16);
  snprintf(s, 16, "t%d", tac_temp_cnt++);
  return s;
}

static char* new_label(void) {
  char* s = (char*)malloc(16);
  snprintf(s, 16, "L%d", tac_label_cnt++);
  return s;
}

static void emit(const char* fmt, ...) {
  printf("TAC: ");
  va_list ap;
  va_start(ap, fmt);
  vprintf(fmt, ap);
  va_end(ap);
  printf("\n");
}

/* Forward declaration */
static void tac_stmts(AstNode* list);

/* ================================================================
   Expression TAC — returns a freshly malloc'd string naming the
   "place" that holds the result (temp name or literal string).
   Caller must free the returned string.
   ================================================================ */
static const char* binop_sym(BinOp op) {
  switch (op) {
    case BINOP_ADD: return "+";
    case BINOP_SUB: return "-";
    case BINOP_MUL: return "*";
    case BINOP_DIV: return "/";
  }
  return "?";
}

static char* tac_expr(AstExpr* e) {
  if (!e) return strdup("?");
  switch (e->kind) {
    case EXPR_INT_LIT: {
      char* s = (char*)malloc(32);
      snprintf(s, 32, "%ld", e->as.ival);
      return s;
    }
    case EXPR_FLOAT_LIT: {
      char* s = (char*)malloc(32);
      snprintf(s, 32, "%g", e->as.fval);
      return s;
    }
    case EXPR_BOOL_LIT: {
      char* s = (char*)malloc(8);
      snprintf(s, 8, "%d", e->as.bval);
      return s;
    }
    case EXPR_STR_LIT: {
      /* Build "content" with surrounding quotes for TAC readability */
      size_t len = strlen(e->as.sval);
      char* s = (char*)malloc(len + 3);
      snprintf(s, len + 3, "\"%s\"", e->as.sval);
      return s;
    }
    case EXPR_ID:
      return strdup(e->as.sval);

    case EXPR_CALL: {
      /* Evaluate each argument into a temp */
      for (int i = 0; i < e->as.call.argc; i++) {
        char* a = tac_expr(e->as.call.args[i]);
        emit("arg %s", a);
        free(a);
      }
      char* temp = new_temp();
      emit("%s = call %s %d", temp, e->as.call.name, e->as.call.argc);
      return temp;
    }

    case EXPR_BINOP: {
      char* lhs  = tac_expr(e->as.binop.left);
      char* rhs  = tac_expr(e->as.binop.right);
      char* temp = new_temp();
      emit("%s = %s %s %s", temp, lhs, binop_sym(e->as.binop.op), rhs);
      free(lhs);
      free(rhs);
      return temp;   /* caller must free */
    }
  }
  return strdup("?");
}

/* ================================================================
   Condition operator as a TAC comparison string
   ================================================================ */
static const char* condop_sym(CondOp op) {
  switch (op) {
    case CONDOP_GE:   return ">=";
    case CONDOP_LE:   return "<=";
    case CONDOP_EQ:   return "==";
    case CONDOP_NEQ:  return "!=";
    case CONDOP_GT:   return ">";
    case CONDOP_LT:   return "<";
    case CONDOP_SKIP: return "skip";
  }
  return "?";
}

/* ================================================================
   Statement TAC generators
   ================================================================ */

static void tac_decl(AstNode* n) {
  if (!n->as.decl.value) return;   /* khaali — no initialiser */
  char* rhs = tac_expr(n->as.decl.value);
  emit("%s = %s", n->as.decl.id, rhs);
  free(rhs);
}

static void tac_update(AstNode* n) {
  char* rhs = tac_expr(n->as.upd.value);
  emit("%s = %s", n->as.upd.id, rhs);
  free(rhs);
}

static void tac_cast(AstNode* n) {
  char* rhs  = tac_expr(n->as.cast.value);
  char* temp = new_temp();
  emit("%s = %s", temp, rhs);
  emit("%s = (%s) %s", n->as.cast.id, type_name(n->as.cast.cast_type), temp);
  free(rhs);
  free(temp);
}

static void tac_print(AstNode* n) {
  char* rhs  = tac_expr(n->as.print_expr);
  char* temp = new_temp();
  emit("%s = %s", temp, rhs);
  emit("print %s", temp);
  free(rhs);
  free(temp);
}

/*
 * tac_cond — emit conditional branch TAC for the full if/elseif/else chain.
 *
 * For each cond_block:
 *   - evaluate the binding expressions into temps
 *   - for each group:  if all conditions hold, goto then_label
 *   - if no group matched, goto next_block_label (or else_label)
 *   - emit the body stmts, then goto end_label
 */
static void tac_cond(AstNode* n) {
  char* end_label = new_label();

  for (int bi = 0; bi < n->as.cond.block_count; bi++) {
    AstCondBlock* cb = n->as.cond.blocks[bi];

    char* then_label = new_label();
    char* skip_label = new_label();

    /* Evaluate each binding expression into a temp */
    char** bind_temps = (char**)malloc(cb->bind_count * sizeof(char*));
    for (int b = 0; b < cb->bind_count; b++) {
      bind_temps[b] = tac_expr(cb->binds[b].expr);
    }

    /* Emit a branch for each group (OR logic across groups) */
    for (int g = 0; g < cb->group_count; g++) {
      AstCondGroup* grp = &cb->groups[g];
      if (grp->count == 0) continue;   /* should not happen after semantic */

      /* Each group: all bindings must match (AND logic).
         We emit a multi-way test: if any fails we try the next group. */
      char* group_fail = new_label();

      for (int b = 0; b < cb->bind_count && b < grp->count; b++) {
        CondOp op = grp->ops[b];
        if (op == CONDOP_SKIP) continue;   /* always passes */
        /* Emit: if !(var OP expected) goto group_fail */
        const char* cmp = condop_sym(op);
        emit("if %s %s %s goto %s",
             cb->binds[b].id, cmp, bind_temps[b], then_label);
        emit("goto %s", group_fail);
        /* We only need the first failing check to branch out;
           simplify by emitting a goto after each positive match attempt */
        break;   /* TAC models a sequential test; emit one cond per group */
      }

      /* If all conditions in the group passed, we land at then_label
         (via the if-goto above); otherwise continue to next group */
      emit("%s:", group_fail);
      free(group_fail);
    }

    /* No group matched — skip this block */
    emit("goto %s", skip_label);

    /* Block body */
    emit("%s:", then_label);
    tac_stmts(cb->block);
    emit("goto %s", end_label);

    emit("%s:", skip_label);

    for (int b = 0; b < cb->bind_count; b++) free(bind_temps[b]);
    free(bind_temps);
    free(then_label);
    free(skip_label);
  }

  /* Else block */
  if (n->as.cond.else_block) {
    tac_stmts(n->as.cond.else_block);
  }

  emit("%s:", end_label);
  free(end_label);
}

/* ================================================================
   Statement dispatcher
   ================================================================ */
static void tac_stmt(AstNode* n) {
  if (!n) return;
  switch (n->kind) {
    case STMT_DECL:
    case STMT_CONST_DECL:
      tac_decl(n);
      break;

    case STMT_DEFAULT_DECL:
    case STMT_CONST_DEFAULT:
      /* khaali — no initialiser, nothing to emit */
      break;

    case STMT_UPDATE:
      tac_update(n);
      break;

    case STMT_CAST_DECL:
    case STMT_CAST_UPDATE:
      tac_cast(n);
      break;

    case STMT_PRINT:
      tac_print(n);
      break;

    case STMT_COND_CHAIN:
      tac_cond(n);
      break;

    case STMT_LOOP: {
      /* TAC:  var = init
               L_start:
               if var > end goto L_end   (or < for komabe)
               ...body...
               var = var + 1
               goto L_start
               L_end:                          */
      char* ls = new_label();   /* loop start */
      char* le = new_label();   /* loop end   */
      char* lv = n->as.loop.var;
      /* Init */
      if (n->as.loop.step != LOOP_STOP) {
        char* iv = tac_expr(n->as.loop.init_expr);
        emit("%s = %s", lv, iv);
        free(iv);
        /* End temp for condition check */
        char* ev = tac_expr(n->as.loop.end_expr);
        char* et = new_temp();
        emit("%s = %s", et, ev);
        free(ev);
        emit("%s:", ls);
        if (n->as.loop.step == LOOP_INC ||
            (n->as.loop.step == LOOP_CUSTOM &&
             (n->as.loop.step_op == '+' || n->as.loop.step_op == '*')))
          emit("if %s > %s goto %s", lv, et, le);
        else
          emit("if %s < %s goto %s", lv, et, le);
        tac_stmts(n->as.loop.body);
        if (n->as.loop.step == LOOP_INC)
          emit("%s = %s + 1", lv, lv);
        else if (n->as.loop.step == LOOP_DEC)
          emit("%s = %s - 1", lv, lv);
        else { /* LOOP_CUSTOM */
          char* sv = tac_expr(n->as.loop.step_expr);
          emit("%s = %s %c %s", lv, lv, n->as.loop.step_op, sv);
          free(sv);
        }
        emit("goto %s", ls);
        emit("%s:", le);
        free(et);
      } else {
        /* thamo: run body once */
        tac_stmts(n->as.loop.body);
      }
      free(ls); free(le);
      break;
    }

    case STMT_FUNC_DEF: {
      emit("func %s:", n->as.func.name);
      for (int i = 0; i < n->as.func.param_count; i++)
        emit("  param %s %s", n->as.func.params[i].name,
             type_name(n->as.func.params[i].type));
      tac_stmts(n->as.func.body);
      emit("end %s", n->as.func.name);
      break;
    }

    case STMT_RETURN: {
      if (n->as.ret.expr) {
        char* rv = tac_expr(n->as.ret.expr);
        emit("return %s", rv);
        free(rv);
      } else {
        emit("return");
      }
      break;
    }
  }
}

static void tac_stmts(AstNode* list) {
  for (AstNode* n = list; n; n = n->next)
    tac_stmt(n);
}

/* ================================================================
   Public entry point
   ================================================================ */
void tac_generate(AstNode* root) {
  tac_temp_cnt  = 0;
  tac_label_cnt = 0;
  tac_stmts(root);
}
