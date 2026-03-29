
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"     /* includes value.h */

int  yylex(void);
void yyerror(const char* s);

extern int yylineno;

/* The completed AST root - read by main() after yyparse() returns. */
AstNode* g_parse_result = NULL;


/* Line 189 of yacc.c  */
#line 90 "parser.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

/* "%code requires" blocks.  */

/* Line 209 of yacc.c  */
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



/* Line 209 of yacc.c  */
#line 135 "parser.tab.c"

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
     KW_FERAO = 269,
     TYPE_INT = 270,
     TYPE_FLOAT = 271,
     TYPE_STR = 272,
     TYPE_BOOL = 273,
     ARROW = 274,
     PIPE = 275,
     LBRACE = 276,
     RBRACE = 277,
     LBRACKET = 278,
     RBRACKET = 279,
     COMMA = 280,
     EQUALS = 281,
     LPAREN = 282,
     RPAREN = 283,
     PLUS = 284,
     MINUS = 285,
     STAR = 286,
     SLASH = 287,
     COND_GE = 288,
     COND_LE = 289,
     COND_EQ = 290,
     COND_NEQ = 291,
     COND_GT = 292,
     COND_LT = 293,
     COND_SKIP = 294,
     COND_UNKNOWN = 295,
     INT = 296,
     FLOAT = 297,
     STRING = 298,
     ID = 299,
     BOOL = 300
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
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



