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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    TOKEN_MAIN = 258,
    TOKEN_BEGIN = 259,
    TOKEN_INT = 260,
    TOKEN_FLOAT = 261,
    TOKEN_DOUBLE = 262,
    TOKEN_CHAR = 263,
    TOKEN_BOOL = 264,
    TOKEN_STR = 265,
    TOKEN_NULL = 266,
    TOKEN_VOID = 267,
    TOKEN_IF = 268,
    TOKEN_ELSE = 269,
    TOKEN_ELSEIF = 270,
    TOKEN_SWITCH = 271,
    TOKEN_CASE = 272,
    TOKEN_DEFAULT = 273,
    TOKEN_IMP = 274,
    TOKEN_BREAK = 275,
    TOKEN_CONTINUE = 276,
    TOKEN_DO = 277,
    TOKEN_FOR = 278,
    TOKEN_WHILE = 279,
    TOKEN_RETURN = 280,
    TOKEN_PRINT = 281,
    TOKEN_ERROR = 282,
    TOKEN_STRUCT = 283,
    TOKEN_NOMEVAR = 284,
    TOKEN_NUM_INT = 285,
    TOKEN_NUM_FLOAT = 286,
    TOKEN_BOOLEAN_FALSE = 287,
    TOKEN_BOOLEAN_TRUE = 288,
    TOKEN_CARACTERE = 289,
    TOKEN_STRING = 290,
    TOKEN_MAIOR = 291,
    TOKEN_MENOR = 292,
    TOKEN_DIF = 293,
    TOKEN_IGUAL = 294,
    TOKEN_MAIORIGUAL = 295,
    TOKEN_MENORIGUAL = 296,
    TOKEN_E = 297,
    TOKEN_OU = 298,
    TOKEN_CONV_FLOAT = 299,
    TOKEN_CONV_INT = 300,
    TOKEN_ATR = 301,
    TOKEN_SCANF = 302,
    TOKEN_COMENT = 303,
    TOKEN_COM_INT = 304,
    TOKEN_COM_END = 305,
    TOKEN_LINECOMENT = 306
  };
#endif
/* Tokens.  */
#define TOKEN_MAIN 258
#define TOKEN_BEGIN 259
#define TOKEN_INT 260
#define TOKEN_FLOAT 261
#define TOKEN_DOUBLE 262
#define TOKEN_CHAR 263
#define TOKEN_BOOL 264
#define TOKEN_STR 265
#define TOKEN_NULL 266
#define TOKEN_VOID 267
#define TOKEN_IF 268
#define TOKEN_ELSE 269
#define TOKEN_ELSEIF 270
#define TOKEN_SWITCH 271
#define TOKEN_CASE 272
#define TOKEN_DEFAULT 273
#define TOKEN_IMP 274
#define TOKEN_BREAK 275
#define TOKEN_CONTINUE 276
#define TOKEN_DO 277
#define TOKEN_FOR 278
#define TOKEN_WHILE 279
#define TOKEN_RETURN 280
#define TOKEN_PRINT 281
#define TOKEN_ERROR 282
#define TOKEN_STRUCT 283
#define TOKEN_NOMEVAR 284
#define TOKEN_NUM_INT 285
#define TOKEN_NUM_FLOAT 286
#define TOKEN_BOOLEAN_FALSE 287
#define TOKEN_BOOLEAN_TRUE 288
#define TOKEN_CARACTERE 289
#define TOKEN_STRING 290
#define TOKEN_MAIOR 291
#define TOKEN_MENOR 292
#define TOKEN_DIF 293
#define TOKEN_IGUAL 294
#define TOKEN_MAIORIGUAL 295
#define TOKEN_MENORIGUAL 296
#define TOKEN_E 297
#define TOKEN_OU 298
#define TOKEN_CONV_FLOAT 299
#define TOKEN_CONV_INT 300
#define TOKEN_ATR 301
#define TOKEN_SCANF 302
#define TOKEN_COMENT 303
#define TOKEN_COM_INT 304
#define TOKEN_COM_END 305
#define TOKEN_LINECOMENT 306

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
