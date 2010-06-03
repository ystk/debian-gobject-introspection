
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
#line 29 "scannerparser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <glib.h>
#include <glib/gstdio.h>
#include "sourcescanner.h"
#include "scannerparser.h"

extern FILE *yyin;
extern int lineno;
extern char linebuf[2000];
extern char *yytext;

extern int yylex (GISourceScanner *scanner);
static void yyerror (GISourceScanner *scanner, const char *str);
 
extern void ctype_free (GISourceType * type);

static int last_enum_value = -1;
static gboolean is_bitfield;
static GHashTable *const_table = NULL;


/* Line 189 of yacc.c  */
#line 99 "scannerparser.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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

/* Line 214 of yacc.c  */
#line 55 "scannerparser.y"

  char *str;
  GList *list;
  GISourceSymbol *symbol;
  GISourceType *ctype;
  StorageClassSpecifier storage_class_specifier;
  TypeQualifier type_qualifier;
  FunctionSpecifier function_specifier;
  UnaryOperator unary_operator;



/* Line 214 of yacc.c  */
#line 284 "scannerparser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 296 "scannerparser.c"

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
#define YYFINAL  66
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1911

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  93
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  75
/* YYNRULES -- Number of rules.  */
#define YYNRULES  242
/* YYNRULES -- Number of states.  */
#define YYNSTATES  400

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   323

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    80,     2,     2,     2,    82,    75,     2,
      69,    70,    76,    77,    74,    78,    73,    81,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    88,    90,
      83,    89,    84,    87,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    71,     2,    72,    85,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    91,    86,    92,    79,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    17,    19,
      22,    24,    26,    28,    30,    35,    40,    44,    48,    52,
      55,    58,    60,    64,    66,    69,    72,    75,    78,    83,
      85,    87,    89,    91,    93,    95,    97,   102,   104,   108,
     112,   116,   118,   122,   126,   128,   132,   136,   138,   142,
     146,   150,   154,   156,   160,   164,   166,   170,   172,   176,
     178,   182,   184,   188,   190,   194,   196,   202,   204,   208,
     210,   212,   214,   216,   218,   220,   222,   224,   226,   228,
     230,   232,   236,   239,   241,   245,   248,   251,   253,   256,
     258,   261,   263,   266,   268,   270,   274,   276,   280,   282,
     284,   286,   288,   290,   292,   294,   296,   298,   300,   302,
     304,   306,   308,   310,   312,   314,   316,   322,   327,   330,
     332,   334,   336,   339,   343,   346,   348,   351,   353,   355,
     359,   360,   362,   365,   369,   375,   380,   387,   393,   396,
     397,   400,   404,   406,   410,   412,   414,   416,   418,   420,
     423,   425,   427,   431,   436,   440,   445,   450,   454,   457,
     459,   463,   466,   468,   471,   473,   477,   480,   483,   485,
     487,   489,   493,   495,   498,   500,   502,   505,   509,   512,
     516,   520,   525,   528,   532,   536,   541,   543,   545,   549,
     554,   556,   560,   562,   564,   566,   568,   570,   572,   576,
     581,   585,   588,   592,   594,   597,   599,   601,   603,   606,
     612,   620,   626,   632,   640,   647,   655,   663,   672,   680,
     689,   698,   708,   712,   715,   718,   721,   725,   727,   730,
     732,   734,   736,   741,   745,   747,   750,   752,   754,   759,
     762,   764,   766
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     159,     0,    -1,    96,    -1,     5,    -1,     7,    -1,     6,
      -1,    95,    -1,    69,   116,    70,    -1,     8,    -1,    95,
       8,    -1,     3,    -1,    96,    -1,   147,    -1,    94,    -1,
      98,    71,   116,    72,    -1,    98,    69,    99,    70,    -1,
      98,    69,    70,    -1,    98,    73,    97,    -1,    98,    30,
      97,    -1,    98,    28,    -1,    98,    29,    -1,   114,    -1,
      99,    74,   114,    -1,    98,    -1,    28,   100,    -1,    29,
     100,    -1,   101,   102,    -1,    57,   100,    -1,    57,    69,
     144,    70,    -1,    75,    -1,    76,    -1,    77,    -1,    78,
      -1,    79,    -1,    80,    -1,   100,    -1,    69,   144,    70,
     102,    -1,   102,    -1,   103,    76,   102,    -1,   103,    81,
     102,    -1,   103,    82,   102,    -1,   103,    -1,   104,    77,
     103,    -1,   104,    78,   103,    -1,   104,    -1,   105,    18,
     104,    -1,   105,    19,   104,    -1,   105,    -1,   106,    83,
     105,    -1,   106,    84,   105,    -1,   106,    24,   105,    -1,
     106,    25,   105,    -1,   106,    -1,   107,    22,   106,    -1,
     107,    23,   106,    -1,   107,    -1,   108,    75,   107,    -1,
     108,    -1,   109,    85,   108,    -1,   109,    -1,   110,    86,
     109,    -1,   110,    -1,   111,    26,   110,    -1,   111,    -1,
     112,    27,   111,    -1,   112,    -1,   112,    87,   116,    88,
     113,    -1,   113,    -1,   100,   115,   114,    -1,    89,    -1,
      12,    -1,    13,    -1,    14,    -1,    10,    -1,    11,    -1,
      20,    -1,    21,    -1,    16,    -1,    15,    -1,    17,    -1,
     114,    -1,   116,    74,   114,    -1,    43,   116,    -1,   113,
      -1,   119,   120,    90,    -1,   119,    90,    -1,   122,   119,
      -1,   122,    -1,   123,   119,    -1,   123,    -1,   135,   119,
      -1,   135,    -1,   136,   119,    -1,   136,    -1,   121,    -1,
     120,    74,   121,    -1,   137,    -1,   137,    89,   148,    -1,
      61,    -1,    44,    -1,    58,    -1,    31,    -1,    52,    -1,
      64,    -1,    35,    -1,    55,    -1,    50,    -1,    51,    -1,
      45,    -1,    40,    -1,    56,    -1,    63,    -1,    32,    -1,
     124,    -1,   131,    -1,   147,    -1,   125,    97,    91,   126,
      92,    -1,   125,    91,   126,    92,    -1,   125,    97,    -1,
      59,    -1,    62,    -1,   127,    -1,   126,   127,    -1,   128,
     129,    90,    -1,   123,   128,    -1,   123,    -1,   135,   128,
      -1,   135,    -1,   130,    -1,   129,    74,   130,    -1,    -1,
     137,    -1,    88,   117,    -1,   137,    88,   117,    -1,    42,
      97,    91,   132,    92,    -1,    42,    91,   132,    92,    -1,
      42,    97,    91,   132,    74,    92,    -1,    42,    91,   132,
      74,    92,    -1,    42,    97,    -1,    -1,   133,   134,    -1,
     132,    74,   134,    -1,    96,    -1,    96,    89,   117,    -1,
      36,    -1,    53,    -1,    43,    -1,    65,    -1,    49,    -1,
     139,   138,    -1,   138,    -1,    96,    -1,    69,   137,    70,
      -1,   138,    71,   114,    72,    -1,   138,    71,    72,    -1,
     138,    69,   141,    70,    -1,   138,    69,   143,    70,    -1,
     138,    69,    70,    -1,    76,   140,    -1,    76,    -1,    76,
     140,   139,    -1,    76,   139,    -1,   135,    -1,   140,   135,
      -1,   142,    -1,   141,    74,   142,    -1,   119,   137,    -1,
     119,   145,    -1,   119,    -1,     9,    -1,    96,    -1,   143,
      74,    96,    -1,   128,    -1,   128,   145,    -1,   139,    -1,
     146,    -1,   139,   146,    -1,    69,   145,    70,    -1,    71,
      72,    -1,    71,   114,    72,    -1,   146,    71,    72,    -1,
     146,    71,   114,    72,    -1,    69,    70,    -1,    69,   141,
      70,    -1,   146,    69,    70,    -1,   146,    69,   141,    70,
      -1,     4,    -1,   114,    -1,    91,   149,    92,    -1,    91,
     149,    74,    92,    -1,   148,    -1,   149,    74,   148,    -1,
     151,    -1,   152,    -1,   155,    -1,   156,    -1,   157,    -1,
     158,    -1,    97,    88,   150,    -1,    34,   117,    88,   150,
      -1,    38,    88,   150,    -1,    91,    92,    -1,    91,   153,
      92,    -1,   154,    -1,   153,   154,    -1,   118,    -1,   150,
      -1,    90,    -1,   116,    90,    -1,    48,    69,   116,    70,
     150,    -1,    48,    69,   116,    70,   150,    41,   150,    -1,
      60,    69,   116,    70,   150,    -1,    66,    69,   116,    70,
     150,    -1,    39,   150,    66,    69,   116,    70,    90,    -1,
      46,    69,    90,    90,    70,   150,    -1,    46,    69,   116,
      90,    90,    70,   150,    -1,    46,    69,    90,   116,    90,
      70,   150,    -1,    46,    69,   116,    90,   116,    90,    70,
     150,    -1,    46,    69,    90,    90,   116,    70,   150,    -1,
      46,    69,   116,    90,    90,   116,    70,   150,    -1,    46,
      69,    90,   116,    90,   116,    70,   150,    -1,    46,    69,
     116,    90,   116,    90,   116,    70,   150,    -1,    47,    97,
      90,    -1,    37,    90,    -1,    33,    90,    -1,    54,    90,
      -1,    54,   116,    90,    -1,   160,    -1,   159,   160,    -1,
     161,    -1,   118,    -1,   167,    -1,   119,   137,   162,   152,
      -1,   119,   137,   152,    -1,   118,    -1,   162,   118,    -1,
      67,    -1,    68,    -1,   163,    69,   143,    70,    -1,   164,
     117,    -1,   165,    -1,   166,    -1,     1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   144,   144,   153,   165,   169,   176,   177,   185,   200,
     214,   221,   222,   226,   227,   231,   235,   239,   243,   247,
     251,   258,   259,   263,   264,   268,   272,   295,   299,   307,
     311,   315,   319,   323,   327,   334,   335,   343,   344,   350,
     358,   369,   370,   376,   385,   386,   398,   407,   408,   414,
     420,   426,   435,   436,   442,   451,   452,   461,   462,   471,
     472,   481,   482,   493,   494,   505,   506,   513,   514,   521,
     522,   523,   524,   525,   526,   527,   528,   529,   530,   531,
     535,   536,   537,   544,   550,   568,   575,   580,   585,   598,
     599,   604,   609,   614,   622,   626,   633,   634,   638,   642,
     646,   650,   654,   661,   665,   669,   673,   677,   681,   685,
     689,   693,   697,   701,   702,   703,   711,   730,   735,   743,
     747,   754,   755,   762,   781,   786,   787,   792,   800,   804,
     812,   815,   816,   820,   831,   838,   845,   852,   859,   867,
     867,   875,   882,   890,   902,   906,   910,   914,   921,   928,
     933,   937,   942,   946,   951,   956,   966,   973,   982,   987,
     991,   996,  1003,  1004,  1011,  1015,  1022,  1027,  1032,  1037,
    1044,  1050,  1059,  1060,  1064,  1069,  1070,  1078,  1082,  1087,
    1092,  1097,  1102,  1108,  1118,  1124,  1137,  1144,  1145,  1146,
    1150,  1151,  1157,  1158,  1159,  1160,  1161,  1162,  1166,  1167,
    1168,  1172,  1173,  1177,  1178,  1182,  1183,  1187,  1188,  1192,
    1193,  1194,  1198,  1199,  1200,  1201,  1202,  1203,  1204,  1205,
    1206,  1207,  1211,  1212,  1213,  1214,  1215,  1221,  1222,  1226,
    1227,  1228,  1232,  1233,  1237,  1238,  1244,  1251,  1258,  1262,
    1273,  1274,  1275
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "\"identifier\"", "\"typedef-name\"",
  "INTEGER", "FLOATING", "CHARACTER", "STRING", "ELLIPSIS", "ADDEQ",
  "SUBEQ", "MULEQ", "DIVEQ", "MODEQ", "XOREQ", "ANDEQ", "OREQ", "SL", "SR",
  "SLEQ", "SREQ", "EQ", "NOTEQ", "LTEQ", "GTEQ", "ANDAND", "OROR",
  "PLUSPLUS", "MINUSMINUS", "ARROW", "AUTO", "BOOL", "BREAK", "CASE",
  "CHAR", "CONST", "CONTINUE", "DEFAULT", "DO", "DOUBLE", "ELSE", "ENUM",
  "EXTENSION", "EXTERN", "FLOAT", "FOR", "GOTO", "IF", "INLINE", "INT",
  "LONG", "REGISTER", "RESTRICT", "RETURN", "SHORT", "SIGNED", "SIZEOF",
  "STATIC", "STRUCT", "SWITCH", "TYPEDEF", "UNION", "UNSIGNED", "VOID",
  "VOLATILE", "WHILE", "FUNCTION_MACRO", "OBJECT_MACRO", "'('", "')'",
  "'['", "']'", "'.'", "','", "'&'", "'*'", "'+'", "'-'", "'~'", "'!'",
  "'/'", "'%'", "'<'", "'>'", "'^'", "'|'", "'?'", "':'", "'='", "';'",
  "'{'", "'}'", "$accept", "primary_expression", "strings", "identifier",
  "identifier_or_typedef_name", "postfix_expression",
  "argument_expression_list", "unary_expression", "unary_operator",
  "cast_expression", "multiplicative_expression", "additive_expression",
  "shift_expression", "relational_expression", "equality_expression",
  "and_expression", "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_expression", "assignment_operator",
  "expression", "constant_expression", "declaration",
  "declaration_specifiers", "init_declarator_list", "init_declarator",
  "storage_class_specifier", "type_specifier", "struct_or_union_specifier",
  "struct_or_union", "struct_declaration_list", "struct_declaration",
  "specifier_qualifier_list", "struct_declarator_list",
  "struct_declarator", "enum_specifier", "enumerator_list", "$@1",
  "enumerator", "type_qualifier", "function_specifier", "declarator",
  "direct_declarator", "pointer", "type_qualifier_list", "parameter_list",
  "parameter_declaration", "identifier_list", "type_name",
  "abstract_declarator", "direct_abstract_declarator", "typedef_name",
  "initializer", "initializer_list", "statement", "labeled_statement",
  "compound_statement", "block_item_list", "block_item",
  "expression_statement", "selection_statement", "iteration_statement",
  "jump_statement", "translation_unit", "external_declaration",
  "function_definition", "declaration_list", "function_macro",
  "object_macro", "function_macro_define", "object_macro_define", "macro", 0
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
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,    40,
      41,    91,    93,    46,    44,    38,    42,    43,    45,   126,
      33,    47,    37,    60,    62,    94,   124,    63,    58,    61,
      59,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    93,    94,    94,    94,    94,    94,    94,    95,    95,
      96,    97,    97,    98,    98,    98,    98,    98,    98,    98,
      98,    99,    99,   100,   100,   100,   100,   100,   100,   101,
     101,   101,   101,   101,   101,   102,   102,   103,   103,   103,
     103,   104,   104,   104,   105,   105,   105,   106,   106,   106,
     106,   106,   107,   107,   107,   108,   108,   109,   109,   110,
     110,   111,   111,   112,   112,   113,   113,   114,   114,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     116,   116,   116,   117,   118,   118,   119,   119,   119,   119,
     119,   119,   119,   119,   120,   120,   121,   121,   122,   122,
     122,   122,   122,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   123,   123,   124,   124,   124,   125,
     125,   126,   126,   127,   128,   128,   128,   128,   129,   129,
     130,   130,   130,   130,   131,   131,   131,   131,   131,   133,
     132,   132,   134,   134,   135,   135,   135,   135,   136,   137,
     137,   138,   138,   138,   138,   138,   138,   138,   139,   139,
     139,   139,   140,   140,   141,   141,   142,   142,   142,   142,
     143,   143,   144,   144,   145,   145,   145,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   147,   148,   148,   148,
     149,   149,   150,   150,   150,   150,   150,   150,   151,   151,
     151,   152,   152,   153,   153,   154,   154,   155,   155,   156,
     156,   156,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   158,   158,   158,   158,   158,   159,   159,   160,
     160,   160,   161,   161,   162,   162,   163,   164,   165,   166,
     167,   167,   167
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     3,     1,     2,
       1,     1,     1,     1,     4,     4,     3,     3,     3,     2,
       2,     1,     3,     1,     2,     2,     2,     2,     4,     1,
       1,     1,     1,     1,     1,     1,     4,     1,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     5,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     2,     1,     3,     2,     2,     1,     2,     1,
       2,     1,     2,     1,     1,     3,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     5,     4,     2,     1,
       1,     1,     2,     3,     2,     1,     2,     1,     1,     3,
       0,     1,     2,     3,     5,     4,     6,     5,     2,     0,
       2,     3,     1,     3,     1,     1,     1,     1,     1,     2,
       1,     1,     3,     4,     3,     4,     4,     3,     2,     1,
       3,     2,     1,     2,     1,     3,     2,     2,     1,     1,
       1,     3,     1,     2,     1,     1,     2,     3,     2,     3,
       3,     4,     2,     3,     3,     4,     1,     1,     3,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     4,
       3,     2,     3,     1,     2,     1,     1,     1,     2,     5,
       7,     5,     5,     7,     6,     7,     7,     8,     7,     8,
       8,     9,     3,     2,     2,     2,     3,     1,     2,     1,
       1,     1,     4,     3,     1,     2,     1,     1,     4,     2,
       1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   242,   186,   101,   112,   104,   144,   109,     0,   146,
      99,   108,   148,   106,   107,   102,   145,   105,   110,   100,
     119,    98,   120,   111,   103,   147,   236,   237,   230,     0,
      87,    89,   113,     0,   114,    91,    93,   115,     0,   227,
     229,     0,     0,   240,   241,   231,    10,   139,    11,   138,
      12,     0,   159,    85,   151,     0,    94,    96,   150,     0,
      86,    88,     0,   118,    90,    92,     1,   228,     0,     3,
       5,     4,     8,     0,     0,     0,     0,    29,    30,    31,
      32,    33,    34,    13,     6,     2,    23,    35,     0,    37,
      41,    44,    47,    52,    55,    57,    59,    61,    63,    65,
      83,   239,     0,     0,   139,     0,   162,   161,   158,     0,
      84,     0,     0,   234,     0,   233,     0,     0,     0,   149,
     125,     0,   121,   130,   127,     0,   170,     0,     0,    24,
      25,     0,    27,   146,    35,    67,    80,     0,   172,     0,
       9,    19,    20,     0,     0,     0,     0,    26,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   135,   142,
     140,     0,   152,   163,   160,    95,    96,     0,   187,    97,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   207,   201,     2,     0,     0,   205,   115,   206,   192,
     193,     0,   203,   194,   195,   196,   197,   235,   232,   169,
     157,   168,     0,   164,     0,   154,     0,   124,   117,   122,
       0,     0,   128,   131,   126,     0,   238,     0,     0,     0,
      82,    73,    74,    70,    71,    72,    78,    77,    79,    75,
      76,    69,     0,     7,     0,     0,     0,   174,   173,   175,
       0,    18,    16,     0,    21,     0,    17,    38,    39,    40,
      42,    43,    45,    46,    50,    51,    48,    49,    53,    54,
      56,    58,    60,    62,    64,     0,   137,   141,     0,     0,
     134,   190,     0,   224,     0,   223,     0,     0,     0,     0,
       0,   225,     0,     0,     0,     0,   208,   202,   204,     0,
     166,   174,   167,   155,     0,   156,   153,   132,   130,   123,
       0,   116,   171,    28,    68,    81,   182,     0,     0,   178,
       0,   176,     0,     0,    36,    15,     0,    14,     0,   143,
     136,     0,   188,     0,   200,     0,     0,     0,   222,     0,
     226,     0,     0,   198,   165,   129,   133,   183,   177,   179,
     184,     0,   180,     0,    22,    66,   189,   191,   199,     0,
       0,     0,     0,     0,     0,     0,   185,   181,     0,     0,
       0,     0,     0,     0,   209,   211,   212,     0,   214,     0,
       0,     0,     0,     0,     0,     0,   213,   218,   216,     0,
     215,     0,     0,     0,   210,   220,   219,   217,     0,   221
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    83,    84,    85,   194,    86,   253,   134,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     135,   136,   242,   195,   101,    28,   211,    55,    56,    30,
      31,    32,    33,   121,   122,   123,   221,   222,    34,   102,
     103,   277,    35,    36,   105,    58,    59,   108,   317,   213,
     127,   139,   318,   249,    37,   179,   282,   198,   199,   200,
     201,   202,   203,   204,   205,   206,    38,    39,    40,   116,
      41,    42,    43,    44,    45
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -211
static const yytype_int16 yypact[] =
{
    1637,  -211,  -211,  -211,  -211,  -211,  -211,  -211,    16,  -211,
    -211,  -211,  -211,  -211,  -211,  -211,  -211,  -211,  -211,  -211,
    -211,  -211,  -211,  -211,  -211,  -211,  -211,  -211,  -211,    76,
    1812,  1812,  -211,    25,  -211,  1812,  1812,  -211,  1584,  -211,
    -211,   -47,  1320,  -211,  -211,  -211,  -211,  -211,  -211,   -57,
    -211,   114,   220,  -211,  -211,   -38,  -211,   764,    15,    45,
    -211,  -211,  1846,    14,  -211,  -211,  -211,  -211,    64,  -211,
    -211,  -211,  -211,  1385,  1385,  1398,  1008,  -211,  -211,  -211,
    -211,  -211,  -211,  -211,    85,  -211,   127,  -211,  1320,  -211,
     133,   238,   249,   129,   307,    24,    26,    33,    98,   -22,
    -211,  -211,   -50,    64,  -211,    72,  -211,  -211,   220,   114,
    -211,   269,   438,  -211,    76,  -211,   807,  1703,  1183,    15,
    1846,   689,  -211,    91,  1846,  1846,  -211,   -39,  1210,  -211,
    -211,  1008,  -211,  1210,   437,  -211,  -211,   -24,   118,   103,
    -211,  -211,  -211,   328,  1263,  1210,   328,  -211,  1320,  1320,
    1320,  1320,  1320,  1320,  1320,  1320,  1320,  1320,  1320,  1320,
    1320,  1320,  1320,  1320,  1320,  1320,  1210,     8,  -211,    80,
    -211,   -36,  -211,  -211,  -211,  -211,   108,   269,  -211,  -211,
      44,  1320,   112,   120,   637,   153,   328,   189,   871,   212,
     219,  -211,  -211,   128,   144,   -17,  -211,   217,  -211,  -211,
    -211,   516,  -211,  -211,  -211,  -211,  -211,  -211,  -211,  -211,
    -211,    99,   147,  -211,   155,  -211,   251,  -211,  -211,  -211,
    1320,    39,  -211,   239,  -211,   729,  -211,    64,  1210,   266,
     278,  -211,  -211,  -211,  -211,  -211,  -211,  -211,  -211,  -211,
    -211,  -211,  1320,  -211,  1320,  1511,  1290,    70,  -211,   164,
    1320,  -211,  -211,   160,  -211,   250,  -211,  -211,  -211,  -211,
     133,   133,   238,   238,   249,   249,   249,   249,   129,   129,
     307,    24,    26,    33,    98,   -19,  -211,  -211,  1320,    11,
    -211,  -211,   -33,  -211,   252,  -211,   637,   277,   887,   263,
    1210,  -211,    46,  1210,  1210,   637,  -211,  -211,  -211,  1448,
    -211,    59,  -211,  -211,  1777,  -211,  -211,  -211,    91,  -211,
    1320,  -211,  -211,  -211,  -211,  -211,  -211,   187,   284,  -211,
     286,   164,  1740,  1306,  -211,  -211,  1320,  -211,  1320,  -211,
    -211,   581,  -211,   637,  -211,   290,   914,    58,  -211,   190,
    -211,   195,   209,  -211,  -211,  -211,  -211,  -211,  -211,  -211,
    -211,   210,  -211,   294,  -211,  -211,  -211,  -211,  -211,  1210,
    1073,   117,   930,   637,   637,   637,  -211,  -211,   229,   637,
     234,  1089,  1128,   121,   321,  -211,  -211,   280,  -211,   637,
     637,   236,   637,   237,  1167,   637,  -211,  -211,  -211,   637,
    -211,   637,   637,   243,  -211,  -211,  -211,  -211,   637,  -211
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -211,  -211,  -211,    -8,    -6,  -211,  -211,    89,  -211,   -78,
     183,   188,   163,   191,   207,   211,   213,   214,   221,  -211,
     -16,   -95,  -211,   -70,  -128,   -27,     9,  -211,   279,  -211,
     -44,  -211,  -211,   262,  -117,    68,  -211,    86,  -211,   289,
    -211,   292,     2,  -211,   -26,   -46,   -40,  -211,  -116,    92,
     283,   270,  -121,  -210,     0,  -170,  -211,    42,  -211,   -42,
    -211,   196,  -211,  -211,  -211,  -211,  -211,   364,  -211,  -211,
    -211,  -211,  -211,  -211,  -211
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -13
static const yytype_int16 yytable[] =
{
      48,   212,    49,    57,   219,   165,   137,   281,    50,    29,
     147,    46,   107,   119,    46,   115,   178,   248,   120,    46,
       2,    54,    68,   216,   167,    48,   100,    63,    46,     2,
     113,   226,   120,    50,   104,   227,   109,   321,   279,    60,
      61,   331,   168,    54,    64,    65,   243,    29,    46,   254,
     244,    54,   110,   284,   106,   244,   280,   244,   137,   332,
     126,   137,    46,   230,   124,   166,   114,    46,   174,   328,
     257,   258,   259,   296,   208,   255,   120,   120,   124,    46,
     120,   120,   178,   176,   117,   196,   118,   120,   176,   207,
     302,   321,   307,   140,    46,   169,   275,   223,   247,   161,
     276,    54,    46,   330,   193,   125,    54,    47,   219,   126,
     173,   162,   197,   308,    51,    54,    62,    46,   292,   163,
     244,   114,   124,   124,   164,   114,   124,   124,   299,   309,
     246,    87,   244,   124,   283,    48,   340,   251,    48,   245,
     256,   246,   172,    50,   138,    51,    50,   314,   362,   315,
     329,   320,    52,   155,   156,   141,   142,   143,   230,   169,
      51,   357,   129,   130,   132,   100,    53,    52,   299,   278,
     246,   301,   324,   250,   196,    52,   193,    87,    48,   220,
     289,   120,   346,    51,    50,   300,    50,   245,   217,   246,
      52,   244,   224,   193,    52,   244,   144,   111,   145,   138,
     146,   197,   285,    54,   100,   247,   351,   371,   286,   148,
     114,   384,   157,   158,   149,   150,   -11,   303,   337,   312,
     339,   304,   288,   341,   342,   305,   287,   124,   353,   227,
     325,   354,   295,   322,   326,   323,   178,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,   119,     6,   347,   290,   301,
     363,   304,   100,     9,   244,   364,   361,   153,   154,   244,
      87,   169,    46,    16,    69,    70,    71,    72,   193,   365,
     366,   293,   223,   244,   304,    25,    50,   193,   294,   368,
     370,    54,   373,    54,   100,    50,    52,    73,    74,   377,
      54,   381,   383,   244,   379,   -12,   389,   391,   244,    87,
     244,   244,   355,   398,   393,   151,   152,   244,   264,   265,
     266,   267,   327,   306,   244,   193,    75,   310,   334,   159,
     160,    46,     2,    50,   260,   261,   313,   343,    76,    87,
     333,   262,   263,   335,    77,    78,    79,    80,    81,    82,
     268,   269,   244,   338,   348,   193,   193,   193,   349,   359,
     177,   193,   385,    50,    50,    50,   367,    87,   270,    50,
     386,   193,   193,   271,   193,   358,   272,   193,   273,    50,
      50,   193,    50,   193,   193,    50,   274,   225,   175,    50,
     193,    50,    50,   171,   345,   170,   344,   298,    50,    87,
     214,   229,    67,     0,     0,   374,   375,   376,     0,     0,
       0,   378,     0,     0,     0,     0,     0,    87,     0,     0,
       0,   387,   388,     0,   390,     0,     0,   394,     0,     0,
       0,   395,     0,   396,   397,     0,     0,     0,     0,     0,
     399,    46,     2,    69,    70,    71,    72,   231,   232,   233,
     234,   235,   236,   237,   238,     0,     0,   239,   240,     0,
       0,     0,     0,     0,     0,     0,    73,    74,     0,     3,
       4,   180,   181,     5,     6,   182,   183,   184,     7,     0,
       8,   133,    10,    11,   185,   186,   187,    12,    13,    14,
      15,    16,   188,    17,    18,    75,    19,    20,   189,    21,
      22,    23,    24,    25,   190,     0,     0,    76,     0,     0,
       0,     0,     0,    77,    78,    79,    80,    81,    82,    46,
       2,    69,    70,    71,    72,     0,   241,     0,   191,   112,
     192,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    73,    74,     0,     3,     4,   180,
     181,     5,     6,   182,   183,   184,     7,     0,     8,   133,
      10,    11,   185,   186,   187,    12,    13,    14,    15,    16,
     188,    17,    18,    75,    19,    20,   189,    21,    22,    23,
      24,    25,   190,     0,    46,    76,    69,    70,    71,    72,
       0,    77,    78,    79,    80,    81,    82,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   191,   112,   297,    73,
      74,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    75,     0,
      46,     2,    69,    70,    71,    72,     0,     0,     0,     0,
      76,     0,     0,     0,     0,     0,    77,    78,    79,    80,
      81,    82,     0,     0,     0,    73,    74,     0,     0,     0,
     180,   181,   177,   356,   182,   183,   184,     0,     0,     0,
     228,     0,     0,   185,   186,   187,     0,     0,     0,     0,
       0,   188,     0,     2,    75,     0,     0,   189,     0,     0,
       0,     0,     0,   190,     0,     0,    76,     0,     0,     0,
       0,     0,    77,    78,    79,    80,    81,    82,     0,     0,
       0,     4,     0,     0,     5,     6,     0,   191,   112,     7,
       0,     8,     9,     2,    11,     0,     0,     0,     0,    13,
      14,     0,    16,     0,    17,    18,     0,     0,    20,     0,
       0,    22,    23,    24,    25,     0,     0,     0,     0,     0,
       0,     4,     0,     0,     5,     6,     0,     0,     2,     7,
       0,     8,     9,     0,    11,     0,     0,     0,     0,    13,
      14,   218,    16,     0,    17,    18,     0,     0,    20,     0,
       0,    22,    23,    24,    25,     3,     4,     0,     0,     5,
       6,     0,     0,     0,     7,     0,     8,     9,    10,    11,
       0,     2,     0,    12,    13,    14,    15,    16,     0,    17,
      18,   311,    19,    20,     0,    21,    22,    23,    24,    25,
       0,     0,     0,     0,     0,     0,     0,     0,     3,     4,
       0,     0,     5,     6,     0,     0,     0,     7,     0,     8,
       9,    10,    11,   111,     0,   112,    12,    13,    14,    15,
      16,     0,    17,    18,     0,    19,    20,     0,    21,    22,
      23,    24,    25,     0,    46,     0,    69,    70,    71,    72,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      46,     0,    69,    70,    71,    72,     0,     0,   112,    73,
      74,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   228,    73,    74,    46,     0,    69,
      70,    71,    72,     0,     0,     0,     0,     0,    75,     0,
     228,     0,     0,    46,     0,    69,    70,    71,    72,     0,
      76,     0,    73,    74,    75,     0,    77,    78,    79,    80,
      81,    82,     0,     0,     0,     0,    76,   228,    73,    74,
       0,   291,    77,    78,    79,    80,    81,    82,     0,     0,
       0,    75,     0,   228,     0,     0,     0,   336,     0,     0,
       0,     0,     0,    76,     0,     0,     0,    75,     0,    77,
      78,    79,    80,    81,    82,     0,     0,     0,     0,    76,
       0,     0,     0,     0,   360,    77,    78,    79,    80,    81,
      82,    46,     2,    69,    70,    71,    72,     0,     0,     0,
     372,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    73,    74,     0,     0,
       4,     0,     0,     5,     6,     0,     0,     0,     7,     0,
       8,   133,     0,    11,     0,     0,     0,     0,    13,    14,
       0,    16,     0,    17,    18,    75,     0,    20,     0,     0,
      22,    23,    24,    25,     0,     0,    46,    76,    69,    70,
      71,    72,     0,    77,    78,    79,    80,    81,    82,     0,
       0,     0,    46,     0,    69,    70,    71,    72,     0,     0,
       0,    73,    74,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   228,    73,    74,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      75,    46,   228,    69,    70,    71,    72,     0,     0,     0,
       0,     0,    76,   369,     0,     0,    75,     0,    77,    78,
      79,    80,    81,    82,     0,     0,    73,    74,    76,   380,
       0,     0,     0,     0,    77,    78,    79,    80,    81,    82,
      46,   228,    69,    70,    71,    72,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    75,    46,     0,    69,    70,
      71,    72,     0,     0,     0,    73,    74,    76,   382,     0,
       0,     0,     0,    77,    78,    79,    80,    81,    82,     0,
     228,    73,    74,    46,     0,    69,    70,    71,    72,     0,
       0,     0,     0,     0,    75,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    76,   392,    73,    74,
      75,     0,    77,    78,    79,    80,    81,    82,     0,     0,
       0,     0,    76,   228,     0,   215,     0,     0,    77,    78,
      79,    80,    81,    82,     0,     0,    46,    75,    69,    70,
      71,    72,     0,     0,     0,     0,     0,     0,     0,    76,
       0,     0,     0,     0,     0,    77,    78,    79,    80,    81,
      82,    73,    74,    46,     0,    69,    70,    71,    72,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    46,
       0,    69,    70,    71,    72,     0,     0,     0,    73,    74,
      75,     0,     0,    46,     0,    69,    70,    71,    72,     0,
       0,     0,    76,   252,    73,    74,     0,     0,    77,    78,
      79,    80,    81,    82,     0,     0,     0,    75,    73,    74,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    76,
       0,     0,   319,    75,     0,    77,    78,    79,    80,    81,
      82,     0,     0,     0,     0,    76,     0,    75,   352,     0,
       0,    77,    78,    79,    80,    81,    82,     0,    46,    76,
      69,    70,    71,    72,     0,    77,    78,    79,    80,    81,
      82,    46,     0,    69,    70,    71,    72,     0,     0,     0,
       0,     0,     0,    73,    74,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    73,    74,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    75,     0,     0,     0,     0,     0,     0,     0,
       0,    46,     2,     0,   128,    75,     0,   209,     0,     0,
      77,    78,    79,    80,    81,    82,     0,   131,     0,     0,
       0,     0,     0,    77,    78,    79,    80,    81,    82,     3,
       4,     0,     0,     5,     6,     0,     0,     0,     7,     0,
       8,     9,    10,    11,     0,     0,     0,    12,    13,    14,
      15,    16,     0,    17,    18,     0,    19,    20,     0,    21,
      22,    23,    24,    25,     0,     2,     0,   299,   316,   246,
     209,     0,     0,     0,    52,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     3,     4,     0,     0,     5,     6,     0,     0,
       0,     7,     0,     8,     9,    10,    11,     0,     0,     0,
      12,    13,    14,    15,    16,     0,    17,    18,     0,    19,
      20,     0,    21,    22,    23,    24,    25,     0,     0,     0,
     245,   316,   246,     0,    66,     1,     0,    52,     2,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     3,     4,     0,     0,     5,
       6,     0,     0,     0,     7,     0,     8,     9,    10,    11,
       0,     0,     0,    12,    13,    14,    15,    16,     1,    17,
      18,     2,    19,    20,     0,    21,    22,    23,    24,    25,
       0,    26,    27,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,     4,
       0,     0,     5,     6,     0,     0,     0,     7,     0,     8,
       9,    10,    11,     0,     0,     0,    12,    13,    14,    15,
      16,     0,    17,    18,     0,    19,    20,     0,    21,    22,
      23,    24,    25,     0,    26,    27,    46,     2,     0,     0,
       0,     0,   209,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     3,     4,     0,     0,     5,     6,
       0,     0,     0,     7,     2,     8,     9,    10,    11,   209,
       0,     0,    12,    13,    14,    15,    16,     0,    17,    18,
       0,    19,    20,     0,    21,    22,    23,    24,    25,     0,
       0,     3,     4,   210,     0,     5,     6,     0,     0,     0,
       7,     2,     8,     9,    10,    11,   209,     0,     0,    12,
      13,    14,    15,    16,     0,    17,    18,     0,    19,    20,
       0,    21,    22,    23,    24,    25,     0,     0,     3,     4,
     350,     0,     5,     6,     0,     0,     2,     7,     0,     8,
       9,    10,    11,     0,     0,     0,    12,    13,    14,    15,
      16,     0,    17,    18,     0,    19,    20,     0,    21,    22,
      23,    24,    25,     3,     4,     0,     0,     5,     6,     0,
       2,     0,     7,     0,     8,     9,    10,    11,     0,     0,
       0,    12,    13,    14,    15,    16,     0,    17,    18,     0,
      19,    20,     0,    21,    22,    23,    24,    25,     4,     0,
       0,     5,     6,     0,     0,     0,     7,     0,     8,     9,
       0,    11,     0,     0,     0,     0,    13,    14,     0,    16,
       0,    17,    18,     0,     0,    20,     0,     0,    22,    23,
      24,    25
};

static const yytype_int16 yycheck[] =
{
       8,   117,     8,    29,   121,    27,    76,   177,     8,     0,
      88,     3,    52,    59,     3,    57,   111,   138,    62,     3,
       4,    29,    69,   118,    74,    33,    42,    33,     3,     4,
      57,    70,    76,    33,    91,    74,    74,   247,    74,    30,
      31,    74,    92,    51,    35,    36,    70,    38,     3,   144,
      74,    59,    90,   181,    52,    74,    92,    74,   128,    92,
      68,   131,     3,   133,    62,    87,    57,     3,   108,    88,
     148,   149,   150,    90,   116,   145,   120,   121,    76,     3,
     124,   125,   177,   109,    69,   112,    71,   131,   114,   116,
     211,   301,   220,     8,     3,   103,   166,   123,   138,    75,
      92,   109,     3,    92,   112,    91,   114,    91,   225,   117,
     108,    85,   112,    74,    69,   123,    91,     3,   188,    86,
      74,   112,   120,   121,    26,   116,   124,   125,    69,    90,
      71,    42,    74,   131,    90,   143,    90,   143,   146,    69,
     146,    71,    70,   143,    76,    69,   146,   242,    90,   244,
     278,   246,    76,    24,    25,    28,    29,    30,   228,   167,
      69,   331,    73,    74,    75,   181,    90,    76,    69,    89,
      71,   211,   250,    70,   201,    76,   184,    88,   186,    88,
     186,   225,   310,    69,   184,   211,   186,    69,   120,    71,
      76,    74,   124,   201,    76,    74,    69,    89,    71,   131,
      73,   201,    90,   211,   220,   245,   322,    90,    88,    76,
     201,    90,    83,    84,    81,    82,    88,    70,   288,   227,
     290,    74,    69,   293,   294,    70,   184,   225,   323,    74,
      70,   326,    88,    69,    74,    71,   331,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   301,    36,    70,    69,   299,
      70,    74,   278,    43,    74,    70,   336,    18,    19,    74,
     181,   279,     3,    53,     5,     6,     7,     8,   286,    70,
      70,    69,   308,    74,    74,    65,   286,   295,    69,   359,
     360,   299,   362,   301,   310,   295,    76,    28,    29,    70,
     308,   371,   372,    74,    70,    88,    70,    70,    74,   220,
      74,    74,   328,    70,   384,    77,    78,    74,   155,   156,
     157,   158,    72,    72,    74,   333,    57,    88,   286,    22,
      23,     3,     4,   333,   151,   152,    70,   295,    69,   250,
      88,   153,   154,    66,    75,    76,    77,    78,    79,    80,
     159,   160,    74,    90,    70,   363,   364,   365,    72,    69,
      91,   369,    41,   363,   364,   365,    72,   278,   161,   369,
      90,   379,   380,   162,   382,   333,   163,   385,   164,   379,
     380,   389,   382,   391,   392,   385,   165,   125,   109,   389,
     398,   391,   392,   104,   308,   103,   304,   201,   398,   310,
     117,   131,    38,    -1,    -1,   363,   364,   365,    -1,    -1,
      -1,   369,    -1,    -1,    -1,    -1,    -1,   328,    -1,    -1,
      -1,   379,   380,    -1,   382,    -1,    -1,   385,    -1,    -1,
      -1,   389,    -1,   391,   392,    -1,    -1,    -1,    -1,    -1,
     398,     3,     4,     5,     6,     7,     8,    10,    11,    12,
      13,    14,    15,    16,    17,    -1,    -1,    20,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    -1,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    -1,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    -1,    -1,    69,    -1,    -1,
      -1,    -1,    -1,    75,    76,    77,    78,    79,    80,     3,
       4,     5,     6,     7,     8,    -1,    89,    -1,    90,    91,
      92,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    29,    -1,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    -1,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    -1,     3,    69,     5,     6,     7,     8,
      -1,    75,    76,    77,    78,    79,    80,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    90,    91,    92,    28,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    -1,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,
      69,    -1,    -1,    -1,    -1,    -1,    75,    76,    77,    78,
      79,    80,    -1,    -1,    -1,    28,    29,    -1,    -1,    -1,
      33,    34,    91,    92,    37,    38,    39,    -1,    -1,    -1,
      43,    -1,    -1,    46,    47,    48,    -1,    -1,    -1,    -1,
      -1,    54,    -1,     4,    57,    -1,    -1,    60,    -1,    -1,
      -1,    -1,    -1,    66,    -1,    -1,    69,    -1,    -1,    -1,
      -1,    -1,    75,    76,    77,    78,    79,    80,    -1,    -1,
      -1,    32,    -1,    -1,    35,    36,    -1,    90,    91,    40,
      -1,    42,    43,     4,    45,    -1,    -1,    -1,    -1,    50,
      51,    -1,    53,    -1,    55,    56,    -1,    -1,    59,    -1,
      -1,    62,    63,    64,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    -1,    -1,    35,    36,    -1,    -1,     4,    40,
      -1,    42,    43,    -1,    45,    -1,    -1,    -1,    -1,    50,
      51,    92,    53,    -1,    55,    56,    -1,    -1,    59,    -1,
      -1,    62,    63,    64,    65,    31,    32,    -1,    -1,    35,
      36,    -1,    -1,    -1,    40,    -1,    42,    43,    44,    45,
      -1,     4,    -1,    49,    50,    51,    52,    53,    -1,    55,
      56,    92,    58,    59,    -1,    61,    62,    63,    64,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,
      -1,    -1,    35,    36,    -1,    -1,    -1,    40,    -1,    42,
      43,    44,    45,    89,    -1,    91,    49,    50,    51,    52,
      53,    -1,    55,    56,    -1,    58,    59,    -1,    61,    62,
      63,    64,    65,    -1,     3,    -1,     5,     6,     7,     8,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,    -1,     5,     6,     7,     8,    -1,    -1,    91,    28,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    28,    29,     3,    -1,     5,
       6,     7,     8,    -1,    -1,    -1,    -1,    -1,    57,    -1,
      43,    -1,    -1,     3,    -1,     5,     6,     7,     8,    -1,
      69,    -1,    28,    29,    57,    -1,    75,    76,    77,    78,
      79,    80,    -1,    -1,    -1,    -1,    69,    43,    28,    29,
      -1,    90,    75,    76,    77,    78,    79,    80,    -1,    -1,
      -1,    57,    -1,    43,    -1,    -1,    -1,    90,    -1,    -1,
      -1,    -1,    -1,    69,    -1,    -1,    -1,    57,    -1,    75,
      76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,    69,
      -1,    -1,    -1,    -1,    90,    75,    76,    77,    78,    79,
      80,     3,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    -1,    -1,
      32,    -1,    -1,    35,    36,    -1,    -1,    -1,    40,    -1,
      42,    43,    -1,    45,    -1,    -1,    -1,    -1,    50,    51,
      -1,    53,    -1,    55,    56,    57,    -1,    59,    -1,    -1,
      62,    63,    64,    65,    -1,    -1,     3,    69,     5,     6,
       7,     8,    -1,    75,    76,    77,    78,    79,    80,    -1,
      -1,    -1,     3,    -1,     5,     6,     7,     8,    -1,    -1,
      -1,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    28,    29,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      57,     3,    43,     5,     6,     7,     8,    -1,    -1,    -1,
      -1,    -1,    69,    70,    -1,    -1,    57,    -1,    75,    76,
      77,    78,    79,    80,    -1,    -1,    28,    29,    69,    70,
      -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,    80,
       3,    43,     5,     6,     7,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    57,     3,    -1,     5,     6,
       7,     8,    -1,    -1,    -1,    28,    29,    69,    70,    -1,
      -1,    -1,    -1,    75,    76,    77,    78,    79,    80,    -1,
      43,    28,    29,     3,    -1,     5,     6,     7,     8,    -1,
      -1,    -1,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    69,    70,    28,    29,
      57,    -1,    75,    76,    77,    78,    79,    80,    -1,    -1,
      -1,    -1,    69,    43,    -1,    72,    -1,    -1,    75,    76,
      77,    78,    79,    80,    -1,    -1,     3,    57,     5,     6,
       7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,
      -1,    -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,
      80,    28,    29,     3,    -1,     5,     6,     7,     8,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
      -1,     5,     6,     7,     8,    -1,    -1,    -1,    28,    29,
      57,    -1,    -1,     3,    -1,     5,     6,     7,     8,    -1,
      -1,    -1,    69,    70,    28,    29,    -1,    -1,    75,    76,
      77,    78,    79,    80,    -1,    -1,    -1,    57,    28,    29,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,
      -1,    -1,    72,    57,    -1,    75,    76,    77,    78,    79,
      80,    -1,    -1,    -1,    -1,    69,    -1,    57,    72,    -1,
      -1,    75,    76,    77,    78,    79,    80,    -1,     3,    69,
       5,     6,     7,     8,    -1,    75,    76,    77,    78,    79,
      80,     3,    -1,     5,     6,     7,     8,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,    -1,    69,    57,    -1,     9,    -1,    -1,
      75,    76,    77,    78,    79,    80,    -1,    69,    -1,    -1,
      -1,    -1,    -1,    75,    76,    77,    78,    79,    80,    31,
      32,    -1,    -1,    35,    36,    -1,    -1,    -1,    40,    -1,
      42,    43,    44,    45,    -1,    -1,    -1,    49,    50,    51,
      52,    53,    -1,    55,    56,    -1,    58,    59,    -1,    61,
      62,    63,    64,    65,    -1,     4,    -1,    69,    70,    71,
       9,    -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    32,    -1,    -1,    35,    36,    -1,    -1,
      -1,    40,    -1,    42,    43,    44,    45,    -1,    -1,    -1,
      49,    50,    51,    52,    53,    -1,    55,    56,    -1,    58,
      59,    -1,    61,    62,    63,    64,    65,    -1,    -1,    -1,
      69,    70,    71,    -1,     0,     1,    -1,    76,     4,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    32,    -1,    -1,    35,
      36,    -1,    -1,    -1,    40,    -1,    42,    43,    44,    45,
      -1,    -1,    -1,    49,    50,    51,    52,    53,     1,    55,
      56,     4,    58,    59,    -1,    61,    62,    63,    64,    65,
      -1,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,
      -1,    -1,    35,    36,    -1,    -1,    -1,    40,    -1,    42,
      43,    44,    45,    -1,    -1,    -1,    49,    50,    51,    52,
      53,    -1,    55,    56,    -1,    58,    59,    -1,    61,    62,
      63,    64,    65,    -1,    67,    68,     3,     4,    -1,    -1,
      -1,    -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    32,    -1,    -1,    35,    36,
      -1,    -1,    -1,    40,     4,    42,    43,    44,    45,     9,
      -1,    -1,    49,    50,    51,    52,    53,    -1,    55,    56,
      -1,    58,    59,    -1,    61,    62,    63,    64,    65,    -1,
      -1,    31,    32,    70,    -1,    35,    36,    -1,    -1,    -1,
      40,     4,    42,    43,    44,    45,     9,    -1,    -1,    49,
      50,    51,    52,    53,    -1,    55,    56,    -1,    58,    59,
      -1,    61,    62,    63,    64,    65,    -1,    -1,    31,    32,
      70,    -1,    35,    36,    -1,    -1,     4,    40,    -1,    42,
      43,    44,    45,    -1,    -1,    -1,    49,    50,    51,    52,
      53,    -1,    55,    56,    -1,    58,    59,    -1,    61,    62,
      63,    64,    65,    31,    32,    -1,    -1,    35,    36,    -1,
       4,    -1,    40,    -1,    42,    43,    44,    45,    -1,    -1,
      -1,    49,    50,    51,    52,    53,    -1,    55,    56,    -1,
      58,    59,    -1,    61,    62,    63,    64,    65,    32,    -1,
      -1,    35,    36,    -1,    -1,    -1,    40,    -1,    42,    43,
      -1,    45,    -1,    -1,    -1,    -1,    50,    51,    -1,    53,
      -1,    55,    56,    -1,    -1,    59,    -1,    -1,    62,    63,
      64,    65
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     4,    31,    32,    35,    36,    40,    42,    43,
      44,    45,    49,    50,    51,    52,    53,    55,    56,    58,
      59,    61,    62,    63,    64,    65,    67,    68,   118,   119,
     122,   123,   124,   125,   131,   135,   136,   147,   159,   160,
     161,   163,   164,   165,   166,   167,     3,    91,    96,    97,
     147,    69,    76,    90,    96,   120,   121,   137,   138,   139,
     119,   119,    91,    97,   119,   119,     0,   160,    69,     5,
       6,     7,     8,    28,    29,    57,    69,    75,    76,    77,
      78,    79,    80,    94,    95,    96,    98,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   117,   132,   133,    91,   137,   135,   139,   140,    74,
      90,    89,    91,   118,   119,   152,   162,    69,    71,   138,
     123,   126,   127,   128,   135,    91,    96,   143,    69,   100,
     100,    69,   100,    43,   100,   113,   114,   116,   128,   144,
       8,    28,    29,    30,    69,    71,    73,   102,    76,    81,
      82,    77,    78,    18,    19,    24,    25,    83,    84,    22,
      23,    75,    85,    86,    26,    27,    87,    74,    92,    96,
     134,   132,    70,   135,   139,   121,   137,    91,   114,   148,
      33,    34,    37,    38,    39,    46,    47,    48,    54,    60,
      66,    90,    92,    96,    97,   116,   118,   147,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   118,   152,     9,
      70,   119,   141,   142,   143,    72,   114,   128,    92,   127,
      88,   129,   130,   137,   128,   126,    70,    74,    43,   144,
     116,    10,    11,    12,    13,    14,    15,    16,    17,    20,
      21,    89,   115,    70,    74,    69,    71,   139,   145,   146,
      70,    97,    70,    99,   114,   116,    97,   102,   102,   102,
     103,   103,   104,   104,   105,   105,   105,   105,   106,   106,
     107,   108,   109,   110,   111,   116,    92,   134,    89,    74,
      92,   148,   149,    90,   117,    90,    88,   150,    69,    97,
      69,    90,   116,    69,    69,    88,    90,    92,   154,    69,
     137,   139,   145,    70,    74,    70,    72,   117,    74,    90,
      88,    92,    96,    70,   114,   114,    70,   141,   145,    72,
     114,   146,    69,    71,   102,    70,    74,    72,    88,   117,
      92,    74,    92,    88,   150,    66,    90,   116,    90,   116,
      90,   116,   116,   150,   142,   130,   117,    70,    70,    72,
      70,   141,    72,   114,   114,   113,    92,   148,   150,    69,
      90,   116,    90,    70,    70,    70,    70,    72,   116,    70,
     116,    90,    90,   116,   150,   150,   150,    70,   150,    70,
      70,   116,    70,   116,    90,    41,    90,   150,   150,    70,
     150,    70,    70,   116,   150,   150,   150,   150,    70,   150
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
      yyerror (scanner, YY_("syntax error: cannot back up")); \
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
# define YYLEX yylex (scanner)
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
		  Type, Value, scanner); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, GISourceScanner* scanner)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, scanner)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    GISourceScanner* scanner;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (scanner);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, GISourceScanner* scanner)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, scanner)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    GISourceScanner* scanner;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, scanner);
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, GISourceScanner* scanner)
#else
static void
yy_reduce_print (yyvsp, yyrule, scanner)
    YYSTYPE *yyvsp;
    int yyrule;
    GISourceScanner* scanner;
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
		       		       , scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, scanner); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, GISourceScanner* scanner)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, scanner)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    GISourceScanner* scanner;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (scanner);

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
int yyparse (GISourceScanner* scanner);
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
yyparse (GISourceScanner* scanner)
#else
int
yyparse (scanner)
    GISourceScanner* scanner;
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
#line 145 "scannerparser.y"
    {
		(yyval.symbol) = g_hash_table_lookup (const_table, (yyvsp[(1) - (1)].str));
		if ((yyval.symbol) == NULL) {
			(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, lineno);
		} else {
			(yyval.symbol) = gi_source_symbol_ref ((yyval.symbol));
		}
	  }
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 154 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		if (g_str_has_prefix (yytext, "0x") && strlen (yytext) > 2) {
			(yyval.symbol)->const_int = strtol (yytext + 2, NULL, 16);
		} else if (g_str_has_prefix (yytext, "0") && strlen (yytext) > 1) {
			(yyval.symbol)->const_int = strtol (yytext + 1, NULL, 8);
		} else {
			(yyval.symbol)->const_int = atoi (yytext);
		}
	  }
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 166 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, lineno);
	  }
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 170 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, lineno);
		(yyval.symbol)->const_double_set = TRUE;
		(yyval.symbol)->const_double = 0.0;
        sscanf (yytext, "%lf", &((yyval.symbol)->const_double));
	  }
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 178 "scannerparser.y"
    {
		(yyval.symbol) = (yyvsp[(2) - (3)].symbol);
	  }
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 186 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, lineno);
		yytext[strlen (yytext) - 1] = '\0';
		(yyval.symbol)->const_string = g_strcompress (yytext + 1);
                if (!g_utf8_validate ((yyval.symbol)->const_string, -1, NULL))
                  {
#if 0
                    g_warning ("Ignoring non-UTF-8 constant string \"%s\"", yytext + 1);
#endif                    
                    g_free((yyval.symbol)->const_string);
                    (yyval.symbol)->const_string = NULL;
                  }

	  }
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 201 "scannerparser.y"
    {
		char *strings, *string2;
		(yyval.symbol) = (yyvsp[(1) - (2)].symbol);
		yytext[strlen (yytext) - 1] = '\0';
		string2 = g_strcompress (yytext + 1);
		strings = g_strconcat ((yyval.symbol)->const_string, string2, NULL);
		g_free ((yyval.symbol)->const_string);
		g_free (string2);
		(yyval.symbol)->const_string = strings;
	  }
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 215 "scannerparser.y"
    {
		(yyval.str) = g_strdup (yytext);
	  }
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 228 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, lineno);
	  }
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 232 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, lineno);
	  }
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 236 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, lineno);
	  }
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 240 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, lineno);
	  }
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 244 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, lineno);
	  }
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 248 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, lineno);
	  }
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 252 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, lineno);
	  }
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 265 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, lineno);
	  }
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 269 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, lineno);
	  }
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 273 "scannerparser.y"
    {
		switch ((yyvsp[(1) - (2)].unary_operator)) {
		case UNARY_PLUS:
			(yyval.symbol) = (yyvsp[(2) - (2)].symbol);
			break;
		case UNARY_MINUS:
			(yyval.symbol) = (yyvsp[(2) - (2)].symbol);
			(yyval.symbol)->const_int = -(yyvsp[(2) - (2)].symbol)->const_int;
			break;
		case UNARY_BITWISE_COMPLEMENT:
			(yyval.symbol) = (yyvsp[(2) - (2)].symbol);
			(yyval.symbol)->const_int = ~(yyvsp[(2) - (2)].symbol)->const_int;
			break;
		case UNARY_LOGICAL_NEGATION:
			(yyval.symbol) = (yyvsp[(2) - (2)].symbol);
			(yyval.symbol)->const_int = !gi_source_symbol_get_const_boolean ((yyvsp[(2) - (2)].symbol));
			break;
		default:
			(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, lineno);
			break;
		}
	  }
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 296 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, lineno);
	  }
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 300 "scannerparser.y"
    {
		ctype_free ((yyvsp[(3) - (4)].ctype));
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, lineno);
	  }
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 308 "scannerparser.y"
    {
		(yyval.unary_operator) = UNARY_ADDRESS_OF;
	  }
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 312 "scannerparser.y"
    {
		(yyval.unary_operator) = UNARY_POINTER_INDIRECTION;
	  }
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 316 "scannerparser.y"
    {
		(yyval.unary_operator) = UNARY_PLUS;
	  }
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 320 "scannerparser.y"
    {
		(yyval.unary_operator) = UNARY_MINUS;
	  }
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 324 "scannerparser.y"
    {
		(yyval.unary_operator) = UNARY_BITWISE_COMPLEMENT;
	  }
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 328 "scannerparser.y"
    {
		(yyval.unary_operator) = UNARY_LOGICAL_NEGATION;
	  }
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 336 "scannerparser.y"
    {
		ctype_free ((yyvsp[(2) - (4)].ctype));
		(yyval.symbol) = (yyvsp[(4) - (4)].symbol);
	  }
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 345 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int * (yyvsp[(3) - (3)].symbol)->const_int;
	  }
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 351 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		if ((yyvsp[(3) - (3)].symbol)->const_int != 0) {
			(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int / (yyvsp[(3) - (3)].symbol)->const_int;
		}
	  }
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 359 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		if ((yyvsp[(3) - (3)].symbol)->const_int != 0) {
			(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int % (yyvsp[(3) - (3)].symbol)->const_int;
		}
	  }
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 371 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int + (yyvsp[(3) - (3)].symbol)->const_int;
	  }
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 377 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int - (yyvsp[(3) - (3)].symbol)->const_int;
	  }
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 387 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int << (yyvsp[(3) - (3)].symbol)->const_int;

		/* assume this is a bitfield/flags declaration
		 * if a left shift operator is sued in an enum value
                 * This mimics the glib-mkenum behavior.
		 */
		is_bitfield = TRUE;
	  }
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 399 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int >> (yyvsp[(3) - (3)].symbol)->const_int;
	  }
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 409 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int < (yyvsp[(3) - (3)].symbol)->const_int;
	  }
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 415 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int > (yyvsp[(3) - (3)].symbol)->const_int;
	  }
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 421 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int <= (yyvsp[(3) - (3)].symbol)->const_int;
	  }
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 427 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int >= (yyvsp[(3) - (3)].symbol)->const_int;
	  }
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 437 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int == (yyvsp[(3) - (3)].symbol)->const_int;
	  }
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 443 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int != (yyvsp[(3) - (3)].symbol)->const_int;
	  }
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 453 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int & (yyvsp[(3) - (3)].symbol)->const_int;
	  }
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 463 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int ^ (yyvsp[(3) - (3)].symbol)->const_int;
	  }
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 473 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int | (yyvsp[(3) - (3)].symbol)->const_int;
	  }
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 483 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int =
		  gi_source_symbol_get_const_boolean ((yyvsp[(1) - (3)].symbol)) &&
		  gi_source_symbol_get_const_boolean ((yyvsp[(3) - (3)].symbol));
	  }
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 495 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int =
		  gi_source_symbol_get_const_boolean ((yyvsp[(1) - (3)].symbol)) ||
		  gi_source_symbol_get_const_boolean ((yyvsp[(3) - (3)].symbol));
	  }
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 507 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_get_const_boolean ((yyvsp[(1) - (5)].symbol)) ? (yyvsp[(3) - (5)].symbol) : (yyvsp[(5) - (5)].symbol);
	  }
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 515 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, lineno);
	  }
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 538 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, lineno);
	  }
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 551 "scannerparser.y"
    {
		GList *l;
		for (l = (yyvsp[(2) - (3)].list); l != NULL; l = l->next) {
			GISourceSymbol *sym = l->data;
			gi_source_symbol_merge_type (sym, gi_source_type_copy ((yyvsp[(1) - (3)].ctype)));
			if ((yyvsp[(1) - (3)].ctype)->storage_class_specifier & STORAGE_CLASS_TYPEDEF) {
				sym->type = CSYMBOL_TYPE_TYPEDEF;
			} else if (sym->base_type->type == CTYPE_FUNCTION) {
				sym->type = CSYMBOL_TYPE_FUNCTION;
			} else {
				sym->type = CSYMBOL_TYPE_OBJECT;
			}
			gi_source_scanner_add_symbol (scanner, sym);
			gi_source_symbol_unref (sym);
		}
		ctype_free ((yyvsp[(1) - (3)].ctype));
	  }
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 569 "scannerparser.y"
    {
		ctype_free ((yyvsp[(1) - (2)].ctype));
	  }
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 576 "scannerparser.y"
    {
		(yyval.ctype) = (yyvsp[(2) - (2)].ctype);
		(yyval.ctype)->storage_class_specifier |= (yyvsp[(1) - (2)].storage_class_specifier);
	  }
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 581 "scannerparser.y"
    {
		(yyval.ctype) = gi_source_type_new (CTYPE_INVALID);
		(yyval.ctype)->storage_class_specifier |= (yyvsp[(1) - (1)].storage_class_specifier);
	  }
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 586 "scannerparser.y"
    {
		(yyval.ctype) = (yyvsp[(1) - (2)].ctype);
		/* combine basic types like unsigned int and long long */
		if ((yyval.ctype)->type == CTYPE_BASIC_TYPE && (yyvsp[(2) - (2)].ctype)->type == CTYPE_BASIC_TYPE) {
			char *name = g_strdup_printf ("%s %s", (yyval.ctype)->name, (yyvsp[(2) - (2)].ctype)->name);
			g_free ((yyval.ctype)->name);
			(yyval.ctype)->name = name;
			ctype_free ((yyvsp[(2) - (2)].ctype));
		} else {
			(yyval.ctype)->base_type = (yyvsp[(2) - (2)].ctype);
		}
	  }
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 600 "scannerparser.y"
    {
		(yyval.ctype) = (yyvsp[(2) - (2)].ctype);
		(yyval.ctype)->type_qualifier |= (yyvsp[(1) - (2)].type_qualifier);
	  }
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 605 "scannerparser.y"
    {
		(yyval.ctype) = gi_source_type_new (CTYPE_INVALID);
		(yyval.ctype)->type_qualifier |= (yyvsp[(1) - (1)].type_qualifier);
	  }
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 610 "scannerparser.y"
    {
		(yyval.ctype) = (yyvsp[(2) - (2)].ctype);
		(yyval.ctype)->function_specifier |= (yyvsp[(1) - (2)].function_specifier);
	  }
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 615 "scannerparser.y"
    {
		(yyval.ctype) = gi_source_type_new (CTYPE_INVALID);
		(yyval.ctype)->function_specifier |= (yyvsp[(1) - (1)].function_specifier);
	  }
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 623 "scannerparser.y"
    {
		(yyval.list) = g_list_append (NULL, (yyvsp[(1) - (1)].symbol));
	  }
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 627 "scannerparser.y"
    {
		(yyval.list) = g_list_append ((yyvsp[(1) - (3)].list), (yyvsp[(3) - (3)].symbol));
	  }
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 639 "scannerparser.y"
    {
		(yyval.storage_class_specifier) = STORAGE_CLASS_TYPEDEF;
	  }
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 643 "scannerparser.y"
    {
		(yyval.storage_class_specifier) = STORAGE_CLASS_EXTERN;
	  }
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 647 "scannerparser.y"
    {
		(yyval.storage_class_specifier) = STORAGE_CLASS_STATIC;
	  }
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 651 "scannerparser.y"
    {
		(yyval.storage_class_specifier) = STORAGE_CLASS_AUTO;
	  }
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 655 "scannerparser.y"
    {
		(yyval.storage_class_specifier) = STORAGE_CLASS_REGISTER;
	  }
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 662 "scannerparser.y"
    {
		(yyval.ctype) = gi_source_type_new (CTYPE_VOID);
	  }
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 666 "scannerparser.y"
    {
		(yyval.ctype) = gi_source_basic_type_new ("char");
	  }
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 670 "scannerparser.y"
    {
		(yyval.ctype) = gi_source_basic_type_new ("short");
	  }
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 674 "scannerparser.y"
    {
		(yyval.ctype) = gi_source_basic_type_new ("int");
	  }
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 678 "scannerparser.y"
    {
		(yyval.ctype) = gi_source_basic_type_new ("long");
	  }
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 682 "scannerparser.y"
    {
		(yyval.ctype) = gi_source_basic_type_new ("float");
	  }
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 686 "scannerparser.y"
    {
		(yyval.ctype) = gi_source_basic_type_new ("double");
	  }
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 690 "scannerparser.y"
    {
		(yyval.ctype) = gi_source_basic_type_new ("signed");
	  }
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 694 "scannerparser.y"
    {
		(yyval.ctype) = gi_source_basic_type_new ("unsigned");
	  }
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 698 "scannerparser.y"
    {
		(yyval.ctype) = gi_source_basic_type_new ("bool");
	  }
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 704 "scannerparser.y"
    {
		(yyval.ctype) = gi_source_typedef_new ((yyvsp[(1) - (1)].str));
		g_free ((yyvsp[(1) - (1)].str));
	  }
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 712 "scannerparser.y"
    {
		(yyval.ctype) = (yyvsp[(1) - (5)].ctype);
		(yyval.ctype)->name = (yyvsp[(2) - (5)].str);
		(yyval.ctype)->child_list = (yyvsp[(4) - (5)].list);

		GISourceSymbol *sym = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, lineno);
		if ((yyval.ctype)->type == CTYPE_STRUCT) {
			sym->type = CSYMBOL_TYPE_STRUCT;
		} else if ((yyval.ctype)->type == CTYPE_UNION) {
			sym->type = CSYMBOL_TYPE_UNION;
		} else {
			g_assert_not_reached ();
		}
		sym->ident = g_strdup ((yyval.ctype)->name);
		sym->base_type = gi_source_type_copy ((yyval.ctype));
		gi_source_scanner_add_symbol (scanner, sym);
		gi_source_symbol_unref (sym);
	  }
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 731 "scannerparser.y"
    {
		(yyval.ctype) = (yyvsp[(1) - (4)].ctype);
		(yyval.ctype)->child_list = (yyvsp[(3) - (4)].list);
	  }
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 736 "scannerparser.y"
    {
		(yyval.ctype) = (yyvsp[(1) - (2)].ctype);
		(yyval.ctype)->name = (yyvsp[(2) - (2)].str);
	  }
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 744 "scannerparser.y"
    {
		(yyval.ctype) = gi_source_struct_new (NULL);
	  }
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 748 "scannerparser.y"
    {
		(yyval.ctype) = gi_source_union_new (NULL);
	  }
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 756 "scannerparser.y"
    {
		(yyval.list) = g_list_concat ((yyvsp[(1) - (2)].list), (yyvsp[(2) - (2)].list));
	  }
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 763 "scannerparser.y"
    {
	    GList *l;
	    (yyval.list) = NULL;
	    for (l = (yyvsp[(2) - (3)].list); l != NULL; l = l->next)
	      {
		GISourceSymbol *sym = l->data;
		if ((yyvsp[(1) - (3)].ctype)->storage_class_specifier & STORAGE_CLASS_TYPEDEF)
		    sym->type = CSYMBOL_TYPE_TYPEDEF;
		else
		    sym->type = CSYMBOL_TYPE_MEMBER;
		gi_source_symbol_merge_type (sym, gi_source_type_copy ((yyvsp[(1) - (3)].ctype)));
		(yyval.list) = g_list_append ((yyval.list), sym);
	      }
	    ctype_free ((yyvsp[(1) - (3)].ctype));
	  }
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 782 "scannerparser.y"
    {
		(yyval.ctype) = (yyvsp[(1) - (2)].ctype);
		(yyval.ctype)->base_type = (yyvsp[(2) - (2)].ctype);
	  }
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 788 "scannerparser.y"
    {
		(yyval.ctype) = (yyvsp[(2) - (2)].ctype);
		(yyval.ctype)->type_qualifier |= (yyvsp[(1) - (2)].type_qualifier);
	  }
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 793 "scannerparser.y"
    {
		(yyval.ctype) = gi_source_type_new (CTYPE_INVALID);
		(yyval.ctype)->type_qualifier |= (yyvsp[(1) - (1)].type_qualifier);
	  }
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 801 "scannerparser.y"
    {
		(yyval.list) = g_list_append (NULL, (yyvsp[(1) - (1)].symbol));
	  }
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 805 "scannerparser.y"
    {
		(yyval.list) = g_list_append ((yyvsp[(1) - (3)].list), (yyvsp[(3) - (3)].symbol));
	  }
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 812 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, lineno);
	  }
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 817 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, lineno);
	  }
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 821 "scannerparser.y"
    {
		(yyval.symbol) = (yyvsp[(1) - (3)].symbol);
		if ((yyvsp[(3) - (3)].symbol)->const_int_set) {
		  (yyval.symbol)->const_int_set = TRUE;
		  (yyval.symbol)->const_int = (yyvsp[(3) - (3)].symbol)->const_int;
		}
	  }
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 832 "scannerparser.y"
    {
		(yyval.ctype) = gi_source_enum_new ((yyvsp[(2) - (5)].str));
		(yyval.ctype)->child_list = (yyvsp[(4) - (5)].list);
		(yyval.ctype)->is_bitfield = is_bitfield;
		last_enum_value = -1;
	  }
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 839 "scannerparser.y"
    {
		(yyval.ctype) = gi_source_enum_new (NULL);
		(yyval.ctype)->child_list = (yyvsp[(3) - (4)].list);
		(yyval.ctype)->is_bitfield = is_bitfield;
		last_enum_value = -1;
	  }
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 846 "scannerparser.y"
    {
		(yyval.ctype) = gi_source_enum_new ((yyvsp[(2) - (6)].str));
		(yyval.ctype)->child_list = (yyvsp[(4) - (6)].list);
		(yyval.ctype)->is_bitfield = is_bitfield;
		last_enum_value = -1;
	  }
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 853 "scannerparser.y"
    {
		(yyval.ctype) = gi_source_enum_new (NULL);
		(yyval.ctype)->child_list = (yyvsp[(3) - (5)].list);
		(yyval.ctype)->is_bitfield = is_bitfield;
		last_enum_value = -1;
	  }
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 860 "scannerparser.y"
    {
		(yyval.ctype) = gi_source_enum_new ((yyvsp[(2) - (2)].str));
	  }
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 867 "scannerparser.y"
    {
		/* reset flag before the first enum value */
		is_bitfield = FALSE;
	  }
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 872 "scannerparser.y"
    {
		(yyval.list) = g_list_append (NULL, (yyvsp[(2) - (2)].symbol));
	  }
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 876 "scannerparser.y"
    {
		(yyval.list) = g_list_append ((yyvsp[(1) - (3)].list), (yyvsp[(3) - (3)].symbol));
	  }
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 883 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_OBJECT, lineno);
		(yyval.symbol)->ident = (yyvsp[(1) - (1)].str);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = ++last_enum_value;
		g_hash_table_insert (const_table, g_strdup ((yyval.symbol)->ident), gi_source_symbol_ref ((yyval.symbol)));
	  }
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 891 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_OBJECT, lineno);
		(yyval.symbol)->ident = (yyvsp[(1) - (3)].str);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = (yyvsp[(3) - (3)].symbol)->const_int;
		last_enum_value = (yyval.symbol)->const_int;
		g_hash_table_insert (const_table, g_strdup ((yyval.symbol)->ident), gi_source_symbol_ref ((yyval.symbol)));
	  }
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 903 "scannerparser.y"
    {
		(yyval.type_qualifier) = TYPE_QUALIFIER_CONST;
	  }
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 907 "scannerparser.y"
    {
		(yyval.type_qualifier) = TYPE_QUALIFIER_RESTRICT;
	  }
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 911 "scannerparser.y"
    {
		(yyval.type_qualifier) = TYPE_QUALIFIER_EXTENSION;
	  }
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 915 "scannerparser.y"
    {
		(yyval.type_qualifier) = TYPE_QUALIFIER_VOLATILE;
	  }
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 922 "scannerparser.y"
    {
		(yyval.function_specifier) = FUNCTION_INLINE;
	  }
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 929 "scannerparser.y"
    {
		(yyval.symbol) = (yyvsp[(2) - (2)].symbol);
		gi_source_symbol_merge_type ((yyval.symbol), (yyvsp[(1) - (2)].ctype));
	  }
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 938 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, lineno);
		(yyval.symbol)->ident = (yyvsp[(1) - (1)].str);
	  }
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 943 "scannerparser.y"
    {
		(yyval.symbol) = (yyvsp[(2) - (3)].symbol);
	  }
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 947 "scannerparser.y"
    {
		(yyval.symbol) = (yyvsp[(1) - (4)].symbol);
		gi_source_symbol_merge_type ((yyval.symbol), gi_source_array_new ((yyvsp[(3) - (4)].symbol)));
	  }
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 952 "scannerparser.y"
    {
		(yyval.symbol) = (yyvsp[(1) - (3)].symbol);
		gi_source_symbol_merge_type ((yyval.symbol), gi_source_array_new (NULL));
	  }
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 957 "scannerparser.y"
    {
		GISourceType *func = gi_source_function_new ();
		// ignore (void) parameter list
		if ((yyvsp[(3) - (4)].list) != NULL && ((yyvsp[(3) - (4)].list)->next != NULL || ((GISourceSymbol *) (yyvsp[(3) - (4)].list)->data)->base_type->type != CTYPE_VOID)) {
			func->child_list = (yyvsp[(3) - (4)].list);
		}
		(yyval.symbol) = (yyvsp[(1) - (4)].symbol);
		gi_source_symbol_merge_type ((yyval.symbol), func);
	  }
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 967 "scannerparser.y"
    {
		GISourceType *func = gi_source_function_new ();
		func->child_list = (yyvsp[(3) - (4)].list);
		(yyval.symbol) = (yyvsp[(1) - (4)].symbol);
		gi_source_symbol_merge_type ((yyval.symbol), func);
	  }
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 974 "scannerparser.y"
    {
		GISourceType *func = gi_source_function_new ();
		(yyval.symbol) = (yyvsp[(1) - (3)].symbol);
		gi_source_symbol_merge_type ((yyval.symbol), func);
	  }
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 983 "scannerparser.y"
    {
		(yyval.ctype) = gi_source_pointer_new (NULL);
		(yyval.ctype)->type_qualifier = (yyvsp[(2) - (2)].type_qualifier);
	  }
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 988 "scannerparser.y"
    {
		(yyval.ctype) = gi_source_pointer_new (NULL);
	  }
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 992 "scannerparser.y"
    {
		(yyval.ctype) = gi_source_pointer_new ((yyvsp[(3) - (3)].ctype));
		(yyval.ctype)->type_qualifier = (yyvsp[(2) - (3)].type_qualifier);
	  }
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 997 "scannerparser.y"
    {
		(yyval.ctype) = gi_source_pointer_new ((yyvsp[(2) - (2)].ctype));
	  }
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 1005 "scannerparser.y"
    {
		(yyval.type_qualifier) = (yyvsp[(1) - (2)].type_qualifier) | (yyvsp[(2) - (2)].type_qualifier);
	  }
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 1012 "scannerparser.y"
    {
		(yyval.list) = g_list_append (NULL, (yyvsp[(1) - (1)].symbol));
	  }
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 1016 "scannerparser.y"
    {
		(yyval.list) = g_list_append ((yyvsp[(1) - (3)].list), (yyvsp[(3) - (3)].symbol));
	  }
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 1023 "scannerparser.y"
    {
		(yyval.symbol) = (yyvsp[(2) - (2)].symbol);
		gi_source_symbol_merge_type ((yyval.symbol), (yyvsp[(1) - (2)].ctype));
	  }
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 1028 "scannerparser.y"
    {
		(yyval.symbol) = (yyvsp[(2) - (2)].symbol);
		gi_source_symbol_merge_type ((yyval.symbol), (yyvsp[(1) - (2)].ctype));
	  }
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 1033 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, lineno);
		(yyval.symbol)->base_type = (yyvsp[(1) - (1)].ctype);
	  }
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 1038 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_ELLIPSIS, lineno);
	  }
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 1045 "scannerparser.y"
    {
		GISourceSymbol *sym = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, lineno);
		sym->ident = (yyvsp[(1) - (1)].str);
		(yyval.list) = g_list_append (NULL, sym);
	  }
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 1051 "scannerparser.y"
    {
		GISourceSymbol *sym = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, lineno);
		sym->ident = (yyvsp[(3) - (3)].str);
		(yyval.list) = g_list_append ((yyvsp[(1) - (3)].list), sym);
	  }
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 1065 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, lineno);
		gi_source_symbol_merge_type ((yyval.symbol), (yyvsp[(1) - (1)].ctype));
	  }
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 1071 "scannerparser.y"
    {
		(yyval.symbol) = (yyvsp[(2) - (2)].symbol);
		gi_source_symbol_merge_type ((yyval.symbol), (yyvsp[(1) - (2)].ctype));
	  }
    break;

  case 177:

