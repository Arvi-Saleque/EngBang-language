%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"     /* includes value.h */

int  yylex(void);
void yyerror(const char* s);

extern int yylineno;

/* The completed AST root - read by main() after yyparse() returns. */
AstNode* g_parse_result = NULL;
%}

/* ----------------------------------------------------------------
   Types injected into the generated parser.tab.h so that the
   lexer (which #includes it) also sees BindList / GrpList / BlockList.
   ---------------------------------------------------------------- */
%code requires {
  #include "ast.h"

  /* Parser-internal list helpers (not in ast.h to keep that header clean). */
  typedef struct { AstBinding*    arr; int count; } BindList;
  typedef struct { AstCondGroup*  arr; int count; } GrpList;
  typedef struct { AstCondBlock** arr; int count; } BlockList;

  /* Loop parsing helpers */
  typedef struct { char* var; int is_new; int new_type; AstExpr* init; } LoopActual;
  typedef struct { char* var; AstExpr* end; } LoopEndAct;
  typedef struct { char step_op; AstExpr* step_expr; } LoopStepData;
  typedef struct { char* var; int step; char step_op; AstExpr* step_expr; } LoopCtrlData;

  /* Function parsing helpers */
  typedef struct { FuncParamNode* arr; int count; } ParamList;
  typedef struct { AstExpr** arr; int count; } ArgList;
}

/* Improved error messages (Bison 2.x syntax) */
%error-verbose

/* ----------------------------------------------------------------
   Semantic value union
   ---------------------------------------------------------------- */
%union {
  long          ival;
  double        fval;
  char*         sval;
  int           tval;     /* Type enum value          */
  int           condop;   /* CondOp value             */
  AstExpr*      expr;     /* expression node          */
  AstNode*      node;     /* statement node / list    */
  AstCondGroup  cgroup;   /* single group (value type) */
  AstCondBlock* cblock;   /* single cond block        */
  AstBinding    bindi;    /* single binding (value)   */
  BindList      blist;    /* binding list             */
  GrpList       glist;    /* group list               */
  BlockList     cblist;   /* cond-block list          */
  LoopActual    lact;     /* loop init data           */
  LoopEndAct    lend;     /* loop end data            */
  LoopStepData  lstep;    /* loop step op+amount      */
  LoopCtrlData  lctrl;    /* loop control step        */
  FuncParamNode fparam;   /* one function parameter   */
  ParamList     plist;    /* parameter list           */
  ArgList       alist;    /* argument list            */
}

/* ----------------------------------------------------------------
   %type declarations
   ---------------------------------------------------------------- */
%type <tval>   type
%type <expr>   value expr func_call
%type <node>   stmt_list stmt
%type <node>   var_decl default_decl const_decl
%type <node>   update_stmt cast_decl cast_update print_stmt
%type <node>   cond_chain else_block_opt else_block block
%type <node>   loop_stmt return_stmt func_decl
%type <condop> cond_item
%type <cgroup> cond_items_opt cond_items group
%type <glist>  group_list
%type <bindi>  binding
%type <blist>  bindings
%type <cblock> cond_block
%type <cblist> else_if_list
%type <lact>   loop_init
%type <lend>   loop_end
%type <lstep>  loop_step
%type <lctrl>  loop_ctrl
%type <fparam> param
%type <plist>  param_list
%type <alist>  arg_list

/* ----------------------------------------------------------------
   Keywords
   ---------------------------------------------------------------- */
%token KW_RAKHO KW_BODLAO KW_PAKKA KW_KHAALI KW_AR KW_BOLO KW_BANAW
%token KW_BARBE KW_KOMABE KW_THAMO KW_PORIBORTON_BY KW_AGAO
%token KW_FERAO

/* Types */
%token TYPE_INT TYPE_FLOAT TYPE_STR TYPE_BOOL

/* Punctuation */
%token ARROW PIPE
%token LBRACE RBRACE
%token LBRACKET RBRACKET
%token COMMA
%token EQUALS LPAREN RPAREN

/* Operators */
%token PLUS MINUS STAR SLASH

