/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

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

#ifndef YY_YY_HOME_DARIA_COMPILER_SRC_TOKENS_H_INCLUDED
# define YY_YY_HOME_DARIA_COMPILER_SRC_TOKENS_H_INCLUDED
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
    BREAK = 266,
    TYPE = 267,
    INT = 268,
    BOOL = 269,
    ID = 270,
    OR = 271,
    AND = 272,
    GE = 273,
    LE = 274,
    GT = 275,
    LT = 276,
    EQ = 277,
    NEQ = 278,
    NOT = 279,
    IF = 280,
    ELSE = 281
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 45 "/home/daria/Compiler/src/bison.y" /* yacc.c:1909  */

    Method* method;
    MyExpr* expr;
    ArgumentList* args;
    Argument* arg;
    StatementList* stmts;
    Statement* stmt;
    ParamList* params;
    VarType type;
    operation op;
    MyValue value;
    char word[256];

#line 95 "/home/daria/Compiler/src/tokens.h" /* yacc.c:1909  */
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

#endif /* !YY_YY_HOME_DARIA_COMPILER_SRC_TOKENS_H_INCLUDED  */