/* Line 1455 of yacc.c  */
#line 1079 "scannerparser.y"
    {
		(yyval.symbol) = (yyvsp[(2) - (3)].symbol);
	  }
    break;

  case 178:

/* Line 1455 of yacc.c  */
#line 1083 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, lineno);
		gi_source_symbol_merge_type ((yyval.symbol), gi_source_array_new (NULL));
	  }
    break;

  case 179:

/* Line 1455 of yacc.c  */
#line 1088 "scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, lineno);
		gi_source_symbol_merge_type ((yyval.symbol), gi_source_array_new ((yyvsp[(2) - (3)].symbol)));
	  }
    break;

  case 180:

/* Line 1455 of yacc.c  */
#line 1093 "scannerparser.y"
    {
		(yyval.symbol) = (yyvsp[(1) - (3)].symbol);
		gi_source_symbol_merge_type ((yyval.symbol), gi_source_array_new (NULL));
	  }
    break;

  case 181:

/* Line 1455 of yacc.c  */
#line 1098 "scannerparser.y"
    {
		(yyval.symbol) = (yyvsp[(1) - (4)].symbol);
		gi_source_symbol_merge_type ((yyval.symbol), gi_source_array_new ((yyvsp[(3) - (4)].symbol)));
	  }
    break;

  case 182:

/* Line 1455 of yacc.c  */
#line 1103 "scannerparser.y"
    {
		GISourceType *func = gi_source_function_new ();
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, lineno);
		gi_source_symbol_merge_type ((yyval.symbol), func);
	  }
    break;

  case 183:

/* Line 1455 of yacc.c  */
#line 1109 "scannerparser.y"
    {
		GISourceType *func = gi_source_function_new ();
		// ignore (void) parameter list
		if ((yyvsp[(2) - (3)].list) != NULL && ((yyvsp[(2) - (3)].list)->next != NULL || ((GISourceSymbol *) (yyvsp[(2) - (3)].list)->data)->base_type->type != CTYPE_VOID)) {
			func->child_list = (yyvsp[(2) - (3)].list);
		}
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, lineno);
		gi_source_symbol_merge_type ((yyval.symbol), func);
	  }
    break;

  case 184:

/* Line 1455 of yacc.c  */
#line 1119 "scannerparser.y"
    {
		GISourceType *func = gi_source_function_new ();
		(yyval.symbol) = (yyvsp[(1) - (3)].symbol);
		gi_source_symbol_merge_type ((yyval.symbol), func);
	  }
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 1125 "scannerparser.y"
    {
		GISourceType *func = gi_source_function_new ();
		// ignore (void) parameter list
		if ((yyvsp[(3) - (4)].list) != NULL && ((yyvsp[(3) - (4)].list)->next != NULL || ((GISourceSymbol *) (yyvsp[(3) - (4)].list)->data)->base_type->type != CTYPE_VOID)) {
			func->child_list = (yyvsp[(3) - (4)].list);
		}
		(yyval.symbol) = (yyvsp[(1) - (4)].symbol);
		gi_source_symbol_merge_type ((yyval.symbol), func);
	  }
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 1138 "scannerparser.y"
    {
		(yyval.str) = g_strdup (yytext);
	  }
    break;

  case 236:

