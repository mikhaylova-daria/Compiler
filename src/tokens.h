/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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
/* Line 1529 of yacc.c.  */
#line 121 "/Users/ava-katushka/Documents/botanstvo/Compilers/Compiler/src/tokens.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

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

extern YYLTYPE yylloc;
