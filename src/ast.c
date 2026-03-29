/* ast.c — AST node constructors and recursive cleanup */
#include "ast.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* ================================================================
   INTERNAL ALLOCATORS
   ================================================================ */
static AstExpr* alloc_expr(ExprKind kind, int line) {
  AstExpr* e = (AstExpr*)calloc(1, sizeof(AstExpr));
  if (!e) { fprintf(stderr, "ast: out of memory\n"); exit(1); }
  e->kind = kind;
  e->line = line;
  return e;
}

static AstNode* alloc_node(StmtKind kind, int line) {
  AstNode* n = (AstNode*)calloc(1, sizeof(AstNode));
  if (!n) { fprintf(stderr, "ast: out of memory\n"); exit(1); }
  n->kind = kind;
  n->line = line;
  return n;
}

/* ================================================================
   EXPRESSION CONSTRUCTORS
   ================================================================ */
AstExpr* ast_expr_int(long v, int line) {
  AstExpr* e = alloc_expr(EXPR_INT_LIT, line);
  e->as.ival = v;
  return e;
}

AstExpr* ast_expr_float(double v, int line) {
  AstExpr* e = alloc_expr(EXPR_FLOAT_LIT, line);
  e->as.fval = v;
  return e;
}

AstExpr* ast_expr_bool(int v, int line) {
  AstExpr* e = alloc_expr(EXPR_BOOL_LIT, line);
  e->as.bval = v;
  return e;
}

/*
 * ast_expr_str: Takes ownership of 'quoted_s' (the raw lexer string including
 * surrounding double-quotes).  Strips the quotes, stores the bare content,
 * and frees the original allocation.
 */
AstExpr* ast_expr_str(char* quoted_s, int line) {
  AstExpr* e = alloc_expr(EXPR_STR_LIT, line);
  if (quoted_s && quoted_s[0] == '"') {
    size_t len = strlen(quoted_s);
    /* quoted_s = "content"  — strip first and last chars */
    char* bare = (char*)malloc(len - 1);  /* len-2 content + '\0' */
    if (!bare) { fprintf(stderr, "ast: out of memory\n"); exit(1); }
    memcpy(bare, quoted_s + 1, len - 2);
    bare[len - 2] = '\0';
    e->as.sval = bare;
    free(quoted_s);
  } else {
    /* Unquoted — should not happen for normal STRING tokens, but handle safely */
    e->as.sval = quoted_s;
  }
  return e;
}

/* ast_expr_id: Takes ownership of the lexer-allocated identifier string. */
AstExpr* ast_expr_id(char* id, int line) {
  AstExpr* e = alloc_expr(EXPR_ID, line);
  e->as.sval = id;   /* take ownership directly; no copy needed */
  return e;
}

AstExpr* ast_expr_binop(BinOp op, AstExpr* left, AstExpr* right, int line) {
  AstExpr* e = alloc_expr(EXPR_BINOP, line);
  e->as.binop.op    = op;
  e->as.binop.left  = left;
  e->as.binop.right = right;
  return e;
}

AstExpr* ast_expr_call(char* name, AstExpr** args, int argc, int line) {
  AstExpr* e = alloc_expr(EXPR_CALL, line);
  e->as.call.name = name;
  e->as.call.args = args;
  e->as.call.argc = argc;
  return e;
}

/* ================================================================
   STATEMENT CONSTRUCTORS
   All char* id arguments transfer ownership to the node.
   ================================================================ */
AstNode* ast_stmt_decl(char* id, Type t, AstExpr* val, int is_const, int line) {
  StmtKind kind = is_const ? STMT_CONST_DECL : STMT_DECL;
  AstNode* n = alloc_node(kind, line);
  n->as.decl.id             = id;
  n->as.decl.declared_type  = t;
  n->as.decl.value          = val;
  n->as.decl.is_const       = is_const;
  return n;
}

AstNode* ast_stmt_default_decl(char* id, Type t, int is_const, int line) {
  StmtKind kind = is_const ? STMT_CONST_DEFAULT : STMT_DEFAULT_DECL;
  AstNode* n = alloc_node(kind, line);
  n->as.decl.id             = id;
  n->as.decl.declared_type  = t;
  n->as.decl.value          = NULL;
  n->as.decl.is_const       = is_const;
  return n;
}

AstNode* ast_stmt_update(char* id, AstExpr* val, int line) {
  AstNode* n = alloc_node(STMT_UPDATE, line);
  n->as.upd.id    = id;
  n->as.upd.value = val;
  return n;
}

AstNode* ast_stmt_cast_decl(char* id, Type cast_t, Type decl_t, AstExpr* val, int line) {
  AstNode* n = alloc_node(STMT_CAST_DECL, line);
  n->as.cast.id             = id;
  n->as.cast.cast_type      = cast_t;
  n->as.cast.declared_type  = decl_t;
  n->as.cast.value          = val;
  n->as.cast.is_update      = 0;
  return n;
}

AstNode* ast_stmt_cast_update(char* id, Type cast_t, AstExpr* val, int line) {
  AstNode* n = alloc_node(STMT_CAST_UPDATE, line);
  n->as.cast.id             = id;
  n->as.cast.cast_type      = cast_t;
  n->as.cast.declared_type  = T_UNKNOWN;  /* filled in by semantic pass */
  n->as.cast.value          = val;
  n->as.cast.is_update      = 1;
  return n;
}

AstNode* ast_stmt_print(AstExpr* val, int line) {
  AstNode* n = alloc_node(STMT_PRINT, line);
  n->as.print_expr = val;
  return n;
}

