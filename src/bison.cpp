/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 2 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:339  */


    #include "tree/MinijavaTree.h"
    #include "tree/TreeBuildHelp.h"

    #include "tokens.h"

    #include <vector>
    #include <iostream>
    #include <string>
    #include <memory>
    using namespace std;

    #include "symbol/Symbol.h"
    using namespace Symbol;

    extern CStorage globalStorage;

    string error_msg;

    int yylex();
    void yyerror(const char *);

    extern int yylineno;
    extern FILE * yyin;
    extern char* yytext;


    extern void printTextPart(Location loc, ostream &out = std::cout);
    Location currLocation;
    Location getLocation() {
        return currLocation;
    }
    void setLocation(YYLTYPE loc) {
        currLocation = Location(loc.first_line, loc.first_column, loc.last_line, loc.last_column);
    }
    void processRule(YYLTYPE loc, const char* ruleName) {
        setLocation(loc);
        //printf("%s ", ruleName);
        //currLocation.print();
        //printTextPart(currLocation);
    }

    std::shared_ptr<CGoal> Goal;

#line 112 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
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
   by #include "tokens.h".  */
#ifndef YY_YY_HOME_NICOLAI_WORK_MINIJAVACOMPILER_SRC_TOKENS_H_INCLUDED
# define YY_YY_HOME_NICOLAI_WORK_MINIJAVACOMPILER_SRC_TOKENS_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    MAIN = 258,
    MAIN_ARGS = 259,
    PUBLIC = 260,
    VOID = 261,
    STATIC = 262,
    CLASS = 263,
    RETURN = 264,
    WHILE = 265,
    PRINT = 266,
    LENGTH = 267,
    NEW = 268,
    EXTENDS = 269,
    THIS = 270,
    INT = 271,
    BOOL = 272,
    INT_VALUE = 273,
    BOOL_VALUE = 274,
    AND = 275,
    EQ = 276,
    NOT = 277,
    _ID = 278,
    IF = 279,
    ELSE = 280
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 48 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:355  */

    IExpression* expression;
    CExpressionList* expressionList;
    CConstant* constant;
    IStatement* statement;
    CStatementList* statementList;
    CMethodBodyDeclaration* methodBodyDeclaration;
    CType* type;
    CVarDeclaration* varDeclaration;
    CMethodArgumentsList* methodArgumentsList;
    CMethodHeaderDeclaration* methodHeaderDeclaration;
    CMethodDeclaration* methodDeclaration;
    CMethodDeclarationList* methodDeclarationList;
    CIdentifier* identifier;
    CClassDeclaration* classDeclaration;
    CMainClass* mainClass;
    CClassDeclarationList* classDeclarationList;

    TVarAndStatementDeclaration varAndStatementDeclaration;
    TVarAndMethodDeclaration varAndMethodDeclaration;

#line 200 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_HOME_NICOLAI_WORK_MINIJAVACOMPILER_SRC_TOKENS_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 229 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

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
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   445

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  81
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  210

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   280

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      33,    34,    27,    23,    37,    24,    25,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    36,
      26,    39,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    29,     2,    38,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    32,     2,    35,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    28,    30,
      31
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   105,   105,   110,   114,   119,   123,   129,   137,   142,
     146,   151,   156,   161,   164,   168,   172,   178,   183,   187,
     193,   200,   204,   208,   213,   218,   222,   226,   230,   236,
     240,   245,   250,   255,   261,   265,   270,   274,   278,   282,
     286,   290,   295,   299,   305,   311,   318,   322,   327,   331,
     336,   340,   346,   350,   356,   364,   368,   372,   376,   380,
     384,   388,   392,   396,   400,   404,   408,   412,   416,   420,
     424,   428,   433,   437,   443,   447,   451,   457,   461,   465,
     469,   474
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "MAIN", "MAIN_ARGS", "PUBLIC", "VOID",
  "STATIC", "CLASS", "RETURN", "WHILE", "PRINT", "LENGTH", "NEW",
  "EXTENDS", "THIS", "INT", "BOOL", "INT_VALUE", "BOOL_VALUE", "AND", "EQ",
  "NOT", "'+'", "'-'", "'.'", "'<'", "'*'", "_ID", "'['", "IF", "ELSE",
  "'{'", "'('", "')'", "'}'", "';'", "','", "']'", "'='", "$accept",
  "GOAL", "CLASS_LIST", "MAIN_CLASS", "CLASS_DECLARATION", "BASE_CLASS",
  "VAR_AND_METHOD_DECLARATION", "METHOD_DECLARATION_LIST",
  "VAR_DECLARATION", "METHOD_DECLARATION", "METHOD_HEADER",
  "ARGS_DECLARATION", "PARAM_DECLARATION", "TYPE", "INT_ARRAY",
  "METHOD_BODY", "VAR_AND_STATEMENT_DECLARATIONS", "STATEMENT_DECLARATION",
  "STATEMENT", "IF_STATEMENT", "WHILE_STATEMENT", "PRINT_STATEMENT",
  "ASSIGNMENT", "ARRAY_ASSIGNMENT", "EXPR", "CONSTANT", "PARAMS",
  "NEW_EXPR", "ID", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,    43,    45,    46,    60,    42,   278,    91,
     279,   280,   123,    40,    41,   125,    59,    44,    93,    61
};
# endif

