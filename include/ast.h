// ast.h — Complete AST node definitions for the EngBang compiler
#ifndef AST_H
#define AST_H

#include "value.h"   /* for Type, Value, EvalVal */

/* ================================================================
   CONDITION OPERATORS  (used in [ {>=}, {==} ] groups )
   ================================================================ */
typedef enum {
  CONDOP_GE,    /* {>=} */
  CONDOP_LE,    /* {<=} */
  CONDOP_EQ,    /* {==} */
  CONDOP_NEQ,   /* {!=} */
  CONDOP_GT,    /* {>}  */
  CONDOP_LT,    /* {<}  */
  CONDOP_SKIP   /* {}   — always matches */
} CondOp;

/* ================================================================
   EXPRESSION NODES
   ================================================================ */
typedef enum {
  EXPR_INT_LIT,    /* integer literal: 42        */
  EXPR_FLOAT_LIT,  /* float literal  : 3.14      */
  EXPR_BOOL_LIT,   /* bool literal   : 0 / 1     */
  EXPR_STR_LIT,    /* string literal : "text"    */
  EXPR_ID,         /* variable name  : someVar   */
  EXPR_BINOP,      /* a OP b                     */
  EXPR_CALL        /* funcName(args)             */
} ExprKind;

typedef enum {
  BINOP_ADD,   /* + */
  BINOP_SUB,   /* - */
  BINOP_MUL,   /* * */
  BINOP_DIV    /* / */
} BinOp;

typedef struct AstExpr AstExpr;
struct AstExpr {
  ExprKind kind;
  int      line;
  union {
    long   ival;       /* EXPR_INT_LIT            */
    double fval;       /* EXPR_FLOAT_LIT          */
    int    bval;       /* EXPR_BOOL_LIT           */
    char*  sval;       /* EXPR_STR_LIT / EXPR_ID  (owned, heap-allocated) */
    struct {
      BinOp    op;
      AstExpr* left;
      AstExpr* right;
    } binop;           /* EXPR_BINOP              */
    struct {
      char*     name;    /* function name (owned)  */
      AstExpr** args;    /* owned array            */
      int       argc;
    } call;            /* EXPR_CALL               */
  } as;
};

/* ================================================================
   CONDITIONAL GROUP — one bracketed operator list  [ {>=}, {==} ]
   MAX_COND_OPS caps binding count per group (generous limit).
   ================================================================ */
#define MAX_COND_OPS 16
typedef struct {
  CondOp ops[MAX_COND_OPS];
  int    count;
} AstCondGroup;

/* One binding:  ID -> expr  (left side of a cond header) */
typedef struct {
  char*    id;    /* variable name (owned) */
  AstExpr* expr;  /* expected value (owned) */
} AstBinding;

/* ================================================================
   STATEMENT NODES
   ================================================================ */
typedef enum {
  STMT_DECL,          /* value rakho ID -> type         */
  STMT_DEFAULT_DECL,  /* khaali rakho ID -> type        */
  STMT_CONST_DECL,    /* value pakka rakho ID -> type   */
  STMT_CONST_DEFAULT, /* khaali pakka rakho ID -> type  */
  STMT_UPDATE,        /* value bodlao ID                */
  STMT_CAST_DECL,     /* value banaw T rakho ID -> T    */
  STMT_CAST_UPDATE,   /* value banaw T bodlao ID        */
  STMT_PRINT,         /* bolo value                     */
  STMT_COND_CHAIN,    /* full if / else-if / else chain  */
  STMT_LOOP,          /* [init, end] { body; var barbe } */
  STMT_FUNC_DEF,      /* name(params) -> type { body }  */
  STMT_RETURN         /* ferao expr                     */
} StmtKind;

/* Payload structs */
typedef struct {
  char*    id;
  Type     declared_type;
  AstExpr* value;     /* NULL for khaali (default) declarations */
  int      is_const;
} DeclData;

typedef struct {
  char*    id;
  AstExpr* value;
} UpdateData;

typedef struct {
  char*    id;
  Type     cast_type;       /* type named in "banaw <type>"           */
  Type     declared_type;   /* type in "-> <type>" (cast_decl only)   */
  AstExpr* value;
  int      is_update;       /* 0 = cast_decl,  1 = cast_update        */
} CastData;

/* LoopStep — how the loop variable advances per iteration */
typedef enum {
  LOOP_INC,    /* barbe         — var++ each iter, continue while var <= end  */
  LOOP_DEC,    /* komabe        — var-- each iter, continue while var >= end  */
  LOOP_STOP,   /* thamo         — execute body once and exit                   */
  LOOP_CUSTOM  /* poriborton_by — custom step: op (+ - * /) + amount          */
} LoopStep;

/* One function parameter */
typedef struct {
  char* name;   /* owned */
  Type  type;
} FuncParamNode;

typedef struct AstNode AstNode;

/* One conditional block: bindings { groups { stmts } } */
typedef struct {
  AstBinding*   binds;        /* heap-allocated array of AstBinding values */
  int           bind_count;
  AstCondGroup* groups;       /* heap-allocated array of AstCondGroup values */
  int           group_count;
  AstNode*      block;        /* statement list to execute when a group matches */
} AstCondBlock;

