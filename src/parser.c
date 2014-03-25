/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "parser.y"

	#define YYERROR_VERBOSE
	#define YYDEBUG 1

	#include <stdio.h>
	#include <stdlib.h>


	#include "variableOp.h"
	#include "operation.h"
	#include "unit.h"
	#include "debug.h"

	#include "hash/hash.h"
	#include "init/params.h"
	#include "constant.h"

	#include "parser.h"

	// Valeurs externes
	extern char* yytext;
	extern FILE* yyin;
	extern int yylineno;

	// Prototypes
	int yylex(void);
	int yyerror(const char *s);

	// Affichage erreur
	void beginToken(const char *t);
	void beginTokenNewLine();

	// Context courant pour le mode interactif
	Exec_context ec_tmp, ec_obj;
	Variable r_base, *r;
	
	// Variables locales
	static int goodbye = 0;

	static int tokenStart = 0;
	static int tokenLength = 0;


/* Line 371 of yacc.c  */
#line 112 "parser.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUMBER = 258,
     BOOL = 259,
     PLUS = 260,
     MINUS = 261,
     STAR = 262,
     SLASH = 263,
     DIV = 264,
     POW = 265,
     EQUAL = 266,
     POINT = 267,
     ADDR = 268,
     MODULO = 269,
     MORE = 270,
     LESS = 271,
     MORE_E = 272,
     LESS_E = 273,
     AND = 274,
     OR = 275,
     NOT = 276,
     EXIST = 277,
     D_EQUAL = 278,
     T_EQUAL = 279,
     DIF = 280,
     P_LEFT = 281,
     P_RIGHT = 282,
     BRACE_LEFT = 283,
     BRACE_RIGHT = 284,
     COMMA = 285,
     VAR = 286,
     ATTR = 287,
     NEW = 288,
     DELETE = 289,
     IDENTIFIER = 290,
     FUNCTION = 291,
     DUMP = 292,
     EXPR_END = 293,
     BREAK = 294,
     RETURN = 295,
     POS = 296,
     NEG = 297,
     ADDR_ACCESS = 298
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 45 "parser.y"

  Unit* function;
  Linked_list* list;
  Operation* op;
  Unit *u;
  char *str;
  float value;
  char bool;


/* Line 387 of yacc.c  */
#line 209 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 237 "parser.tab.c"

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
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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