/* Condition tokens */
%token COND_GE COND_LE COND_EQ COND_NEQ COND_GT COND_LT
%token COND_SKIP
%token <sval> COND_UNKNOWN

/* Literals and identifiers */
%token <ival> INT
%token <fval> FLOAT
%token <sval> STRING
%token <sval> ID
%token <ival> BOOL

/* Operator precedence (same as original) */
%left  PLUS MINUS
%left  STAR SLASH

%start program

%%

/* ================================================================
   TOP LEVEL
   ================================================================ */

program
  : stmt_list
    { g_parse_result = $1; }
  ;

stmt_list
  : /* empty */
    { $$ = NULL; }
  | stmt_list stmt
    { $$ = ast_list_concat($1, $2); }
  ;

stmt
  : var_decl     PIPE  { $$ = $1; }
  | default_decl PIPE  { $$ = $1; }
  | const_decl   PIPE  { $$ = $1; }
  | update_stmt  PIPE  { $$ = $1; }
  | cast_decl    PIPE  { $$ = $1; }
  | cast_update  PIPE  { $$ = $1; }
  | print_stmt   PIPE  { $$ = $1; }
  | cond_chain   PIPE  { $$ = $1; }
  | loop_stmt          { $$ = $1; }
  | func_decl          { $$ = $1; }
  | return_stmt  PIPE  { $$ = $1; }
  | KW_THAMO     PIPE  { $$ = ast_stmt_break(yylineno); }
  | KW_AGAO      PIPE  { $$ = ast_stmt_continue(yylineno); }
  ;

/* ================================================================
   TYPES
   ================================================================ */

type
  : TYPE_INT   { $$ = T_INT; }
  | TYPE_FLOAT { $$ = T_FLOAT; }
  | TYPE_STR   { $$ = T_STR; }
  | TYPE_BOOL  { $$ = T_BOOL; }
  ;

/* ================================================================
   EXPRESSIONS
   value is just an alias; keeping it matches the original grammar.
   ================================================================ */

value
  : expr  { $$ = $1; }
  ;

expr
  : INT      { $$ = ast_expr_int($1, yylineno); }
  | FLOAT    { $$ = ast_expr_float($1, yylineno); }
  | BOOL     { $$ = ast_expr_bool((int)$1, yylineno); }
  | STRING   { $$ = ast_expr_str($1, yylineno); /* takes ownership, strips quotes */ }
  | ID       { $$ = ast_expr_id($1, yylineno);  /* takes ownership */ }
  | expr PLUS  expr { $$ = ast_expr_binop(BINOP_ADD, $1, $3, yylineno); }
  | expr MINUS expr { $$ = ast_expr_binop(BINOP_SUB, $1, $3, yylineno); }
  | expr STAR  expr { $$ = ast_expr_binop(BINOP_MUL, $1, $3, yylineno); }
  | expr SLASH expr { $$ = ast_expr_binop(BINOP_DIV, $1, $3, yylineno); }
  | LPAREN expr RPAREN { $$ = $2; }
  | func_call          { $$ = $1; }
  ;

/* ================================================================
   DECLARATIONS
   ================================================================ */

/*
 * var_decl - normal (mutable) variable declaration.
 * Syntax:  value rakho ID -> type
 * Chained: var_decl ar value rakho ID -> type
 * The ar-chain returns a linked list via ast_list_concat.
 */
var_decl
  : value KW_RAKHO ID ARROW type
    {
      $$ = ast_stmt_decl($3, (Type)$5, $1, 0, yylineno);
    }
  | var_decl KW_AR value KW_RAKHO ID ARROW type
    {
      AstNode* more = ast_stmt_decl($5, (Type)$7, $3, 0, yylineno);
      $$ = ast_list_concat($1, more);
    }
  ;

/*
 * default_decl - uninitialized variable.
 * Syntax:  khaali rakho ID -> type
 */
default_decl
  : KW_KHAALI KW_RAKHO ID ARROW type
    {
      $$ = ast_stmt_default_decl($3, (Type)$5, 0, yylineno);
    }
  | default_decl KW_AR KW_KHAALI KW_RAKHO ID ARROW type
    {
      AstNode* more = ast_stmt_default_decl($5, (Type)$7, 0, yylineno);
      $$ = ast_list_concat($1, more);
    }
  ;

