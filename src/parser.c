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


	#include "variable.h"
	#include "variableOp.h"
	#include "operation.h"
	#include "unit.h"
	#include "debug.h"

	#include "hash/hash.h"
	#include "init/params.h"
	#include "constant.h"

	#include "parser.h"

	#include "builtin/built-in.h"

	// Valeurs externes
	extern char* yytext;
	extern FILE* yyin;
	extern int yylineno;

	extern unsigned int inside;
	extern char show_prompt;

	// Prototypes
	int yylex(void);
	int yyerror(const char *s);

	// Affichage erreur
	void beginToken(const char *t);
	void beginTokenNewLine();
	void interactive(void* to_exec, ptr_type type);

	// Context courant pour le mode interactif
	Exec_context ec_tmp, ec_obj;
	Variable r_base, *r;

	// Variables locales
	static int goodbye = 0;

	static int tokenStart = 0;
	static int tokenLength = 0;

	// Tableau des fonctions built-in lancées de base avec le programme
	struct s_Object*(*func_builtin_tab[128])(Exec_context*);
	unsigned int func_builtin_tab_n;

/* Line 371 of yacc.c  */
#line 122 "parser.tab.c"

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
     TYPE = 260,
     STRING = 261,
     PLUS = 262,
     MINUS = 263,
     STAR = 264,
     SLASH = 265,
     DIV = 266,
     POW = 267,
     EQUAL = 268,
     POINT = 269,
     ADDR = 270,
     MODULO = 271,
     MORE = 272,
     LESS = 273,
     MORE_E = 274,
     LESS_E = 275,
     AND = 276,
     OR = 277,
     NOT = 278,
     EXIST = 279,
     D_EQUAL = 280,
     T_EQUAL = 281,
     DIF = 282,
     P_LEFT = 283,
     P_RIGHT = 284,
     BRACE_LEFT = 285,
     BRACE_RIGHT = 286,
     COMMA = 287,
     VAR = 288,
     ATTR = 289,
     NEW = 290,
     DELETE = 291,
     TYPEOF = 292,
     IS = 293,
     IDENTIFIER = 294,
     FUNCTION = 295,
     IF = 296,
     ELSE = 297,
     FOR = 298,
     WHILE = 299,
     LOOP = 300,
     DUMP = 301,
     EXPR_END = 302,
     NEW_LINE = 303,
     BREAK = 304,
     RETURN = 305,
     POS = 306,
     NEG = 307,
     ADDR_ACCESS = 308
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 55 "parser.y"

  Unit_conditional *condition;
  Unit_loop *loop;
  Unit* function;
  Linked_list* list;
  Operation* op;
  Unit *u;
  language_type type;
  char *str;
  float value;
  char bool;