#define YYPACT_NINF -89

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-89)))

#define YYTABLE_NINF -75

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      42,    24,    56,    71,   -89,    54,   -89,    24,   -89,    71,
      44,    73,   -89,    88,    85,    24,    61,    68,    96,   -89,
      72,   104,   111,    24,    -7,    92,   -89,    98,   -89,    72,
       7,    91,    24,   -89,   -89,    24,   106,    45,    24,     1,
     -89,   -89,    24,   -89,   263,    93,    97,   105,    -7,   -89,
     107,    99,   -89,   113,    24,   115,   120,   121,   117,   263,
     100,   135,   -89,   117,   -89,   -89,   -89,   -89,   -89,   -24,
     -89,   124,   125,    24,   128,   126,    24,   102,   -89,   122,
     173,   181,   189,   130,   -24,   -89,   -89,    52,   -89,   197,
     219,   117,   134,   133,   -89,    -7,   -89,   137,   138,   139,
      -3,   -89,   -89,   -89,    52,    52,   368,   -89,   -89,   -89,
     143,   380,   144,   392,   -89,   312,   131,   261,   132,   326,
     145,   117,   147,   -89,   -89,   -89,   117,   152,   154,   416,
     404,    52,    52,    52,    52,    -8,    52,    52,   227,   117,
     153,   157,   117,    16,   -89,   158,   166,   -89,   -89,   178,
     183,   117,   -89,   235,     6,   -89,   416,   416,     3,     3,
     -89,   188,     3,   194,   186,   277,   -89,   -89,   -89,   195,
     196,   198,    52,   243,   -89,   200,   204,   193,   287,   199,
     -89,   142,   -89,   -89,   117,   117,    94,   340,   207,   354,
     -89,   216,   -89,   -89,   -89,   225,   297,   232,   -89,   -89,
     -89,   -89,   -89,   -89,   -89,   -89,   -89,    52,   -89,   -89
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     4,    81,     0,     1,     0,     2,     4,
       0,     9,     3,     0,     0,     0,     0,     0,     0,    10,
       0,     0,     0,     0,     0,    27,    26,     0,    12,     0,
       0,     0,     0,    25,    28,     0,     0,     0,     0,     0,
       8,    11,     0,    13,     0,     0,     0,     0,    21,    16,
       0,     0,    29,     0,     0,     0,     0,     0,    35,     0,
       0,     0,    33,    35,    37,    38,    39,    40,    41,    28,
      15,     0,     0,     0,     0,    22,     0,     0,    30,     0,
       0,     0,     0,     0,     0,    32,    17,     0,    34,     0,
       0,     0,     0,     0,    20,    21,    24,     0,     0,     0,
       0,    65,    72,    73,     0,     0,     0,    66,    63,    64,
       0,     0,     0,     0,    36,     0,     0,     0,     0,     0,
       0,     0,     0,    23,    19,    18,     0,     0,     0,    61,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    31,     0,     0,    51,    50,     0,
       0,     0,    47,     0,     0,    62,    58,    60,    55,    56,
      69,     0,    59,    57,     0,     0,    46,    49,    48,     0,
       0,     0,     0,     0,     7,     0,     0,     0,     0,     0,
      79,     0,    68,    67,     0,     0,     0,     0,     0,     0,
       6,     0,    78,    77,    80,     0,    75,     0,    43,    44,
      45,    42,    53,    54,    52,     5,    71,    74,    70,    76
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -89,   -89,   258,   -89,   -89,   -89,   240,   245,   -43,   -89,
     -89,   -59,   -89,   -13,   -89,   -89,   211,   -34,   -88,   -89,
     -89,   -89,   -89,   -89,   -21,   -89,    70,   -89,    -1
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     8,     3,     9,    16,    27,    28,    29,    30,
      31,    74,    75,    32,    33,    60,    61,    62,    63,    64,
      65,    66,    67,    68,   196,   107,   197,   108,   109
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       5,    59,    51,   120,   160,    89,    11,   179,    42,    25,
      26,    38,    24,   127,    19,    90,    59,   170,    98,    34,
       4,     4,    37,    34,    83,     4,    55,    56,    34,    88,
     137,    45,   138,   150,    46,    76,   123,    50,   152,    52,
     180,    53,   -14,    69,     4,    13,    57,    34,    58,    14,
       1,   166,     4,    79,   169,   171,     6,    84,    69,   106,
     111,   113,    84,   176,    76,   100,   115,   101,   117,   119,
     102,   103,    93,    23,   104,    96,    34,    24,    48,     7,
       4,    49,    76,   129,   130,   105,    10,    15,    25,    26,
      84,    17,    18,    20,    34,   200,   198,   199,   201,   128,
       4,    21,    22,    97,    55,    56,    72,   -14,    35,    73,
     156,   157,   158,   159,    36,   162,   163,   165,    25,    26,
      84,    39,     4,    44,    57,    84,    58,    55,    56,    70,
       4,    71,   178,    40,   161,    86,   -21,    78,    84,    47,
      77,    84,    84,   195,    87,     4,    48,    57,    80,    58,
      84,   187,   189,    81,    82,   100,    91,   101,    49,    92,
     102,   103,    94,    95,   104,   114,   121,   122,   147,   145,
       4,   124,   125,   126,    99,   105,   -74,   140,   142,   151,
     149,   153,   110,    84,    84,    84,   100,   154,   101,   167,
     112,   102,   103,   168,   100,   104,   101,   172,   116,   102,
     103,     4,   100,   104,   101,   173,   105,   102,   103,     4,
     100,   104,   101,   174,   105,   102,   103,     4,   175,   104,
     118,   181,   105,   138,   182,     4,   184,   185,   164,   186,
     105,   192,   100,   194,   101,   190,   177,   102,   103,   191,
     100,   104,   101,   203,   188,   102,   103,     4,   100,   104,
     101,   205,   105,   102,   103,     4,   100,   104,   101,   206,
     105,   102,   103,     4,    54,   104,   208,    12,   105,    41,
      85,     4,   -35,    55,    56,    43,   105,   209,     0,    25,
      26,   131,   132,     0,   133,   134,   135,   136,   137,     0,
     138,     4,     0,    57,     0,    58,     0,   131,   132,   146,
     133,   134,   135,   136,   137,     0,   138,   131,   132,     0,
     133,   134,   135,   136,   137,   183,   138,   131,   132,     0,
     133,   134,   135,   136,   137,   193,   138,     0,     0,     0,
       0,     0,   131,   132,   207,   133,   134,   135,   136,   137,
       0,   138,     0,     0,     0,     0,   131,   132,   144,   133,
     134,   135,   136,   137,     0,   138,     0,     0,     0,     0,
     131,   132,   148,   133,   134,   135,   136,   137,     0,   138,
       0,     0,     0,     0,   131,   132,   202,   133,   134,   135,
     136,   137,     0,   138,     0,     0,     0,     0,   131,   132,
     204,   133,   134,   135,   136,   137,     0,   138,     0,     0,
     131,   132,   139,   133,   134,   135,   136,   137,     0,   138,
       0,     0,   131,   132,   141,   133,   134,   135,   136,   137,
       0,   138,     0,     0,   131,   132,   143,   133,   134,   135,
     136,   137,     0,   138,     0,     0,     0,     0,   155,   133,
     134,   135,   136,   137,     0,   138
};