/*
 * const_decl - immutable variable (pakka).
 * Syntax:  value pakka rakho ID -> type
 *           khaali pakka rakho ID -> type   (default const)
 */
const_decl
  : value KW_PAKKA KW_RAKHO ID ARROW type
    {
      $$ = ast_stmt_decl($4, (Type)$6, $1, 1, yylineno);
    }
  | KW_KHAALI KW_PAKKA KW_RAKHO ID ARROW type
    {
      $$ = ast_stmt_default_decl($4, (Type)$6, 1, yylineno);
    }
  | const_decl KW_AR value KW_PAKKA KW_RAKHO ID ARROW type
    {
      AstNode* more = ast_stmt_decl($6, (Type)$8, $3, 1, yylineno);
      $$ = ast_list_concat($1, more);
    }
  | const_decl KW_AR KW_KHAALI KW_PAKKA KW_RAKHO ID ARROW type
    {
      AstNode* more = ast_stmt_default_decl($6, (Type)$8, 1, yylineno);
      $$ = ast_list_concat($1, more);
    }
  ;

/* ================================================================
   UPDATES
   ================================================================ */

/*
 * update_stmt - reassign a variable.
 * Syntax:  value bodlao ID
 */
update_stmt
  : value KW_BODLAO ID
    {
      $$ = ast_stmt_update($3, $1, yylineno);
    }
  ;

/* ================================================================
   CASTS
   ================================================================ */

/*
 * cast_decl - declare with explicit type cast.
 * Syntax:  value banaw <castType> rakho ID -> <declType>
 */
cast_decl
  : value KW_BANAW type KW_RAKHO ID ARROW type
    {
      $$ = ast_stmt_cast_decl($5, (Type)$3, (Type)$7, $1, yylineno);
    }
  ;

/*
 * cast_update - update with explicit type cast.
 * Syntax:  value banaw <castType> bodlao ID
 */
cast_update
  : value KW_BANAW type KW_BODLAO ID
    {
      $$ = ast_stmt_cast_update($5, (Type)$3, $1, yylineno);
    }
  ;

/* ================================================================
   PRINT
   ================================================================ */

/*
 * print_stmt - output a value.
 * Syntax:  bolo value
 */
print_stmt
  : KW_BOLO value
    {
      $$ = ast_stmt_print($2, yylineno);
    }
  ;

/* ================================================================
   CONDITIONALS
   ================================================================ */

/*
 * Full conditional chain:
 *   first_cond_block  zero-or-more-else-if-cond_blocks  optional-else-block
 *
 * The second alternative (cond_chain PIPE) is retained from the original
 * grammar to preserve identical parse behaviour.
 */
cond_chain
  : cond_block else_if_list else_block_opt
    {
      int total = 1 + $2.count;
      AstCondBlock** blocks =
          (AstCondBlock**)malloc(total * sizeof(AstCondBlock*));
      blocks[0] = $1;
      for (int i = 0; i < $2.count; i++) blocks[i + 1] = $2.arr[i];
      free($2.arr);
      $$ = ast_stmt_cond(blocks, total, $3, yylineno);
    }
  | cond_chain PIPE
    { $$ = $1; }
  ;

else_if_list
  : /* empty */
    { $$.arr = NULL; $$.count = 0; }
  | else_if_list cond_block
    {
      $$ = $1;
      $$.arr = (AstCondBlock**)realloc($$.arr,
                  ($$.count + 1) * sizeof(AstCondBlock*));
      $$.arr[$$.count++] = $2;
    }
  ;

else_block_opt
  : /* empty */  { $$ = NULL; }
  | else_block   { $$ = $1;   }
  ;

/*
 * else_block - the fall-through branch.
 * Syntax:  [] { stmts }
 */
else_block
  : LBRACKET RBRACKET block
    { $$ = $3; }
  ;

/*
 * cond_block - one if / else-if branch.
 * Structure:  bindings { group_list  block }
 */
