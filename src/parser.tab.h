
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* "%code requires" blocks.  */

/* Line 1676 of yacc.c  */
#line 21 "parser.y"

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



/* Line 1676 of yacc.c  */
#line 61 "parser.tab.h"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     KW_RAKHO = 258,
     KW_BODLAO = 259,
     KW_PAKKA = 260,
     KW_KHAALI = 261,
     KW_AR = 262,
     KW_BOLO = 263,
     KW_BANAW = 264,
     KW_BARBE = 265,
     KW_KOMABE = 266,
     KW_THAMO = 267,
     KW_PORIBORTON_BY = 268,
     KW_AGAO = 269,
     KW_FERAO = 270,
     TYPE_INT = 271,
     TYPE_FLOAT = 272,
     TYPE_STR = 273,
     TYPE_BOOL = 274,
     ARROW = 275,
     PIPE = 276,
     LBRACE = 277,
     RBRACE = 278,
     LBRACKET = 279,
     RBRACKET = 280,
     COMMA = 281,
     EQUALS = 282,
     LPAREN = 283,
     RPAREN = 284,
     PLUS = 285,
     MINUS = 286,
     STAR = 287,
     SLASH = 288,
     COND_GE = 289,
     COND_LE = 290,
     COND_EQ = 291,
     COND_NEQ = 292,
     COND_GT = 293,
     COND_LT = 294,
     COND_SKIP = 295,
     COND_UNKNOWN = 296,
     INT = 297,
     FLOAT = 298,
     STRING = 299,
     ID = 300,
     BOOL = 301
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 46 "parser.y"

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



/* Line 1676 of yacc.c  */
#line 149 "parser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


