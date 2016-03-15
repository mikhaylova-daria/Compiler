/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
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
     NOT = 275,
     EQ = 276,
     AND = 277,
     _ID = 278,
     IF = 279,
     ELSE = 280
   };
#endif
/* Tokens.  */
#define MAIN 258
#define MAIN_ARGS 259
#define PUBLIC 260
#define VOID 261
#define STATIC 262
#define CLASS 263
#define RETURN 264
#define WHILE 265
#define PRINT 266
#define LENGTH 267
#define NEW 268
#define EXTENDS 269
#define THIS 270
#define INT 271
#define BOOL 272
#define INT_VALUE 273
#define BOOL_VALUE 274
#define NOT 275
#define EQ 276
#define AND 277
#define _ID 278
#define IF 279
#define ELSE 280




/* Copy the first part of user declarations.  */
#line 2 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"


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


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 48 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
{
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
}
/* Line 193 of yacc.c.  */
#line 214 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/bison.cpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 239 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/bison.cpp"

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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   462

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  81
/* YYNRULES -- Number of states.  */
#define YYNSTATES  210

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   280

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     9,    10,    26,    41,    55,    62,
      63,    66,    69,    71,    74,    75,    79,    83,    88,    95,
     102,   108,   109,   111,   115,   118,   120,   122,   124,   126,
     130,   135,   140,   143,   145,   148,   149,   153,   155,   157,
     159,   161,   163,   171,   179,   187,   195,   201,   207,   213,
     219,   224,   229,   237,   245,   253,   257,   261,   265,   269,
     273,   277,   280,   284,   286,   288,   290,   292,   297,   302,
     306,   313,   320,   322,   324,   325,   327,   331,   337,   343,
     348,   354
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      41,     0,    -1,    43,    42,    -1,    44,    42,    -1,    -1,
       8,    68,    32,     5,     7,     6,     3,    33,     4,    68,
      34,    32,    58,    35,    35,    -1,     8,    68,    32,     5,
       7,     6,     3,    33,     1,    34,    32,    58,    35,    35,
      -1,     8,    68,    32,     1,     3,    33,     4,    68,    34,
      32,    58,    35,    35,    -1,     8,    68,    45,    32,    46,
      35,    -1,    -1,    14,    68,    -1,    48,    46,    -1,    47,
      -1,    49,    47,    -1,    -1,    53,    68,    36,    -1,     1,
      68,    36,    -1,    50,    32,    55,    35,    -1,     5,    53,
      68,    33,    51,    34,    -1,     5,    53,    68,    33,     1,
      34,    -1,     1,    68,    33,    51,    34,    -1,    -1,    52,
      -1,    52,    37,    51,    -1,    53,    68,    -1,    54,    -1,
      17,    -1,    16,    -1,    68,    -1,    16,    29,    38,    -1,
      16,    29,     1,    38,    -1,    56,     9,    64,    36,    -1,
      48,    56,    -1,    57,    -1,    58,    57,    -1,    -1,    32,
      57,    35,    -1,    59,    -1,    60,    -1,    61,    -1,    62,
      -1,    63,    -1,    30,    33,    64,    34,    58,    31,    58,
      -1,    30,    33,     1,    34,    58,    31,    58,    -1,    30,
      33,    64,    34,     1,    31,    58,    -1,    30,    33,    64,
      34,    58,    31,     1,    -1,    10,    33,    64,    34,    58,
      -1,    10,    33,     1,    34,    58,    -1,    11,    33,    64,
      34,    36,    -1,    11,    33,     1,    34,    36,    -1,    68,
      39,    64,    36,    -1,    68,    39,     1,    36,    -1,    68,
      29,    64,    38,    39,    64,    36,    -1,    68,    29,     1,
      38,    39,    64,    36,    -1,    68,    29,    64,    38,    39,
       1,    36,    -1,    64,    23,    64,    -1,    64,    24,    64,
      -1,    64,    27,    64,    -1,    64,    22,    64,    -1,    64,
      26,    64,    -1,    64,    21,    64,    -1,    20,    64,    -1,
      33,    64,    34,    -1,    67,    -1,    68,    -1,    15,    -1,
      65,    -1,    64,    29,    64,    38,    -1,    64,    29,     1,
      38,    -1,    64,    25,    12,    -1,    64,    25,    68,    33,
      66,    34,    -1,    64,    25,    68,    33,     1,    34,    -1,
      18,    -1,    19,    -1,    -1,    64,    -1,    64,    37,    66,
      -1,    13,    16,    29,    64,    38,    -1,    13,    16,    29,
       1,    38,    -1,    13,    68,    33,    34,    -1,    13,    68,
      33,     1,    34,    -1,    28,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
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

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "MAIN", "MAIN_ARGS", "PUBLIC", "VOID",
  "STATIC", "CLASS", "RETURN", "WHILE", "PRINT", "LENGTH", "NEW",
  "EXTENDS", "THIS", "INT", "BOOL", "INT_VALUE", "BOOL_VALUE", "NOT", "EQ",
  "AND", "'+'", "'-'", "'.'", "'<'", "'*'", "_ID", "'['", "IF", "ELSE",
  "'{'", "'('", "')'", "'}'", "';'", "','", "']'", "'='", "$accept",
  "GOAL", "CLASS_LIST", "MAIN_CLASS", "CLASS_DECLARATION", "BASE_CLASS",
  "VAR_AND_METHOD_DECLARATION", "METHOD_DECLARATION_LIST",
  "VAR_DECLARATION", "METHOD_DECLARATION", "METHOD_HEADER",
  "ARGS_DECLARATION", "PARAM_DECLARATION", "TYPE", "INT_ARRAY",
  "METHOD_BODY", "VAR_AND_STATEMENT_DECLARATIONS", "STATEMENT_DECLARATION",
  "STATEMENT", "IF_STATEMENT", "WHILE_STATEMENT", "PRINT_STATEMENT",
  "ASSIGNMENT", "ARRAY_ASSIGNMENT", "EXPR", "CONSTANT", "PARAMS",
  "NEW_EXPR", "ID", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,    43,    45,    46,    60,    42,   278,    91,
     279,   280,   123,    40,    41,   125,    59,    44,    93,    61
};
# endif

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

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
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

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
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
       0,     0,    47,     0,     0,    62,    60,    58,    55,    56,
      69,     0,    59,    57,     0,     0,    46,    49,    48,     0,
       0,     0,     0,     0,     7,     0,     0,     0,     0,     0,
      79,     0,    68,    67,     0,     0,     0,     0,     0,     0,
       6,     0,    78,    77,    80,     0,    75,     0,    43,    44,
      45,    42,    53,    54,    52,     5,    71,    74,    70,    76
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     8,     3,     9,    16,    27,    28,    29,    30,
      31,    74,    75,    32,    33,    60,    61,    62,    63,    64,
      65,    66,    67,    68,   196,   107,   197,   108,   109
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -89
static const yytype_int16 yypact[] =
{
      42,    24,    56,    57,   -89,    46,   -89,    24,   -89,    57,
      44,    65,   -89,    77,    74,    24,    53,    54,    80,   -89,
      72,    87,    89,    24,    -7,    64,   -89,    66,   -89,    72,
       7,    76,    24,   -89,   -89,    24,    69,    34,    24,     1,
     -89,   -89,    24,   -89,   257,    73,    95,    70,    -7,   -89,
      81,    68,   -89,    88,    24,    90,    98,   100,   117,   257,
     104,   126,   -89,   117,   -89,   -89,   -89,   -89,   -89,   -24,
     -89,   105,   106,    24,   110,   109,    24,   102,   -89,   112,
     153,   176,   187,   118,   -24,   -89,   -89,   263,   -89,   198,
     209,   117,   124,   125,   -89,    -7,   -89,   129,   130,   131,
      -3,   -89,   -89,   -89,   263,   263,   379,   -89,   -89,   -89,
     133,   393,   135,   407,   -89,   315,   120,   276,   138,   331,
     143,   117,   147,   -89,   -89,   -89,   117,   151,   149,   433,
     421,   263,   263,   263,   263,    -8,   263,   263,   220,   117,
     154,   156,   117,    16,   -89,   148,   158,   -89,   -89,   163,
     166,   117,   -89,   231,     6,   -89,   433,   433,     3,     3,
     -89,   160,     3,   174,   170,   286,   -89,   -89,   -89,   181,
     183,   188,   263,   242,   -89,   190,   195,   185,   296,   200,
     -89,   142,   -89,   -89,   117,   117,    94,   347,   205,   363,
     -89,   201,   -89,   -89,   -89,   211,   306,   213,   -89,   -89,
     -89,   -89,   -89,   -89,   -89,   -89,   -89,   263,   -89,   -89
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -89,   -89,   243,   -89,   -89,   -89,   225,   226,   -43,   -89,
     -89,   -59,   -89,   -13,   -89,   -89,   204,   -34,   -88,   -89,
     -89,   -89,   -89,   -89,   -21,   -89,    58,   -89,    -1
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -75
static const yytype_int16 yytable[] =
{
       5,    59,    51,   120,   160,    89,    11,   179,    42,    25,
      26,    38,    24,   127,    19,    90,    59,   170,    98,    34,
       4,     4,    37,    34,    83,     4,    55,    56,    34,    88,
     137,    45,   138,   150,    46,    76,   123,    50,   152,    52,
     180,    53,   -14,    69,     4,    13,    57,    34,    58,    14,
       1,   166,     4,    79,   169,   171,     6,    84,    69,   106,
     111,   113,    84,   176,    76,     7,   115,    48,   117,   119,
      49,    72,    93,    23,    73,    96,    34,    24,    10,    15,
      17,    18,    76,   129,   130,    20,    22,    21,    25,    26,
      84,    35,    36,    39,    34,   200,   198,   199,   201,   128,
       4,    40,    47,    97,    55,    56,    78,   -14,    44,    70,
     156,   157,   158,   159,    77,   162,   163,   165,    25,    26,
      84,    48,     4,    80,    57,    84,    58,    55,    56,    71,
       4,    81,   178,    82,   161,    87,   -21,    91,    84,    86,
      92,    84,    84,   195,    94,     4,    95,    57,    49,    58,
      84,   187,   189,   114,    99,   100,   121,   101,   145,   122,
     102,   103,   104,   124,   125,   126,   100,   140,   101,   142,
       4,   102,   103,   104,   147,   105,   -74,   110,   149,   151,
     153,     4,   154,    84,    84,    84,   105,   172,   112,   100,
     167,   101,   168,   181,   102,   103,   104,   173,   174,   116,
     100,   175,   101,   138,     4,   102,   103,   104,   182,   105,
     118,   100,   184,   101,   185,     4,   102,   103,   104,   186,
     105,   164,   100,   192,   101,   190,     4,   102,   103,   104,
     191,   105,   177,   100,   194,   101,   205,     4,   102,   103,
     104,   203,   105,   188,   100,   206,   101,   208,     4,   102,
     103,   104,    12,   105,    41,   100,    43,   101,    54,     4,
     102,   103,   104,    85,   105,   209,   -35,    55,    56,     0,
       4,     0,     0,    25,    26,   105,   100,     0,   101,     0,
       0,   102,   103,   104,     0,     4,     0,    57,     0,    58,
       0,     4,     0,     0,     0,     0,   105,   131,   132,   133,
     134,   135,   136,   137,     0,   138,     0,   131,   132,   133,
     134,   135,   136,   137,   146,   138,     0,   131,   132,   133,
     134,   135,   136,   137,   183,   138,     0,   131,   132,   133,
     134,   135,   136,   137,   193,   138,   131,   132,   133,   134,
     135,   136,   137,   207,   138,     0,     0,     0,     0,     0,
       0,   144,   131,   132,   133,   134,   135,   136,   137,     0,
     138,     0,     0,     0,     0,     0,     0,   148,   131,   132,
     133,   134,   135,   136,   137,     0,   138,     0,     0,     0,
       0,     0,     0,   202,   131,   132,   133,   134,   135,   136,
     137,     0,   138,     0,     0,     0,     0,     0,     0,   204,
     131,   132,   133,   134,   135,   136,   137,     0,   138,     0,
       0,     0,     0,   139,   131,   132,   133,   134,   135,   136,
     137,     0,   138,     0,     0,     0,     0,   141,   131,   132,
     133,   134,   135,   136,   137,     0,   138,     0,     0,     0,
       0,   143,   131,   132,   133,   134,   135,   136,   137,     0,
     138,     0,     0,     0,     0,   155,   133,   134,   135,   136,
     137,     0,   138
};

static const yytype_int16 yycheck[] =
{
       1,    44,     1,    91,    12,    29,     7,     1,     1,    16,
      17,    24,     5,    16,    15,    39,    59,     1,    77,    20,
      28,    28,    23,    24,    58,    28,    10,    11,    29,    63,
      27,    32,    29,   121,    35,    48,    95,    38,   126,    38,
      34,    42,    35,    44,    28,     1,    30,    48,    32,     5,
       8,   139,    28,    54,   142,   143,     0,    58,    59,    80,
      81,    82,    63,   151,    77,     8,    87,    33,    89,    90,
      36,     1,    73,     1,     4,    76,    77,     5,    32,    14,
       3,     7,    95,   104,   105,    32,     6,    33,    16,    17,
      91,     4,     3,    29,    95,     1,   184,   185,   186,   100,
      28,    35,    33,     1,    10,    11,    38,    35,    32,    36,
     131,   132,   133,   134,    33,   136,   137,   138,    16,    17,
     121,    33,    28,    33,    30,   126,    32,    10,    11,    34,
      28,    33,   153,    33,   135,     9,    34,    32,   139,    35,
      34,   142,   143,     1,    34,    28,    37,    30,    36,    32,
     151,   172,   173,    35,     1,    13,    32,    15,    38,    34,
      18,    19,    20,    34,    34,    34,    13,    34,    15,    34,
      28,    18,    19,    20,    36,    33,    34,     1,    35,    32,
      29,    28,    33,   184,   185,   186,    33,    39,     1,    13,
      36,    15,    36,    33,    18,    19,    20,    39,    35,     1,
      13,    35,    15,    29,    28,    18,    19,    20,    38,    33,
       1,    13,    31,    15,    31,    28,    18,    19,    20,    31,
      33,     1,    13,    38,    15,    35,    28,    18,    19,    20,
      35,    33,     1,    13,    34,    15,    35,    28,    18,    19,
      20,    36,    33,     1,    13,    34,    15,    34,    28,    18,
      19,    20,     9,    33,    29,    13,    30,    15,     1,    28,
      18,    19,    20,    59,    33,   207,     9,    10,    11,    -1,
      28,    -1,    -1,    16,    17,    33,    13,    -1,    15,    -1,
      -1,    18,    19,    20,    -1,    28,    -1,    30,    -1,    32,
      -1,    28,    -1,    -1,    -1,    -1,    33,    21,    22,    23,
      24,    25,    26,    27,    -1,    29,    -1,    21,    22,    23,
      24,    25,    26,    27,    38,    29,    -1,    21,    22,    23,
      24,    25,    26,    27,    38,    29,    -1,    21,    22,    23,
      24,    25,    26,    27,    38,    29,    21,    22,    23,    24,
      25,    26,    27,    37,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    21,    22,    23,    24,    25,    26,    27,    -1,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    36,    21,    22,
      23,    24,    25,    26,    27,    -1,    29,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    21,    22,    23,    24,    25,    26,
      27,    -1,    29,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      21,    22,    23,    24,    25,    26,    27,    -1,    29,    -1,
      -1,    -1,    -1,    34,    21,    22,    23,    24,    25,    26,
      27,    -1,    29,    -1,    -1,    -1,    -1,    34,    21,    22,
      23,    24,    25,    26,    27,    -1,    29,    -1,    -1,    -1,
      -1,    34,    21,    22,    23,    24,    25,    26,    27,    -1,
      29,    -1,    -1,    -1,    -1,    34,    23,    24,    25,    26,
      27,    -1,    29
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
      13,    15,    18,    19,    20,    33,    64,    65,    67,    68,
       1,    64,     1,    64,    35,    64,     1,    64,     1,    64,
      58,    32,    34,    51,    34,    34,    34,    16,    68,    64,
      64,    21,    22,    23,    24,    25,    26,    27,    29,    34,
      34,    34,    34,    34,    36,    38,    38,    36,    36,    35,
      58,    32,    58,    29,    33,    34,    64,    64,    64,    64,
      12,    68,    64,    64,     1,    64,    58,    36,    36,    58,
       1,    58,    39,    39,    35,    35,    58,     1,    64,     1,
      34,    33,    38,    38,    31,    31,    31,    64,     1,    64,
      35,    35,    38,    38,    34,     1,    64,    66,    58,    58,
       1,    58,    36,    36,    36,    35,    34,    37,    34,    66
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
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
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
		  Type, Value, Location); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the look-ahead symbol.  */
YYLTYPE yylloc;



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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[2];

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;
#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 0;
#endif

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
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
     `$$ = $1'.

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
#line 105 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "GOAL");
    Goal = std::shared_ptr<CGoal>(new CGoal(getLocation(), (yyvsp[(1) - (2)].mainClass), (yyvsp[(2) - (2)].classDeclarationList)));
;}
    break;

  case 3:
#line 110 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "CLASS_LIST");
    (yyval.classDeclarationList) = new CClassDeclarationList(getLocation(), (yyvsp[(1) - (2)].classDeclaration), (yyvsp[(2) - (2)].classDeclarationList));
;}
    break;

  case 4:
#line 114 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "ARGS_DECLARATION");
    (yyval.classDeclarationList) = nullptr;
;}
    break;

  case 5:
#line 119 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "MAIN_CLASS");
    (yyval.mainClass) = new CMainClass(getLocation(), (yyvsp[(2) - (15)].identifier), (yyvsp[(10) - (15)].identifier), (yyvsp[(13) - (15)].statement));
;}
    break;

  case 6:
#line 123 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "MAIN_CLASS");
    delete (yyvsp[(2) - (14)].identifier);
    delete (yyvsp[(12) - (14)].statement);
    (yyval.mainClass) = nullptr;
;}
    break;

  case 7:
#line 129 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "MAIN_CLASS");
    delete (yyvsp[(2) - (13)].identifier);
    delete (yyvsp[(8) - (13)].identifier);
    delete (yyvsp[(11) - (13)].statement);
    (yyval.mainClass) = nullptr;
;}
    break;

  case 8:
#line 137 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "CLASS_DECLARATION");
    (yyval.classDeclaration) = new CClassDeclaration(getLocation(), (yyvsp[(2) - (6)].identifier), (yyvsp[(3) - (6)].identifier), (yyvsp[(5) - (6)].varAndMethodDeclaration).varDeclList, (yyvsp[(5) - (6)].varAndMethodDeclaration).methodDeclList);
;}
    break;

  case 9:
#line 142 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "BASE_CLASS");
    (yyval.identifier) = nullptr;
;}
    break;

  case 10:
#line 146 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "BASE_CLASS");
    (yyval.identifier) =  (yyvsp[(2) - (2)].identifier);
;}
    break;

  case 11:
#line 151 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "VAR_AND_METHOD_DECLARATION");
    (yyvsp[(2) - (2)].varAndMethodDeclaration).varDeclList = new CVarDeclarationList(getLocation(), (yyvsp[(1) - (2)].varDeclaration), (yyvsp[(2) - (2)].varAndMethodDeclaration).varDeclList);
    (yyval.varAndMethodDeclaration) = (yyvsp[(2) - (2)].varAndMethodDeclaration);
;}
    break;

  case 12:
#line 156 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    (yyval.varAndMethodDeclaration).varDeclList = nullptr;
    (yyval.varAndMethodDeclaration).methodDeclList = (yyvsp[(1) - (1)].methodDeclarationList);
;}
    break;

  case 13:
#line 161 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    (yyval.methodDeclarationList) = new CMethodDeclarationList(getLocation(), (yyvsp[(1) - (2)].methodDeclaration), (yyvsp[(2) - (2)].methodDeclarationList));
;}
    break;

  case 14:
#line 164 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    (yyval.methodDeclarationList) = nullptr;
;}
    break;

  case 15:
#line 168 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "VAR_DECLARATION");
    (yyval.varDeclaration) = new CVarDeclaration(getLocation(), (yyvsp[(1) - (3)].type), (yyvsp[(2) - (3)].identifier));
;}
    break;

  case 16:
#line 172 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "VAR_DECLARATION");
    delete (yyvsp[(2) - (3)].identifier);
    (yyval.varDeclaration) = nullptr;
;}
    break;

  case 17:
#line 178 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "METHOD_DECLARATION");
    (yyval.methodDeclaration) = new CMethodDeclaration(getLocation(), (yyvsp[(1) - (4)].methodHeaderDeclaration), (yyvsp[(3) - (4)].methodBodyDeclaration));
;}
    break;

  case 18:
#line 183 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "METHOD_HEADER");
    (yyval.methodHeaderDeclaration) = new CMethodHeaderDeclaration(getLocation(), (yyvsp[(2) - (6)].type), (yyvsp[(3) - (6)].identifier), (yyvsp[(5) - (6)].methodArgumentsList));
;}
    break;

  case 19:
#line 187 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "METHOD_HEADER");
    delete (yyvsp[(2) - (6)].type);
    delete (yyvsp[(3) - (6)].identifier);
    (yyval.methodHeaderDeclaration) = nullptr;
;}
    break;

  case 20:
#line 193 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "METHOD_HEADER");
    delete (yyvsp[(2) - (5)].identifier);
    delete (yyvsp[(4) - (5)].methodArgumentsList);
    (yyval.methodHeaderDeclaration) = nullptr;
;}
    break;

  case 21:
#line 200 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "ARGS_DECLARATION");
    (yyval.methodArgumentsList) = nullptr;
;}
    break;

  case 22:
#line 204 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
     processRule((yyloc), "ARGS_DECLARATION");
     (yyval.methodArgumentsList) = new CMethodArgumentsList(getLocation(), (yyvsp[(1) - (1)].varDeclaration), nullptr);
 ;}
    break;

  case 23:
#line 208 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "ARGS_DECLARATION");
    (yyval.methodArgumentsList) = new CMethodArgumentsList(getLocation(), (yyvsp[(1) - (3)].varDeclaration), (yyvsp[(3) - (3)].methodArgumentsList));
;}
    break;

  case 24:
#line 213 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "PARAM_DECLARATION");
    (yyval.varDeclaration) = new CVarDeclaration(getLocation(), (yyvsp[(1) - (2)].type), (yyvsp[(2) - (2)].identifier));
;}
    break;

  case 25:
#line 218 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "INT_ARRAY");
    (yyval.type) = (yyvsp[(1) - (1)].type);
;}
    break;

  case 26:
#line 222 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "TYPE");
    (yyval.type) = new CType(getLocation(), T_BOOL, globalStorage.Get("boolean"));
;}
    break;

  case 27:
#line 226 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "TYPE");
    (yyval.type) = new CType(getLocation(), T_INT, globalStorage.Get("int"));
;}
    break;

  case 28:
#line 230 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "TYPE");
    (yyval.type) = new CType(getLocation(), T_CLASS, (yyvsp[(1) - (1)].identifier)->Symbol);
    delete (yyvsp[(1) - (1)].identifier);
;}
    break;

  case 29:
#line 236 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "INT_ARRAY");
    (yyval.type) = new CType(getLocation(), T_INT_ARRAY, globalStorage.Get("int[]"));
;}
    break;

  case 30:
#line 240 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "INT_ARRAY");
    (yyval.type) = nullptr;
;}
    break;

  case 31:
#line 245 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "METHOD_BODY");
    (yyval.methodBodyDeclaration) = new CMethodBodyDeclaration(getLocation(), (yyvsp[(1) - (4)].varAndStatementDeclaration).varDeclList, (yyvsp[(1) - (4)].varAndStatementDeclaration).statementList, (yyvsp[(3) - (4)].expression));
;}
    break;

  case 32:
#line 250 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "VAR_AND_STATEMENT_DECLARATIONS");
    (yyvsp[(2) - (2)].varAndStatementDeclaration).varDeclList = new CVarDeclarationList(getLocation(), (yyvsp[(1) - (2)].varDeclaration), (yyvsp[(2) - (2)].varAndStatementDeclaration).varDeclList);
    (yyval.varAndStatementDeclaration) = (yyvsp[(2) - (2)].varAndStatementDeclaration);
;}
    break;

  case 33:
#line 255 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "VAR_AND_STATEMENT_DECLARATIONS");
    (yyval.varAndStatementDeclaration).statementList = (yyvsp[(1) - (1)].statementList);
    (yyval.varAndStatementDeclaration).varDeclList = nullptr;
;}
    break;

  case 34:
#line 261 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "STATEMENT_DECLARATION");
    (yyval.statementList) = new CStatementList(getLocation(), (yyvsp[(1) - (2)].statement), (yyvsp[(2) - (2)].statementList));
;}
    break;

  case 35:
#line 265 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "STATEMENT_DECLARATION");
    (yyval.statementList) = nullptr;
;}
    break;

  case 36:
#line 270 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "STATEMENT");
    (yyval.statement) = new CBracketStatement(getLocation(), (yyvsp[(2) - (3)].statementList));
;}
    break;

  case 37:
#line 274 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "STATEMENT");
    (yyval.statement) = (yyvsp[(1) - (1)].statement);
;}
    break;

  case 38:
#line 278 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "STATEMENT");
    (yyval.statement) = (yyvsp[(1) - (1)].statement);
;}
    break;

  case 39:
#line 282 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "STATEMENT");
    (yyval.statement) = (yyvsp[(1) - (1)].statement);
;}
    break;

  case 40:
#line 286 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "STATEMENT");
    (yyval.statement) = (yyvsp[(1) - (1)].statement);
;}
    break;

  case 41:
#line 290 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "STATEMENT");
    (yyval.statement) = (yyvsp[(1) - (1)].statement);
;}
    break;

  case 42:
#line 295 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "IF_STATEMENT");
    (yyval.statement) = new CIfStatement(getLocation(), (yyvsp[(3) - (7)].expression), (yyvsp[(5) - (7)].statement), (yyvsp[(7) - (7)].statement));
;}
    break;

  case 43:
#line 299 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "IF_STATEMENT");
    delete (yyvsp[(5) - (7)].statement);
    delete (yyvsp[(7) - (7)].statement);
    (yyval.statement) = nullptr;
;}
    break;

  case 44:
#line 305 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "IF_STATEMENT");
    delete (yyvsp[(3) - (7)].expression);
    delete (yyvsp[(7) - (7)].statement);
    (yyval.statement) = nullptr;
;}
    break;

  case 45:
#line 311 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "IF_STATEMENT");
    delete (yyvsp[(3) - (7)].expression);
    delete (yyvsp[(5) - (7)].statement);
    (yyval.statement) = nullptr;
;}
    break;

  case 46:
#line 318 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "WHILE_STATEMENT");
    (yyval.statement) = new CWhileStatement(getLocation(), (yyvsp[(3) - (5)].expression), (yyvsp[(5) - (5)].statement));
;}
    break;

  case 47:
#line 322 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "WHILE_STATEMENT");
    (yyval.statement) = nullptr;
;}
    break;

  case 48:
#line 327 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "PRINT_STATEMENT");
    (yyval.statement) = new CPrintStatement(getLocation(), (yyvsp[(3) - (5)].expression));
;}
    break;

  case 49:
#line 331 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "PRINT_STATEMENT");
    (yyval.statement) = nullptr;
;}
    break;

  case 50:
#line 336 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "ASSIGNMENT");
    (yyval.statement) = new CAssignmentStatement(getLocation(), (yyvsp[(3) - (4)].expression), new CVariable(getLocation(), (yyvsp[(1) - (4)].identifier)));
;}
    break;

  case 51:
#line 340 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "ASSIGNMENT");
    delete (yyvsp[(1) - (4)].identifier);
    (yyval.statement) = nullptr;
;}
    break;

  case 52:
#line 346 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "ARRAY_ASSIGNMENT");
    (yyval.statement) = new CIntArrayAssignmentStatement(getLocation(), (yyvsp[(3) - (7)].expression), (yyvsp[(6) - (7)].expression), new CVariable(getLocation(), (yyvsp[(1) - (7)].identifier)));
;}
    break;

  case 53:
#line 350 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "ARRAY_ASSIGNMENT");
    delete (yyvsp[(1) - (7)].identifier);
    delete (yyvsp[(6) - (7)].expression);
    (yyval.statement) = nullptr;
;}
    break;

  case 54:
#line 356 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "ARRAY_ASSIGNMENT");
    delete (yyvsp[(1) - (7)].identifier);
    delete (yyvsp[(3) - (7)].expression);
    (yyval.statement) = nullptr;
;}
    break;

  case 55:
#line 364 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "EXPR");
    (yyval.expression) = new CBinaryExpression(getLocation(), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression), BE_PLUS);
;}
    break;

  case 56:
#line 368 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "EXPR");
    (yyval.expression) = new CBinaryExpression(getLocation(), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression), BE_MINUS);
;}
    break;

  case 57:
#line 372 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "EXPR");
    (yyval.expression) = new CBinaryExpression(getLocation(), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression), BE_MULTIPLICATION);
;}
    break;

  case 58:
#line 376 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "EXPR");
    (yyval.expression) = new CBinaryExpression(getLocation(), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression), BE_AND);
;}
    break;

  case 59:
#line 380 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "EXPR");
    (yyval.expression) = new CBinaryExpression(getLocation(), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression), BE_LESS);
;}
    break;

  case 60:
#line 384 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "EXPR");
    (yyval.expression) = new CBinaryExpression(getLocation(), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression), BE_EQUAL);
;}
    break;

  case 61:
#line 388 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "EXPR");
    (yyval.expression) = new CNotExpression(getLocation(), (yyvsp[(2) - (2)].expression));
;}
    break;

  case 62:
#line 392 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "EXPR");
    (yyval.expression) = new CBracketExpression(getLocation(), (yyvsp[(2) - (3)].expression));
;}
    break;

  case 63:
#line 396 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "EXPR");
    (yyval.expression) = (yyvsp[(1) - (1)].expression);
;}
    break;

  case 64:
#line 400 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "EXPR");
    (yyval.expression) = new CVariable(getLocation(), (yyvsp[(1) - (1)].identifier));
;}
    break;

  case 65:
#line 404 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "EXPR");
    (yyval.expression) = new CVariable(getLocation(), new CIdentifier(getLocation(), globalStorage.Get("this")));
;}
    break;

  case 66:
#line 408 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "EXPR");
    (yyval.expression) = (yyvsp[(1) - (1)].constant);
;}
    break;

  case 67:
#line 412 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "INVOKE_EXPR");
    (yyval.expression) = new CBinaryExpression(getLocation(), (yyvsp[(1) - (4)].expression), (yyvsp[(3) - (4)].expression), BE_SQ_BRACKETS);
;}
    break;

  case 68:
#line 416 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "INVOKE_EXPR");
    (yyval.expression) = 0;
;}
    break;

  case 69:
#line 420 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "INVOKE_EXPR");
    (yyval.expression) = new CLengthExpression(getLocation(), (yyvsp[(1) - (3)].expression));
;}
    break;

  case 70:
#line 424 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "INVOKE_EXPR");
    (yyval.expression) = new CInvocation(getLocation(), (yyvsp[(1) - (6)].expression), (yyvsp[(3) - (6)].identifier), (yyvsp[(5) - (6)].expressionList));
;}
    break;

  case 71:
#line 428 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "INVOKE_EXPR");
    (yyval.expression) = 0;
;}
    break;

  case 72:
#line 433 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "CONSTANT");
    (yyval.constant) = new CConstant(getLocation(), new CType(getLocation(), T_INT, globalStorage.Get("int")), yytext);
;}
    break;

  case 73:
#line 437 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "CONSTANT");
    (yyval.constant) = new CConstant(getLocation(), new CType(getLocation(), T_BOOL, globalStorage.Get("boolean")), yytext);
;}
    break;

  case 74:
#line 443 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "PARAMS");
    (yyval.expressionList) = 0;
;}
    break;

  case 75:
#line 447 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "PARAMS");
    (yyval.expressionList) = new CExpressionList(getLocation(), (yyvsp[(1) - (1)].expression), 0);
;}
    break;

  case 76:
#line 451 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "PARAMS");
    (yyval.expressionList) = new CExpressionList(getLocation(), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expressionList));
;}
    break;

  case 77:
#line 457 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "NEW_EXPR");
    (yyval.expression) = new CIntArrayNewExpression(getLocation(), (yyvsp[(4) - (5)].expression));
;}
    break;

  case 78:
#line 461 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "NEW_EXPR");
    (yyval.expression) = 0;
;}
    break;

  case 79:
#line 465 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "NEW_EXPR");
    (yyval.expression) = new CNewExpression(getLocation(), (yyvsp[(2) - (4)].identifier));
;}
    break;

  case 80:
#line 469 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "NEW_EXPR");
    (yyval.expression) = 0;
;}
    break;

  case 81:
#line 474 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"
    {
    processRule((yyloc), "NEW_EXPR");
    (yyval.identifier) = new CIdentifier(getLocation(), globalStorage.Get(yytext));
;}
    break;


/* Line 1267 of yacc.c.  */
#line 2345 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/bison.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

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

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  yyerror_range[0] = yylsp[1-yylen];
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

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the look-ahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 479 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/minijava.y"


extern void printError(Location location, const char *s);
void yyerror(const char *s)
{
    printError(Location(yylloc.first_line, yylloc.first_column, yylloc.last_line, yylloc.last_column), s);
}
extern int main(int argc, const char* argv[]);