cond_block
  : bindings LBRACE group_list block RBRACE
    {
      $$ = ast_cond_block_new($1.arr, $1.count,
                               $3.arr, $3.count,
                               $4);
    }
  ;

/* ================================================================
   BINDINGS   - ID -> value  (ar ID -> value)*
   ================================================================ */

bindings
  : binding
    {
      $$.arr = (AstBinding*)malloc(sizeof(AstBinding));
      $$.arr[0] = $1;
      $$.count = 1;
    }
  | bindings KW_AR binding
    {
      $$ = $1;
      $$.arr = (AstBinding*)realloc($$.arr,
                    ($$.count + 1) * sizeof(AstBinding));
      $$.arr[$$.count++] = $3;
    }
  ;

binding
  : ID ARROW value
    {
      $$.id   = $1;   /* take ownership of the lexer string */
      $$.expr = $3;   /* take ownership of the expr node    */
    }
  ;

/* ================================================================
   CONDITION GROUPS   - [ {op}, {op} ]
   ================================================================ */

group_list
  : group
    {
      $$.arr = (AstCondGroup*)malloc(sizeof(AstCondGroup));
      $$.arr[0] = $1;
      $$.count = 1;
    }
  | group_list group
    {
      $$ = $1;
      $$.arr = (AstCondGroup*)realloc($$.arr,
                    ($$.count + 1) * sizeof(AstCondGroup));
      $$.arr[$$.count++] = $2;
    }
  ;

group
  : LBRACKET cond_items_opt RBRACKET
    { $$ = $2; }
  ;

cond_items_opt
  : /* empty */
    { $$.count = 0; }
  | cond_items
    { $$ = $1; }
  ;

cond_items
  : cond_item
    {
      $$.count  = 1;
      $$.ops[0] = (CondOp)$1;
    }
  | cond_items COMMA cond_item
    {
      $$ = $1;
      if ($$.count < MAX_COND_OPS)
        $$.ops[$$.count++] = (CondOp)$3;
    }
  ;

cond_item
  : COND_GE      { $$ = CONDOP_GE;   }
  | COND_LE      { $$ = CONDOP_LE;   }
  | COND_EQ      { $$ = CONDOP_EQ;   }
  | COND_NEQ     { $$ = CONDOP_NEQ;  }
  | COND_GT      { $$ = CONDOP_GT;   }
  | COND_LT      { $$ = CONDOP_LT;   }
  | COND_SKIP    { $$ = CONDOP_SKIP; }
  | COND_UNKNOWN { $$ = CONDOP_SKIP; free($1); }
  ;

/* ================================================================
   BLOCK
   ================================================================ */

block
  : LBRACE stmt_list RBRACE
    { $$ = $2; }
  ;

/* ================================================================
   LOOPS
   Syntax:  [varName -> initVal, varName -> endVal] { stmts; varName barbe/komabe }
   Or with new variable declaration:
            [varName -> initVal -> type, varName -> endVal] { ... }
   ================================================================ */

loop_stmt
  : LBRACKET loop_init COMMA loop_end RBRACKET LBRACE stmt_list loop_ctrl RBRACE
    {
      /* Ownership of $4.var and $8.var transfers into the AST node
         so semantic.c can validate variable name consistency. */
      $$ = ast_stmt_loop($2.var, $2.is_new, (Type)$2.new_type, $2.init,
                          $4.var, $4.end,
                          $8.var, (LoopStep)$8.step, $8.step_op, $8.step_expr,
                          $7, yylineno);
    }
  ;

loop_init
  : ID ARROW value
    { $$.var = $1; $$.is_new = 0; $$.new_type = T_UNKNOWN; $$.init = $3; }
  | ID ARROW value ARROW type
    { $$.var = $1; $$.is_new = 1; $$.new_type = $5; $$.init = $3; }
  ;

loop_end
  : ID ARROW value
    { $$.var = $1; $$.end = $3; }
  ;