# define YYCOPY_NEEDED 1

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

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   417

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  9
/* YYNRULES -- Number of rules.  */
#define YYNRULES  55
/* YYNRULES -- Number of states.  */
#define YYNSTATES  104

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

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
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     7,    12,    18,    20,    24,    26,
      30,    34,    37,    39,    41,    44,    48,    50,    52,    56,
      60,    64,    68,    72,    76,    82,    87,    92,    96,    98,
     101,   104,   108,   112,   116,   120,   124,   128,   132,   135,
     138,   142,   146,   150,   154,   158,   162,   166,   170,   174,
     177,   180,   183,   185,   187,   190
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      45,     0,    -1,    -1,    45,    50,    -1,    36,    26,    27,
      49,    -1,    36,    26,    47,    27,    49,    -1,    35,    -1,
      47,    30,    35,    -1,    52,    -1,    48,    30,    52,    -1,
      28,    50,    29,    -1,    50,    51,    -1,    51,    -1,    38,
      -1,    52,    38,    -1,    52,    11,    52,    -1,     3,    -1,
       4,    -1,    52,    12,    35,    -1,    33,    31,    35,    -1,
      33,    32,    35,    -1,    34,    31,    35,    -1,    34,    32,
      35,    -1,    26,    52,    27,    -1,    33,    52,    26,    48,
      27,    -1,    33,    52,    26,    27,    -1,    52,    26,    48,
      27,    -1,    52,    26,    27,    -1,    35,    -1,    31,    35,
      -1,    32,    35,    -1,    52,    10,    52,    -1,    52,     5,
      52,    -1,    52,     6,    52,    -1,    52,     7,    52,    -1,
      52,     8,    52,    -1,    52,     9,    52,    -1,    52,    14,
      52,    -1,     6,    52,    -1,     5,    52,    -1,    52,    15,
      52,    -1,    52,    16,    52,    -1,    52,    17,    52,    -1,
      52,    18,    52,    -1,    52,    23,    52,    -1,    52,    24,
      52,    -1,    52,    25,    52,    -1,    52,    19,    52,    -1,
      52,    20,    52,    -1,    21,    52,    -1,    22,    52,    -1,
      40,    52,    -1,    40,    -1,    39,    -1,    37,    52,    -1,
      46,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    98,    98,   100,   122,   126,   134,   143,   156,   160,
     168,   175,   179,   187,   195,   252,   255,   259,   263,   268,
     273,   278,   283,   288,   291,   296,   299,   304,   307,   312,
     317,   322,   325,   328,   331,   334,   337,   340,   343,   346,
     349,   352,   355,   358,   361,   364,   367,   370,   373,   376,
     379,   382,   385,   388,   391,   394
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "BOOL", "PLUS", "MINUS",
  "STAR", "SLASH", "DIV", "POW", "EQUAL", "POINT", "ADDR", "MODULO",
  "MORE", "LESS", "MORE_E", "LESS_E", "AND", "OR", "NOT", "EXIST",
  "D_EQUAL", "T_EQUAL", "DIF", "P_LEFT", "P_RIGHT", "BRACE_LEFT",
  "BRACE_RIGHT", "COMMA", "VAR", "ATTR", "NEW", "DELETE", "IDENTIFIER",
  "FUNCTION", "DUMP", "EXPR_END", "BREAK", "RETURN", "POS", "NEG",
  "ADDR_ACCESS", "$accept", "Input", "Function", "Param_list",
  "Param_call_list", "Unit", "Statements", "Statement", "Expression", YY_NULL
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
     295,   296,   297,   298
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    45,    45,    46,    46,    47,    47,    48,    48,
      49,    50,    50,    51,    51,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     4,     5,     1,     3,     1,     3,
       3,     2,     1,     1,     2,     3,     1,     1,     3,     3,
       3,     3,     3,     3,     5,     4,     4,     3,     1,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     2,     1,     1,     2,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,    16,    17,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    28,     0,     0,    13,    53,    52,
      55,     3,    12,     0,    39,    38,    49,    50,     0,    29,
      30,     0,     0,     0,     0,     0,     0,    54,    51,    11,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    14,
      23,    19,    20,     0,    21,    22,     0,     6,     0,    32,
      33,    34,    35,    36,    31,    15,    18,    37,    40,    41,
      42,    43,    47,    48,    44,    45,    46,    27,     0,     8,
      25,     0,     0,     4,     0,     0,    26,     0,    24,     0,
       5,     7,     9,    10
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,    20,    68,    88,    93,    21,    22,    23
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -26
static const yytype_int16 yypact[] =
{
     -26,    63,   -26,   -26,   -26,   239,   239,   239,   239,   239,
     -25,    -8,   263,   -14,   -26,    -7,   239,   -26,   -26,   239,
     -26,   139,   -26,   299,    -6,    -6,    -6,    -6,   324,   -26,
     -26,    20,    25,   347,    26,    30,   -19,   369,   369,   -26,
     239,   239,   239,   239,   239,   239,   239,    41,   239,   239,
     239,   239,   239,   239,   239,   239,   239,   239,   163,   -26,
     -26,   -26,   -26,   201,   -26,   -26,    34,   -26,   -18,   102,
     102,     3,     3,     3,     3,   369,   -26,     3,    65,    65,
      65,    65,   391,   391,    16,    16,    16,   -26,    27,   369,
     -26,    29,   139,   -26,    34,    43,   -26,   239,   -26,   101,
     -26,   -26,   369,   -26
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -26,   -26,   -26,   -26,     1,   -13,   -12,   -16,    -5
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      24,    25,    26,    27,    28,    39,    47,    33,    66,    94,
      29,    37,    95,    45,    38,    47,    67,    34,    35,    36,
      58,    40,    41,    42,    43,    44,    45,    30,    47,    58,
      48,    49,    50,    51,    52,    69,    70,    71,    72,    73,
      74,    75,    58,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    89,    96,    61,    98,    97,    89,    97,
      62,    64,    92,     2,    91,    65,     3,     4,     5,     6,
      40,    41,    42,    43,    44,    45,    76,    47,   101,    48,
      99,   100,     0,    39,     7,     8,     0,     0,     0,     9,
       0,    58,   102,     0,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     3,     4,     5,     6,     0,    42,
      43,    44,    45,     0,    47,     0,    48,     0,     0,     0,
       0,     0,     7,     8,     0,     0,     0,     9,    58,     0,
     103,     0,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     3,     4,     5,     6,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       7,     8,     0,     0,     0,     9,     3,     4,     5,     6,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,     0,     0,     0,     7,     8,     0,     0,     0,     9,
      87,     0,     0,     0,    10,    11,    12,    13,    14,    15,
      16,     0,    18,    19,     3,     4,     5,     6,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     7,     8,     0,     0,     0,     9,    90,     0,
       0,     0,    10,    11,    12,    13,    14,    15,    16,     0,
      18,    19,     3,     4,     5,     6,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       7,     8,     0,     0,     0,     9,     3,     4,     5,     6,
      10,    11,    12,    13,    14,    15,    16,     0,    18,    19,
       0,     0,     0,     0,     7,     8,     0,     0,     0,     9,
       0,     0,     0,     0,    31,    32,    12,    13,    14,    15,
      16,     0,    18,    19,    40,    41,    42,    43,    44,    45,
      46,    47,     0,    48,    49,    50,    51,    52,    53,    54,
       0,     0,    55,    56,    57,    58,     0,     0,     0,    40,
      41,    42,    43,    44,    45,    46,    47,    59,    48,    49,
      50,    51,    52,    53,    54,     0,     0,    55,    56,    57,
      58,    60,    40,    41,    42,    43,    44,    45,    46,    47,
       0,    48,    49,    50,    51,    52,    53,    54,     0,     0,
      55,    56,    57,    63,    40,    41,    42,    43,    44,    45,
      46,    47,     0,    48,    49,    50,    51,    52,    53,    54,
       0,     0,    55,    56,    57,    58,    40,    41,    42,    43,
      44,    45,     0,    47,     0,    48,    49,    50,    51,    52,
       0,     0,     0,     0,    55,    56,    57,    58
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-26)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
       5,     6,     7,     8,     9,    21,    12,    12,    27,    27,
      35,    16,    30,    10,    19,    12,    35,    31,    32,    26,
      26,     5,     6,     7,     8,     9,    10,    35,    12,    26,
      14,    15,    16,    17,    18,    40,    41,    42,    43,    44,
      45,    46,    26,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    27,    35,    27,    30,    63,    30,
      35,    35,    28,     0,    63,    35,     3,     4,     5,     6,
       5,     6,     7,     8,     9,    10,    35,    12,    35,    14,
      92,    94,    -1,    99,    21,    22,    -1,    -1,    -1,    26,
      -1,    26,    97,    -1,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,     3,     4,     5,     6,    -1,     7,
       8,     9,    10,    -1,    12,    -1,    14,    -1,    -1,    -1,
      -1,    -1,    21,    22,    -1,    -1,    -1,    26,    26,    -1,
      29,    -1,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,     3,     4,     5,     6,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    22,    -1,    -1,    -1,    26,     3,     4,     5,     6,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      -1,    -1,    -1,    -1,    21,    22,    -1,    -1,    -1,    26,
      27,    -1,    -1,    -1,    31,    32,    33,    34,    35,    36,
      37,    -1,    39,    40,     3,     4,     5,     6,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,    22,    -1,    -1,    -1,    26,    27,    -1,
      -1,    -1,    31,    32,    33,    34,    35,    36,    37,    -1,
      39,    40,     3,     4,     5,     6,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    22,    -1,    -1,    -1,    26,     3,     4,     5,     6,
      31,    32,    33,    34,    35,    36,    37,    -1,    39,    40,
      -1,    -1,    -1,    -1,    21,    22,    -1,    -1,    -1,    26,
      -1,    -1,    -1,    -1,    31,    32,    33,    34,    35,    36,
      37,    -1,    39,    40,     5,     6,     7,     8,     9,    10,
      11,    12,    -1,    14,    15,    16,    17,    18,    19,    20,
      -1,    -1,    23,    24,    25,    26,    -1,    -1,    -1,     5,
       6,     7,     8,     9,    10,    11,    12,    38,    14,    15,
      16,    17,    18,    19,    20,    -1,    -1,    23,    24,    25,
      26,    27,     5,     6,     7,     8,     9,    10,    11,    12,
      -1,    14,    15,    16,    17,    18,    19,    20,    -1,    -1,
      23,    24,    25,    26,     5,     6,     7,     8,     9,    10,
      11,    12,    -1,    14,    15,    16,    17,    18,    19,    20,
      -1,    -1,    23,    24,    25,    26,     5,     6,     7,     8,
       9,    10,    -1,    12,    -1,    14,    15,    16,    17,    18,
      -1,    -1,    -1,    -1,    23,    24,    25,    26
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    45,     0,     3,     4,     5,     6,    21,    22,    26,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      46,    50,    51,    52,    52,    52,    52,    52,    52,    35,
      35,    31,    32,    52,    31,    32,    26,    52,    52,    51,
       5,     6,     7,     8,     9,    10,    11,    12,    14,    15,
      16,    17,    18,    19,    20,    23,    24,    25,    26,    38,
      27,    35,    35,    26,    35,    35,    27,    35,    47,    52,
      52,    52,    52,    52,    52,    52,    35,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    27,    48,    52,
      27,    48,    28,    49,    27,    30,    27,    30,    27,    50,
      49,    35,    52,    29
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
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




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

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

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  if (yypact_value_is_default (yyn))
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
      if (yytable_value_is_error (yyn))
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
        case 3:
/* Line 1792 of yacc.c  */
#line 100 "parser.y"
    {
			Unit u;
			u.args = NULL;
			u.operations = (yyvsp[(2) - (2)].list);

			p.end_parsing = clock();

			if(p.show_operation) {
				puts("[>] Result in memory :"), unit_dump(&u);
				fputs("[*] Press enter to eval", stdout);
				getchar();
			}

			if(p.show_timer)
				printf("[i] Parsed in %.4fs\n", ((p.end_parsing-p.start_parsing)/(double)CLOCKS_PER_SEC));

			eval_main(&u);
	  }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 122 "parser.y"
    {
	  	(yyval.function) = unit_new((yyvsp[(4) - (4)].list), NULL);
	  }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 126 "parser.y"
    {
	  	// A faire les paramètres
	  	(yyval.function) = unit_new((yyvsp[(5) - (5)].list), (yyvsp[(3) - (5)].list));
	  }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 134 "parser.y"
    {
		Variable *v = var_new(NULL, 0, T_NULL);
	  	v->name = (yyvsp[(1) - (1)].str);
	  	v->name_h = str_hash((yyvsp[(1) - (1)].str));
	  	v->deletable = 1;

		(yyval.list) = NULL;
		linked_list_append(&(yyval.list), (void*)v);
	  }
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 143 "parser.y"
    {
		Variable *v = var_new(NULL, 0, T_NULL);
	  	v->name = (yyvsp[(3) - (3)].str);
	  	v->name_h = str_hash((yyvsp[(3) - (3)].str));
	  	v->deletable = 1;

		linked_list_append(&(yyvsp[(1) - (3)].list), (void*)v);
		(yyval.list) = (yyvsp[(1) - (3)].list);
	  }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 156 "parser.y"
    {
		(yyval.list) = NULL;
		linked_list_append(&(yyval.list), (void*)(yyvsp[(1) - (1)].op));
	  }
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 160 "parser.y"
    {
		linked_list_append(&(yyvsp[(1) - (3)].list), (void*)(yyvsp[(3) - (3)].op));
		(yyval.list) = (yyvsp[(1) - (3)].list);
	  }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 168 "parser.y"
    {
		(yyval.list) = (yyvsp[(2) - (3)].list);
	  }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 175 "parser.y"
    {
	  	(yyval.list) = (yyvsp[(1) - (2)].list); // Il faut ajouter le statement à la liste des statement
	  	if((yyvsp[(2) - (2)].op)) linked_list_append(&(yyvsp[(1) - (2)].list), (void*)(yyvsp[(2) - (2)].op));
	  }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 179 "parser.y"
    {
		(yyval.list) = NULL; // Pas encore de liste, il faut la créer
	  	if((yyvsp[(1) - (1)].op)) linked_list_append(&(yyval.list), (void*)(yyvsp[(1) - (1)].op)); // On met notre statement dedans
	  }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 187 "parser.y"
    {
	  	if(p.interactive_mod) {
			puts("[!] Empty statement\n");
			beginTokenNewLine();
		} else {
			(yyval.op) = NULL;
		}
	  }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 195 "parser.y"
    {
	  	if(p.interactive_mod) {
			// Initialisation valeur retour
			var_init_loc(&r_base, NULL, 0, T_NULL);
			r_base.deletable = 0;
			r = &r_base;

			if(p.show_operation) {
				puts("[>] Result in memory :"), op_dump((yyvsp[(1) - (2)].op));
				fputs("[*] Press enter to eval", stdout);
				getchar();
			}

			// Evaluation
			puts("\n[<] Evaluating the operations ...");
			switch(op_eval((yyvsp[(1) - (2)].op), &ec_obj, &ec_tmp, &r)) {
				case RC_WARNING :
					err_display_last();
				case RC_BREAK :
				case RC_OK :
					break;
				case RC_ERROR :
					err_display_last();
					break;
				case RC_CRITICAL:
					err_display_last();
					printf("[x] Error, interpreter stopped with code %x \n", e.type);
					return e.type;
				case RC_RETURN :
					if(r->type == T_NUM)
						goodbye = (int)r->value.v_num;
					printf("[i] Interpreter stopped (%x) \n", goodbye);
					exit(goodbye);
				default:
					break;
			}

			puts("[<] Evaluation done");

			if(p.auto_dump) {
				puts("\n[>] Statement value :");
				var_dump(r);
			}

			// Suppression valeur temporaire
			var_delete(&r_base, 1);
			beginTokenNewLine();
			puts("");
		} else {
			(yyval.op) = (yyvsp[(1) - (2)].op);
			(yyval.op)->info.line = yylineno;
		}
	}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 252 "parser.y"
    {                                // Affectation (OP_ASSIGN)
	  	(yyval.op) = op_new(OP_ASSIGN, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 255 "parser.y"
    {                                                     // Nombre (OP_VALUE)
	  	(yyval.op) = op_new(OP_VALUE, NULL, NULL, var_new(NULL, 0, T_NUM));
	  	(yyval.op)->value->value.v_num = (yyvsp[(1) - (1)].value);
	  }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 259 "parser.y"
    {                                                       // Booléen (OP_VALUE)
	  	(yyval.op) = op_new(OP_VALUE, NULL, NULL, var_new(NULL, 0, T_BOOL));
	  	(yyval.op)->value->value.v_bool = (yyvsp[(1) - (1)].bool);
	  }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 263 "parser.y"
    {                                // Accès a une variable membre (OP_ATTR_ACCESS)
	  	(yyval.op) = op_new(OP_ATTR_ACCESS, (yyvsp[(1) - (3)].op), NULL, NULL);
	  	(yyval.op)->info.val = (yyvsp[(3) - (3)].str);
	  	(yyval.op)->info.val_h = str_hash((yyvsp[(3) - (3)].str));
	  }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 268 "parser.y"
    {                                         // Création d'une variable temporaire (OP_DEC_VAR)
		(yyval.op) = op_new(OP_DEC_VAR, NULL, NULL, NULL);
	  	(yyval.op)->info.val = (yyvsp[(3) - (3)].str);
	  	(yyval.op)->info.val_h = str_hash((yyvsp[(3) - (3)].str));
	  }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 273 "parser.y"
    {                                        // Création d'une variable membre (OP_DEC_ATTR)
		(yyval.op) = op_new(OP_DEC_ATTR, NULL, NULL, NULL);
	  	(yyval.op)->info.val = (yyvsp[(3) - (3)].str);
	  	(yyval.op)->info.val_h = str_hash((yyvsp[(3) - (3)].str));
	  }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 278 "parser.y"
    {                                      // Création d'une variable temporaire (OP_DEC_VAR)
		(yyval.op) = op_new(OP_DELETE_VAR, NULL, NULL, NULL);
	  	(yyval.op)->info.val = (yyvsp[(3) - (3)].str);
	  	(yyval.op)->info.val_h = str_hash((yyvsp[(3) - (3)].str));
	  }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 283 "parser.y"
    {                                     // Création d'une variable membre (OP_DEC_ATTR)
		(yyval.op) = op_new(OP_DELETE_ATTR, NULL, NULL, NULL);
	  	(yyval.op)->info.val = (yyvsp[(3) - (3)].str);
	  	(yyval.op)->info.val_h = str_hash((yyvsp[(3) - (3)].str));
	  }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 288 "parser.y"
    {                                  // Parenthèses, uniquement utile aux prioritées
		(yyval.op) = (yyvsp[(2) - (3)].op);
	  }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 291 "parser.y"
    {              // Appel d'unit comme fonction (OP_UNIT_NEW)
		Variable *v = var_new(NULL, 0, T_ARGS);
		v->value.v_llist = (yyvsp[(4) - (5)].list);
	  	(yyval.op) = op_new(OP_UNIT_NEW, (yyvsp[(2) - (5)].op), NULL, v);
	  }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 296 "parser.y"
    {                              // Appel d'unit comme fonction (OP_UNIT_NEW)
	  	(yyval.op) = op_new(OP_UNIT_NEW, (yyvsp[(2) - (4)].op), NULL, NULL);
	  }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 299 "parser.y"
    {                  // Appel d'unit comme fonction (OP_UNIT_CALL)
		Variable *v = var_new(NULL, 0, T_ARGS);
		v->value.v_llist = (yyvsp[(3) - (4)].list);
	  	(yyval.op) = op_new(OP_UNIT_CALL, (yyvsp[(1) - (4)].op), NULL, v);
	  }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 304 "parser.y"
    {                                  // Appel d'unit comme fonction (OP_UNIT_CALL)
	  	(yyval.op) = op_new(OP_UNIT_CALL, (yyvsp[(1) - (3)].op), NULL, NULL);
	  }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 307 "parser.y"
    {                                                 // Accès à une variable (OP_ACCES)
	  	(yyval.op) = op_new(OP_ACCES, NULL, NULL, NULL);
	  	(yyval.op)->info.val = (yyvsp[(1) - (1)].str);
	  	(yyval.op)->info.val_h = str_hash((yyvsp[(1) - (1)].str));
	  }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 312 "parser.y"
    {                                             // Accès à une variable (OP_ACCES)
	  	(yyval.op) = op_new(OP_ACCES_VAR, NULL, NULL, NULL);
	  	(yyval.op)->info.val = (yyvsp[(2) - (2)].str);
	  	(yyval.op)->info.val_h = str_hash((yyvsp[(2) - (2)].str));
	  }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 317 "parser.y"
    {                                            // Accès à une variable (OP_ACCES)
	  	(yyval.op) = op_new(OP_ACCES_ATTR, NULL, NULL, NULL);
	  	(yyval.op)->info.val = (yyvsp[(2) - (2)].str);
	  	(yyval.op)->info.val_h = str_hash((yyvsp[(2) - (2)].str));
	  }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 322 "parser.y"
    {                                  // Puissance (OP_MATH_POW)
	  	(yyval.op) = op_new(OP_MATH_POW, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 325 "parser.y"
    {                                 // Addition (OP_MATH_PLUS)
	  	(yyval.op) = op_new(OP_MATH_PLUS, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 328 "parser.y"
    {                                // Soustraction (OP_MATH_MINUS)
	  	(yyval.op) = op_new(OP_MATH_MINUS, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 331 "parser.y"
    {                                 // Multiplication (OP_MATH_MULT)
	  	(yyval.op) = op_new(OP_MATH_MULT, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 334 "parser.y"
    {                                // Division (OP_MATH_DIV)
	  	(yyval.op) = op_new(OP_MATH_DIV, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 337 "parser.y"
    {                                  // Division entière (OP_MATH_INTDIV)
	  	(yyval.op) = op_new(OP_MATH_INTDIV, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 340 "parser.y"
    {                               // Modulo (OP_MATH_MODULO)
	  	(yyval.op) = op_new(OP_MATH_MODULO, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 343 "parser.y"
    {                                 // Moins unaire (OP_MATH_M_UNARY)
	  	(yyval.op) = op_new(OP_MATH_M_UNARY, (yyvsp[(2) - (2)].op), NULL, NULL);
	  }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 346 "parser.y"
    {                                  // Plus unaire (OP_MATH_P_UNARY)
	  	(yyval.op) = op_new(OP_MATH_P_UNARY, (yyvsp[(2) - (2)].op), NULL, NULL);
	  }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 349 "parser.y"
    {                                 // Supérieur (OP_LOG_GT)
	  	(yyval.op) = op_new(OP_LOG_GT, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 352 "parser.y"
    {                                 // inférieur (OP_LOG_LT)
		(yyval.op) = op_new(OP_LOG_LT, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 355 "parser.y"
    {                               // Supérieur ou égal (OP_LOG_GE)
	  	(yyval.op) = op_new(OP_LOG_GE, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 358 "parser.y"
    {                               // Supérieur (OP_LOG_LE)
	  	(yyval.op) = op_new(OP_LOG_LE, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 361 "parser.y"
    {                              // Egalité (OP_LOG_EQ)
	  	(yyval.op) = op_new(OP_LOG_EQ, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 364 "parser.y"
    {                              // Egalité de type (OP_LOG_TYPE)
		(yyval.op) = op_new(OP_LOG_TYPE, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 367 "parser.y"
    {                                  // Différence (OP_LOG_DIF)
	  	(yyval.op) = op_new(OP_LOG_DIF, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 370 "parser.y"
    {                                  // ET (OP_LOG_AND)
	  	(yyval.op) = op_new(OP_LOG_AND, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 373 "parser.y"
    {                                   // OU (OP_LOG_OR)
	  	(yyval.op) = op_new(OP_LOG_OR, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 376 "parser.y"
    {                                             // Inversion logique (OP_LOG_NOT)
	  	(yyval.op) = op_new(OP_LOG_NOT, (yyvsp[(2) - (2)].op), NULL, NULL);
	  }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 379 "parser.y"
    {                                           // Test existance (OP_LOG_EXIST)
	  	(yyval.op) = op_new(OP_LOG_EXIST, (yyvsp[(2) - (2)].op), NULL, NULL);
	  }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 382 "parser.y"
    {                                          // Return (OP_RETURN)
	  	(yyval.op) = op_new(OP_RETURN, (yyvsp[(2) - (2)].op), NULL, NULL);
	  }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 385 "parser.y"
    {                                                     // Return (seul) (OP_RETURN)
	  	(yyval.op) = op_new(OP_RETURN, NULL, NULL, NULL);
	  }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 388 "parser.y"
    {                                                      // Break (OP_BREAK)
	  	(yyval.op) = op_new(OP_BREAK, NULL, NULL, NULL);
	  }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 391 "parser.y"
    {                                            // Dump (OP_OUTPUT_VAR_DUMP)	  	
		(yyval.op) = op_new(OP_OUTPUT_VAR_DUMP, (yyvsp[(2) - (2)].op), NULL, NULL);
	  }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 394 "parser.y"
    {                                                   // Déclaration de fonction (OP_UNIT)
	  	(yyval.op) = op_new(OP_UNIT, NULL, NULL, var_new(NULL, 0, T_FUNCTION));
	  	(yyval.op)->value->value.v_func = (yyvsp[(1) - (1)].function); 
	}
    break;


/* Line 1792 of yacc.c  */
#line 2111 "parser.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
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


/* Line 2055 of yacc.c  */
#line 400 "parser.y"


// Erreur durant l'analyse lexicale (flex) ou syntaxique (yacc)
int yyerror(const char *s) {
	int start = tokenStart;
	int i = 1;

	if(!p.interactive_mod) {
		int c = '*';

		rewind(yyin);
		while(i < yylineno) {
			while((c = getc(yyin)) != '\n' && c != EOF);
			i++;
			if(c == EOF) {
  				printf("[x] Error | %d: %s: '%s'\n", yylineno, s, yytext);
  				return 0;
			}
		}

	    fputs("> ", stdout);

		while((c = getc(yyin)) != '\n' && c != EOF) {
			putc(c, stdout);
		}
		putc('\n', stdout);
	}

	fputs("...", stdout);
    for (i = 1; i < start; i++)
    	putc('.', stdout);
    puts("^");

  	printf("[x] Error | %d: %s: '%s'\n", yylineno, s, yytext);
  	
  	return 0;
}

// Début d'un token 
void beginToken(const char *t) {
	// Avant le token
	tokenStart += tokenLength;
	// Longueur du token
	tokenLength = strlen(t);

}

// Nouvelle ligne
void beginTokenNewLine() {
	// Remise à zéro
	tokenStart = 0;
	tokenLength = 0;
}

// Main
int main(int argc, char **argv) {

	// Init des args
	params_init();
	params_make(argc, argv);

	if(p.interactive_mod) {
		puts("[i] Starting in interactive mode");
		ec_init_loc(&ec_obj);
		ec_init_loc(&ec_tmp);
		yyparse();
	} else {
		puts("[i] Starting in file mode");
		if(p.file) {
			yyin = p.file;
			p.start_parsing = clock();
			yyparse();
		} else {
			puts("[x] No file to read");
			return 1;
		}
	}
	return 0;
}