/* Line 387 of yacc.c  */
#line 232 "parser.tab.c"
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
#line 260 "parser.tab.c"

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
#define YYLAST   849

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  11
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNRULES -- Number of states.  */
#define YYNSTATES  149

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   308

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
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,    17,    23,    26,    32,    38,
      46,    54,    58,    62,    67,    73,    75,    79,    81,    85,
      89,    92,    95,    98,   101,   103,   105,   107,   109,   111,
     113,   116,   119,   123,   125,   127,   129,   131,   135,   139,
     143,   147,   151,   155,   161,   166,   171,   175,   177,   180,
     183,   187,   191,   195,   199,   203,   207,   211,   214,   217,
     221,   225,   229,   233,   237,   241,   245,   249,   253,   256,
     259,   262,   264,   266,   269,   273,   276
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      55,     0,    -1,    -1,    55,    62,    -1,    43,    28,    64,
      47,    64,    47,    64,    29,    61,    -1,    44,    28,    64,
      29,    61,    -1,    45,    61,    -1,    41,    28,    64,    29,
      61,    -1,    41,    28,    64,    29,    63,    -1,    57,    42,
      41,    28,    64,    29,    61,    -1,    57,    42,    41,    28,
      64,    29,    63,    -1,    57,    42,    61,    -1,    57,    42,
      63,    -1,    40,    28,    29,    61,    -1,    40,    28,    59,
      29,    61,    -1,    39,    -1,    59,    32,    39,    -1,    64,
      -1,    60,    32,    64,    -1,    30,    62,    31,    -1,    62,
      63,    -1,    62,    61,    -1,    62,    57,    -1,    62,    56,
      -1,    63,    -1,    61,    -1,    57,    -1,    56,    -1,    47,
      -1,    48,    -1,    64,    47,    -1,    64,    48,    -1,    64,
      13,    64,    -1,     5,    -1,     3,    -1,     4,    -1,     6,
      -1,    64,    14,    39,    -1,    35,    33,    39,    -1,    35,
      34,    39,    -1,    36,    33,    39,    -1,    36,    34,    39,
      -1,    28,    64,    29,    -1,    35,    64,    28,    60,    29,
      -1,    35,    64,    28,    29,    -1,    64,    28,    60,    29,
      -1,    64,    28,    29,    -1,    39,    -1,    33,    39,    -1,
      34,    39,    -1,    64,    12,    64,    -1,    64,     7,    64,
      -1,    64,     8,    64,    -1,    64,     9,    64,    -1,    64,
      10,    64,    -1,    64,    11,    64,    -1,    64,    16,    64,
      -1,     8,    64,    -1,     7,    64,    -1,    64,    17,    64,
      -1,    64,    18,    64,    -1,    64,    19,    64,    -1,    64,
      20,    64,    -1,    64,    25,    64,    -1,    64,    26,    64,
      -1,    64,    27,    64,    -1,    64,    21,    64,    -1,    64,
      22,    64,    -1,    23,    64,    -1,    24,    64,    -1,    50,
      64,    -1,    50,    -1,    49,    -1,    37,    64,    -1,    64,
      38,    64,    -1,    46,    64,    -1,    58,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   115,   115,   117,   139,   143,   146,   152,   155,   160,
     167,   177,   184,   197,   200,   207,   211,   219,   223,   231,
     239,   244,   249,   254,   259,   264,   269,   274,   283,   286,
     289,   292,   299,   302,   306,   310,   314,   321,   326,   331,
     336,   341,   346,   349,   354,   357,   362,   365,   370,   375,
     380,   383,   386,   389,   392,   395,   398,   401,   404,   407,
     410,   413,   416,   419,   422,   425,   428,   431,   434,   437,
     440,   443,   446,   449,   452,   455,   458
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "BOOL", "TYPE", "STRING",
  "PLUS", "MINUS", "STAR", "SLASH", "DIV", "POW", "EQUAL", "POINT", "ADDR",
  "MODULO", "MORE", "LESS", "MORE_E", "LESS_E", "AND", "OR", "NOT",
  "EXIST", "D_EQUAL", "T_EQUAL", "DIF", "P_LEFT", "P_RIGHT", "BRACE_LEFT",
  "BRACE_RIGHT", "COMMA", "VAR", "ATTR", "NEW", "DELETE", "TYPEOF", "IS",
  "IDENTIFIER", "FUNCTION", "IF", "ELSE", "FOR", "WHILE", "LOOP", "DUMP",
  "EXPR_END", "NEW_LINE", "BREAK", "RETURN", "POS", "NEG", "ADDR_ACCESS",
  "$accept", "Input", "Loop", "Condition", "Function", "Param_list",
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    55,    55,    56,    56,    56,    57,    57,    57,
      57,    57,    57,    58,    58,    59,    59,    60,    60,    61,
      62,    62,    62,    62,    62,    62,    62,    62,    63,    63,
      63,    63,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     9,     5,     2,     5,     5,     7,
       7,     3,     3,     4,     5,     1,     3,     1,     3,     3,
       2,     2,     2,     2,     1,     1,     1,     1,     1,     1,
       2,     2,     3,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     5,     4,     4,     3,     1,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       2,     1,     1,     2,     3,     2,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,    34,    35,    33,    36,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    47,     0,
       0,     0,     0,     0,     0,    28,    29,    72,    71,    27,
      26,    76,    25,     3,    24,     0,    58,    57,    68,    69,
       0,     0,    48,    49,     0,     0,     0,     0,     0,    73,
       0,     0,     0,     0,     6,    75,    70,     0,    23,    22,
      21,    20,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    30,    31,    42,    19,    38,    39,     0,    40,
      41,     0,    15,     0,     0,     0,     0,     0,    11,    12,
      51,    52,    53,    54,    55,    50,    32,    37,    56,    59,
      60,    61,    62,    66,    67,    63,    64,    65,    46,     0,
      17,    74,    44,     0,    13,     0,     0,     0,     0,     0,
       0,    45,     0,    43,    14,    16,     7,     8,     0,     5,
       0,    18,     0,     0,     0,     9,    10,     0,     4
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,    29,    30,    31,    93,   119,    32,    33,    34,
      35
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -35
static const yytype_int16 yypact[] =
{
     -35,   134,   -35,   -35,   -35,   -35,   -35,   470,   470,   470,
     470,   470,   230,   -34,   -32,   518,   -10,   470,   -35,   -12,
       9,    13,    21,    23,   470,   -35,   -35,   -35,   470,   -35,
      12,   -35,   -35,   230,   -35,   562,    -3,    -3,    -3,    -3,
      76,   182,   -35,   -35,    36,    37,   742,    39,    40,   376,
     -17,   470,   470,   470,   -35,   765,   765,   278,   -35,    12,
     -35,   -35,   470,   470,   470,   470,   470,   470,   470,    41,
     470,   470,   470,   470,   470,   470,   470,   470,   470,   470,
     374,   470,   -35,   -35,   -35,   -35,   -35,   -35,   422,   -35,
     -35,    23,   -35,    10,   650,   604,   673,    34,   -35,   -35,
     108,   108,     1,     1,     1,     1,   765,   -35,     1,    24,
      24,    24,    24,   788,   788,   811,   811,   811,   -35,    18,
     765,   376,   -35,    19,   -35,    23,    43,   326,   470,    23,
     470,   -35,   470,   -35,   -35,   -35,   -35,   -35,   627,   -35,
     696,   765,   470,   326,   719,   -35,   -35,    23,   -35
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -35,   -35,   -15,   -13,   -35,   -35,     3,   -14,    87,   -27,
      -7
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      36,    37,    38,    39,    40,    42,    61,    43,    46,    54,
      49,    69,    91,    67,    61,    69,    50,    55,    58,    60,
      59,    56,    92,    47,    48,    80,    58,    60,    59,    80,
      99,    62,    63,    64,    65,    66,    67,    51,    69,   125,
      70,    52,   126,    98,    94,    95,    96,   131,   133,    53,
     132,   132,    80,    12,    57,   100,   101,   102,   103,   104,
     105,   106,   130,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   120,   121,    86,    87,   124,    89,    90,
     107,   120,   135,    62,    63,    64,    65,    66,    67,    68,
      69,   123,    70,    71,    72,    73,    74,    75,    76,    41,
     137,    77,    78,    79,    80,    84,     0,     0,     0,     0,
       0,   134,     0,   136,    81,   139,   146,    64,    65,    66,
      67,   138,    69,   140,    70,   141,     0,     0,     0,   145,
       0,     0,     0,   148,     2,   144,    80,     3,     4,     5,
       6,     7,     8,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     9,    10,     0,
       0,     0,    11,     0,    12,     0,     0,    13,    14,    15,
      16,    17,     0,    18,    19,    20,     0,    21,    22,    23,
      24,    25,    26,    27,    28,     3,     4,     5,     6,     7,
       8,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     9,    10,     0,     0,     0,
      11,     0,    12,    85,     0,    13,    14,    15,    16,    17,
       0,    18,    19,    20,     0,    21,    22,    23,    24,    25,
      26,    27,    28,     3,     4,     5,     6,     7,     8,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     9,    10,     0,     0,     0,    11,     0,
      12,     0,     0,    13,    14,    15,    16,    17,     0,    18,
      19,    20,     0,    21,    22,    23,    24,    25,    26,    27,
      28,     3,     4,     5,     6,     7,     8,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     9,    10,     0,     0,     0,    11,     0,    12,     0,
       0,    13,    14,    15,    16,    17,     0,    18,    19,    97,
       0,     0,     0,     0,    24,    25,    26,    27,    28,     3,
       4,     5,     6,     7,     8,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     9,
      10,     0,     0,     0,    11,     0,    12,     0,     0,    13,
      14,    15,    16,    17,     0,    18,    19,     0,     0,     0,
       0,     0,    24,    25,    26,    27,    28,     3,     4,     5,
       6,     7,     8,    62,    63,    64,    65,    66,    67,     0,
      69,     0,    70,    71,    72,    73,    74,     9,    10,     0,
       0,     0,    11,   118,    80,     0,     0,    13,    14,    15,
      16,    17,     0,    18,    19,     0,     0,     0,     0,     0,
      24,     0,     0,    27,    28,     3,     4,     5,     6,     7,
       8,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     9,    10,     0,     0,     0,
      11,   122,     0,     0,     0,    13,    14,    15,    16,    17,
       0,    18,    19,     0,     0,     0,     0,     0,    24,     0,
       0,    27,    28,     3,     4,     5,     6,     7,     8,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     9,    10,     0,     0,     0,    11,     0,
       0,     0,     0,    13,    14,    15,    16,    17,     0,    18,
      19,     0,     0,     0,     0,     0,    24,     0,     0,    27,
      28,     3,     4,     5,     6,     7,     8,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     9,    10,     0,     0,     0,    11,     0,     0,     0,
       0,    44,    45,    15,    16,    17,     0,    18,    19,     0,
       0,     0,     0,     0,    24,     0,     0,    27,    28,    62,
      63,    64,    65,    66,    67,    68,    69,     0,    70,    71,
      72,    73,    74,    75,    76,     0,     0,    77,    78,    79,
      80,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      81,     0,     0,     0,     0,     0,     0,     0,     0,    82,
      83,    62,    63,    64,    65,    66,    67,    68,    69,     0,
      70,    71,    72,    73,    74,    75,    76,     0,     0,    77,
      78,    79,    80,     0,    62,    63,    64,    65,    66,    67,
      68,    69,    81,    70,    71,    72,    73,    74,    75,    76,
       0,   128,    77,    78,    79,    80,     0,    62,    63,    64,
      65,    66,    67,    68,    69,    81,    70,    71,    72,    73,
      74,    75,    76,     0,   142,    77,    78,    79,    80,   127,
      62,    63,    64,    65,    66,    67,    68,    69,    81,    70,
      71,    72,    73,    74,    75,    76,     0,     0,    77,    78,
      79,    80,   129,    62,    63,    64,    65,    66,    67,    68,
      69,    81,    70,    71,    72,    73,    74,    75,    76,     0,
       0,    77,    78,    79,    80,   143,    62,    63,    64,    65,
      66,    67,    68,    69,    81,    70,    71,    72,    73,    74,
      75,    76,     0,     0,    77,    78,    79,    80,   147,    62,
      63,    64,    65,    66,    67,    68,    69,    81,    70,    71,
      72,    73,    74,    75,    76,     0,     0,    77,    78,    79,
      88,     0,    62,    63,    64,    65,    66,    67,    68,    69,
      81,    70,    71,    72,    73,    74,    75,    76,     0,     0,
      77,    78,    79,    80,     0,    62,    63,    64,    65,    66,
      67,     0,    69,    81,    70,    71,    72,    73,    74,     0,
       0,     0,     0,    77,    78,    79,    80,     0,    62,    63,
      64,    65,    66,    67,     0,    69,    81,    70,    71,    72,
      73,    74,     0,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    81
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-35)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       7,     8,     9,    10,    11,    39,    33,    39,    15,    23,
      17,    14,    29,    12,    41,    14,    28,    24,    33,    33,
      33,    28,    39,    33,    34,    28,    41,    41,    41,    28,
      57,     7,     8,     9,    10,    11,    12,    28,    14,    29,
      16,    28,    32,    57,    51,    52,    53,    29,    29,    28,
      32,    32,    28,    30,    42,    62,    63,    64,    65,    66,
      67,    68,    28,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    39,    39,    91,    39,    39,
      39,    88,    39,     7,     8,     9,    10,    11,    12,    13,
      14,    88,    16,    17,    18,    19,    20,    21,    22,    12,
     127,    25,    26,    27,    28,    29,    -1,    -1,    -1,    -1,
      -1,   125,    -1,   127,    38,   129,   143,     9,    10,    11,
      12,   128,    14,   130,    16,   132,    -1,    -1,    -1,   143,
      -1,    -1,    -1,   147,     0,   142,    28,     3,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    24,    -1,
      -1,    -1,    28,    -1,    30,    -1,    -1,    33,    34,    35,
      36,    37,    -1,    39,    40,    41,    -1,    43,    44,    45,
      46,    47,    48,    49,    50,     3,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    23,    24,    -1,    -1,    -1,
      28,    -1,    30,    31,    -1,    33,    34,    35,    36,    37,
      -1,    39,    40,    41,    -1,    43,    44,    45,    46,    47,
      48,    49,    50,     3,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    23,    24,    -1,    -1,    -1,    28,    -1,
      30,    -1,    -1,    33,    34,    35,    36,    37,    -1,    39,
      40,    41,    -1,    43,    44,    45,    46,    47,    48,    49,
      50,     3,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    23,    24,    -1,    -1,    -1,    28,    -1,    30,    -1,
      -1,    33,    34,    35,    36,    37,    -1,    39,    40,    41,
      -1,    -1,    -1,    -1,    46,    47,    48,    49,    50,     3,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,
      24,    -1,    -1,    -1,    28,    -1,    30,    -1,    -1,    33,
      34,    35,    36,    37,    -1,    39,    40,    -1,    -1,    -1,
      -1,    -1,    46,    47,    48,    49,    50,     3,     4,     5,
       6,     7,     8,     7,     8,     9,    10,    11,    12,    -1,
      14,    -1,    16,    17,    18,    19,    20,    23,    24,    -1,
      -1,    -1,    28,    29,    28,    -1,    -1,    33,    34,    35,
      36,    37,    -1,    39,    40,    -1,    -1,    -1,    -1,    -1,
      46,    -1,    -1,    49,    50,     3,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    23,    24,    -1,    -1,    -1,
      28,    29,    -1,    -1,    -1,    33,    34,    35,    36,    37,
      -1,    39,    40,    -1,    -1,    -1,    -1,    -1,    46,    -1,
      -1,    49,    50,     3,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    23,    24,    -1,    -1,    -1,    28,    -1,
      -1,    -1,    -1,    33,    34,    35,    36,    37,    -1,    39,
      40,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    49,
      50,     3,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    23,    24,    -1,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    33,    34,    35,    36,    37,    -1,    39,    40,    -1,
      -1,    -1,    -1,    -1,    46,    -1,    -1,    49,    50,     7,
       8,     9,    10,    11,    12,    13,    14,    -1,    16,    17,
      18,    19,    20,    21,    22,    -1,    -1,    25,    26,    27,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      48,     7,     8,     9,    10,    11,    12,    13,    14,    -1,
      16,    17,    18,    19,    20,    21,    22,    -1,    -1,    25,
      26,    27,    28,    -1,     7,     8,     9,    10,    11,    12,
      13,    14,    38,    16,    17,    18,    19,    20,    21,    22,
      -1,    47,    25,    26,    27,    28,    -1,     7,     8,     9,
      10,    11,    12,    13,    14,    38,    16,    17,    18,    19,
      20,    21,    22,    -1,    47,    25,    26,    27,    28,    29,
       7,     8,     9,    10,    11,    12,    13,    14,    38,    16,
      17,    18,    19,    20,    21,    22,    -1,    -1,    25,    26,
      27,    28,    29,     7,     8,     9,    10,    11,    12,    13,
      14,    38,    16,    17,    18,    19,    20,    21,    22,    -1,
      -1,    25,    26,    27,    28,    29,     7,     8,     9,    10,
      11,    12,    13,    14,    38,    16,    17,    18,    19,    20,
      21,    22,    -1,    -1,    25,    26,    27,    28,    29,     7,
       8,     9,    10,    11,    12,    13,    14,    38,    16,    17,
      18,    19,    20,    21,    22,    -1,    -1,    25,    26,    27,
      28,    -1,     7,     8,     9,    10,    11,    12,    13,    14,
      38,    16,    17,    18,    19,    20,    21,    22,    -1,    -1,
      25,    26,    27,    28,    -1,     7,     8,     9,    10,    11,
      12,    -1,    14,    38,    16,    17,    18,    19,    20,    -1,
      -1,    -1,    -1,    25,    26,    27,    28,    -1,     7,     8,
       9,    10,    11,    12,    -1,    14,    38,    16,    17,    18,
      19,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    55,     0,     3,     4,     5,     6,     7,     8,    23,
      24,    28,    30,    33,    34,    35,    36,    37,    39,    40,
      41,    43,    44,    45,    46,    47,    48,    49,    50,    56,
      57,    58,    61,    62,    63,    64,    64,    64,    64,    64,
      64,    62,    39,    39,    33,    34,    64,    33,    34,    64,
      28,    28,    28,    28,    61,    64,    64,    42,    56,    57,
      61,    63,     7,     8,     9,    10,    11,    12,    13,    14,
      16,    17,    18,    19,    20,    21,    22,    25,    26,    27,
      28,    38,    47,    48,    29,    31,    39,    39,    28,    39,
      39,    29,    39,    59,    64,    64,    64,    41,    61,    63,
      64,    64,    64,    64,    64,    64,    64,    39,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    29,    60,
      64,    64,    29,    60,    61,    29,    32,    29,    47,    29,
      28,    29,    32,    29,    61,    39,    61,    63,    64,    61,
      64,    64,    47,    29,    64,    61,    63,    29,    61
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
#line 117 "parser.y"
    {
			Unit u;
			u.args = NULL;
			u.statements = (yyvsp[(2) - (2)].list);

			p.end_parsing = clock();

			if(p.show_operation) {
				puts("[>] Result in memory :"), unit_dump(&u);
				fputs("[*] Press enter to eval", stdout);
				getchar();
			}

			if(p.show_timer)
				printf("[i] Parsed in %.4fs\n", ((p.end_parsing-p.start_parsing)/(double)CLOCKS_PER_SEC));

			unit_main(&u);
	  }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 139 "parser.y"
    {
	  	if((yyvsp[(7) - (9)].op)) linked_list_append(&(yyvsp[(9) - (9)].list), LLT_OPERATION, (void*)(yyvsp[(7) - (9)].op));
    	(yyval.loop) = unit_loop_new((yyvsp[(5) - (9)].op), NULL, (yyvsp[(3) - (9)].op), (yyvsp[(9) - (9)].list));
      }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 143 "parser.y"
    {
    	(yyval.loop) = unit_loop_new((yyvsp[(3) - (5)].op), NULL, NULL, (yyvsp[(5) - (5)].list));
      }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 146 "parser.y"
    {
    	(yyval.loop) = unit_loop_new(NULL, NULL, NULL, (yyvsp[(2) - (2)].list));
      }
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 152 "parser.y"
    {
	  	(yyval.condition) = unit_cond_new((yyvsp[(3) - (5)].op), NULL, (yyvsp[(5) - (5)].list));
	  }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 155 "parser.y"
    {
		Linked_list* ll = NULL;
	  	linked_list_append(&ll, LLT_OPERATION, (void*)(yyvsp[(5) - (5)].op));
	  	(yyval.condition) = unit_cond_new((yyvsp[(3) - (5)].op), NULL, ll);
	  }
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 160 "parser.y"
    {
		Unit_conditional *uc = (yyvsp[(1) - (7)].condition);
		while(uc->next)
			uc = uc->next;
		uc->next = unit_cond_new((yyvsp[(5) - (7)].op), uc, (yyvsp[(7) - (7)].list));
		(yyval.condition) = (yyvsp[(1) - (7)].condition);
	  }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 167 "parser.y"
    {
		Linked_list* ll = NULL;
	  	linked_list_append(&ll, LLT_OPERATION, (void*)(yyvsp[(7) - (7)].op));

		Unit_conditional *uc = (yyvsp[(1) - (7)].condition);
		while(uc->next)
			uc = uc->next;
		uc->next = unit_cond_new((yyvsp[(5) - (7)].op), uc, ll);
		(yyval.condition) = (yyvsp[(1) - (7)].condition);
	  }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 177 "parser.y"
    {
		Unit_conditional *uc = (yyvsp[(1) - (3)].condition);
		while(uc->next)
			uc = uc->next;
		uc->next = unit_cond_new(NULL, uc, (yyvsp[(3) - (3)].list));
		(yyval.condition) = (yyvsp[(1) - (3)].condition);
	  }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 184 "parser.y"
    {
		Linked_list* ll = NULL;
	  	linked_list_append(&ll, LLT_OPERATION, (void*)(yyvsp[(3) - (3)].op));

		Unit_conditional *uc = (yyvsp[(1) - (3)].condition);
		while(uc->next)
			uc = uc->next;
		uc->next = unit_cond_new(NULL, uc, ll);
		(yyval.condition) = (yyvsp[(1) - (3)].condition);
	  }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 197 "parser.y"
    {
	  	(yyval.function) = unit_new((yyvsp[(4) - (4)].list), NULL);
	  }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 200 "parser.y"
    {
	  	(yyval.function) = unit_new((yyvsp[(5) - (5)].list), (yyvsp[(3) - (5)].list));
	  }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 207 "parser.y"
    {
		(yyval.list) = NULL;
		linked_list_append(&(yyval.list), LLT_VARIABLE, (void*)var_new((yyvsp[(1) - (1)].str), str_hash((yyvsp[(1) - (1)].str)), T_NULL));
	  }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 211 "parser.y"
    {
		(yyval.list) = (yyvsp[(1) - (3)].list);
		linked_list_append(&(yyvsp[(1) - (3)].list), LLT_VARIABLE, (void*)var_new((yyvsp[(3) - (3)].str), str_hash((yyvsp[(3) - (3)].str)), T_NULL));
	  }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 219 "parser.y"
    {
		(yyval.list) = NULL;
		linked_list_append(&(yyval.list), LLT_OPERATION, (void*)(yyvsp[(1) - (1)].op));
	  }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 223 "parser.y"
    {
		(yyval.list) = (yyvsp[(1) - (3)].list);
		linked_list_append(&(yyvsp[(1) - (3)].list), LLT_OPERATION, (void*)(yyvsp[(3) - (3)].op));
	  }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 231 "parser.y"
    {
		(yyval.list) = (yyvsp[(2) - (3)].list);
	  }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 239 "parser.y"
    {
	  	(yyval.list) = (yyvsp[(1) - (2)].list); // Il faut ajouter le statement à la liste
	  	if((yyvsp[(2) - (2)].op)) linked_list_append(&(yyvsp[(1) - (2)].list), LLT_OPERATION, (void*)(yyvsp[(2) - (2)].op));
	  	if((yyvsp[(2) - (2)].op) && p.interactive_mod && !inside) interactive((void*)(yyvsp[(2) - (2)].op), LLT_OPERATION);
	  }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 244 "parser.y"
    {
	  	(yyval.list) = (yyvsp[(1) - (2)].list); // Il faut ajouter l'unit à la liste
	  	if((yyvsp[(2) - (2)].list)) linked_list_append(&(yyvsp[(1) - (2)].list), LLT_UNIT, (void*)(yyvsp[(2) - (2)].list));
	  	if((yyvsp[(2) - (2)].list) && p.interactive_mod && !inside) interactive((void*)(yyvsp[(2) - (2)].list), LLT_UNIT);
	  }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 249 "parser.y"
    {
	  	(yyval.list) = (yyvsp[(1) - (2)].list); // Il faut ajouter la condition à la liste
	  	if((yyvsp[(2) - (2)].condition)) linked_list_append(&(yyvsp[(1) - (2)].list), LLT_CONDITION, (void*)(yyvsp[(2) - (2)].condition));
	  	if((yyvsp[(2) - (2)].condition) && p.interactive_mod && !inside) interactive((void*)(yyvsp[(2) - (2)].condition), LLT_CONDITION);
	  }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 254 "parser.y"
    {
	  	(yyval.list) = (yyvsp[(1) - (2)].list); // Il faut ajouter la boucle à la liste
	  	if((yyvsp[(2) - (2)].loop)) linked_list_append(&(yyvsp[(1) - (2)].list), LLT_LOOP, (void*)(yyvsp[(2) - (2)].loop));
	  	if((yyvsp[(2) - (2)].loop) && p.interactive_mod && !inside) interactive((void*)(yyvsp[(2) - (2)].loop), LLT_LOOP);
	  }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 259 "parser.y"
    {
		(yyval.list) = NULL; // Pas encore de liste, il faut la créer
	  	if((yyvsp[(1) - (1)].op)) linked_list_append(&(yyval.list), LLT_OPERATION, (void*)(yyvsp[(1) - (1)].op)); // On met notre statement dedans
	  	if((yyvsp[(1) - (1)].op) && p.interactive_mod && !inside) interactive((void*)(yyvsp[(1) - (1)].op), LLT_OPERATION);
	  }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 264 "parser.y"
    {
		(yyval.list) = NULL; // Pas encore de liste, il faut la créer
	  	if((yyvsp[(1) - (1)].list)) linked_list_append(&(yyval.list), LLT_UNIT, (void*)(yyvsp[(1) - (1)].list)); // On met notre unit dedans
	  	if((yyvsp[(1) - (1)].list) && p.interactive_mod && !inside) interactive((void*)(yyvsp[(1) - (1)].list), LLT_UNIT);
	  }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 269 "parser.y"
    {
		(yyval.list) = NULL; // Pas encore de liste, il faut la créer
	  	if((yyvsp[(1) - (1)].condition)) linked_list_append(&(yyval.list), LLT_CONDITION, (void*)(yyvsp[(1) - (1)].condition)); // On met notre condition dedans
	  	if((yyvsp[(1) - (1)].condition) && p.interactive_mod && !inside) interactive((void*)(yyvsp[(1) - (1)].condition), LLT_CONDITION);
	  }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 274 "parser.y"
    {
		(yyval.list) = NULL; // Pas encore de liste, il faut la créer
	  	if((yyvsp[(1) - (1)].loop)) linked_list_append(&(yyval.list), LLT_LOOP, (void*)(yyvsp[(1) - (1)].loop)); // On met notre boucle dedans
	  	if((yyvsp[(1) - (1)].loop) && p.interactive_mod && !inside) interactive((void*)(yyvsp[(1) - (1)].loop), LLT_LOOP);
	  }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 283 "parser.y"
    {
		(yyval.op) = NULL;
	  }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 286 "parser.y"
    {
		(yyval.op) = NULL;
	}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 289 "parser.y"
    {
		(yyval.op) = (yyvsp[(1) - (2)].op);
	}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 292 "parser.y"
    {
		(yyval.op) = (yyvsp[(1) - (2)].op);
	}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 299 "parser.y"
    {                                // Affectation (OP_ASSIGN)
	  	(yyval.op) = op_new(OP_ASSIGN, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 302 "parser.y"
    {                                                       // Type (OP_VALUE)
	  	(yyval.op) = op_new(OP_VALUE, NULL, NULL, var_new(NULL, 0, T_TYPE));
	  	(yyval.op)->value->value.v_type = (yyvsp[(1) - (1)].type);
	  }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 306 "parser.y"
    {                                                     // Nombre (OP_VALUE)
	  	(yyval.op) = op_new(OP_VALUE, NULL, NULL, var_new(NULL, 0, T_NUM));
	  	(yyval.op)->value->value.v_num = (yyvsp[(1) - (1)].value);
	  }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 310 "parser.y"
    {                                                       // Booléen (OP_VALUE)
	  	(yyval.op) = op_new(OP_VALUE, NULL, NULL, var_new(NULL, 0, T_BOOL));
	  	(yyval.op)->value->value.v_bool = (yyvsp[(1) - (1)].bool);
	  }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 314 "parser.y"
    {                                                      // String (OP_VALUE)
	  	(yyval.op) = op_new(OP_VALUE, NULL, NULL, var_new(NULL, 0, T_OBJECT));

	  	strings_string(NULL, NULL, (yyval.op)->value, 1);
	  	((VK_String*)(yyval.op)->value->value.v_obj->data)->s = (yyvsp[(1) - (1)].str);
	  	((VK_String*)(yyval.op)->value->value.v_obj->data)->n = strlen((yyvsp[(1) - (1)].str));
	  }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 321 "parser.y"
    {                                // Accès a une variable membre (OP_ATTR_ACCESS)
	  	(yyval.op) = op_new(OP_ATTR_ACCESS, (yyvsp[(1) - (3)].op), NULL, NULL);
	  	(yyval.op)->identifier.s = (yyvsp[(3) - (3)].str);
	  	(yyval.op)->identifier.s_h = str_hash((yyvsp[(3) - (3)].str));
	  }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 326 "parser.y"
    {                                         // Création d'une variable temporaire (OP_DEC_VAR)
		(yyval.op) = op_new(OP_DEC_VAR, NULL, NULL, NULL);
	  	(yyval.op)->identifier.s = (yyvsp[(3) - (3)].str);
	  	(yyval.op)->identifier.s_h = str_hash((yyvsp[(3) - (3)].str));
	  }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 331 "parser.y"
    {                                        // Création d'une variable membre (OP_DEC_ATTR)
		(yyval.op) = op_new(OP_DEC_ATTR, NULL, NULL, NULL);
	  	(yyval.op)->identifier.s = (yyvsp[(3) - (3)].str);
	  	(yyval.op)->identifier.s_h = str_hash((yyvsp[(3) - (3)].str));
	  }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 336 "parser.y"
    {                                      // Création d'une variable temporaire (OP_DEC_VAR)
		(yyval.op) = op_new(OP_DELETE_VAR, NULL, NULL, NULL);
	  	(yyval.op)->identifier.s = (yyvsp[(3) - (3)].str);
	  	(yyval.op)->identifier.s_h = str_hash((yyvsp[(3) - (3)].str));
	  }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 341 "parser.y"
    {                                     // Création d'une variable membre (OP_DEC_ATTR)
		(yyval.op) = op_new(OP_DELETE_ATTR, NULL, NULL, NULL);
	  	(yyval.op)->identifier.s = (yyvsp[(3) - (3)].str);
	  	(yyval.op)->identifier.s_h = str_hash((yyvsp[(3) - (3)].str));
	  }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 346 "parser.y"
    {                                  // Parenthèses, uniquement utile aux prioritées
		(yyval.op) = (yyvsp[(2) - (3)].op);
	  }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 349 "parser.y"
    {              // Appel d'unit comme fonction (OP_UNIT_NEW)
		Variable *v = var_new(NULL, 0, T_ARGS);
		v->value.v_llist = (yyvsp[(4) - (5)].list);
	  	(yyval.op) = op_new(OP_UNIT_NEW, (yyvsp[(2) - (5)].op), NULL, v);
	  }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 354 "parser.y"
    {                              // Appel d'unit comme fonction (OP_UNIT_NEW)
	  	(yyval.op) = op_new(OP_UNIT_NEW, (yyvsp[(2) - (4)].op), NULL, NULL);
	  }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 357 "parser.y"
    {                  // Appel d'unit comme fonction (OP_UNIT_CALL)
		Variable *v = var_new(NULL, 0, T_ARGS);
		v->value.v_llist = (yyvsp[(3) - (4)].list);
	  	(yyval.op) = op_new(OP_UNIT_CALL, (yyvsp[(1) - (4)].op), NULL, v);
	  }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 362 "parser.y"
    {                                  // Appel d'unit comme fonction (OP_UNIT_CALL)
	  	(yyval.op) = op_new(OP_UNIT_CALL, (yyvsp[(1) - (3)].op), NULL, NULL);
	  }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 365 "parser.y"
    {                                                 // Accès à une variable (OP_ACCES)
	  	(yyval.op) = op_new(OP_ACCES, NULL, NULL, NULL);
	  	(yyval.op)->identifier.s = (yyvsp[(1) - (1)].str);
	  	(yyval.op)->identifier.s_h = str_hash((yyvsp[(1) - (1)].str));
	  }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 370 "parser.y"
    {                                             // Accès à une variable (OP_ACCES)
	  	(yyval.op) = op_new(OP_ACCES_VAR, NULL, NULL, NULL);
	  	(yyval.op)->identifier.s = (yyvsp[(2) - (2)].str);
	  	(yyval.op)->identifier.s_h = str_hash((yyvsp[(2) - (2)].str));
	  }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 375 "parser.y"
    {                                            // Accès à une variable (OP_ACCES)
	  	(yyval.op) = op_new(OP_ACCES_ATTR, NULL, NULL, NULL);
	  	(yyval.op)->identifier.s = (yyvsp[(2) - (2)].str);
	  	(yyval.op)->identifier.s_h = str_hash((yyvsp[(2) - (2)].str));
	  }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 380 "parser.y"
    {                                  // Puissance (OP_MATH_POW)
	  	(yyval.op) = op_new(OP_MATH_POW, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 383 "parser.y"
    {                                 // Addition (OP_MATH_PLUS)
	  	(yyval.op) = op_new(OP_MATH_PLUS, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 386 "parser.y"
    {                                // Soustraction (OP_MATH_MINUS)
	  	(yyval.op) = op_new(OP_MATH_MINUS, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 389 "parser.y"
    {                                 // Multiplication (OP_MATH_MULT)
	  	(yyval.op) = op_new(OP_MATH_MULT, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 392 "parser.y"
    {                                // Division (OP_MATH_DIV)
	  	(yyval.op) = op_new(OP_MATH_DIV, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 395 "parser.y"
    {                                  // Division entière (OP_MATH_INTDIV)
	  	(yyval.op) = op_new(OP_MATH_INTDIV, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 398 "parser.y"
    {                               // Modulo (OP_MATH_MODULO)
	  	(yyval.op) = op_new(OP_MATH_MODULO, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 401 "parser.y"
    {                                 // Moins unaire (OP_MATH_M_UNARY)
	  	(yyval.op) = op_new(OP_MATH_M_UNARY, (yyvsp[(2) - (2)].op), NULL, NULL);
	  }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 404 "parser.y"
    {                                  // Plus unaire (OP_MATH_P_UNARY)
	  	(yyval.op) = op_new(OP_MATH_P_UNARY, (yyvsp[(2) - (2)].op), NULL, NULL);
	  }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 407 "parser.y"
    {                                 // Supérieur (OP_LOG_GT)
	  	(yyval.op) = op_new(OP_LOG_GT, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 410 "parser.y"
    {                                 // inférieur (OP_LOG_LT)
		(yyval.op) = op_new(OP_LOG_LT, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 413 "parser.y"
    {                               // Supérieur ou égal (OP_LOG_GE)
	  	(yyval.op) = op_new(OP_LOG_GE, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 416 "parser.y"
    {                               // Supérieur (OP_LOG_LE)
	  	(yyval.op) = op_new(OP_LOG_LE, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 419 "parser.y"
    {                              // Egalité (OP_LOG_EQ)
	  	(yyval.op) = op_new(OP_LOG_EQ, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 422 "parser.y"
    {                              // Egalité de type (OP_LOG_TYPE)
		(yyval.op) = op_new(OP_LOG_TYPE, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 425 "parser.y"
    {                                  // Différence (OP_LOG_DIF)
	  	(yyval.op) = op_new(OP_LOG_DIF, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 428 "parser.y"
    {                                  // ET (OP_LOG_AND)
	  	(yyval.op) = op_new(OP_LOG_AND, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 431 "parser.y"
    {                                   // OU (OP_LOG_OR)
	  	(yyval.op) = op_new(OP_LOG_OR, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 434 "parser.y"
    {                                             // Inversion logique (OP_LOG_NOT)
	  	(yyval.op) = op_new(OP_LOG_NOT, (yyvsp[(2) - (2)].op), NULL, NULL);
	  }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 437 "parser.y"
    {                                           // Test existance (OP_LOG_EXIST)
	  	(yyval.op) = op_new(OP_LOG_EXIST, (yyvsp[(2) - (2)].op), NULL, NULL);
	  }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 440 "parser.y"
    {                                          // Return (OP_RETURN)
	  	(yyval.op) = op_new(OP_RETURN, (yyvsp[(2) - (2)].op), NULL, NULL);
	  }
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 443 "parser.y"
    {                                                     // Return (seul) (OP_RETURN)
	  	(yyval.op) = op_new(OP_RETURN, NULL, NULL, NULL);
	  }
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 446 "parser.y"
    {                                                      // Break (OP_BREAK)
	  	(yyval.op) = op_new(OP_BREAK, NULL, NULL, NULL);
	  }
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 449 "parser.y"
    {                                          // Typeof (OP_TYPE_TYPEOF)
		(yyval.op) = op_new(OP_TYPE_TYPEOF, (yyvsp[(2) - (2)].op), NULL, NULL);
	  }
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 452 "parser.y"
    {                                   // Typeof (OP_TYPE_IS)
		(yyval.op) = op_new(OP_TYPE_IS, (yyvsp[(1) - (3)].op), (yyvsp[(3) - (3)].op), NULL);
	  }
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 455 "parser.y"
    {                                            // Dump (OP_OUTPUT_VAR_DUMP)
		(yyval.op) = op_new(OP_OUTPUT_VAR_DUMP, (yyvsp[(2) - (2)].op), NULL, NULL);
	  }
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 458 "parser.y"
    {                                                   // Déclaration de fonction (OP_UNIT)
	  	(yyval.op) = op_new(OP_UNIT, NULL, NULL, var_new(NULL, 0, T_FUNCTION));
	  	(yyval.op)->value->value.v_func = (yyvsp[(1) - (1)].function);
	  }
    break;


/* Line 1792 of yacc.c  */
#line 2399 "parser.tab.c"
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
#line 464 "parser.y"


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
	if(*t != '\t')
		tokenLength = strlen(t);
	else
		tokenLength = 4;
}

// Nouvelle ligne
void beginTokenNewLine() {
	// Remise à zéro
	tokenStart = 0;
	tokenLength = 0;
}

// Lecture interactive (condition/boucle/statement)
void interactive(void* to_exec, ptr_type type) {

	return_code rc = RC_OK;

	// Initialisation valeur retour
	var_init_loc(&r_base, NULL, 0, T_NULL);
	r = &r_base;


	// Opération simple
	if(type == LLT_OPERATION) {

		if(p.show_operation) {
			puts("[>] Result in memory :"), op_dump((Operation*)to_exec);
			fputs("[*] Press enter to eval", stdout);
			getchar();
		}

		// Evaluation
		if(p.verbose) puts("\n[<] Evaluating the statement ...");
		rc = op_eval(&ec_obj, &ec_tmp, (Operation*)to_exec, &r);

	} else if(type == LLT_CONDITION) {

		if(p.show_operation) {
			puts("[>] Result in memory :"), unit_cond_dump((Unit_conditional*)to_exec);
			fputs("[*] Press enter to eval", stdout);
			getchar();
		}

		// Evaluation
		if(p.verbose) puts("\n[<] Evaluating the condition ...");
		rc = unit_cond_eval(&ec_obj, &ec_tmp, (Unit_conditional*)to_exec, r);
	} else if(type == LLT_LOOP) {

		if(p.show_operation) {
			puts("[>] Result in memory :"), unit_loop_dump((Unit_loop*)to_exec);
			fputs("[*] Press enter to eval", stdout);
			getchar();
		}

		// Evaluation
		if(p.verbose) puts("\n[<] Evaluating the loop ...");
		rc = unit_loop_eval(&ec_obj, &ec_tmp, (Unit_loop*)to_exec, r);
	} else if(type == LLT_UNIT) {

		if(p.show_operation) {
			puts("[>] Result in memory :"), unit_dump((Unit*)to_exec);
			fputs("[*] Press enter to eval", stdout);
			getchar();
		}

		// Evaluation
		if(p.verbose) puts("\n[<] Evaluating the unit ...");
		rc = unit_eval(&ec_obj, &ec_tmp, ((Unit*)to_exec)->statements, r);
	}

	// Analyse
	switch(rc) {
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
			exit(e.type);
		case RC_RETURN :
			if(r_base.type == T_NUM)
				goodbye = (int)r_base.value.v_num;
			printf("[i] Interpreter stopped (%x) \n", goodbye);
			exit(goodbye);
		default:
			break;
	}

	if(p.verbose) puts("[<] Evaluation done");

	if(p.auto_dump && type == LLT_OPERATION) {
		puts("\n[>] Statement value :");
		var_dump(&r_base);
	}

	// Suppression valeur temporaire
	if(r_base.type != T_NULL)
		var_empty(&r_base);
	else
		r = &r_base;

	beginTokenNewLine();
	if(p.verbose) puts("");
}

// Main
int main(int argc, char **argv) {

	// Init des args
	params_init();
	params_make(argc, argv);

	// Init des fonctions built-in
	func_builtin_tab[0] = console_init;
	func_builtin_tab[1] = strings_init;
	func_builtin_tab_n = 2;


	if(p.interactive_mod) {
		puts("[i] Starting in interactive mode");
		inside = 0; show_prompt = 1;

		// Contexte
		ec_init_loc(&ec_obj);
		ec_init_loc(&ec_tmp);

		// Initialisation des fonctions built-in
    	unit_init_builtin(&ec_obj);

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

