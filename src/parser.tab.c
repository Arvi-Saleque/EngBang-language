
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
#line 223 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 235 "parser.tab.c"

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
#define YYLAST   263

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  100
/* YYNRULES -- Number of states.  */
#define YYNSTATES  215

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   301

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
      45,    46
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    12,    15,    18,    21,
      24,    27,    30,    33,    35,    37,    40,    43,    46,    48,
      50,    52,    54,    56,    58,    60,    62,    64,    66,    70,
      74,    78,    82,    86,    88,    94,   102,   108,   116,   123,
     130,   139,   148,   152,   160,   166,   169,   173,   176,   177,
     180,   181,   183,   187,   193,   195,   199,   203,   205,   208,
     212,   213,   215,   217,   221,   223,   225,   227,   229,   231,
     233,   235,   237,   241,   251,   255,   261,   265,   268,   271,
     273,   277,   280,   283,   286,   289,   292,   295,   298,   301,
     303,   305,   315,   324,   326,   330,   334,   339,   343,   345,
     349
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      48,     0,    -1,    49,    -1,    -1,    49,    50,    -1,    54,
      21,    -1,    55,    21,    -1,    56,    21,    -1,    57,    21,
      -1,    58,    21,    -1,    59,    21,    -1,    60,    21,    -1,
      61,    21,    -1,    74,    -1,    79,    -1,    84,    21,    -1,
      12,    21,    -1,    14,    21,    -1,    16,    -1,    17,    -1,
      18,    -1,    19,    -1,    53,    -1,    42,    -1,    43,    -1,
      46,    -1,    44,    -1,    45,    -1,    53,    30,    53,    -1,
      53,    31,    53,    -1,    53,    32,    53,    -1,    53,    33,
      53,    -1,    28,    53,    29,    -1,    82,    -1,    52,     3,
      45,    20,    51,    -1,    54,     7,    52,     3,    45,    20,
      51,    -1,     6,     3,    45,    20,    51,    -1,    55,     7,
       6,     3,    45,    20,    51,    -1,    52,     5,     3,    45,
      20,    51,    -1,     6,     5,     3,    45,    20,    51,    -1,
      56,     7,    52,     5,     3,    45,    20,    51,    -1,    56,
       7,     6,     5,     3,    45,    20,    51,    -1,    52,     4,
      45,    -1,    52,     9,    51,     3,    45,    20,    51,    -1,
      52,     9,    51,     4,    45,    -1,     8,    52,    -1,    65,
      62,    63,    -1,    61,    21,    -1,    -1,    62,    65,    -1,
      -1,    64,    -1,    24,    25,    73,    -1,    66,    22,    68,
      73,    23,    -1,    67,    -1,    66,     7,    67,    -1,    45,
      20,    52,    -1,    69,    -1,    68,    69,    -1,    24,    70,
      25,    -1,    -1,    71,    -1,    72,    -1,    71,    26,    72,
      -1,    34,    -1,    35,    -1,    36,    -1,    37,    -1,    38,
      -1,    39,    -1,    40,    -1,    41,    -1,    22,    49,    23,
      -1,    24,    75,    26,    76,    25,    22,    49,    77,    23,
      -1,    45,    20,    52,    -1,    45,    20,    52,    20,    51,
      -1,    45,    20,    52,    -1,    45,    10,    -1,    45,    11,
      -1,    12,    -1,    45,    13,    78,    -1,    30,    42,    -1,
      31,    42,    -1,    32,    42,    -1,    33,    42,    -1,    30,
      43,    -1,    31,    43,    -1,    32,    43,    -1,    33,    43,
      -1,    42,    -1,    43,    -1,    45,    28,    80,    29,    20,
      51,    22,    49,    23,    -1,    45,    28,    29,    20,    51,
      22,    49,    23,    -1,    81,    -1,    80,    26,    81,    -1,
      45,    20,    51,    -1,    45,    28,    83,    29,    -1,    45,
      28,    29,    -1,    53,    -1,    83,    26,    53,    -1,    15,
      53,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   139,   139,   145,   146,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   171,   172,
     173,   174,   183,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   211,   215,   227,   231,   244,   248,
     252,   257,   273,   288,   299,   314,   332,   342,   348,   349,
     359,   360,   368,   377,   390,   396,   406,   418,   424,   434,
     440,   441,   446,   451,   460,   461,   462,   463,   464,   465,
     466,   467,   475,   487,   499,   501,   506,   511,   512,   513,
     514,   520,   521,   522,   523,   524,   525,   526,   527,   528,
     533,   545,   547,   552,   555,   563,   568,   570,   575,   578,
     586
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "KW_RAKHO", "KW_BODLAO", "KW_PAKKA",
  "KW_KHAALI", "KW_AR", "KW_BOLO", "KW_BANAW", "KW_BARBE", "KW_KOMABE",
  "KW_THAMO", "KW_PORIBORTON_BY", "KW_AGAO", "KW_FERAO", "TYPE_INT",
  "TYPE_FLOAT", "TYPE_STR", "TYPE_BOOL", "ARROW", "PIPE", "LBRACE",
  "RBRACE", "LBRACKET", "RBRACKET", "COMMA", "EQUALS", "LPAREN", "RPAREN",
  "PLUS", "MINUS", "STAR", "SLASH", "COND_GE", "COND_LE", "COND_EQ",
  "COND_NEQ", "COND_GT", "COND_LT", "COND_SKIP", "COND_UNKNOWN", "INT",
  "FLOAT", "STRING", "ID", "BOOL", "$accept", "program", "stmt_list",
  "stmt", "type", "value", "expr", "var_decl", "default_decl",
  "const_decl", "update_stmt", "cast_decl", "cast_update", "print_stmt",
  "cond_chain", "else_if_list", "else_block_opt", "else_block",
  "cond_block", "bindings", "binding", "group_list", "group",
  "cond_items_opt", "cond_items", "cond_item", "block", "loop_stmt",
  "loop_init", "loop_end", "loop_ctrl", "loop_step", "func_decl",
  "param_list", "param", "func_call", "arg_list", "return_stmt", 0
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
     295,   296,   297,   298,   299,   300,   301
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    47,    48,    49,    49,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    51,    51,
      51,    51,    52,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    54,    54,    55,    55,    56,    56,
      56,    56,    57,    58,    59,    60,    61,    61,    62,    62,
      63,    63,    64,    65,    66,    66,    67,    68,    68,    69,
      70,    70,    71,    71,    72,    72,    72,    72,    72,    72,
      72,    72,    73,    74,    75,    75,    76,    77,    77,    77,
      77,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    79,    79,    80,    80,    81,    82,    82,    83,    83,
      84
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     1,     1,     2,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     1,     5,     7,     5,     7,     6,     6,
       8,     8,     3,     7,     5,     2,     3,     2,     0,     2,
       0,     1,     3,     5,     1,     3,     3,     1,     2,     3,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     9,     3,     5,     3,     2,     2,     1,
       3,     2,     2,     2,     2,     2,     2,     2,     2,     1,
       1,     9,     8,     1,     3,     3,     4,     3,     1,     3,
       2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     2,     1,     0,     0,     0,     0,     0,     0,
       0,    23,    24,    26,    27,    25,     4,     0,    22,     0,
       0,     0,     0,     0,     0,     0,     0,    48,     0,    54,
      13,    14,    33,     0,     0,     0,    27,    45,    16,    17,
     100,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     5,     0,     6,     0,     7,
       8,     9,    10,    11,    12,    50,     0,     0,    15,     0,
       0,     0,     0,     0,    32,    56,    97,    27,    98,     0,
      93,     0,     0,    42,     0,    18,    19,    20,    21,     0,
      28,    29,    30,    31,     0,     0,     0,     0,     0,     0,
      46,    51,    49,    55,    60,     0,    57,     0,     0,    97,
      74,     0,     0,     0,     0,     0,     0,     0,    96,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    64,    65,
      66,    67,    68,    69,    70,    71,     0,    61,    62,     3,
      58,     0,    36,     0,     0,     0,     0,     0,    95,     0,
      94,     0,    99,    34,     0,     0,    44,     0,     0,     0,
       0,    52,    59,     0,     0,    53,    39,    75,    76,     3,
       3,     0,    38,     0,     0,     0,     0,     0,    63,    72,
       0,     0,     3,    43,    35,    37,     0,     0,    79,    27,
       0,    92,     0,    41,    40,    77,    78,     0,    73,    91,
       0,     0,     0,     0,    89,    90,    80,    81,    85,    82,
      86,    83,    87,    84,    88
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    16,    89,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    65,   100,   101,    27,    28,
      29,   105,   106,   136,   137,   138,   141,    30,    42,   112,
     190,   206,    31,    79,    80,    32,    81,    33
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -115
static const yytype_int16 yypact[] =
{
    -115,     9,   141,  -115,    96,    45,    -6,     3,    45,   -26,
      45,  -115,  -115,  -115,   -14,  -115,  -115,    73,   196,     0,
       1,    29,    16,    21,    26,    33,    37,  -115,    -2,  -115,
    -115,  -115,  -115,    71,    24,   100,    85,  -115,  -115,  -115,
     196,   108,    97,   192,    45,   -16,    86,    94,   140,   214,
      45,    45,    45,    45,    45,  -115,   142,  -115,   152,  -115,
    -115,  -115,  -115,  -115,   129,   -22,   106,   128,  -115,   134,
     112,   -11,    45,   114,  -115,  -115,   146,    32,   196,    76,
    -115,    93,   147,  -115,   123,  -115,  -115,  -115,  -115,    58,
      48,    48,  -115,  -115,   168,   170,   172,   176,   149,   155,
    -115,  -115,  -115,  -115,   179,   103,  -115,   214,   162,  -115,
     171,   173,   165,   214,   214,   144,   183,    45,  -115,   214,
     184,   160,   189,   190,   191,   234,   235,   217,  -115,  -115,
    -115,  -115,  -115,  -115,  -115,  -115,   215,   216,  -115,  -115,
    -115,   218,  -115,   214,   214,    45,   221,   222,  -115,   225,
    -115,   214,   196,  -115,   214,   226,  -115,   227,   228,   204,
     205,  -115,  -115,   179,    51,  -115,  -115,  -115,  -115,  -115,
    -115,   229,  -115,   214,   214,   214,   232,   233,  -115,  -115,
     164,    92,  -115,  -115,  -115,  -115,   214,   214,    -6,   101,
     231,  -115,   118,  -115,  -115,  -115,  -115,   169,  -115,  -115,
      43,    66,    75,   102,  -115,  -115,  -115,  -115,  -115,  -115,
    -115,  -115,  -115,  -115,  -115
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -115,  -115,  -114,  -115,  -103,    -5,    -7,  -115,  -115,  -115,
    -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,   193,  -115,
     194,  -115,   150,  -115,  -115,    98,   130,  -115,  -115,  -115,
    -115,  -115,  -115,  -115,   148,  -115,  -115,  -115
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -48
static const yytype_int16 yytable[] =
{
      37,    40,    98,    43,   142,    66,    44,    54,    56,     3,
     147,   148,    10,    76,    45,    38,   153,    10,   109,    41,
      67,    55,    57,    99,    39,   164,    11,    12,    13,    77,
      15,    11,    12,    13,    36,    15,    58,    60,    78,    75,
     166,   167,    61,    90,    91,    92,    93,    62,   171,    94,
      59,   172,   114,    97,    63,   180,   181,     4,    64,     5,
      71,   121,   122,     6,    78,     7,     8,   110,   192,    69,
     183,   184,   185,    10,   179,     9,    46,    47,    48,    10,
      52,    53,    49,   193,   194,   207,   208,    11,    12,    13,
      36,    15,    68,    11,    12,    13,    14,    15,     4,    34,
       5,    35,   115,    70,     6,   116,     7,     8,   209,   210,
     152,   195,   196,    71,   197,   191,     9,   211,   212,   117,
      10,    44,   118,    73,     4,   139,     5,   104,    72,    45,
       6,    82,     7,     8,    11,    12,    13,    14,    15,    83,
     168,   199,     9,    84,   213,   214,    10,     4,    95,     5,
     -47,    99,   104,     6,   107,     7,     8,   108,    96,   111,
      11,    12,    13,    14,    15,     9,   113,   119,   120,    10,
       4,   123,     5,   124,   127,    44,   188,   125,     7,     8,
      10,   126,   143,    11,    12,    13,    14,    15,     9,   149,
     146,   144,    10,   145,    11,    12,    13,    36,    15,   200,
     201,   202,   203,   151,   154,   155,    11,    12,    13,   189,
      15,   204,   205,   128,   129,   130,   131,   132,   133,   134,
     135,    74,    50,    51,    52,    53,    50,    51,    52,    53,
      85,    86,    87,    88,   156,   157,   158,   159,   160,   139,
     162,   165,   163,   169,   170,   114,   173,   174,   175,   176,
     177,   182,   186,   187,   198,   140,     0,   161,   102,     0,
     103,   178,     0,   150
};

static const yytype_int16 yycheck[] =
{
       5,     8,    24,    10,   107,     7,    20,     7,     7,     0,
     113,   114,    28,    29,    28,    21,   119,    28,    29,    45,
      22,    21,    21,    45,    21,   139,    42,    43,    44,    45,
      46,    42,    43,    44,    45,    46,     7,    21,    45,    44,
     143,   144,    21,    50,    51,    52,    53,    21,   151,    54,
      21,   154,    20,    58,    21,   169,   170,     6,    21,     8,
      28,     3,     4,    12,    71,    14,    15,    72,   182,    45,
     173,   174,   175,    28,    23,    24,     3,     4,     5,    28,
      32,    33,     9,   186,   187,    42,    43,    42,    43,    44,
      45,    46,    21,    42,    43,    44,    45,    46,     6,     3,
       8,     5,    26,     3,    12,    29,    14,    15,    42,    43,
     117,    10,    11,    28,    13,    23,    24,    42,    43,    26,
      28,    20,    29,    26,     6,    22,     8,    24,    20,    28,
      12,    45,    14,    15,    42,    43,    44,    45,    46,    45,
     145,    23,    24,     3,    42,    43,    28,     6,     6,     8,
      21,    45,    24,    12,    20,    14,    15,    45,     6,    45,
      42,    43,    44,    45,    46,    24,    20,    20,    45,    28,
       6,     3,     8,     3,    25,    20,    12,     5,    14,    15,
      28,     5,    20,    42,    43,    44,    45,    46,    24,    45,
      25,    20,    28,    20,    42,    43,    44,    45,    46,    30,
      31,    32,    33,    20,    20,    45,    42,    43,    44,    45,
      46,    42,    43,    34,    35,    36,    37,    38,    39,    40,
      41,    29,    30,    31,    32,    33,    30,    31,    32,    33,
      16,    17,    18,    19,    45,    45,    45,     3,     3,    22,
      25,    23,    26,    22,    22,    20,    20,    20,    20,    45,
      45,    22,    20,    20,    23,   105,    -1,   127,    65,    -1,
      66,   163,    -1,   115
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    48,    49,     0,     6,     8,    12,    14,    15,    24,
      28,    42,    43,    44,    45,    46,    50,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    65,    66,    67,
      74,    79,    82,    84,     3,     5,    45,    52,    21,    21,
      53,    45,    75,    53,    20,    28,     3,     4,     5,     9,
      30,    31,    32,    33,     7,    21,     7,    21,     7,    21,
      21,    21,    21,    21,    21,    62,     7,    22,    21,    45,
       3,    28,    20,    26,    29,    52,    29,    45,    53,    80,
      81,    83,    45,    45,     3,    16,    17,    18,    19,    51,
      53,    53,    53,    53,    52,     6,     6,    52,    24,    45,
      63,    64,    65,    67,    24,    68,    69,    20,    45,    29,
      52,    45,    76,    20,    20,    26,    29,    26,    29,    20,
      45,     3,     4,     3,     3,     5,     5,    25,    34,    35,
      36,    37,    38,    39,    40,    41,    70,    71,    72,    22,
      69,    73,    51,    20,    20,    20,    25,    51,    51,    45,
      81,    20,    53,    51,    20,    45,    45,    45,    45,     3,
       3,    73,    25,    26,    49,    23,    51,    51,    52,    22,
      22,    51,    51,    20,    20,    20,    45,    45,    72,    23,
      49,    49,    22,    51,    51,    51,    20,    20,    12,    45,
      77,    23,    49,    51,    51,    10,    11,    13,    23,    23,
      30,    31,    32,    33,    42,    43,    78,    42,    43,    42,
      43,    42,    43,    42,    43
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
#line 162 "parser.y"
    { (yyval.node) = ast_stmt_break(yylineno); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 163 "parser.y"
    { (yyval.node) = ast_stmt_continue(yylineno); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 171 "parser.y"
    { (yyval.tval) = T_INT; ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 172 "parser.y"
    { (yyval.tval) = T_FLOAT; ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 173 "parser.y"
    { (yyval.tval) = T_STR; ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 174 "parser.y"
    { (yyval.tval) = T_BOOL; ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 183 "parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 187 "parser.y"
    { (yyval.expr) = ast_expr_int((yyvsp[(1) - (1)].ival), yylineno); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 188 "parser.y"
    { (yyval.expr) = ast_expr_float((yyvsp[(1) - (1)].fval), yylineno); ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 189 "parser.y"
    { (yyval.expr) = ast_expr_bool((int)(yyvsp[(1) - (1)].ival), yylineno); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 190 "parser.y"
    { (yyval.expr) = ast_expr_str((yyvsp[(1) - (1)].sval), yylineno); /* takes ownership, strips quotes */ ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 191 "parser.y"
    { (yyval.expr) = ast_expr_id((yyvsp[(1) - (1)].sval), yylineno);  /* takes ownership */ ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 192 "parser.y"
    { (yyval.expr) = ast_expr_binop(BINOP_ADD, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), yylineno); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 193 "parser.y"
    { (yyval.expr) = ast_expr_binop(BINOP_SUB, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), yylineno); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 194 "parser.y"
    { (yyval.expr) = ast_expr_binop(BINOP_MUL, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), yylineno); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 195 "parser.y"
    { (yyval.expr) = ast_expr_binop(BINOP_DIV, (yyvsp[(1) - (3)].expr), (yyvsp[(3) - (3)].expr), yylineno); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 196 "parser.y"
    { (yyval.expr) = (yyvsp[(2) - (3)].expr); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 197 "parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 212 "parser.y"
    {
      (yyval.node) = ast_stmt_decl((yyvsp[(3) - (5)].sval), (Type)(yyvsp[(5) - (5)].tval), (yyvsp[(1) - (5)].expr), 0, yylineno);
    ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 216 "parser.y"
    {
      AstNode* more = ast_stmt_decl((yyvsp[(5) - (7)].sval), (Type)(yyvsp[(7) - (7)].tval), (yyvsp[(3) - (7)].expr), 0, yylineno);
      (yyval.node) = ast_list_concat((yyvsp[(1) - (7)].node), more);
    ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 228 "parser.y"
    {
      (yyval.node) = ast_stmt_default_decl((yyvsp[(3) - (5)].sval), (Type)(yyvsp[(5) - (5)].tval), 0, yylineno);
    ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 232 "parser.y"
    {
      AstNode* more = ast_stmt_default_decl((yyvsp[(5) - (7)].sval), (Type)(yyvsp[(7) - (7)].tval), 0, yylineno);
      (yyval.node) = ast_list_concat((yyvsp[(1) - (7)].node), more);
    ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 245 "parser.y"
    {
      (yyval.node) = ast_stmt_decl((yyvsp[(4) - (6)].sval), (Type)(yyvsp[(6) - (6)].tval), (yyvsp[(1) - (6)].expr), 1, yylineno);
    ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 249 "parser.y"
    {
      (yyval.node) = ast_stmt_default_decl((yyvsp[(4) - (6)].sval), (Type)(yyvsp[(6) - (6)].tval), 1, yylineno);
    ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 253 "parser.y"
    {
      AstNode* more = ast_stmt_decl((yyvsp[(6) - (8)].sval), (Type)(yyvsp[(8) - (8)].tval), (yyvsp[(3) - (8)].expr), 1, yylineno);
      (yyval.node) = ast_list_concat((yyvsp[(1) - (8)].node), more);
    ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 258 "parser.y"
    {
      AstNode* more = ast_stmt_default_decl((yyvsp[(6) - (8)].sval), (Type)(yyvsp[(8) - (8)].tval), 1, yylineno);
      (yyval.node) = ast_list_concat((yyvsp[(1) - (8)].node), more);
    ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 274 "parser.y"
    {
      (yyval.node) = ast_stmt_update((yyvsp[(3) - (3)].sval), (yyvsp[(1) - (3)].expr), yylineno);
    ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 289 "parser.y"
    {
      (yyval.node) = ast_stmt_cast_decl((yyvsp[(5) - (7)].sval), (Type)(yyvsp[(3) - (7)].tval), (Type)(yyvsp[(7) - (7)].tval), (yyvsp[(1) - (7)].expr), yylineno);
    ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 300 "parser.y"
    {
      (yyval.node) = ast_stmt_cast_update((yyvsp[(5) - (5)].sval), (Type)(yyvsp[(3) - (5)].tval), (yyvsp[(1) - (5)].expr), yylineno);
    ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 315 "parser.y"
    {
      (yyval.node) = ast_stmt_print((yyvsp[(2) - (2)].expr), yylineno);
    ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 333 "parser.y"
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

  case 47:

/* Line 1455 of yacc.c  */
#line 343 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 348 "parser.y"
    { (yyval.cblist).arr = NULL; (yyval.cblist).count = 0; ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 350 "parser.y"
    {
      (yyval.cblist) = (yyvsp[(1) - (2)].cblist);
      (yyval.cblist).arr = (AstCondBlock**)realloc((yyval.cblist).arr,
                  ((yyval.cblist).count + 1) * sizeof(AstCondBlock*));
      (yyval.cblist).arr[(yyval.cblist).count++] = (yyvsp[(2) - (2)].cblock);
    ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 359 "parser.y"
    { (yyval.node) = NULL; ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 360 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node);   ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 369 "parser.y"
    { (yyval.node) = (yyvsp[(3) - (3)].node); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 378 "parser.y"
    {
      (yyval.cblock) = ast_cond_block_new((yyvsp[(1) - (5)].blist).arr, (yyvsp[(1) - (5)].blist).count,
                               (yyvsp[(3) - (5)].glist).arr, (yyvsp[(3) - (5)].glist).count,
                               (yyvsp[(4) - (5)].node));
    ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 391 "parser.y"
    {
      (yyval.blist).arr = (AstBinding*)malloc(sizeof(AstBinding));
      (yyval.blist).arr[0] = (yyvsp[(1) - (1)].bindi);
      (yyval.blist).count = 1;
    ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 397 "parser.y"
    {
      (yyval.blist) = (yyvsp[(1) - (3)].blist);
      (yyval.blist).arr = (AstBinding*)realloc((yyval.blist).arr,
                    ((yyval.blist).count + 1) * sizeof(AstBinding));
      (yyval.blist).arr[(yyval.blist).count++] = (yyvsp[(3) - (3)].bindi);
    ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 407 "parser.y"
    {
      (yyval.bindi).id   = (yyvsp[(1) - (3)].sval);   /* take ownership of the lexer string */
      (yyval.bindi).expr = (yyvsp[(3) - (3)].expr);   /* take ownership of the expr node    */
    ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 419 "parser.y"
    {
      (yyval.glist).arr = (AstCondGroup*)malloc(sizeof(AstCondGroup));
      (yyval.glist).arr[0] = (yyvsp[(1) - (1)].cgroup);
      (yyval.glist).count = 1;
    ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 425 "parser.y"
    {
      (yyval.glist) = (yyvsp[(1) - (2)].glist);
      (yyval.glist).arr = (AstCondGroup*)realloc((yyval.glist).arr,
                    ((yyval.glist).count + 1) * sizeof(AstCondGroup));
      (yyval.glist).arr[(yyval.glist).count++] = (yyvsp[(2) - (2)].cgroup);
    ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 435 "parser.y"
    { (yyval.cgroup) = (yyvsp[(2) - (3)].cgroup); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 440 "parser.y"
    { (yyval.cgroup).count = 0; ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 442 "parser.y"
    { (yyval.cgroup) = (yyvsp[(1) - (1)].cgroup); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 447 "parser.y"
    {
      (yyval.cgroup).count  = 1;
      (yyval.cgroup).ops[0] = (CondOp)(yyvsp[(1) - (1)].condop);
    ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 452 "parser.y"
    {
      (yyval.cgroup) = (yyvsp[(1) - (3)].cgroup);
      if ((yyval.cgroup).count < MAX_COND_OPS)
        (yyval.cgroup).ops[(yyval.cgroup).count++] = (CondOp)(yyvsp[(3) - (3)].condop);
    ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 460 "parser.y"
    { (yyval.condop) = CONDOP_GE;   ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 461 "parser.y"
    { (yyval.condop) = CONDOP_LE;   ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 462 "parser.y"
    { (yyval.condop) = CONDOP_EQ;   ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 463 "parser.y"
    { (yyval.condop) = CONDOP_NEQ;  ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 464 "parser.y"
    { (yyval.condop) = CONDOP_GT;   ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 465 "parser.y"
    { (yyval.condop) = CONDOP_LT;   ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 466 "parser.y"
    { (yyval.condop) = CONDOP_SKIP; ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 467 "parser.y"
    { (yyval.condop) = CONDOP_SKIP; free((yyvsp[(1) - (1)].sval)); ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 476 "parser.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 488 "parser.y"
    {
      /* Ownership of $4.var and $8.var transfers into the AST node
         so semantic.c can validate variable name consistency. */
      (yyval.node) = ast_stmt_loop((yyvsp[(2) - (9)].lact).var, (yyvsp[(2) - (9)].lact).is_new, (Type)(yyvsp[(2) - (9)].lact).new_type, (yyvsp[(2) - (9)].lact).init,
                          (yyvsp[(4) - (9)].lend).var, (yyvsp[(4) - (9)].lend).end,
                          (yyvsp[(8) - (9)].lctrl).var, (LoopStep)(yyvsp[(8) - (9)].lctrl).step, (yyvsp[(8) - (9)].lctrl).step_op, (yyvsp[(8) - (9)].lctrl).step_expr,
                          (yyvsp[(7) - (9)].node), yylineno);
    ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 500 "parser.y"
    { (yyval.lact).var = (yyvsp[(1) - (3)].sval); (yyval.lact).is_new = 0; (yyval.lact).new_type = T_UNKNOWN; (yyval.lact).init = (yyvsp[(3) - (3)].expr); ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 502 "parser.y"
    { (yyval.lact).var = (yyvsp[(1) - (5)].sval); (yyval.lact).is_new = 1; (yyval.lact).new_type = (yyvsp[(5) - (5)].tval); (yyval.lact).init = (yyvsp[(3) - (5)].expr); ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 507 "parser.y"
    { (yyval.lend).var = (yyvsp[(1) - (3)].sval); (yyval.lend).end = (yyvsp[(3) - (3)].expr); ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 511 "parser.y"
    { (yyval.lctrl).var = (yyvsp[(1) - (2)].sval); (yyval.lctrl).step = LOOP_INC; (yyval.lctrl).step_op = 0; (yyval.lctrl).step_expr = NULL; ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 512 "parser.y"
    { (yyval.lctrl).var = (yyvsp[(1) - (2)].sval); (yyval.lctrl).step = LOOP_DEC; (yyval.lctrl).step_op = 0; (yyval.lctrl).step_expr = NULL; ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 513 "parser.y"
    { (yyval.lctrl).var = NULL; (yyval.lctrl).step = LOOP_STOP; (yyval.lctrl).step_op = 0; (yyval.lctrl).step_expr = NULL; ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 515 "parser.y"
    { (yyval.lctrl).var = (yyvsp[(1) - (3)].sval); (yyval.lctrl).step = LOOP_CUSTOM;
                   (yyval.lctrl).step_op = (yyvsp[(3) - (3)].lstep).step_op; (yyval.lctrl).step_expr = (yyvsp[(3) - (3)].lstep).step_expr; ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 520 "parser.y"
    { (yyval.lstep).step_op = '+'; (yyval.lstep).step_expr = ast_expr_int((yyvsp[(2) - (2)].ival),   yylineno); ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 521 "parser.y"
    { (yyval.lstep).step_op = '-'; (yyval.lstep).step_expr = ast_expr_int((yyvsp[(2) - (2)].ival),   yylineno); ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 522 "parser.y"
    { (yyval.lstep).step_op = '*'; (yyval.lstep).step_expr = ast_expr_int((yyvsp[(2) - (2)].ival),   yylineno); ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 523 "parser.y"
    { (yyval.lstep).step_op = '/'; (yyval.lstep).step_expr = ast_expr_int((yyvsp[(2) - (2)].ival),   yylineno); ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 524 "parser.y"
    { (yyval.lstep).step_op = '+'; (yyval.lstep).step_expr = ast_expr_float((yyvsp[(2) - (2)].fval), yylineno); ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 525 "parser.y"
    { (yyval.lstep).step_op = '-'; (yyval.lstep).step_expr = ast_expr_float((yyvsp[(2) - (2)].fval), yylineno); ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 526 "parser.y"
    { (yyval.lstep).step_op = '*'; (yyval.lstep).step_expr = ast_expr_float((yyvsp[(2) - (2)].fval), yylineno); ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 527 "parser.y"
    { (yyval.lstep).step_op = '/'; (yyval.lstep).step_expr = ast_expr_float((yyvsp[(2) - (2)].fval), yylineno); ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 529 "parser.y"
    { /* handles lexer-embedded sign, e.g. -2 tokenised as INT(-2) */
      if ((yyvsp[(1) - (1)].ival) < 0) { (yyval.lstep).step_op = '-'; (yyval.lstep).step_expr = ast_expr_int(-(yyvsp[(1) - (1)].ival), yylineno); }
      else        { (yyval.lstep).step_op = '+'; (yyval.lstep).step_expr = ast_expr_int((yyvsp[(1) - (1)].ival),  yylineno); }
    ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 534 "parser.y"
    { if ((yyvsp[(1) - (1)].fval) < 0.0) { (yyval.lstep).step_op = '-'; (yyval.lstep).step_expr = ast_expr_float(-(yyvsp[(1) - (1)].fval), yylineno); }
      else          { (yyval.lstep).step_op = '+'; (yyval.lstep).step_expr = ast_expr_float((yyvsp[(1) - (1)].fval),  yylineno); }
    ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 546 "parser.y"
    { (yyval.node) = ast_stmt_func_def((yyvsp[(1) - (9)].sval), (Type)(yyvsp[(6) - (9)].tval), (yyvsp[(3) - (9)].plist).arr, (yyvsp[(3) - (9)].plist).count, (yyvsp[(8) - (9)].node), yylineno); ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 548 "parser.y"
    { (yyval.node) = ast_stmt_func_def((yyvsp[(1) - (8)].sval), (Type)(yyvsp[(5) - (8)].tval), NULL, 0, (yyvsp[(7) - (8)].node), yylineno); ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 553 "parser.y"
    { (yyval.plist).arr = (FuncParamNode*)malloc(sizeof(FuncParamNode));
      (yyval.plist).arr[0] = (yyvsp[(1) - (1)].fparam); (yyval.plist).count = 1; ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 556 "parser.y"
    { (yyval.plist) = (yyvsp[(1) - (3)].plist);
      (yyval.plist).arr = (FuncParamNode*)realloc((yyval.plist).arr,
                  ((yyval.plist).count + 1) * sizeof(FuncParamNode));
      (yyval.plist).arr[(yyval.plist).count++] = (yyvsp[(3) - (3)].fparam); ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 564 "parser.y"
    { (yyval.fparam).name = (yyvsp[(1) - (3)].sval); (yyval.fparam).type = (Type)(yyvsp[(3) - (3)].tval); ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 569 "parser.y"
    { (yyval.expr) = ast_expr_call((yyvsp[(1) - (4)].sval), (yyvsp[(3) - (4)].alist).arr, (yyvsp[(3) - (4)].alist).count, yylineno); ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 571 "parser.y"
    { (yyval.expr) = ast_expr_call((yyvsp[(1) - (3)].sval), NULL, 0, yylineno); ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 576 "parser.y"
    { (yyval.alist).arr = (AstExpr**)malloc(sizeof(AstExpr*));
      (yyval.alist).arr[0] = (yyvsp[(1) - (1)].expr); (yyval.alist).count = 1; ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 579 "parser.y"
    { (yyval.alist) = (yyvsp[(1) - (3)].alist);
      (yyval.alist).arr = (AstExpr**)realloc((yyval.alist).arr,
                  ((yyval.alist).count + 1) * sizeof(AstExpr*));
      (yyval.alist).arr[(yyval.alist).count++] = (yyvsp[(3) - (3)].expr); ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 587 "parser.y"
    { (yyval.node) = ast_stmt_return((yyvsp[(2) - (2)].expr), yylineno); ;}
    break;



/* Line 1455 of yacc.c  */
#line 2417 "parser.tab.c"
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
#line 590 "parser.y"


/* ================================================================
   ERROR HANDLER
   ================================================================ */

void yyerror(const char* s) {
  fprintf(stderr, "PARSE_ERROR at line %d: %s\n", yylineno, s);
}