static const yytype_int16 yycheck[] =
{
       1,    44,     1,    91,    12,    29,     7,     1,     1,    16,
      17,    24,     5,    16,    15,    39,    59,     1,    77,    20,
      28,    28,    23,    24,    58,    28,    10,    11,    29,    63,
      27,    32,    29,   121,    35,    48,    95,    38,   126,    38,
      34,    42,    35,    44,    28,     1,    30,    48,    32,     5,
       8,   139,    28,    54,   142,   143,     0,    58,    59,    80,
      81,    82,    63,   151,    77,    13,    87,    15,    89,    90,
      18,    19,    73,     1,    22,    76,    77,     5,    33,     8,
      28,    36,    95,   104,   105,    33,    32,    14,    16,    17,
      91,     3,     7,    32,    95,     1,   184,   185,   186,   100,
      28,    33,     6,     1,    10,    11,     1,    35,     4,     4,
     131,   132,   133,   134,     3,   136,   137,   138,    16,    17,
     121,    29,    28,    32,    30,   126,    32,    10,    11,    36,
      28,    34,   153,    35,   135,    35,    34,    38,   139,    33,
      33,   142,   143,     1,     9,    28,    33,    30,    33,    32,
     151,   172,   173,    33,    33,    13,    32,    15,    36,    34,
      18,    19,    34,    37,    22,    35,    32,    34,    36,    38,
      28,    34,    34,    34,     1,    33,    34,    34,    34,    32,
      35,    29,     1,   184,   185,   186,    13,    33,    15,    36,
       1,    18,    19,    36,    13,    22,    15,    39,     1,    18,
      19,    28,    13,    22,    15,    39,    33,    18,    19,    28,
      13,    22,    15,    35,    33,    18,    19,    28,    35,    22,
       1,    33,    33,    29,    38,    28,    31,    31,     1,    31,
      33,    38,    13,    34,    15,    35,     1,    18,    19,    35,
      13,    22,    15,    36,     1,    18,    19,    28,    13,    22,
      15,    35,    33,    18,    19,    28,    13,    22,    15,    34,
      33,    18,    19,    28,     1,    22,    34,     9,    33,    29,
      59,    28,     9,    10,    11,    30,    33,   207,    -1,    16,
      17,    20,    21,    -1,    23,    24,    25,    26,    27,    -1,
      29,    28,    -1,    30,    -1,    32,    -1,    20,    21,    38,
      23,    24,    25,    26,    27,    -1,    29,    20,    21,    -1,
      23,    24,    25,    26,    27,    38,    29,    20,    21,    -1,
      23,    24,    25,    26,    27,    38,    29,    -1,    -1,    -1,
      -1,    -1,    20,    21,    37,    23,    24,    25,    26,    27,
      -1,    29,    -1,    -1,    -1,    -1,    20,    21,    36,    23,
      24,    25,    26,    27,    -1,    29,    -1,    -1,    -1,    -1,
      20,    21,    36,    23,    24,    25,    26,    27,    -1,    29,
      -1,    -1,    -1,    -1,    20,    21,    36,    23,    24,    25,
      26,    27,    -1,    29,    -1,    -1,    -1,    -1,    20,    21,
      36,    23,    24,    25,    26,    27,    -1,    29,    -1,    -1,
      20,    21,    34,    23,    24,    25,    26,    27,    -1,    29,
      -1,    -1,    20,    21,    34,    23,    24,    25,    26,    27,
      -1,    29,    -1,    -1,    20,    21,    34,    23,    24,    25,
      26,    27,    -1,    29,    -1,    -1,    -1,    -1,    34,    23,
      24,    25,    26,    27,    -1,    29
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,    41,    43,    28,    68,     0,     8,    42,    44,
      32,    68,    42,     1,     5,    14,    45,     3,     7,    68,
      32,    33,     6,     1,     5,    16,    17,    46,    47,    48,
      49,    50,    53,    54,    68,     4,     3,    68,    53,    29,
      35,    46,     1,    47,    32,    68,    68,    33,    33,    36,
      68,     1,    38,    68,     1,    10,    11,    30,    32,    48,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    68,
      36,    34,     1,     4,    51,    52,    53,    33,    38,    68,
      33,    33,    33,    57,    68,    56,    35,     9,    57,    29,
      39,    32,    34,    68,    34,    37,    68,     1,    51,     1,
      13,    15,    18,    19,    22,    33,    64,    65,    67,    68,
       1,    64,     1,    64,    35,    64,     1,    64,     1,    64,
      58,    32,    34,    51,    34,    34,    34,    16,    68,    64,
      64,    20,    21,    23,    24,    25,    26,    27,    29,    34,
      34,    34,    34,    34,    36,    38,    38,    36,    36,    35,
      58,    32,    58,    29,    33,    34,    64,    64,    64,    64,
      12,    68,    64,    64,     1,    64,    58,    36,    36,    58,
       1,    58,    39,    39,    35,    35,    58,     1,    64,     1,
      34,    33,    38,    38,    31,    31,    31,    64,     1,    64,
      35,    35,    38,    38,    34,     1,    64,    66,    58,    58,
       1,    58,    36,    36,    36,    35,    34,    37,    34,    66
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    43,    43,    44,    45,
      45,    46,    46,    47,    47,    48,    48,    49,    50,    50,
      50,    51,    51,    51,    52,    53,    53,    53,    53,    54,
      54,    55,    56,    56,    57,    57,    58,    58,    58,    58,
      58,    58,    59,    59,    59,    59,    60,    60,    61,    61,
      62,    62,    63,    63,    63,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    65,    65,    66,    66,    66,    67,    67,    67,
      67,    68
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     0,    15,    14,    13,     6,     0,
       2,     2,     1,     2,     0,     3,     3,     4,     6,     6,
       5,     0,     1,     3,     2,     1,     1,     1,     1,     3,
       4,     4,     2,     1,     2,     0,     3,     1,     1,     1,
       1,     1,     7,     7,     7,     7,     5,     5,     5,     5,
       4,     4,     7,     7,     7,     3,     3,     3,     3,     3,
       3,     2,     3,     1,     1,     1,     1,     4,     4,     3,
       6,     6,     1,     1,     0,     1,     3,     5,     5,     4,
       5,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yychar = yylex ();
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
  *++yylsp = yylloc;
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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 105 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "GOAL");
    Goal = std::shared_ptr<CGoal>(new CGoal(getLocation(), (yyvsp[-1].mainClass), (yyvsp[0].classDeclarationList)));
}
#line 1585 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 110 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "CLASS_LIST");
    (yyval.classDeclarationList) = new CClassDeclarationList(getLocation(), (yyvsp[-1].classDeclaration), (yyvsp[0].classDeclarationList));
}
#line 1594 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 114 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "ARGS_DECLARATION");
    (yyval.classDeclarationList) = nullptr;
}
#line 1603 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 119 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "MAIN_CLASS");
    (yyval.mainClass) = new CMainClass(getLocation(), (yyvsp[-13].identifier), (yyvsp[-5].identifier), (yyvsp[-2].statement));
}
#line 1612 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 123 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "MAIN_CLASS");
    delete (yyvsp[-12].identifier);
    delete (yyvsp[-2].statement);
    (yyval.mainClass) = nullptr;
}
#line 1623 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 129 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "MAIN_CLASS");
    delete (yyvsp[-11].identifier);
    delete (yyvsp[-5].identifier);
    delete (yyvsp[-2].statement);
    (yyval.mainClass) = nullptr;
}
#line 1635 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 137 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "CLASS_DECLARATION");
    (yyval.classDeclaration) = new CClassDeclaration(getLocation(), (yyvsp[-4].identifier), (yyvsp[-3].identifier), (yyvsp[-1].varAndMethodDeclaration).varDeclList, (yyvsp[-1].varAndMethodDeclaration).methodDeclList);
}
#line 1644 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 142 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "BASE_CLASS");
    (yyval.identifier) = nullptr;
}
#line 1653 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 146 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "BASE_CLASS");
    (yyval.identifier) =  (yyvsp[0].identifier);
}
#line 1662 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 151 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "VAR_AND_METHOD_DECLARATION");
    (yyvsp[0].varAndMethodDeclaration).varDeclList = new CVarDeclarationList(getLocation(), (yyvsp[-1].varDeclaration), (yyvsp[0].varAndMethodDeclaration).varDeclList);
    (yyval.varAndMethodDeclaration) = (yyvsp[0].varAndMethodDeclaration);
}
#line 1672 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 156 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    (yyval.varAndMethodDeclaration).varDeclList = nullptr;
    (yyval.varAndMethodDeclaration).methodDeclList = (yyvsp[0].methodDeclarationList);
}
#line 1681 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 161 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    (yyval.methodDeclarationList) = new CMethodDeclarationList(getLocation(), (yyvsp[-1].methodDeclaration), (yyvsp[0].methodDeclarationList));
}
#line 1689 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 164 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    (yyval.methodDeclarationList) = nullptr;
}
#line 1697 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 168 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "VAR_DECLARATION");
    (yyval.varDeclaration) = new CVarDeclaration(getLocation(), (yyvsp[-2].type), (yyvsp[-1].identifier));
}
#line 1706 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 172 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "VAR_DECLARATION");
    delete (yyvsp[-1].identifier);
    (yyval.varDeclaration) = nullptr;
}
#line 1716 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 178 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "METHOD_DECLARATION");
    (yyval.methodDeclaration) = new CMethodDeclaration(getLocation(), (yyvsp[-3].methodHeaderDeclaration), (yyvsp[-1].methodBodyDeclaration));
}
#line 1725 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 183 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "METHOD_HEADER");
    (yyval.methodHeaderDeclaration) = new CMethodHeaderDeclaration(getLocation(), (yyvsp[-4].type), (yyvsp[-3].identifier), (yyvsp[-1].methodArgumentsList));
}
#line 1734 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 187 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "METHOD_HEADER");
    delete (yyvsp[-4].type);
    delete (yyvsp[-3].identifier);
    (yyval.methodHeaderDeclaration) = nullptr;
}
#line 1745 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 193 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "METHOD_HEADER");
    delete (yyvsp[-3].identifier);
    delete (yyvsp[-1].methodArgumentsList);
    (yyval.methodHeaderDeclaration) = nullptr;
}
#line 1756 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 200 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "ARGS_DECLARATION");
    (yyval.methodArgumentsList) = nullptr;
}
#line 1765 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 204 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
     processRule((yyloc), "ARGS_DECLARATION");
     (yyval.methodArgumentsList) = new CMethodArgumentsList(getLocation(), (yyvsp[0].varDeclaration), nullptr);
 }
