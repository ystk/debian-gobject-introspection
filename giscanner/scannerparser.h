
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENTIFIER = 258,
     TYPEDEF_NAME = 259,
     INTEGER = 260,
     FLOATING = 261,
     CHARACTER = 262,
     STRING = 263,
     ELLIPSIS = 264,
     ADDEQ = 265,
     SUBEQ = 266,
     MULEQ = 267,
     DIVEQ = 268,
     MODEQ = 269,
     XOREQ = 270,
     ANDEQ = 271,
     OREQ = 272,
     SL = 273,
     SR = 274,
     SLEQ = 275,
     SREQ = 276,
     EQ = 277,
     NOTEQ = 278,
     LTEQ = 279,
     GTEQ = 280,
     ANDAND = 281,
     OROR = 282,
     PLUSPLUS = 283,
     MINUSMINUS = 284,
     ARROW = 285,
     AUTO = 286,
     BOOL = 287,
     BREAK = 288,
     CASE = 289,
     CHAR = 290,
     CONST = 291,
     CONTINUE = 292,
     DEFAULT = 293,
     DO = 294,
     DOUBLE = 295,
     ELSE = 296,
     ENUM = 297,
     EXTENSION = 298,
     EXTERN = 299,
     FLOAT = 300,
     FOR = 301,
     GOTO = 302,
     IF = 303,
     INLINE = 304,
     INT = 305,
     LONG = 306,
     REGISTER = 307,
     RESTRICT = 308,
     RETURN = 309,
     SHORT = 310,
     SIGNED = 311,
     SIZEOF = 312,
     STATIC = 313,
     STRUCT = 314,
     SWITCH = 315,
     TYPEDEF = 316,
     UNION = 317,
     UNSIGNED = 318,
     VOID = 319,
     VOLATILE = 320,
     WHILE = 321,
     FUNCTION_MACRO = 322,
     OBJECT_MACRO = 323
   };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define TYPEDEF_NAME 259
#define INTEGER 260
#define FLOATING 261
#define CHARACTER 262
#define STRING 263
#define ELLIPSIS 264
#define ADDEQ 265
#define SUBEQ 266
#define MULEQ 267
#define DIVEQ 268
#define MODEQ 269
#define XOREQ 270
#define ANDEQ 271
#define OREQ 272
#define SL 273
#define SR 274
#define SLEQ 275
#define SREQ 276
#define EQ 277
#define NOTEQ 278
#define LTEQ 279
#define GTEQ 280
#define ANDAND 281
#define OROR 282
#define PLUSPLUS 283
#define MINUSMINUS 284
#define ARROW 285
#define AUTO 286
#define BOOL 287
#define BREAK 288
#define CASE 289
#define CHAR 290
#define CONST 291
#define CONTINUE 292
#define DEFAULT 293
#define DO 294
#define DOUBLE 295
#define ELSE 296
#define ENUM 297
#define EXTENSION 298
#define EXTERN 299
#define FLOAT 300
#define FOR 301
#define GOTO 302
#define IF 303
#define INLINE 304
#define INT 305
#define LONG 306
#define REGISTER 307
#define RESTRICT 308
#define RETURN 309
#define SHORT 310
#define SIGNED 311
#define SIZEOF 312
#define STATIC 313
#define STRUCT 314
#define SWITCH 315
#define TYPEDEF 316
#define UNION 317
#define UNSIGNED 318
#define VOID 319
#define VOLATILE 320
#define WHILE 321
#define FUNCTION_MACRO 322
#define OBJECT_MACRO 323




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 55 "scannerparser.y"

  char *str;
  GList *list;
  GISourceSymbol *symbol;
  GISourceType *ctype;
  StorageClassSpecifier storage_class_specifier;
  TypeQualifier type_qualifier;
  FunctionSpecifier function_specifier;
  UnaryOperator unary_operator;



/* Line 1676 of yacc.c  */
#line 201 "scannerparser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


