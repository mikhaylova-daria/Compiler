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
     BREAK = 266,
     PRINT = 267,
     LENGTH = 268,
     NEW = 269,
     EXTENDS = 270,
     THIS = 271,
     INT = 272,
     BOOL = 273,
     ID = 274,
     INT_VALUE = 275,
     BOOL_VALUE = 276,
     STATEMENTS = 277,
     DECLARATION = 278,
     FIELD_DECLARATION = 279,
     RETURN_STATEMENT = 280,
     BREAK_STATEMENT = 281,
     INVOKE_STATEMENT = 282,
     NOT = 283,
     NEQ = 284,
     EQ = 285,
     LT = 286,
     GT = 287,
     LE = 288,
     GE = 289,
     AND = 290,
     OR = 291,
     IF = 292,
     ELSE = 293
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
#define BREAK 266
#define PRINT 267
#define LENGTH 268
#define NEW 269
#define EXTENDS 270
#define THIS 271
#define INT 272
#define BOOL 273
#define ID 274
#define INT_VALUE 275
#define BOOL_VALUE 276
#define STATEMENTS 277
#define DECLARATION 278
#define FIELD_DECLARATION 279
#define RETURN_STATEMENT 280
#define BREAK_STATEMENT 281
#define INVOKE_STATEMENT 282
#define NOT 283
#define NEQ 284
#define EQ 285
#define LT 286
#define GT 287
#define LE 288
#define GE 289
#define AND 290
#define OR 291
#define IF 292
#define ELSE 293




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
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