loop_ctrl
  : ID KW_BARBE  { $$.var = $1; $$.step = LOOP_INC; $$.step_op = 0; $$.step_expr = NULL; }
  | ID KW_KOMABE { $$.var = $1; $$.step = LOOP_DEC; $$.step_op = 0; $$.step_expr = NULL; }
  | KW_THAMO     { $$.var = NULL; $$.step = LOOP_STOP; $$.step_op = 0; $$.step_expr = NULL; }
  | ID KW_PORIBORTON_BY loop_step
                 { $$.var = $1; $$.step = LOOP_CUSTOM;
                   $$.step_op = $3.step_op; $$.step_expr = $3.step_expr; }
  ;

loop_step
  : PLUS  INT   { $$.step_op = '+'; $$.step_expr = ast_expr_int($2,   yylineno); }
  | MINUS INT   { $$.step_op = '-'; $$.step_expr = ast_expr_int($2,   yylineno); }
  | STAR  INT   { $$.step_op = '*'; $$.step_expr = ast_expr_int($2,   yylineno); }
  | SLASH INT   { $$.step_op = '/'; $$.step_expr = ast_expr_int($2,   yylineno); }
  | PLUS  FLOAT { $$.step_op = '+'; $$.step_expr = ast_expr_float($2, yylineno); }
  | MINUS FLOAT { $$.step_op = '-'; $$.step_expr = ast_expr_float($2, yylineno); }
  | STAR  FLOAT { $$.step_op = '*'; $$.step_expr = ast_expr_float($2, yylineno); }
  | SLASH FLOAT { $$.step_op = '/'; $$.step_expr = ast_expr_float($2, yylineno); }
  | INT
    { /* handles lexer-embedded sign, e.g. -2 tokenised as INT(-2) */
      if ($1 < 0) { $$.step_op = '-'; $$.step_expr = ast_expr_int(-$1, yylineno); }
      else        { $$.step_op = '+'; $$.step_expr = ast_expr_int($1,  yylineno); }
    }
  | FLOAT
    { if ($1 < 0.0) { $$.step_op = '-'; $$.step_expr = ast_expr_float(-$1, yylineno); }
      else          { $$.step_op = '+'; $$.step_expr = ast_expr_float($1,  yylineno); }
    }
  ;

/* ================================================================
   FUNCTIONS
   Syntax:  funcName(param -> type, ...) -> returnType { stmts }
   ================================================================ */

func_decl
  : ID LPAREN param_list RPAREN ARROW type LBRACE stmt_list RBRACE
    { $$ = ast_stmt_func_def($1, (Type)$6, $3.arr, $3.count, $8, yylineno); }
  | ID LPAREN RPAREN ARROW type LBRACE stmt_list RBRACE
    { $$ = ast_stmt_func_def($1, (Type)$5, NULL, 0, $7, yylineno); }
  ;

param_list
  : param
    { $$.arr = (FuncParamNode*)malloc(sizeof(FuncParamNode));
      $$.arr[0] = $1; $$.count = 1; }
  | param_list COMMA param
    { $$ = $1;
      $$.arr = (FuncParamNode*)realloc($$.arr,
                  ($$.count + 1) * sizeof(FuncParamNode));
      $$.arr[$$.count++] = $3; }
  ;

param
  : ID ARROW type
    { $$.name = $1; $$.type = (Type)$3; }
  ;

func_call
  : ID LPAREN arg_list RPAREN
    { $$ = ast_expr_call($1, $3.arr, $3.count, yylineno); }
  | ID LPAREN RPAREN
    { $$ = ast_expr_call($1, NULL, 0, yylineno); }
  ;

arg_list
  : expr
    { $$.arr = (AstExpr**)malloc(sizeof(AstExpr*));
      $$.arr[0] = $1; $$.count = 1; }
  | arg_list COMMA expr
    { $$ = $1;
      $$.arr = (AstExpr**)realloc($$.arr,
                  ($$.count + 1) * sizeof(AstExpr*));
      $$.arr[$$.count++] = $3; }
  ;

return_stmt
  : KW_FERAO expr
    { $$ = ast_stmt_return($2, yylineno); }
  ;

%%

/* ================================================================
   ERROR HANDLER
   ================================================================ */

void yyerror(const char* s) {
  fprintf(stderr, "PARSE_ERROR at line %d: %s\n", yylineno, s);
}