#line 1774 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 208 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "ARGS_DECLARATION");
    (yyval.methodArgumentsList) = new CMethodArgumentsList(getLocation(), (yyvsp[-2].varDeclaration), (yyvsp[0].methodArgumentsList));
}
#line 1783 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 213 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "PARAM_DECLARATION");
    (yyval.varDeclaration) = new CVarDeclaration(getLocation(), (yyvsp[-1].type), (yyvsp[0].identifier));
}
#line 1792 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 218 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "INT_ARRAY");
    (yyval.type) = (yyvsp[0].type);
}
#line 1801 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 222 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "TYPE");
    (yyval.type) = new CType(getLocation(), T_BOOL, globalStorage.Get("boolean"));
}
#line 1810 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 226 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "TYPE");
    (yyval.type) = new CType(getLocation(), T_INT, globalStorage.Get("int"));
}
#line 1819 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 230 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "TYPE");
    (yyval.type) = new CType(getLocation(), T_CLASS, (yyvsp[0].identifier)->Symbol);
    delete (yyvsp[0].identifier);
}
#line 1829 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 236 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "INT_ARRAY");
    (yyval.type) = new CType(getLocation(), T_INT_ARRAY, globalStorage.Get("int[]"));
}
#line 1838 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 240 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "INT_ARRAY");
    (yyval.type) = nullptr;
}
#line 1847 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 245 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "METHOD_BODY");
    (yyval.methodBodyDeclaration) = new CMethodBodyDeclaration(getLocation(), (yyvsp[-3].varAndStatementDeclaration).varDeclList, (yyvsp[-3].varAndStatementDeclaration).statementList, (yyvsp[-1].expression));
}
#line 1856 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 250 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "VAR_AND_STATEMENT_DECLARATIONS");
    (yyvsp[0].varAndStatementDeclaration).varDeclList = new CVarDeclarationList(getLocation(), (yyvsp[-1].varDeclaration), (yyvsp[0].varAndStatementDeclaration).varDeclList);
    (yyval.varAndStatementDeclaration) = (yyvsp[0].varAndStatementDeclaration);
}
#line 1866 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 255 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "VAR_AND_STATEMENT_DECLARATIONS");
    (yyval.varAndStatementDeclaration).statementList = (yyvsp[0].statementList);
    (yyval.varAndStatementDeclaration).varDeclList = nullptr;
}
#line 1876 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 261 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "STATEMENT_DECLARATION");
    (yyval.statementList) = new CStatementList(getLocation(), (yyvsp[-1].statement), (yyvsp[0].statementList));
}
#line 1885 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 265 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "STATEMENT_DECLARATION");
    (yyval.statementList) = nullptr;
}
#line 1894 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 270 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "STATEMENT");
    (yyval.statement) = new CBracketStatement(getLocation(), (yyvsp[-1].statementList));
}
#line 1903 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 274 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "STATEMENT");
    (yyval.statement) = (yyvsp[0].statement);
}
#line 1912 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 278 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "STATEMENT");
    (yyval.statement) = (yyvsp[0].statement);
}
#line 1921 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 282 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "STATEMENT");
    (yyval.statement) = (yyvsp[0].statement);
}
#line 1930 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 286 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "STATEMENT");
    (yyval.statement) = (yyvsp[0].statement);
}
#line 1939 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 290 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "STATEMENT");
    (yyval.statement) = (yyvsp[0].statement);
}
#line 1948 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 295 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "IF_STATEMENT");
    (yyval.statement) = new CIfStatement(getLocation(), (yyvsp[-4].expression), (yyvsp[-2].statement), (yyvsp[0].statement));
}
#line 1957 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 299 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "IF_STATEMENT");
    delete (yyvsp[-2].statement);
    delete (yyvsp[0].statement);
    (yyval.statement) = nullptr;
}
#line 1968 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 305 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "IF_STATEMENT");
    delete (yyvsp[-4].expression);
    delete (yyvsp[0].statement);
    (yyval.statement) = nullptr;
}
#line 1979 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 311 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "IF_STATEMENT");
    delete (yyvsp[-4].expression);
    delete (yyvsp[-2].statement);
    (yyval.statement) = nullptr;
}
#line 1990 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 318 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "WHILE_STATEMENT");
    (yyval.statement) = new CWhileStatement(getLocation(), (yyvsp[-2].expression), (yyvsp[0].statement));
}
#line 1999 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 322 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "WHILE_STATEMENT");
    (yyval.statement) = nullptr;
}
#line 2008 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 327 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "PRINT_STATEMENT");
    (yyval.statement) = new CPrintStatement(getLocation(), (yyvsp[-2].expression));
}
#line 2017 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 331 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "PRINT_STATEMENT");
    (yyval.statement) = nullptr;
}
#line 2026 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 336 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "ASSIGNMENT");
    (yyval.statement) = new CAssignmentStatement(getLocation(), (yyvsp[-1].expression), new CVariable(getLocation(), (yyvsp[-3].identifier)));
}
#line 2035 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 340 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "ASSIGNMENT");
    delete (yyvsp[-3].identifier);
    (yyval.statement) = nullptr;
}
#line 2045 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 346 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "ARRAY_ASSIGNMENT");
    (yyval.statement) = new CIntArrayAssignmentStatement(getLocation(), (yyvsp[-4].expression), (yyvsp[-1].expression), new CVariable(getLocation(), (yyvsp[-6].identifier)));
}
#line 2054 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 350 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "ARRAY_ASSIGNMENT");
    delete (yyvsp[-6].identifier);
    delete (yyvsp[-1].expression);
    (yyval.statement) = nullptr;
}
#line 2065 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 356 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "ARRAY_ASSIGNMENT");
    delete (yyvsp[-6].identifier);
    delete (yyvsp[-4].expression);
    (yyval.statement) = nullptr;
}
#line 2076 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 364 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "EXPR");
    (yyval.expression) = new CBinaryExpression(getLocation(), (yyvsp[-2].expression), (yyvsp[0].expression), BE_PLUS);
}
#line 2085 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 368 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "EXPR");
    (yyval.expression) = new CBinaryExpression(getLocation(), (yyvsp[-2].expression), (yyvsp[0].expression), BE_MINUS);
}
#line 2094 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 372 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "EXPR");
    (yyval.expression) = new CBinaryExpression(getLocation(), (yyvsp[-2].expression), (yyvsp[0].expression), BE_MULTIPLICATION);
}
#line 2103 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 376 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "EXPR");
    (yyval.expression) = new CBinaryExpression(getLocation(), (yyvsp[-2].expression), (yyvsp[0].expression), BE_AND);
}
#line 2112 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 380 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "EXPR");
    (yyval.expression) = new CBinaryExpression(getLocation(), (yyvsp[-2].expression), (yyvsp[0].expression), BE_LESS);
}
#line 2121 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 384 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "EXPR");
    (yyval.expression) = new CBinaryExpression(getLocation(), (yyvsp[-2].expression), (yyvsp[0].expression), BE_EQUAL);
}
#line 2130 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 388 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "EXPR");
    (yyval.expression) = new CNotExpression(getLocation(), (yyvsp[0].expression));
}
#line 2139 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 392 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "EXPR");
    (yyval.expression) = new CBracketExpression(getLocation(), (yyvsp[-1].expression));
}
#line 2148 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 396 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "EXPR");
    (yyval.expression) = (yyvsp[0].expression);
}
#line 2157 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 400 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "EXPR");
    (yyval.expression) = new CVariable(getLocation(), (yyvsp[0].identifier));
}
#line 2166 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 404 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "EXPR");
    (yyval.expression) = new CVariable(getLocation(), new CIdentifier(getLocation(), globalStorage.Get("this")));
}
#line 2175 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 408 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "EXPR");
    (yyval.expression) = (yyvsp[0].constant);
}
#line 2184 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 412 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "INVOKE_EXPR");
    (yyval.expression) = new CBinaryExpression(getLocation(), (yyvsp[-3].expression), (yyvsp[-1].expression), BE_SQ_BRACKETS);
}
#line 2193 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 416 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "INVOKE_EXPR");
    (yyval.expression) = 0;
}
#line 2202 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 420 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "INVOKE_EXPR");
    (yyval.expression) = new CLengthExpression(getLocation(), (yyvsp[-2].expression));
}
#line 2211 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 424 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "INVOKE_EXPR");
    (yyval.expression) = new CInvocation(getLocation(), (yyvsp[-5].expression), (yyvsp[-3].identifier), (yyvsp[-1].expressionList));
}
#line 2220 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 428 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "INVOKE_EXPR");
    (yyval.expression) = 0;
}
#line 2229 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 433 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "CONSTANT");
    (yyval.constant) = new CConstant(getLocation(), new CType(getLocation(), T_INT, globalStorage.Get("int")), yytext);
}
#line 2238 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 437 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "CONSTANT");
    (yyval.constant) = new CConstant(getLocation(), new CType(getLocation(), T_BOOL, globalStorage.Get("boolean")), yytext);
}
#line 2247 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 443 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "PARAMS");
    (yyval.expressionList) = 0;
}
#line 2256 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 447 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "PARAMS");
    (yyval.expressionList) = new CExpressionList(getLocation(), (yyvsp[0].expression), 0);
}
#line 2265 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 451 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "PARAMS");
    (yyval.expressionList) = new CExpressionList(getLocation(), (yyvsp[-2].expression), (yyvsp[0].expressionList));
}
#line 2274 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 457 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "NEW_EXPR");
    (yyval.expression) = new CIntArrayNewExpression(getLocation(), (yyvsp[-1].expression));
}
#line 2283 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 461 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "NEW_EXPR");
    (yyval.expression) = 0;
}
#line 2292 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 465 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "NEW_EXPR");
    (yyval.expression) = new CNewExpression(getLocation(), (yyvsp[-2].identifier));
}
#line 2301 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 469 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "NEW_EXPR");
    (yyval.expression) = 0;
}
#line 2310 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 474 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1646  */
    {
    processRule((yyloc), "NEW_EXPR");
    (yyval.identifier) = new CIdentifier(getLocation(), globalStorage.Get(yytext));
}
#line 2319 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
    break;


#line 2323 "/home/nicolai/work/MiniJavaCompiler/src/bison.cpp" /* yacc.c:1646  */
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
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
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
  return yyresult;
}
#line 479 "/home/nicolai/work/MiniJavaCompiler/src/minijava.y" /* yacc.c:1906  */


extern void printError(Location location, const char *s);
void yyerror(const char *s)
{
    printError(Location(yylloc.first_line, yylloc.first_column, yylloc.last_line, yylloc.last_column), s);
}
extern int main(int argc, const char* argv[]);