/* Payload for STMT_LOOP */
typedef struct {
  char*    var;        /* init variable name (owned)             */
  char*    end_var;    /* end variable name (owned, must == var) */
  char*    ctrl_var;   /* ctrl variable name (owned, NULL=thamo) */
  int      is_new;     /* 1 = declare var in loop header         */
  Type     new_type;   /* declared type if is_new == 1           */
  AstExpr* init_expr;  /* starting value expression (owned)      */
  AstExpr* end_expr;   /* terminal value expression (owned)      */
  LoopStep step;       /* LOOP_INC / LOOP_DEC / LOOP_STOP / LOOP_CUSTOM   */
  char     step_op;    /* '+' '-' '*' '/'  — used only for LOOP_CUSTOM    */
  AstExpr* step_expr;  /* step amount expression (owned, LOOP_CUSTOM only) */
  AstNode* body;       /* loop body statement list (owned)                 */
} LoopData;

/* Payload for STMT_FUNC_DEF */
typedef struct {
  char*          name;         /* function name (owned)          */
  Type           return_type;
  FuncParamNode* params;       /* owned array, may be NULL       */
  int            param_count;
  AstNode*       body;         /* function body (owned)          */
} FuncDefData;

/* Payload for STMT_RETURN */
typedef struct {
  AstExpr* expr;   /* returned expression (owned); NULL = void */
} ReturnData;

/* ===== AstNode ===== */
struct AstNode {
  StmtKind  kind;
  int       line;
  AstNode*  next;   /* intrusive linked list — builds the stmt_list */
  union {
    DeclData    decl;
    UpdateData  upd;
    CastData    cast;
    AstExpr*    print_expr;    /* STMT_PRINT */
    struct {
      AstCondBlock** blocks;       /* if block + all elseif blocks */
      int            block_count;
      AstNode*       else_block;   /* NULL if no [] else clause */
    } cond;
    LoopData    loop;
    FuncDefData func;
    ReturnData  ret;
  } as;
};

/* ================================================================
   EXPRESSION CONSTRUCTORS
   All char* arguments transfer ownership to the new node.
   ================================================================ */
AstExpr* ast_expr_int  (long v,   int line);
AstExpr* ast_expr_float(double v, int line);
AstExpr* ast_expr_bool (int v,    int line);
/* ast_expr_str: takes ownership of the raw quoted string from the lexer
   and strips the surrounding quotes internally. */
AstExpr* ast_expr_str  (char* quoted_s, int line);
/* ast_expr_id: takes ownership of the lexer-allocated identifier string. */
AstExpr* ast_expr_id   (char* id,       int line);
AstExpr* ast_expr_binop(BinOp op, AstExpr* left, AstExpr* right, int line);

/* ================================================================
   STATEMENT CONSTRUCTORS
   char* id arguments transfer ownership to the new node.
   ================================================================ */
AstNode* ast_stmt_decl        (char* id, Type t, AstExpr* val, int is_const, int line);
AstNode* ast_stmt_default_decl(char* id, Type t, int is_const,  int line);
AstNode* ast_stmt_update      (char* id, AstExpr* val, int line);
AstNode* ast_stmt_cast_decl   (char* id, Type cast_t, Type decl_t, AstExpr* val, int line);
AstNode* ast_stmt_cast_update (char* id, Type cast_t,              AstExpr* val, int line);
AstNode* ast_stmt_print       (AstExpr* val, int line);
AstNode* ast_stmt_cond        (AstCondBlock** blocks, int count, AstNode* else_block, int line);
AstNode* ast_stmt_loop        (char* var, int is_new, Type new_type,
                               AstExpr* init, char* end_var, AstExpr* end,
                               char* ctrl_var, LoopStep step,
                               char step_op, AstExpr* step_expr,
                               AstNode* body, int line);
AstNode* ast_stmt_func_def    (char* name, Type ret_type,
                               FuncParamNode* params, int count,
                               AstNode* body, int line);
AstNode* ast_stmt_return      (AstExpr* expr, int line);
AstExpr* ast_expr_call        (char* name, AstExpr** args, int argc, int line);

/* ================================================================
   CONDITIONAL BLOCK CONSTRUCTOR
   Takes ownership of both arrays (binds, groups).
   ================================================================ */
AstCondBlock* ast_cond_block_new(AstBinding*   binds,  int bind_count,
                                  AstCondGroup* groups, int group_count,
                                  AstNode*      block);

/* ================================================================
   LIST BUILDING
   Appends 'more' (itself potentially a linked list via ->next)
   to the tail of 'list'.  Returns the head of the combined list.
   ================================================================ */
AstNode* ast_list_concat(AstNode* list, AstNode* more);

/* ================================================================
   CLEANUP
   ================================================================ */
void ast_expr_free      (AstExpr*    e);
void ast_cond_block_free(AstCondBlock* cb);
void ast_list_free      (AstNode*    list);   /* frees the whole linked list */

#endif /* AST_H */