/* Line 1455 of yacc.c  */
#line 1245 "scannerparser.y"
    {
		(yyval.str) = g_strdup (yytext + strlen ("#define "));
	  }
    break;

  case 237:

/* Line 1455 of yacc.c  */
#line 1252 "scannerparser.y"
    {
		(yyval.str) = g_strdup (yytext + strlen ("#define "));
	  }
    break;

  case 239:

/* Line 1455 of yacc.c  */
#line 1263 "scannerparser.y"
    {
		if ((yyvsp[(2) - (2)].symbol)->const_int_set || (yyvsp[(2) - (2)].symbol)->const_double_set || (yyvsp[(2) - (2)].symbol)->const_string != NULL) {
			(yyvsp[(2) - (2)].symbol)->ident = (yyvsp[(1) - (2)].str);
			gi_source_scanner_add_symbol (scanner, (yyvsp[(2) - (2)].symbol));
			gi_source_symbol_unref ((yyvsp[(2) - (2)].symbol));
		}
	  }
    break;



/* Line 1455 of yacc.c  */
#line 3726 "scannerparser.c"
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
      yyerror (scanner, YY_("syntax error"));
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
	    yyerror (scanner, yymsg);
	  }
	else
	  {
	    yyerror (scanner, YY_("syntax error"));
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
		      yytoken, &yylval, scanner);
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
		  yystos[yystate], yyvsp, scanner);
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
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, scanner);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, scanner);
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
#line 1278 "scannerparser.y"