/* Line 214 of yacc.c  */
#line 222 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 234 "parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   250

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  98
/* YYNRULES -- Number of states.  */
#define YYNSTATES  211

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   300

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    12,    15,    18,    21,
      24,    27,    30,    33,    35,    37,    40,    42,    44,    46,
      48,    50,    52,    54,    56,    58,    60,    64,    68,    72,
      76,    80,    82,    88,    96,   102,   110,   117,   124,   133,
     142,   146,   154,   160,   163,   167,   170,   171,   174,   175,
     177,   181,   187,   189,   193,   197,   199,   202,   206,   207,
     209,   211,   215,   217,   219,   221,   223,   225,   227,   229,
     231,   235,   245,   249,   255,   259,   262,   265,   267,   271,
     274,   277,   280,   283,   286,   289,   292,   295,   297,   299,
     309,   318,   320,   324,   328,   333,   337,   339,   343
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      47,     0,    -1,    48,    -1,    -1,    48,    49,    -1,    53,
      20,    -1,    54,    20,    -1,    55,    20,    -1,    56,    20,
      -1,    57,    20,    -1,    58,    20,    -1,    59,    20,    -1,
      60,    20,    -1,    73,    -1,    78,    -1,    83,    20,    -1,
      15,    -1,    16,    -1,    17,    -1,    18,    -1,    52,    -1,
      41,    -1,    42,    -1,    45,    -1,    43,    -1,    44,    -1,
      52,    29,    52,    -1,    52,    30,    52,    -1,    52,    31,
      52,    -1,    52,    32,    52,    -1,    27,    52,    28,    -1,
      81,    -1,    51,     3,    44,    19,    50,    -1,    53,     7,
      51,     3,    44,    19,    50,    -1,     6,     3,    44,    19,
      50,    -1,    54,     7,     6,     3,    44,    19,    50,    -1,
      51,     5,     3,    44,    19,    50,    -1,     6,     5,     3,
      44,    19,    50,    -1,    55,     7,    51,     5,     3,    44,
      19,    50,    -1,    55,     7,     6,     5,     3,    44,    19,
      50,    -1,    51,     4,    44,    -1,    51,     9,    50,     3,
      44,    19,    50,    -1,    51,     9,    50,     4,    44,    -1,
       8,    51,    -1,    64,    61,    62,    -1,    60,    20,    -1,
      -1,    61,    64,    -1,    -1,    63,    -1,    23,    24,    72,
      -1,    65,    21,    67,    72,    22,    -1,    66,    -1,    65,
       7,    66,    -1,    44,    19,    51,    -1,    68,    -1,    67,
      68,    -1,    23,    69,    24,    -1,    -1,    70,    -1,    71,
      -1,    70,    25,    71,    -1,    33,    -1,    34,    -1,    35,
      -1,    36,    -1,    37,    -1,    38,    -1,    39,    -1,    40,
      -1,    21,    48,    22,    -1,    23,    74,    25,    75,    24,
      21,    48,    76,    22,    -1,    44,    19,    51,    -1,    44,
      19,    51,    19,    50,    -1,    44,    19,    51,    -1,    44,
      10,    -1,    44,    11,    -1,    12,    -1,    44,    13,    77,
      -1,    29,    41,    -1,    30,    41,    -1,    31,    41,    -1,
      32,    41,    -1,    29,    42,    -1,    30,    42,    -1,    31,
      42,    -1,    32,    42,    -1,    41,    -1,    42,    -1,    44,
      27,    79,    28,    19,    50,    21,    48,    22,    -1,    44,
      27,    28,    19,    50,    21,    48,    22,    -1,    80,    -1,
      79,    25,    80,    -1,    44,    19,    50,    -1,    44,    27,
      82,    28,    -1,    44,    27,    28,    -1,    52,    -1,    82,
      25,    52,    -1,    14,    52,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   139,   139,   145,   146,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   169,   170,   171,   172,
     181,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   209,   213,   225,   229,   242,   246,   250,   255,
     271,   286,   297,   312,   330,   340,   346,   347,   357,   358,
     366,   375,   388,   394,   404,   416,   422,   432,   438,   439,
     444,   449,   458,   459,   460,   461,   462,   463,   464,   465,
     473,   485,   497,   499,   504,   509,   510,   511,   512,   518,
     519,   520,   521,   522,   523,   524,   525,   526,   531,   543,
     545,   550,   553,   561,   566,   568,   573,   576,   584
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "KW_RAKHO", "KW_BODLAO", "KW_PAKKA",
  "KW_KHAALI", "KW_AR", "KW_BOLO", "KW_BANAW", "KW_BARBE", "KW_KOMABE",
  "KW_THAMO", "KW_PORIBORTON_BY", "KW_FERAO", "TYPE_INT", "TYPE_FLOAT",
  "TYPE_STR", "TYPE_BOOL", "ARROW", "PIPE", "LBRACE", "RBRACE", "LBRACKET",
  "RBRACKET", "COMMA", "EQUALS", "LPAREN", "RPAREN", "PLUS", "MINUS",
  "STAR", "SLASH", "COND_GE", "COND_LE", "COND_EQ", "COND_NEQ", "COND_GT",
  "COND_LT", "COND_SKIP", "COND_UNKNOWN", "INT", "FLOAT", "STRING", "ID",
  "BOOL", "$accept", "program", "stmt_list", "stmt", "type", "value",
  "expr", "var_decl", "default_decl", "const_decl", "update_stmt",
  "cast_decl", "cast_update", "print_stmt", "cond_chain", "else_if_list",
  "else_block_opt", "else_block", "cond_block", "bindings", "binding",
  "group_list", "group", "cond_items_opt", "cond_items", "cond_item",
  "block", "loop_stmt", "loop_init", "loop_end", "loop_ctrl", "loop_step",
  "func_decl", "param_list", "param", "func_call", "arg_list",
  "return_stmt", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    48,    48,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    50,    50,    50,    50,
      51,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    53,    53,    54,    54,    55,    55,    55,    55,
      56,    57,    58,    59,    60,    60,    61,    61,    62,    62,
      63,    64,    65,    65,    66,    67,    67,    68,    69,    69,
      70,    70,    71,    71,    71,    71,    71,    71,    71,    71,
      72,    73,    74,    74,    75,    76,    76,    76,    76,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    78,
      78,    79,    79,    80,    81,    81,    82,    82,    83
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     1,     5,     7,     5,     7,     6,     6,     8,     8,
       3,     7,     5,     2,     3,     2,     0,     2,     0,     1,
       3,     5,     1,     3,     3,     1,     2,     3,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     9,     3,     5,     3,     2,     2,     1,     3,     2,
       2,     2,     2,     2,     2,     2,     2,     1,     1,     9,
       8,     1,     3,     3,     4,     3,     1,     3,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     2,     1,     0,     0,     0,     0,     0,    21,
      22,    24,    25,    23,     4,     0,    20,     0,     0,     0,
       0,     0,     0,     0,     0,    46,     0,    52,    13,    14,
      31,     0,     0,     0,    25,    43,    98,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     5,     0,     6,     0,     7,     8,     9,    10,    11,
      12,    48,     0,     0,    15,     0,     0,     0,     0,     0,
      30,    54,    95,    25,    96,     0,    91,     0,     0,    40,
       0,    16,    17,    18,    19,     0,    26,    27,    28,    29,
       0,     0,     0,     0,     0,     0,    44,    49,    47,    53,
      58,     0,    55,     0,     0,    95,    72,     0,     0,     0,
       0,     0,     0,     0,    94,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    62,    63,    64,    65,    66,    67,
      68,    69,     0,    59,    60,     3,    56,     0,    34,     0,
       0,     0,     0,     0,    93,     0,    92,     0,    97,    32,
       0,     0,    42,     0,     0,     0,     0,    50,    57,     0,
       0,    51,    37,    73,    74,     3,     3,     0,    36,     0,
       0,     0,     0,     0,    61,    70,     0,     0,     3,    41,
      33,    35,     0,     0,    77,    25,     0,    90,     0,    39,
      38,    75,    76,     0,    71,    89,     0,     0,     0,     0,
      87,    88,    78,    79,    83,    80,    84,    81,    85,    82,
      86
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    14,    85,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    61,    96,    97,    25,    26,
      27,   101,   102,   132,   133,   134,   137,    28,    38,   108,
     186,   202,    29,    75,    76,    30,    77,    31
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -135
static const yytype_int16 yypact[] =
{
    -135,    12,   125,  -135,     2,   144,   144,   -38,   144,  -135,
    -135,  -135,    11,  -135,  -135,   108,   124,     1,     7,    22,
      23,    28,    45,    58,    60,  -135,    -3,  -135,  -135,  -135,
    -135,    84,   -10,    82,   101,  -135,   124,   111,   107,   166,
     144,    46,    94,    96,   106,   197,   144,   144,   144,   144,
     144,  -135,   135,  -135,   131,  -135,  -135,  -135,  -135,  -135,
     122,   -21,   105,   127,  -135,   132,   113,   136,   144,   115,
    -135,  -135,   141,    48,   124,    36,  -135,    51,   142,  -135,
     118,  -135,  -135,  -135,  -135,    90,    71,    71,  -135,  -135,
     162,   179,   178,   194,   160,   181,  -135,  -135,  -135,  -135,
     171,     3,  -135,   197,   182,  -135,   198,   199,   192,   197,
     197,   175,   201,   144,  -135,   197,   202,   180,   183,   184,
     185,   219,   220,   204,  -135,  -135,  -135,  -135,  -135,  -135,
    -135,  -135,   206,   207,  -135,  -135,  -135,   209,  -135,   197,
     197,   144,   205,   212,  -135,   215,  -135,   197,   124,  -135,
     197,   216,  -135,   217,   218,   195,   196,  -135,  -135,   171,
      14,  -135,  -135,  -135,  -135,  -135,  -135,   221,  -135,   197,
     197,   197,   222,   224,  -135,  -135,    54,    78,  -135,  -135,
    -135,  -135,   197,   197,  -135,     6,   223,  -135,   102,  -135,
    -135,  -135,  -135,   161,  -135,  -135,    65,    73,    85,    93,
    -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,
    -135
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -135,  -135,  -134,  -135,  -100,    -5,     5,  -135,  -135,  -135,
    -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,   177,  -135,
     186,  -135,   143,  -135,  -135,    87,   126,  -135,  -135,  -135,
    -135,  -135,  -135,  -135,   139,  -135,  -135,  -135
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -46
static const yytype_int16 yytable[] =
{
      35,   160,    94,   138,    62,    32,    37,    33,    50,   143,
     144,    36,     3,    39,    52,   149,   191,   192,    63,   193,
       4,    51,     5,    95,   135,    40,   100,    53,     6,    54,
      40,   176,   177,    41,    65,    71,   175,     7,    41,   162,
     163,     8,    55,    56,   188,    90,    74,   167,    57,    93,
     168,    86,    87,    88,    89,     9,    10,    11,    12,    13,
       4,   111,     5,   106,   112,    58,   184,   110,     6,   179,
     180,   181,    74,     8,    72,    67,   113,     7,    59,   114,
      60,     8,   189,   190,     4,    66,     5,     9,    10,    11,
      73,    13,     6,   117,   118,     9,    10,    11,   185,    13,
     187,     7,    48,    49,    64,     8,   203,   204,     4,    80,
       5,    42,    43,    44,   205,   206,     6,    45,   148,     9,
      10,    11,    12,    13,   195,     7,   207,   208,    67,     8,
      68,     4,    69,     5,   209,   210,   164,    92,    78,     6,
      79,    91,   -45,     9,    10,    11,    12,    13,     7,    95,
     100,   103,     8,    46,    47,    48,    49,   104,     8,   107,
     109,   115,   116,     8,   105,   119,     9,    10,    11,    12,
      13,     8,     9,    10,    11,    34,    13,     9,    10,    11,
      34,    13,   120,   121,   123,     9,    10,    11,    34,    13,
     196,   197,   198,   199,    70,    46,    47,    48,    49,   122,
      40,   139,   200,   201,   124,   125,   126,   127,   128,   129,
     130,   131,    81,    82,    83,    84,   142,   140,   141,   145,
     147,   150,   155,   156,   151,   135,   165,   152,   153,   154,
     158,   161,   159,   166,   110,   169,   170,   171,    98,   172,
     173,   182,   178,   183,   136,   194,   174,     0,    99,   157,
     146
};

static const yytype_int16 yycheck[] =
{
       5,   135,    23,   103,     7,     3,    44,     5,     7,   109,
     110,     6,     0,     8,     7,   115,    10,    11,    21,    13,
       6,    20,     8,    44,    21,    19,    23,    20,    14,     7,
      19,   165,   166,    27,    44,    40,    22,    23,    27,   139,
     140,    27,    20,    20,   178,    50,    41,   147,    20,    54,
     150,    46,    47,    48,    49,    41,    42,    43,    44,    45,
       6,    25,     8,    68,    28,    20,    12,    19,    14,   169,
     170,   171,    67,    27,    28,    27,    25,    23,    20,    28,
      20,    27,   182,   183,     6,     3,     8,    41,    42,    43,
      44,    45,    14,     3,     4,    41,    42,    43,    44,    45,
      22,    23,    31,    32,    20,    27,    41,    42,     6,     3,
       8,     3,     4,     5,    41,    42,    14,     9,   113,    41,
      42,    43,    44,    45,    22,    23,    41,    42,    27,    27,
      19,     6,    25,     8,    41,    42,   141,     6,    44,    14,
      44,     6,    20,    41,    42,    43,    44,    45,    23,    44,
      23,    19,    27,    29,    30,    31,    32,    44,    27,    44,
      19,    19,    44,    27,    28,     3,    41,    42,    43,    44,
      45,    27,    41,    42,    43,    44,    45,    41,    42,    43,
      44,    45,     3,     5,    24,    41,    42,    43,    44,    45,
      29,    30,    31,    32,    28,    29,    30,    31,    32,     5,
      19,    19,    41,    42,    33,    34,    35,    36,    37,    38,
      39,    40,    15,    16,    17,    18,    24,    19,    19,    44,
      19,    19,     3,     3,    44,    21,    21,    44,    44,    44,
      24,    22,    25,    21,    19,    19,    19,    19,    61,    44,
      44,    19,    21,    19,   101,    22,   159,    -1,    62,   123,
     111
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    47,    48,     0,     6,     8,    14,    23,    27,    41,
      42,    43,    44,    45,    49,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    64,    65,    66,    73,    78,
      81,    83,     3,     5,    44,    51,    52,    44,    74,    52,
      19,    27,     3,     4,     5,     9,    29,    30,    31,    32,
       7,    20,     7,    20,     7,    20,    20,    20,    20,    20,
      20,    61,     7,    21,    20,    44,     3,    27,    19,    25,
      28,    51,    28,    44,    52,    79,    80,    82,    44,    44,
       3,    15,    16,    17,    18,    50,    52,    52,    52,    52,
      51,     6,     6,    51,    23,    44,    62,    63,    64,    66,
      23,    67,    68,    19,    44,    28,    51,    44,    75,    19,
      19,    25,    28,    25,    28,    19,    44,     3,     4,     3,
       3,     5,     5,    24,    33,    34,    35,    36,    37,    38,
      39,    40,    69,    70,    71,    21,    68,    72,    50,    19,
      19,    19,    24,    50,    50,    44,    80,    19,    52,    50,
      19,    44,    44,    44,    44,     3,     3,    72,    24,    25,
      48,    22,    50,    50,    51,    21,    21,    50,    50,    19,
      19,    19,    44,    44,    71,    22,    48,    48,    21,    50,
      50,    50,    19,    19,    12,    44,    76,    22,    48,    50,
      50,    10,    11,    13,    22,    22,    29,    30,    31,    32,
      41,    42,    77,    41,    42,    41,    42,    41,    42,    41,
      42
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 140 "parser.y"
    { g_parse_result = (yyvsp[(1) - (1)].node); ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 145 "parser.y"
    { (yyval.node) = NULL; ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 147 "parser.y"
    { (yyval.node) = ast_list_concat((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 151 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 152 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 153 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 154 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 155 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 156 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 157 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 158 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 159 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 160 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 161 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 169 "parser.y"
    { (yyval.tval) = T_INT; ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 170 "parser.y"
    { (yyval.tval) = T_FLOAT; ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 171 "parser.y"
    { (yyval.tval) = T_STR; ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 172 "parser.y"
    { (yyval.tval) = T_BOOL; ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 181 "parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 185 "parser.y"
    { (yyval.expr) = ast_expr_int((yyvsp[(1) - (1)].ival), yylineno); ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 186 "parser.y"
    { (yyval.expr) = ast_expr_float((yyvsp[(1) - (1)].fval), yylineno); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 187 "parser.y"
    { (yyval.expr) = ast_expr_bool((int)(yyvsp[(1) - (1)].ival), yylineno); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 188 "parser.y"
    { (yyval.expr) = ast_expr_str((yyvsp[(1) - (1)].sval), yylineno); /* takes ownership, strips quotes */ ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 189 "parser.y"
    { (yyval.expr) = ast_expr_id((yyvsp[(1) - (1)].sval), yylineno);  /* takes ownership */ ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 190 "parser.y"
    { (yyval.expr) = ast_expr_binop(BINOP_ADD, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), yylineno); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 191 "parser.y"
    { (yyval.expr) = ast_expr_binop(BINOP_SUB, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), yylineno); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 192 "parser.y"
    { (yyval.expr) = ast_expr_binop(BINOP_MUL, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), yylineno); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 193 "parser.y"
    { (yyval.expr) = ast_expr_binop(BINOP_DIV, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), yylineno); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 194 "parser.y"
    { (yyval.expr) = (yyvsp[(2) - (3)].expr); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 195 "parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 210 "parser.y"
    {
      (yyval.node) = ast_stmt_decl((yyvsp[(3) - (5)].sval), (Type)(yyvsp[(5) - (5)].tval), (yyvsp[(1) - (5)].expr), 0, yylineno);
    ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 214 "parser.y"
    {
      AstNode* more = ast_stmt_decl((yyvsp[(5) - (7)].sval), (Type)(yyvsp[(7) - (7)].tval), (yyvsp[(3) - (7)].expr), 0, yylineno);
      (yyval.node) = ast_list_concat((yyvsp[(1) - (7)].node), more);
    ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 226 "parser.y"
    {
      (yyval.node) = ast_stmt_default_decl((yyvsp[(3) - (5)].sval), (Type)(yyvsp[(5) - (5)].tval), 0, yylineno);
    ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 230 "parser.y"
    {
      AstNode* more = ast_stmt_default_decl((yyvsp[(5) - (7)].sval), (Type)(yyvsp[(7) - (7)].tval), 0, yylineno);
      (yyval.node) = ast_list_concat((yyvsp[(1) - (7)].node), more);
    ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 243 "parser.y"
    {
      (yyval.node) = ast_stmt_decl((yyvsp[(4) - (6)].sval), (Type)(yyvsp[(6) - (6)].tval), (yyvsp[(1) - (6)].expr), 1, yylineno);
    ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 247 "parser.y"
    {
      (yyval.node) = ast_stmt_default_decl((yyvsp[(4) - (6)].sval), (Type)(yyvsp[(6) - (6)].tval), 1, yylineno);
    ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 251 "parser.y"
    {
      AstNode* more = ast_stmt_decl((yyvsp[(6) - (8)].sval), (Type)(yyvsp[(8) - (8)].tval), (yyvsp[(3) - (8)].expr), 1, yylineno);
      (yyval.node) = ast_list_concat((yyvsp[(1) - (8)].node), more);
    ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 256 "parser.y"
    {
      AstNode* more = ast_stmt_default_decl((yyvsp[(6) - (8)].sval), (Type)(yyvsp[(8) - (8)].tval), 1, yylineno);
      (yyval.node) = ast_list_concat((yyvsp[(1) - (8)].node), more);
    ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 272 "parser.y"
    {
      (yyval.node) = ast_stmt_update((yyvsp[(3) - (3)].sval), (yyvsp[(1) - (3)].expr), yylineno);
    ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 287 "parser.y"
    {
      (yyval.node) = ast_stmt_cast_decl((yyvsp[(5) - (7)].sval), (Type)(yyvsp[(3) - (7)].tval), (Type)(yyvsp[(7) - (7)].tval), (yyvsp[(1) - (7)].expr), yylineno);
    ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 298 "parser.y"
    {
      (yyval.node) = ast_stmt_cast_update((yyvsp[(5) - (5)].sval), (Type)(yyvsp[(3) - (5)].tval), (yyvsp[(1) - (5)].expr), yylineno);
    ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 313 "parser.y"
    {
      (yyval.node) = ast_stmt_print((yyvsp[(2) - (2)].expr), yylineno);
    ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 331 "parser.y"
    {
      int total = 1 + (yyvsp[(2) - (3)].cblist).count;
      AstCondBlock** blocks =
          (AstCondBlock**)malloc(total * sizeof(AstCondBlock*));
      blocks[0] = (yyvsp[(1) - (3)].cblock);
      for (int i = 0; i < (yyvsp[(2) - (3)].cblist).count; i++) blocks[i + 1] = (yyvsp[(2) - (3)].cblist).arr[i];
      free((yyvsp[(2) - (3)].cblist).arr);
      (yyval.node) = ast_stmt_cond(blocks, total, (yyvsp[(3) - (3)].node), yylineno);
    ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 341 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 346 "parser.y"
    { (yyval.cblist).arr = NULL; (yyval.cblist).count = 0; ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 348 "parser.y"
    {
      (yyval.cblist) = (yyvsp[(1) - (2)].cblist);
      (yyval.cblist).arr = (AstCondBlock**)realloc((yyval.cblist).arr,
                  ((yyval.cblist).count + 1) * sizeof(AstCondBlock*));
      (yyval.cblist).arr[(yyval.cblist).count++] = (yyvsp[(2) - (2)].cblock);
    ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 357 "parser.y"
    { (yyval.node) = NULL; ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 358 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node);   ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 367 "parser.y"
    { (yyval.node) = (yyvsp[(3) - (3)].node); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 376 "parser.y"
    {
      (yyval.cblock) = ast_cond_block_new((yyvsp[(1) - (5)].blist).arr, (yyvsp[(1) - (5)].blist).count,
                               (yyvsp[(3) - (5)].glist).arr, (yyvsp[(3) - (5)].glist).count,
                               (yyvsp[(4) - (5)].node));
    ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 389 "parser.y"
    {
      (yyval.blist).arr = (AstBinding*)malloc(sizeof(AstBinding));
      (yyval.blist).arr[0] = (yyvsp[(1) - (1)].bindi);
      (yyval.blist).count = 1;
    ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 395 "parser.y"
    {
      (yyval.blist) = (yyvsp[(1) - (3)].blist);
      (yyval.blist).arr = (AstBinding*)realloc((yyval.blist).arr,
                    ((yyval.blist).count + 1) * sizeof(AstBinding));
      (yyval.blist).arr[(yyval.blist).count++] = (yyvsp[(3) - (3)].bindi);
    ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 405 "parser.y"
    {
      (yyval.bindi).id   = (yyvsp[(1) - (3)].sval);   /* take ownership of the lexer string */
      (yyval.bindi).expr = (yyvsp[(3) - (3)].expr);   /* take ownership of the expr node    */
    ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 417 "parser.y"
    {
      (yyval.glist).arr = (AstCondGroup*)malloc(sizeof(AstCondGroup));
      (yyval.glist).arr[0] = (yyvsp[(1) - (1)].cgroup);
      (yyval.glist).count = 1;
    ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 423 "parser.y"
    {
      (yyval.glist) = (yyvsp[(1) - (2)].glist);
      (yyval.glist).arr = (AstCondGroup*)realloc((yyval.glist).arr,
                    ((yyval.glist).count + 1) * sizeof(AstCondGroup));
      (yyval.glist).arr[(yyval.glist).count++] = (yyvsp[(2) - (2)].cgroup);
    ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 433 "parser.y"
    { (yyval.cgroup) = (yyvsp[(2) - (3)].cgroup); ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 438 "parser.y"
    { (yyval.cgroup).count = 0; ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 440 "parser.y"
    { (yyval.cgroup) = (yyvsp[(1) - (1)].cgroup); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 445 "parser.y"
    {
      (yyval.cgroup).count  = 1;
      (yyval.cgroup).ops[0] = (CondOp)(yyvsp[(1) - (1)].condop);
    ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 450 "parser.y"
    {
      (yyval.cgroup) = (yyvsp[(1) - (3)].cgroup);
      if ((yyval.cgroup).count < MAX_COND_OPS)
        (yyval.cgroup).ops[(yyval.cgroup).count++] = (CondOp)(yyvsp[(3) - (3)].condop);
    ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 458 "parser.y"
    { (yyval.condop) = CONDOP_GE;   ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 459 "parser.y"
    { (yyval.condop) = CONDOP_LE;   ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 460 "parser.y"
    { (yyval.condop) = CONDOP_EQ;   ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 461 "parser.y"
    { (yyval.condop) = CONDOP_NEQ;  ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 462 "parser.y"
    { (yyval.condop) = CONDOP_GT;   ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 463 "parser.y"
    { (yyval.condop) = CONDOP_LT;   ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 464 "parser.y"
    { (yyval.condop) = CONDOP_SKIP; ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 465 "parser.y"
    { (yyval.condop) = CONDOP_SKIP; free((yyvsp[(1) - (1)].sval)); ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 474 "parser.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 486 "parser.y"
    {
      /* Ownership of $4.var and $8.var transfers into the AST node
         so semantic.c can validate variable name consistency. */
      (yyval.node) = ast_stmt_loop((yyvsp[(2) - (9)].lact).var, (yyvsp[(2) - (9)].lact).is_new, (Type)(yyvsp[(2) - (9)].lact).new_type, (yyvsp[(2) - (9)].lact).init,
                          (yyvsp[(4) - (9)].lend).var, (yyvsp[(4) - (9)].lend).end,
                          (yyvsp[(8) - (9)].lctrl).var, (LoopStep)(yyvsp[(8) - (9)].lctrl).step, (yyvsp[(8) - (9)].lctrl).step_op, (yyvsp[(8) - (9)].lctrl).step_expr,
                          (yyvsp[(7) - (9)].node), yylineno);
    ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 498 "parser.y"
    { (yyval.lact).var = (yyvsp[(1) - (3)].sval); (yyval.lact).is_new = 0; (yyval.lact).new_type = T_UNKNOWN; (yyval.lact).init = (yyvsp[(3) - (3)].expr); ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 500 "parser.y"
    { (yyval.lact).var = (yyvsp[(1) - (5)].sval); (yyval.lact).is_new = 1; (yyval.lact).new_type = (yyvsp[(5) - (5)].tval); (yyval.lact).init = (yyvsp[(3) - (5)].expr); ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 505 "parser.y"
    { (yyval.lend).var = (yyvsp[(1) - (3)].sval); (yyval.lend).end = (yyvsp[(3) - (3)].expr); ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 509 "parser.y"
    { (yyval.lctrl).var = (yyvsp[(1) - (2)].sval); (yyval.lctrl).step = LOOP_INC; (yyval.lctrl).step_op = 0; (yyval.lctrl).step_expr = NULL; ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 510 "parser.y"
    { (yyval.lctrl).var = (yyvsp[(1) - (2)].sval); (yyval.lctrl).step = LOOP_DEC; (yyval.lctrl).step_op = 0; (yyval.lctrl).step_expr = NULL; ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 511 "parser.y"
    { (yyval.lctrl).var = NULL; (yyval.lctrl).step = LOOP_STOP; (yyval.lctrl).step_op = 0; (yyval.lctrl).step_expr = NULL; ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 513 "parser.y"
    { (yyval.lctrl).var = (yyvsp[(1) - (3)].sval); (yyval.lctrl).step = LOOP_CUSTOM;
                   (yyval.lctrl).step_op = (yyvsp[(3) - (3)].lstep).step_op; (yyval.lctrl).step_expr = (yyvsp[(3) - (3)].lstep).step_expr; ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 518 "parser.y"
    { (yyval.lstep).step_op = '+'; (yyval.lstep).step_expr = ast_expr_int((yyvsp[(2) - (2)].ival),   yylineno); ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 519 "parser.y"
    { (yyval.lstep).step_op = '-'; (yyval.lstep).step_expr = ast_expr_int((yyvsp[(2) - (2)].ival),   yylineno); ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 520 "parser.y"
    { (yyval.lstep).step_op = '*'; (yyval.lstep).step_expr = ast_expr_int((yyvsp[(2) - (2)].ival),   yylineno); ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 521 "parser.y"
    { (yyval.lstep).step_op = '/'; (yyval.lstep).step_expr = ast_expr_int((yyvsp[(2) - (2)].ival),   yylineno); ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 522 "parser.y"
    { (yyval.lstep).step_op = '+'; (yyval.lstep).step_expr = ast_expr_float((yyvsp[(2) - (2)].fval), yylineno); ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 523 "parser.y"
    { (yyval.lstep).step_op = '-'; (yyval.lstep).step_expr = ast_expr_float((yyvsp[(2) - (2)].fval), yylineno); ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 524 "parser.y"
    { (yyval.lstep).step_op = '*'; (yyval.lstep).step_expr = ast_expr_float((yyvsp[(2) - (2)].fval), yylineno); ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 525 "parser.y"
    { (yyval.lstep).step_op = '/'; (yyval.lstep).step_expr = ast_expr_float((yyvsp[(2) - (2)].fval), yylineno); ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 527 "parser.y"
    { /* handles lexer-embedded sign, e.g. -2 tokenised as INT(-2) */
      if ((yyvsp[(1) - (1)].ival) < 0) { (yyval.lstep).step_op = '-'; (yyval.lstep).step_expr = ast_expr_int(-(yyvsp[(1) - (1)].ival), yylineno); }
      else        { (yyval.lstep).step_op = '+'; (yyval.lstep).step_expr = ast_expr_int((yyvsp[(1) - (1)].ival),  yylineno); }
    ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 532 "parser.y"
    { if ((yyvsp[(1) - (1)].fval) < 0.0) { (yyval.lstep).step_op = '-'; (yyval.lstep).step_expr = ast_expr_float(-(yyvsp[(1) - (1)].fval), yylineno); }
      else          { (yyval.lstep).step_op = '+'; (yyval.lstep).step_expr = ast_expr_float((yyvsp[(1) - (1)].fval),  yylineno); }
    ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 544 "parser.y"
    { (yyval.node) = ast_stmt_func_def((yyvsp[(1) - (9)].sval), (Type)(yyvsp[(6) - (9)].tval), (yyvsp[(3) - (9)].plist).arr, (yyvsp[(3) - (9)].plist).count, (yyvsp[(8) - (9)].node), yylineno); ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 546 "parser.y"
    { (yyval.node) = ast_stmt_func_def((yyvsp[(1) - (8)].sval), (Type)(yyvsp[(5) - (8)].tval), NULL, 0, (yyvsp[(7) - (8)].node), yylineno); ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 551 "parser.y"
    { (yyval.plist).arr = (FuncParamNode*)malloc(sizeof(FuncParamNode));
      (yyval.plist).arr[0] = (yyvsp[(1) - (1)].fparam); (yyval.plist).count = 1; ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 554 "parser.y"
    { (yyval.plist) = (yyvsp[(1) - (3)].plist);
      (yyval.plist).arr = (FuncParamNode*)realloc((yyval.plist).arr,
                  ((yyval.plist).count + 1) * sizeof(FuncParamNode));
      (yyval.plist).arr[(yyval.plist).count++] = (yyvsp[(3) - (3)].fparam); ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 562 "parser.y"
    { (yyval.fparam).name = (yyvsp[(1) - (3)].sval); (yyval.fparam).type = (Type)(yyvsp[(3) - (3)].tval); ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 567 "parser.y"
    { (yyval.expr) = ast_expr_call((yyvsp[(1) - (4)].sval), (yyvsp[(3) - (4)].alist).arr, (yyvsp[(3) - (4)].alist).count, yylineno); ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 569 "parser.y"
    { (yyval.expr) = ast_expr_call((yyvsp[(1) - (3)].sval), NULL, 0, yylineno); ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 574 "parser.y"
    { (yyval.alist).arr = (AstExpr**)malloc(sizeof(AstExpr*));
      (yyval.alist).arr[0] = (yyvsp[(1) - (1)].expr); (yyval.alist).count = 1; ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 577 "parser.y"
    { (yyval.alist) = (yyvsp[(1) - (3)].alist);
      (yyval.alist).arr = (AstExpr**)realloc((yyval.alist).arr,
                  ((yyval.alist).count + 1) * sizeof(AstExpr*));
      (yyval.alist).arr[(yyval.alist).count++] = (yyvsp[(3) - (3)].expr); ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 585 "parser.y"
    { (yyval.node) = ast_stmt_return((yyvsp[(2) - (2)].expr), yylineno); ;}
    break;



/* Line 1455 of yacc.c  */
#line 2395 "parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 588 "parser.y"


/* ================================================================
   ERROR HANDLER
   ================================================================ */

void yyerror(const char* s) {
  fprintf(stderr, "PARSE_ERROR at line %d: %s\n", yylineno, s);
}