AstNode* ast_stmt_cond(AstCondBlock** blocks, int count,
                        AstNode* else_block, int line) {
  AstNode* n = alloc_node(STMT_COND_CHAIN, line);
  n->as.cond.blocks      = blocks;
  n->as.cond.block_count = count;
  n->as.cond.else_block  = else_block;
  return n;
}

AstNode* ast_stmt_loop(char* var, int is_new, Type new_type,
                        AstExpr* init, char* end_var, AstExpr* end,
                        char* ctrl_var, LoopStep step,
                        char step_op, AstExpr* step_expr,
                        AstNode* body, int line) {
  AstNode* n = alloc_node(STMT_LOOP, line);
  n->as.loop.var       = var;
  n->as.loop.end_var   = end_var;
  n->as.loop.ctrl_var  = ctrl_var;
  n->as.loop.is_new    = is_new;
  n->as.loop.new_type  = new_type;
  n->as.loop.init_expr = init;
  n->as.loop.end_expr  = end;
  n->as.loop.step      = step;
  n->as.loop.step_op   = step_op;
  n->as.loop.step_expr = step_expr;
  n->as.loop.body      = body;
  return n;
}

AstNode* ast_stmt_func_def(char* name, Type ret_type,
                            FuncParamNode* params, int count,
                            AstNode* body, int line) {
  AstNode* n = alloc_node(STMT_FUNC_DEF, line);
  n->as.func.name        = name;
  n->as.func.return_type = ret_type;
  n->as.func.params      = params;
  n->as.func.param_count = count;
  n->as.func.body        = body;
  return n;
}

AstNode* ast_stmt_return(AstExpr* expr, int line) {
  AstNode* n = alloc_node(STMT_RETURN, line);
  n->as.ret.expr = expr;
  return n;
}

AstNode* ast_stmt_break(int line) {
  return alloc_node(STMT_BREAK, line);
}

AstNode* ast_stmt_continue(int line) {
  return alloc_node(STMT_CONTINUE, line);
}

/* ================================================================
   CONDITIONAL BLOCK CONSTRUCTOR
   Takes ownership of both arrays.
   ================================================================ */
AstCondBlock* ast_cond_block_new(AstBinding*   binds,  int bind_count,
                                  AstCondGroup* groups, int group_count,
                                  AstNode*      block) {
  AstCondBlock* cb = (AstCondBlock*)calloc(1, sizeof(AstCondBlock));
  if (!cb) { fprintf(stderr, "ast: out of memory\n"); exit(1); }
  cb->binds        = binds;
  cb->bind_count   = bind_count;
  cb->groups       = groups;
  cb->group_count  = group_count;
  cb->block        = block;
  return cb;
}

/* ================================================================
   LIST BUILDING
   ================================================================ */
AstNode* ast_list_concat(AstNode* list, AstNode* more) {
  if (!list) return more;
  if (!more) return list;
  AstNode* tail = list;
  while (tail->next) tail = tail->next;
  tail->next = more;
  return list;
}

/* ================================================================
   CLEANUP
   ================================================================ */
void ast_expr_free(AstExpr* e) {
  if (!e) return;
  switch (e->kind) {
    case EXPR_STR_LIT:
    case EXPR_ID:
      free(e->as.sval);
      break;
    case EXPR_BINOP:
      ast_expr_free(e->as.binop.left);
      ast_expr_free(e->as.binop.right);
      break;
    case EXPR_CALL:
      free(e->as.call.name);
      for (int i = 0; i < e->as.call.argc; i++)
        ast_expr_free(e->as.call.args[i]);
      free(e->as.call.args);
      break;
    default:
      break;
  }
  free(e);
}

void ast_cond_block_free(AstCondBlock* cb) {
  if (!cb) return;
  for (int i = 0; i < cb->bind_count; i++) {
    free(cb->binds[i].id);
    ast_expr_free(cb->binds[i].expr);
  }
  free(cb->binds);
  free(cb->groups);
  ast_list_free(cb->block);
  free(cb);
}

void ast_list_free(AstNode* list) {
  while (list) {
    AstNode* next = list->next;
    switch (list->kind) {
      case STMT_DECL:
      case STMT_DEFAULT_DECL:
      case STMT_CONST_DECL:
      case STMT_CONST_DEFAULT:
        free(list->as.decl.id);
        ast_expr_free(list->as.decl.value);
        break;
      case STMT_UPDATE:
        free(list->as.upd.id);
        ast_expr_free(list->as.upd.value);
        break;
      case STMT_CAST_DECL:
      case STMT_CAST_UPDATE:
        free(list->as.cast.id);
        ast_expr_free(list->as.cast.value);
        break;
      case STMT_PRINT:
        ast_expr_free(list->as.print_expr);
        break;
      case STMT_COND_CHAIN:
        for (int i = 0; i < list->as.cond.block_count; i++)
          ast_cond_block_free(list->as.cond.blocks[i]);
        free(list->as.cond.blocks);
        ast_list_free(list->as.cond.else_block);
        break;
      case STMT_LOOP:
        free(list->as.loop.var);
        free(list->as.loop.end_var);
        free(list->as.loop.ctrl_var);
        ast_expr_free(list->as.loop.init_expr);
        ast_expr_free(list->as.loop.end_expr);
        ast_expr_free(list->as.loop.step_expr);
        ast_list_free(list->as.loop.body);
        break;
      case STMT_FUNC_DEF:
        free(list->as.func.name);
        for (int i = 0; i < list->as.func.param_count; i++)
          free(list->as.func.params[i].name);
        free(list->as.func.params);
        ast_list_free(list->as.func.body);
        break;
      case STMT_RETURN:
        ast_expr_free(list->as.ret.expr);
        break;
      case STMT_BREAK:
        break;  /* no owned data */
      case STMT_CONTINUE:
        break;  /* no owned data */
    }
    free(list);
    list = next;
  }
}