static void
yyerror (GISourceScanner *scanner, const char *s)
{
  /* ignore errors while doing a macro scan as not all object macros
   * have valid expressions */
  if (!scanner->macro_scan)
    {
      fprintf(stderr, "%s:%d: %s in '%s' at '%s'\n",
	      scanner->current_filename, lineno, s, linebuf, yytext);
    }
}

static int
eat_hspace (FILE * f)
{
  int c;
  do
    {
      c = fgetc (f);
    }
  while (c == ' ' || c == '\t');
  return c;
}

static int
eat_line (FILE * f, int c)
{
  while (c != EOF && c != '\n')
    {
      c = fgetc (f);
    }
  if (c == '\n')
    {
      c = fgetc (f);
      if (c == ' ' || c == '\t')
        {
          c = eat_hspace (f);
        }
    }
  return c;
}

static int
read_identifier (FILE * f, int c, char **identifier)
{
  GString *id = g_string_new ("");
  while (g_ascii_isalnum (c) || c == '_')
    {
      g_string_append_c (id, c);
      c = fgetc (f);
    }
  *identifier = g_string_free (id, FALSE);
  return c;
}

void
gi_source_scanner_parse_macros (GISourceScanner *scanner, GList *filenames)
{
  GError *error = NULL;
  char *tmp_name = NULL;
  FILE *fmacros =
    fdopen (g_file_open_tmp ("gen-introspect-XXXXXX.h", &tmp_name, &error),
            "w+");
  g_unlink (tmp_name);

  GList *l;
  for (l = filenames; l != NULL; l = l->next)
    {
      FILE *f = fopen (l->data, "r");
      int line = 1;

      GString *define_line;
      char *str;
      gboolean error_line = FALSE;
      int c = eat_hspace (f);
      while (c != EOF)
        {
          if (c != '#')
            {
              /* ignore line */
              c = eat_line (f, c);
              line++;
              continue;
            }

          /* print current location */
          str = g_strescape (l->data, "");
          fprintf (fmacros, "# %d \"%s\"\n", line, str);
          g_free (str);

          c = eat_hspace (f);
          c = read_identifier (f, c, &str);
          if (strcmp (str, "define") != 0 || (c != ' ' && c != '\t'))
            {
              g_free (str);
              /* ignore line */
              c = eat_line (f, c);
              line++;
              continue;
            }
          g_free (str);
          c = eat_hspace (f);
          c = read_identifier (f, c, &str);
          if (strlen (str) == 0 || (c != ' ' && c != '\t' && c != '('))
            {
              g_free (str);
              /* ignore line */
              c = eat_line (f, c);
              line++;
              continue;
            }
          define_line = g_string_new ("#define ");
          g_string_append (define_line, str);
          g_free (str);
          if (c == '(')
            {
              while (c != ')')
                {
                  g_string_append_c (define_line, c);
                  c = fgetc (f);
                  if (c == EOF || c == '\n')
                    {
                      error_line = TRUE;
                      break;
                    }
                }
              if (error_line)
                {
                  g_string_free (define_line, TRUE);
                  /* ignore line */
                  c = eat_line (f, c);
                  line++;
                  continue;
                }

              g_assert (c == ')');
              g_string_append_c (define_line, c);
              c = fgetc (f);

              /* found function-like macro */
              fprintf (fmacros, "%s\n", define_line->str);

              g_string_free (define_line, TRUE);
              /* ignore rest of line */
              c = eat_line (f, c);
              line++;
              continue;
            }
          if (c != ' ' && c != '\t')
            {
              g_string_free (define_line, TRUE);
              /* ignore line */
              c = eat_line (f, c);
              line++;
              continue;
            }
          while (c != EOF && c != '\n')
            {
              g_string_append_c (define_line, c);
              c = fgetc (f);
              if (c == '\\')
                {
                  c = fgetc (f);
                  if (c == '\n')
                    {
                      /* fold lines when seeing backslash new-line sequence */
                      c = fgetc (f);
                    }
                  else
                    {
                      g_string_append_c (define_line, '\\');
                    }
                }
            }

          /* found object-like macro */
          fprintf (fmacros, "%s\n", define_line->str);

          c = eat_line (f, c);
          line++;
        }

      fclose (f);
    }

  rewind (fmacros);
  gi_source_scanner_parse_file (scanner, fmacros);
}

gboolean
gi_source_scanner_parse_file (GISourceScanner *scanner, FILE *file)
{
  g_return_val_if_fail (file != NULL, FALSE);
  
  const_table = g_hash_table_new_full (g_str_hash, g_str_equal,
				       g_free, (GDestroyNotify)gi_source_symbol_unref);
  
  lineno = 1;
  yyin = file;
  yyparse (scanner);
  
  g_hash_table_destroy (const_table);
  const_table = NULL;
  
  yyin = NULL;

  return TRUE;
}

gboolean
gi_source_scanner_lex_filename (GISourceScanner *scanner, const gchar *filename)
{
  yyin = fopen (filename, "r");

  while (yylex (scanner) != YYEOF)
    ;

  fclose (yyin);
  
  return TRUE;
}

