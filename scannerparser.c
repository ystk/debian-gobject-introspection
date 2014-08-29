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
#line 29 "giscanner/scannerparser.y"

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

/**
 * parse_c_string_literal:
 * @str: A string containing a C string literal
 *
 * Based on g_strcompress(), but also handles
 * hexadecimal escapes.
 */
static char *
parse_c_string_literal (const char *str)
{
  const gchar *p = str, *num;
  gchar *dest = g_malloc (strlen (str) + 1);
  gchar *q = dest;

  while (*p)
    {
      if (*p == '\\')
        {
          p++;
          switch (*p)
            {
            case '\0':
              g_warning ("parse_c_string_literal: trailing \\");
              goto out;
            case '0':  case '1':  case '2':  case '3':  case '4':
            case '5':  case '6':  case '7':
              *q = 0;
              num = p;
              while ((p < num + 3) && (*p >= '0') && (*p <= '7'))
                {
                  *q = (*q * 8) + (*p - '0');
                  p++;
                }
              q++;
              p--;
              break;
	    case 'x':
	      *q = 0;
	      p++;
	      num = p;
	      while ((p < num + 2) && (g_ascii_isxdigit(*p)))
		{
		  *q = (*q * 16) + g_ascii_xdigit_value(*p);
		  p++;
		}
              q++;
              p--;
	      break;
            case 'b':
              *q++ = '\b';
              break;
            case 'f':
              *q++ = '\f';
              break;
            case 'n':
              *q++ = '\n';
              break;
            case 'r':
              *q++ = '\r';
              break;
            case 't':
              *q++ = '\t';
              break;
            default:            /* Also handles \" and \\ */
              *q++ = *p;
              break;
            }
        }
      else
        *q++ = *p;
      p++;
    }
out:
  *q = 0;

  return dest;
}

enum {
  IRRELEVANT = 1,
  NOT_GI_SCANNER = 2,
  FOR_GI_SCANNER = 3,
};

static void
update_skipping (GISourceScanner *scanner)
{
  GList *l;
  for (l = scanner->conditionals.head; l != NULL; l = g_list_next (l))
    {
      if (GPOINTER_TO_INT (l->data) == NOT_GI_SCANNER)
        {
           scanner->skipping = TRUE;
           return;
        }
    }

  scanner->skipping = FALSE;
}

static void
push_conditional (GISourceScanner *scanner,
                  gint type)
{
  g_assert (type != 0);
  g_queue_push_head (&scanner->conditionals, GINT_TO_POINTER (type));
}

static gint
pop_conditional (GISourceScanner *scanner)
{
  gint type = GPOINTER_TO_INT (g_queue_pop_head (&scanner->conditionals));

  if (type == 0)
    {
      gchar *filename = g_file_get_path (scanner->current_file);
      fprintf (stderr, "%s:%d: mismatched %s", filename, lineno, yytext);
      g_free (filename);
    }

  return type;
}

static void
warn_if_cond_has_gi_scanner (GISourceScanner *scanner,
                             const gchar *text)
{
  /* Some other conditional that is not __GI_SCANNER__ */
  if (strstr (text, "__GI_SCANNER__"))
    {
      gchar *filename = g_file_get_path (scanner->current_file);
      fprintf (stderr, "%s:%d: the __GI_SCANNER__ constant should only be used with simple #ifdef or #endif: %s",
               filename, lineno, text);
      g_free (filename);
    }
}

static void
toggle_conditional (GISourceScanner *scanner)
{
  switch (pop_conditional (scanner))
    {
    case FOR_GI_SCANNER:
      push_conditional (scanner, NOT_GI_SCANNER);
      break;
    case NOT_GI_SCANNER:
      push_conditional (scanner, FOR_GI_SCANNER);
      break;
    case 0:
      break;
    default:
      push_conditional (scanner, IRRELEVANT);
      break;
    }
}


/* Line 371 of yacc.c  */
#line 250 "scannerparser.c"

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
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_SCANNERPARSER_H_INCLUDED
# define YY_YY_SCANNERPARSER_H_INCLUDED
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
     IDENTIFIER = 258,
     TYPEDEF_NAME = 259,
     INTEGER = 260,
     FLOATING = 261,
     BOOLEAN = 262,
     CHARACTER = 263,
     STRING = 264,
     INTL_CONST = 265,
     INTUL_CONST = 266,
     ELLIPSIS = 267,
     ADDEQ = 268,
     SUBEQ = 269,
     MULEQ = 270,
     DIVEQ = 271,
     MODEQ = 272,
     XOREQ = 273,
     ANDEQ = 274,
     OREQ = 275,
     SL = 276,
     SR = 277,
     SLEQ = 278,
     SREQ = 279,
     EQ = 280,
     NOTEQ = 281,
     LTEQ = 282,
     GTEQ = 283,
     ANDAND = 284,
     OROR = 285,
     PLUSPLUS = 286,
     MINUSMINUS = 287,
     ARROW = 288,
     AUTO = 289,
     BOOL = 290,
     BREAK = 291,
     CASE = 292,
     CHAR = 293,
     CONST = 294,
     CONTINUE = 295,
     DEFAULT = 296,
     DO = 297,
     DOUBLE = 298,
     ELSE = 299,
     ENUM = 300,
     EXTENSION = 301,
     EXTERN = 302,
     FLOAT = 303,
     FOR = 304,
     GOTO = 305,
     IF = 306,
     INLINE = 307,
     INT = 308,
     LONG = 309,
     REGISTER = 310,
     RESTRICT = 311,
     RETURN = 312,
     SHORT = 313,
     SIGNED = 314,
     SIZEOF = 315,
     STATIC = 316,
     STRUCT = 317,
     SWITCH = 318,
     TYPEDEF = 319,
     UNION = 320,
     UNSIGNED = 321,
     VOID = 322,
     VOLATILE = 323,
     WHILE = 324,
     FUNCTION_MACRO = 325,
     OBJECT_MACRO = 326,
     IFDEF_GI_SCANNER = 327,
     IFNDEF_GI_SCANNER = 328,
     IFDEF_COND = 329,
     IFNDEF_COND = 330,
     IF_COND = 331,
     ELIF_COND = 332,
     ELSE_COND = 333,
     ENDIF_COND = 334
   };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define TYPEDEF_NAME 259
#define INTEGER 260
#define FLOATING 261
#define BOOLEAN 262
#define CHARACTER 263
#define STRING 264
#define INTL_CONST 265
#define INTUL_CONST 266
#define ELLIPSIS 267
#define ADDEQ 268
#define SUBEQ 269
#define MULEQ 270
#define DIVEQ 271
#define MODEQ 272
#define XOREQ 273
#define ANDEQ 274
#define OREQ 275
#define SL 276
#define SR 277
#define SLEQ 278
#define SREQ 279
#define EQ 280
#define NOTEQ 281
#define LTEQ 282
#define GTEQ 283
#define ANDAND 284
#define OROR 285
#define PLUSPLUS 286
#define MINUSMINUS 287
#define ARROW 288
#define AUTO 289
#define BOOL 290
#define BREAK 291
#define CASE 292
#define CHAR 293
#define CONST 294
#define CONTINUE 295
#define DEFAULT 296
#define DO 297
#define DOUBLE 298
#define ELSE 299
#define ENUM 300
#define EXTENSION 301
#define EXTERN 302
#define FLOAT 303
#define FOR 304
#define GOTO 305
#define IF 306
#define INLINE 307
#define INT 308
#define LONG 309
#define REGISTER 310
#define RESTRICT 311
#define RETURN 312
#define SHORT 313
#define SIGNED 314
#define SIZEOF 315
#define STATIC 316
#define STRUCT 317
#define SWITCH 318
#define TYPEDEF 319
#define UNION 320
#define UNSIGNED 321
#define VOID 322
#define VOLATILE 323
#define WHILE 324
#define FUNCTION_MACRO 325
#define OBJECT_MACRO 326
#define IFDEF_GI_SCANNER 327
#define IFNDEF_GI_SCANNER 328
#define IFDEF_COND 329
#define IFNDEF_COND 330
#define IF_COND 331
#define ELIF_COND 332
#define ELSE_COND 333
#define ENDIF_COND 334



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 212 "giscanner/scannerparser.y"

  char *str;
  GList *list;
  GISourceSymbol *symbol;
  GISourceType *ctype;
  StorageClassSpecifier storage_class_specifier;
  TypeQualifier type_qualifier;
  FunctionSpecifier function_specifier;
  UnaryOperator unary_operator;


/* Line 387 of yacc.c  */
#line 463 "scannerparser.c"
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
int yyparse (GISourceScanner* scanner);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_SCANNERPARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 491 "scannerparser.c"

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
#define YYFINAL  76
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2799

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  104
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  77
/* YYNRULES -- Number of rules.  */
#define YYNRULES  256
/* YYNRULES -- Number of states.  */
#define YYNSTATES  426

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   334

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    93,     2,     2,     2,    95,    88,     2,
      80,    81,    89,    90,    87,    91,    86,    94,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   101,   103,
      96,   102,    97,   100,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    84,     2,    85,    98,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    82,    99,    83,    92,     2,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    15,    19,
      26,    28,    31,    33,    35,    37,    39,    44,    49,    53,
      57,    61,    64,    67,    69,    73,    75,    78,    81,    84,
      89,    94,    97,   102,   104,   106,   108,   110,   112,   114,
     116,   121,   123,   127,   131,   135,   137,   141,   145,   147,
     151,   155,   157,   161,   165,   169,   173,   175,   179,   183,
     185,   189,   191,   195,   197,   201,   203,   207,   209,   213,
     215,   221,   223,   227,   229,   231,   233,   235,   237,   239,
     241,   243,   245,   247,   249,   251,   255,   258,   260,   264,
     267,   270,   272,   275,   277,   280,   282,   285,   287,   289,
     293,   295,   299,   301,   303,   305,   307,   309,   311,   313,
     315,   317,   319,   321,   323,   325,   327,   329,   331,   333,
     335,   341,   346,   349,   351,   353,   355,   358,   362,   365,
     367,   370,   372,   374,   378,   379,   381,   384,   388,   394,
     399,   406,   412,   415,   417,   418,   421,   425,   427,   431,
     433,   435,   437,   439,   441,   444,   446,   448,   452,   457,
     461,   466,   471,   475,   478,   480,   484,   487,   489,   492,
     494,   498,   501,   504,   506,   508,   510,   514,   516,   519,
     521,   523,   526,   530,   533,   537,   541,   546,   549,   553,
     557,   562,   564,   566,   570,   575,   577,   581,   583,   585,
     587,   589,   591,   593,   597,   602,   606,   609,   613,   615,
     618,   620,   622,   624,   627,   633,   641,   647,   653,   661,
     668,   676,   684,   693,   701,   710,   719,   729,   733,   736,
     739,   742,   746,   748,   751,   753,   755,   757,   762,   766,
     768,   771,   773,   775,   780,   783,   785,   787,   789,   791,
     793,   795,   797,   799,   801,   803,   805
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     171,     0,    -1,   107,    -1,     5,    -1,     7,    -1,     8,
      -1,     6,    -1,   106,    -1,    80,   127,    81,    -1,    46,
      80,    82,   165,    83,    81,    -1,     9,    -1,   106,     9,
      -1,     3,    -1,   107,    -1,   159,    -1,   105,    -1,   109,
      84,   127,    85,    -1,   109,    80,   110,    81,    -1,   109,
      80,    81,    -1,   109,    86,   108,    -1,   109,    33,   108,
      -1,   109,    31,    -1,   109,    32,    -1,   125,    -1,   110,
      87,   125,    -1,   109,    -1,    31,   111,    -1,    32,   111,
      -1,   112,   113,    -1,    10,    80,   111,    81,    -1,    11,
      80,   111,    81,    -1,    60,   111,    -1,    60,    80,   156,
      81,    -1,    88,    -1,    89,    -1,    90,    -1,    91,    -1,
      92,    -1,    93,    -1,   111,    -1,    80,   156,    81,   113,
      -1,   113,    -1,   114,    89,   113,    -1,   114,    94,   113,
      -1,   114,    95,   113,    -1,   114,    -1,   115,    90,   114,
      -1,   115,    91,   114,    -1,   115,    -1,   116,    21,   115,
      -1,   116,    22,   115,    -1,   116,    -1,   117,    96,   116,
      -1,   117,    97,   116,    -1,   117,    27,   116,    -1,   117,
      28,   116,    -1,   117,    -1,   118,    25,   117,    -1,   118,
      26,   117,    -1,   118,    -1,   119,    88,   118,    -1,   119,
      -1,   120,    98,   119,    -1,   120,    -1,   121,    99,   120,
      -1,   121,    -1,   122,    29,   121,    -1,   122,    -1,   123,
      30,   122,    -1,   123,    -1,   123,   100,   127,   101,   127,
      -1,   124,    -1,   111,   126,   125,    -1,   102,    -1,    15,
      -1,    16,    -1,    17,    -1,    13,    -1,    14,    -1,    23,
      -1,    24,    -1,    19,    -1,    18,    -1,    20,    -1,   125,
      -1,   127,    87,   125,    -1,    46,   127,    -1,   124,    -1,
     130,   131,   103,    -1,   130,   103,    -1,   133,   130,    -1,
     133,    -1,   134,   130,    -1,   134,    -1,   147,   130,    -1,
     147,    -1,   148,   130,    -1,   148,    -1,   132,    -1,   131,
      87,   132,    -1,   149,    -1,   149,   102,   160,    -1,    64,
      -1,    47,    -1,    61,    -1,    34,    -1,    55,    -1,    67,
      -1,    38,    -1,    58,    -1,    53,    -1,    54,    -1,    48,
      -1,    43,    -1,    59,    -1,    66,    -1,    35,    -1,   135,
      -1,   142,    -1,   159,    -1,   136,   108,    82,   137,    83,
      -1,   136,    82,   137,    83,    -1,   136,   108,    -1,    62,
      -1,    65,    -1,   138,    -1,   137,   138,    -1,   139,   140,
     103,    -1,   134,   139,    -1,   134,    -1,   147,   139,    -1,
     147,    -1,   141,    -1,   140,    87,   141,    -1,    -1,   149,
      -1,   101,   128,    -1,   149,   101,   128,    -1,   143,   108,
      82,   144,    83,    -1,   143,    82,   144,    83,    -1,   143,
     108,    82,   144,    87,    83,    -1,   143,    82,   144,    87,
      83,    -1,   143,   108,    -1,    45,    -1,    -1,   145,   146,
      -1,   144,    87,   146,    -1,   107,    -1,   107,   102,   128,
      -1,    39,    -1,    56,    -1,    46,    -1,    68,    -1,    52,
      -1,   151,   150,    -1,   150,    -1,   107,    -1,    80,   149,
      81,    -1,   150,    84,   125,    85,    -1,   150,    84,    85,
      -1,   150,    80,   153,    81,    -1,   150,    80,   155,    81,
      -1,   150,    80,    81,    -1,    89,   152,    -1,    89,    -1,
      89,   152,   151,    -1,    89,   151,    -1,   147,    -1,   152,
     147,    -1,   154,    -1,   153,    87,   154,    -1,   130,   149,
      -1,   130,   157,    -1,   130,    -1,    12,    -1,   107,    -1,
     155,    87,   107,    -1,   139,    -1,   139,   157,    -1,   151,
      -1,   158,    -1,   151,   158,    -1,    80,   157,    81,    -1,
      84,    85,    -1,    84,   125,    85,    -1,   158,    84,    85,
      -1,   158,    84,   125,    85,    -1,    80,    81,    -1,    80,
     153,    81,    -1,   158,    80,    81,    -1,   158,    80,   153,
      81,    -1,     4,    -1,   125,    -1,    82,   161,    83,    -1,
      82,   161,    87,    83,    -1,   160,    -1,   161,    87,   160,
      -1,   163,    -1,   164,    -1,   167,    -1,   168,    -1,   169,
      -1,   170,    -1,   108,   101,   162,    -1,    37,   128,   101,
     162,    -1,    41,   101,   162,    -1,    82,    83,    -1,    82,
     165,    83,    -1,   166,    -1,   165,   166,    -1,   129,    -1,
     162,    -1,   103,    -1,   127,   103,    -1,    51,    80,   127,
      81,   162,    -1,    51,    80,   127,    81,   162,    44,   162,
      -1,    63,    80,   127,    81,   162,    -1,    69,    80,   127,
      81,   162,    -1,    42,   162,    69,    80,   127,    81,   103,
      -1,    49,    80,   103,   103,    81,   162,    -1,    49,    80,
     127,   103,   103,    81,   162,    -1,    49,    80,   103,   127,
     103,    81,   162,    -1,    49,    80,   127,   103,   127,   103,
      81,   162,    -1,    49,    80,   103,   103,   127,    81,   162,
      -1,    49,    80,   127,   103,   103,   127,    81,   162,    -1,
      49,    80,   103,   127,   103,   127,    81,   162,    -1,    49,
      80,   127,   103,   127,   103,   127,    81,   162,    -1,    50,
     108,   103,    -1,    40,   103,    -1,    36,   103,    -1,    57,
     103,    -1,    57,   127,   103,    -1,   172,    -1,   171,   172,
      -1,   173,    -1,   129,    -1,   180,    -1,   130,   149,   174,
     164,    -1,   130,   149,   164,    -1,   129,    -1,   174,   129,
      -1,    70,    -1,    71,    -1,   175,    80,   155,    81,    -1,
     176,   128,    -1,    72,    -1,    73,    -1,    74,    -1,    75,
      -1,    76,    -1,    77,    -1,    78,    -1,    79,    -1,   177,
      -1,   178,    -1,   179,    -1,     1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   304,   304,   313,   329,   335,   341,   348,   349,   353,
     361,   376,   390,   397,   398,   402,   403,   407,   411,   415,
     419,   423,   427,   434,   435,   439,   440,   444,   448,   471,
     478,   485,   489,   497,   501,   505,   509,   513,   517,   524,
     525,   537,   538,   544,   552,   563,   564,   570,   579,   580,
     592,   601,   602,   608,   614,   620,   629,   630,   636,   645,
     646,   655,   656,   665,   666,   675,   676,   687,   688,   699,
     700,   707,   708,   715,   716,   717,   718,   719,   720,   721,
     722,   723,   724,   725,   729,   730,   731,   738,   744,   762,
     769,   774,   779,   792,   793,   798,   803,   808,   816,   820,
     827,   828,   832,   836,   840,   844,   848,   855,   859,   863,
     867,   871,   875,   879,   883,   887,   891,   895,   896,   897,
     905,   925,   930,   938,   943,   951,   952,   959,   979,   984,
     985,   990,   998,  1002,  1010,  1013,  1014,  1018,  1029,  1036,
    1043,  1050,  1057,  1064,  1073,  1073,  1082,  1090,  1098,  1110,
    1114,  1118,  1122,  1129,  1136,  1141,  1145,  1150,  1154,  1159,
    1164,  1174,  1181,  1190,  1195,  1199,  1210,  1223,  1224,  1231,
    1235,  1242,  1247,  1252,  1257,  1264,  1270,  1279,  1280,  1284,
    1289,  1290,  1298,  1302,  1307,  1312,  1317,  1322,  1328,  1338,
    1344,  1357,  1364,  1365,  1366,  1370,  1371,  1377,  1378,  1379,
    1380,  1381,  1382,  1386,  1387,  1388,  1392,  1393,  1397,  1398,
    1402,  1403,  1407,  1408,  1412,  1413,  1414,  1418,  1419,  1420,
    1421,  1422,  1423,  1424,  1425,  1426,  1427,  1431,  1432,  1433,
    1434,  1435,  1441,  1442,  1446,  1447,  1448,  1452,  1453,  1457,
    1458,  1464,  1471,  1478,  1482,  1493,  1498,  1503,  1508,  1513,
    1518,  1525,  1530,  1538,  1539,  1540,  1541
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "\"identifier\"", "\"typedef-name\"",
  "INTEGER", "FLOATING", "BOOLEAN", "CHARACTER", "STRING", "INTL_CONST",
  "INTUL_CONST", "ELLIPSIS", "ADDEQ", "SUBEQ", "MULEQ", "DIVEQ", "MODEQ",
  "XOREQ", "ANDEQ", "OREQ", "SL", "SR", "SLEQ", "SREQ", "EQ", "NOTEQ",
  "LTEQ", "GTEQ", "ANDAND", "OROR", "PLUSPLUS", "MINUSMINUS", "ARROW",
  "AUTO", "BOOL", "BREAK", "CASE", "CHAR", "CONST", "CONTINUE", "DEFAULT",
  "DO", "DOUBLE", "ELSE", "ENUM", "EXTENSION", "EXTERN", "FLOAT", "FOR",
  "GOTO", "IF", "INLINE", "INT", "LONG", "REGISTER", "RESTRICT", "RETURN",
  "SHORT", "SIGNED", "SIZEOF", "STATIC", "STRUCT", "SWITCH", "TYPEDEF",
  "UNION", "UNSIGNED", "VOID", "VOLATILE", "WHILE", "FUNCTION_MACRO",
  "OBJECT_MACRO", "IFDEF_GI_SCANNER", "IFNDEF_GI_SCANNER", "IFDEF_COND",
  "IFNDEF_COND", "IF_COND", "ELIF_COND", "ELSE_COND", "ENDIF_COND", "'('",
  "')'", "'{'", "'}'", "'['", "']'", "'.'", "','", "'&'", "'*'", "'+'",
  "'-'", "'~'", "'!'", "'/'", "'%'", "'<'", "'>'", "'^'", "'|'", "'?'",
  "':'", "'='", "';'", "$accept", "primary_expression", "strings",
  "identifier", "identifier_or_typedef_name", "postfix_expression",
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
  "struct_declarator", "enum_specifier", "enum_keyword", "enumerator_list",
  "$@1", "enumerator", "type_qualifier", "function_specifier",
  "declarator", "direct_declarator", "pointer", "type_qualifier_list",
  "parameter_list", "parameter_declaration", "identifier_list",
  "type_name", "abstract_declarator", "direct_abstract_declarator",
  "typedef_name", "initializer", "initializer_list", "statement",
  "labeled_statement", "compound_statement", "block_item_list",
  "block_item", "expression_statement", "selection_statement",
  "iteration_statement", "jump_statement", "translation_unit",
  "external_declaration", "function_definition", "declaration_list",
  "function_macro", "object_macro", "function_macro_define",
  "object_macro_define", "preproc_conditional", "macro", YY_NULL
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
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
      40,    41,   123,   125,    91,    93,    46,    44,    38,    42,
      43,    45,   126,    33,    47,    37,    60,    62,    94,   124,
      63,    58,    61,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   104,   105,   105,   105,   105,   105,   105,   105,   105,
     106,   106,   107,   108,   108,   109,   109,   109,   109,   109,
     109,   109,   109,   110,   110,   111,   111,   111,   111,   111,
     111,   111,   111,   112,   112,   112,   112,   112,   112,   113,
     113,   114,   114,   114,   114,   115,   115,   115,   116,   116,
     116,   117,   117,   117,   117,   117,   118,   118,   118,   119,
     119,   120,   120,   121,   121,   122,   122,   123,   123,   124,
     124,   125,   125,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   127,   127,   127,   128,   129,   129,
     130,   130,   130,   130,   130,   130,   130,   130,   131,   131,
     132,   132,   133,   133,   133,   133,   133,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     135,   135,   135,   136,   136,   137,   137,   138,   139,   139,
     139,   139,   140,   140,   141,   141,   141,   141,   142,   142,
     142,   142,   142,   143,   145,   144,   144,   146,   146,   147,
     147,   147,   147,   148,   149,   149,   150,   150,   150,   150,
     150,   150,   150,   151,   151,   151,   151,   152,   152,   153,
     153,   154,   154,   154,   154,   155,   155,   156,   156,   157,
     157,   157,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   159,   160,   160,   160,   161,   161,   162,   162,   162,
     162,   162,   162,   163,   163,   163,   164,   164,   165,   165,
     166,   166,   167,   167,   168,   168,   168,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   170,   170,   170,
     170,   170,   171,   171,   172,   172,   172,   173,   173,   174,
     174,   175,   176,   177,   178,   179,   179,   179,   179,   179,
     179,   179,   179,   180,   180,   180,   180
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     3,     6,
       1,     2,     1,     1,     1,     1,     4,     4,     3,     3,
       3,     2,     2,     1,     3,     1,     2,     2,     2,     4,
       4,     2,     4,     1,     1,     1,     1,     1,     1,     1,
       4,     1,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       5,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     2,     1,     3,     2,
       2,     1,     2,     1,     2,     1,     2,     1,     1,     3,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       5,     4,     2,     1,     1,     1,     2,     3,     2,     1,
       2,     1,     1,     3,     0,     1,     2,     3,     5,     4,
       6,     5,     2,     1,     0,     2,     3,     1,     3,     1,
       1,     1,     1,     1,     2,     1,     1,     3,     4,     3,
       4,     4,     3,     2,     1,     3,     2,     1,     2,     1,
       3,     2,     2,     1,     1,     1,     3,     1,     2,     1,
       1,     2,     3,     2,     3,     3,     4,     2,     3,     3,
       4,     1,     1,     3,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     3,     4,     3,     2,     3,     1,     2,
       1,     1,     1,     2,     5,     7,     5,     5,     7,     6,
       7,     7,     8,     7,     8,     8,     9,     3,     2,     2,
       2,     3,     1,     2,     1,     1,     1,     4,     3,     1,
       2,     1,     1,     4,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   256,   191,   105,   116,   108,   149,   113,   143,   151,
     103,   112,   153,   110,   111,   106,   150,   109,   114,   104,
     123,   102,   124,   115,   107,   152,   241,   242,   245,   246,
     247,   248,   249,   250,   251,   252,   235,     0,    91,    93,
     117,     0,   118,     0,    95,    97,   119,     0,   232,   234,
       0,     0,   253,   254,   255,   236,    12,     0,   164,    89,
     156,     0,    98,   100,   155,     0,    90,    92,     0,    13,
     122,    14,   144,   142,    94,    96,     1,   233,     0,     3,
       6,     4,     5,    10,     0,     0,     0,     0,     0,     0,
       0,    33,    34,    35,    36,    37,    38,    15,     7,     2,
      25,    39,     0,    41,    45,    48,    51,    56,    59,    61,
      63,    65,    67,    69,    87,   244,     0,   167,   166,   163,
       0,    88,     0,     0,   239,     0,   238,     0,     0,     0,
     154,   129,     0,   125,   134,   131,     0,     0,     0,   144,
     175,     0,     0,     0,     0,    26,    27,     0,     0,    31,
     151,    39,    71,    84,     0,   177,     0,    11,    21,    22,
       0,     0,     0,     0,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   157,   168,   165,    99,   100,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     206,   212,     2,     0,     0,   210,   119,   211,   197,   198,
       0,   208,   199,   200,   201,   202,     0,   192,   101,   240,
     237,   174,   162,   173,     0,   169,     0,   159,     0,   128,
     121,   126,     0,     0,   132,   135,   130,     0,   139,     0,
     147,   145,     0,   243,     0,     0,     0,     0,     0,     0,
       0,    86,    77,    78,    74,    75,    76,    82,    81,    83,
      79,    80,    73,     0,     8,     0,     0,     0,   179,   178,
     180,     0,    20,    18,     0,    23,     0,    19,    42,    43,
      44,    46,    47,    49,    50,    54,    55,    52,    53,    57,
      58,    60,    62,    64,    66,    68,     0,   229,     0,   228,
       0,     0,     0,     0,     0,   230,     0,     0,     0,     0,
     213,   207,   209,   195,     0,     0,   171,   179,   172,   160,
       0,   161,   158,   136,   134,   127,     0,   120,   141,   146,
       0,   138,     0,   176,    29,    30,     0,    32,    72,    85,
     187,     0,     0,   183,     0,   181,     0,     0,    40,    17,
       0,    16,     0,     0,   205,     0,     0,     0,   227,     0,
     231,     0,     0,   203,   193,     0,   170,   133,   137,   148,
     140,     0,   188,   182,   184,   189,     0,   185,     0,    24,
      70,   204,     0,     0,     0,     0,     0,     0,     0,   194,
     196,     9,   190,   186,     0,     0,     0,     0,     0,     0,
     214,   216,   217,     0,   219,     0,     0,     0,     0,     0,
       0,     0,   218,   223,   221,     0,   220,     0,     0,     0,
     215,   225,   224,   222,     0,   226
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    97,    98,    99,   203,   100,   274,   151,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     152,   153,   263,   204,   115,   205,   125,    61,    62,    38,
      39,    40,    41,   132,   133,   134,   233,   234,    42,    43,
     137,   138,   329,    44,    45,   116,    64,    65,   119,   341,
     225,   141,   156,   342,   270,    46,   218,   314,   207,   208,
     209,   210,   211,   212,   213,   214,   215,    47,    48,    49,
     127,    50,    51,    52,    53,    54,    55
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -234
static const yytype_int16 yypact[] =
{
    2506,  -234,  -234,  -234,  -234,  -234,  -234,  -234,  -234,  -234,
    -234,  -234,  -234,  -234,  -234,  -234,  -234,  -234,  -234,  -234,
    -234,  -234,  -234,  -234,  -234,  -234,  -234,  -234,  -234,  -234,
    -234,  -234,  -234,  -234,  -234,  -234,  -234,    33,  2731,  2731,
    -234,    39,  -234,    46,  2731,  2731,  -234,  2373,  -234,  -234,
     -63,  1962,  -234,  -234,  -234,  -234,  -234,    35,   120,  -234,
    -234,   -48,  -234,  1134,   -20,    15,  -234,  -234,  1083,  -234,
     -55,  -234,  -234,   -45,  -234,  -234,  -234,  -234,    31,  -234,
    -234,  -234,  -234,  -234,    10,    34,  2025,  2025,    40,  2088,
    1266,  -234,  -234,  -234,  -234,  -234,  -234,  -234,    56,  -234,
     184,  -234,  1962,  -234,    80,   213,   279,    41,   282,    44,
      59,    69,   114,     3,  -234,  -234,    98,  -234,  -234,   120,
      35,  -234,   468,  1395,  -234,    33,  -234,  2620,  2583,  1458,
     -20,  1083,  2419,  -234,    45,  1083,  1083,    -1,    31,  -234,
    -234,    90,  2025,  2025,  2151,  -234,  -234,   110,  1266,  -234,
    2214,   571,  -234,  -234,   100,   109,   122,  -234,  -234,  -234,
     311,  1521,  2151,   311,  -234,  1962,  1962,  1962,  1962,  1962,
    1962,  1962,  1962,  1962,  1962,  1962,  1962,  1962,  1962,  1962,
    1962,  1962,  1962,  2151,  -234,  -234,  -234,  -234,   112,   153,
    1962,   156,   140,   819,   191,   311,   194,   884,   208,   211,
    -234,  -234,   193,   204,   -40,  -234,   218,  -234,  -234,  -234,
     569,  -234,  -234,  -234,  -234,  -234,  1395,  -234,  -234,  -234,
    -234,  -234,  -234,    64,   123,  -234,   125,  -234,   238,  -234,
    -234,  -234,  1962,   -29,  -234,   225,  -234,  2455,  -234,    16,
     228,  -234,   107,  -234,    31,   215,   250,  2214,   751,   253,
    1200,   249,  -234,  -234,  -234,  -234,  -234,  -234,  -234,  -234,
    -234,  -234,  -234,  1962,  -234,  1962,  2333,  1584,   121,  -234,
     199,  1962,  -234,  -234,   157,  -234,    22,  -234,  -234,  -234,
    -234,    80,    80,   213,   213,   279,   279,   279,   279,    41,
      41,   282,    44,    59,    69,   114,    30,  -234,   236,  -234,
     819,   269,   947,   237,  2151,  -234,   -28,  2151,  2151,   819,
    -234,  -234,  -234,  -234,   210,  2274,  -234,    12,  -234,  -234,
    2695,  -234,  -234,  -234,    45,  -234,  1962,  -234,  -234,  -234,
    1962,  -234,    23,  -234,  -234,  -234,   660,  -234,  -234,  -234,
    -234,   159,   258,  -234,   256,   199,  2658,  1647,  -234,  -234,
    1962,  -234,  2151,   819,  -234,   264,  1010,   -25,  -234,   161,
    -234,   164,   168,  -234,  -234,  1332,  -234,  -234,  -234,  -234,
    -234,   265,  -234,  -234,  -234,  -234,   179,  -234,   260,  -234,
     249,  -234,  2151,  1710,    58,  1073,   819,   819,   819,  -234,
    -234,  -234,  -234,  -234,   180,   819,   188,  1773,  1836,    77,
     310,  -234,  -234,   252,  -234,   819,   819,   195,   819,   203,
    1899,   819,  -234,  -234,  -234,   819,  -234,   819,   819,   205,
    -234,  -234,  -234,  -234,   819,  -234
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -234,  -234,  -234,   -37,   -33,  -234,  -234,    53,  -234,   -86,
     149,   150,   138,   152,   178,   182,   177,   181,   183,  -234,
     -49,  -100,  -234,   -50,  -176,    24,     7,  -234,   239,  -234,
     -59,  -234,  -234,   227,  -119,   -78,  -234,    42,  -234,  -234,
     231,  -234,   226,   333,  -234,   -15,   -64,   -53,  -234,  -107,
      47,   244,   234,  -130,  -233,   -11,  -205,  -234,    43,  -234,
     -19,   137,  -207,  -234,  -234,  -234,  -234,  -234,   326,  -234,
    -234,  -234,  -234,  -234,  -234,  -234,  -234
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -15
static const yytype_int16 yytable[] =
{
      60,   130,   114,   312,    69,   118,    69,    37,    70,   131,
      73,   313,   155,   231,   298,    56,   164,    78,    56,    56,
      60,   224,    63,   217,    36,   269,    56,   136,    60,   228,
      71,   131,    71,   182,    56,   345,    56,   139,    56,   120,
     154,   140,    56,     2,   126,    66,    67,   265,    56,    56,
       2,    74,    75,   229,    37,   121,   323,   236,   324,   265,
     128,   275,   265,   310,   129,   157,   186,    56,   172,   173,
     155,    36,   131,   131,   325,   360,   131,   131,   385,   278,
     279,   280,   238,    60,   345,   202,   239,   124,    60,   131,
     142,   140,   315,   318,   154,    57,   267,    60,   154,   328,
     251,   240,   268,   183,   101,   188,   370,   351,   220,   265,
     188,   206,   276,    57,   143,    57,   217,   265,   231,   235,
     147,    68,    58,    69,    58,    57,    69,   272,    72,   312,
     277,   352,   178,   296,    58,   223,    59,   174,   175,   145,
     146,   114,   149,   181,   315,   265,   232,   306,   267,    71,
     368,   219,    71,    58,   369,   101,   202,   179,    69,     6,
     390,   397,   303,   338,   265,   339,     9,   344,   180,   165,
     317,   243,   155,   202,   166,   167,    16,   244,   131,   184,
     410,   264,    71,   114,    71,   348,    60,   265,    25,   266,
     331,   131,   248,   267,   332,   245,   246,   251,    58,   206,
     154,   266,   240,   271,   319,   267,   321,   333,   316,    58,
     320,   202,   244,   268,   123,   158,   159,   160,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   301,   206,   349,   376,
     372,   300,   386,   101,   350,   387,   320,   378,   265,   388,
     379,   265,   357,   130,   359,   265,   297,   361,   362,   299,
     392,   403,   317,   202,   161,   217,   320,   265,   162,   405,
     163,   302,   202,   223,   304,   265,   415,   114,    60,   346,
      60,   114,   265,   347,   417,   101,   424,    60,   307,    71,
     265,   308,   265,   364,   -13,   240,   334,   365,    71,   202,
     170,   171,   380,   168,   169,   309,   384,   176,   177,   235,
     285,   286,   287,   288,    56,     2,   202,   281,   282,   -14,
     283,   284,   223,   322,   101,   206,   326,   223,   289,   290,
     330,   335,   394,   396,   337,   399,   265,   353,   355,   373,
     358,   374,    71,   354,   382,   393,   391,   407,   409,   202,
     202,   202,   363,   223,   411,   412,   291,   293,   202,   187,
     419,   292,   294,   237,   241,   295,   367,   366,   202,   202,
     242,   202,   226,    77,   202,    71,    71,    71,   202,   101,
     202,   202,   249,   101,    71,   336,     0,   202,     0,     0,
       0,   117,     0,     0,    71,    71,   381,    71,     0,     0,
      71,   135,     0,     0,    71,     0,    71,    71,     0,     0,
       0,     0,     0,    71,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   135,     0,     0,     0,     0,     0,   400,
     401,   402,     0,     0,     0,     0,     0,     0,   404,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   413,   414,
       0,   416,   185,     0,   420,     0,     0,     0,   421,     0,
     422,   423,     0,     0,   135,   135,     0,   425,   135,   135,
       0,    56,     2,    79,    80,    81,    82,    83,    84,    85,
       0,   135,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    86,
      87,     0,     3,     4,   189,   190,     5,     6,   191,   192,
     193,     7,     0,     8,   150,    10,    11,   194,   195,   196,
      12,    13,    14,    15,    16,   197,    17,    18,    89,    19,
      20,   198,    21,    22,    23,    24,    25,   199,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    90,     0,
     122,   200,     0,     0,     0,     0,    91,    92,    93,    94,
      95,    96,     0,     0,     0,     0,     0,     0,     0,     0,
     135,   201,    56,     2,    79,    80,    81,    82,    83,    84,
      85,     0,     0,   135,   252,   253,   254,   255,   256,   257,
     258,   259,     0,     0,   260,   261,     0,     0,     0,     0,
      86,    87,     0,     3,     4,   189,   190,     5,     6,   191,
     192,   193,     7,     0,     8,   150,    10,    11,   194,   195,
     196,    12,    13,    14,    15,    16,   197,    17,    18,    89,
      19,    20,   198,    21,    22,    23,    24,    25,   199,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    90,
       0,   122,   311,     0,     0,     0,     0,    91,    92,    93,
      94,    95,    96,    56,     2,    79,    80,    81,    82,    83,
      84,    85,   201,   262,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    86,    87,     0,     3,     4,   189,   190,     5,     6,
     191,   192,   193,     7,     0,     8,   150,    10,    11,   194,
     195,   196,    12,    13,    14,    15,    16,   197,    17,    18,
      89,    19,    20,   198,    21,    22,    23,    24,    25,   199,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      90,     0,   122,   371,     0,     0,     0,     0,    91,    92,
      93,    94,    95,    96,    56,     2,    79,    80,    81,    82,
      83,    84,    85,   201,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    86,    87,     0,     3,     4,   189,   190,     5,
       6,   191,   192,   193,     7,     0,     8,   150,    10,    11,
     194,   195,   196,    12,    13,    14,    15,    16,   197,    17,
      18,    89,    19,    20,   198,    21,    22,    23,    24,    25,
     199,     0,    56,     2,    79,    80,    81,    82,    83,    84,
      85,    90,     0,   122,     0,     0,     0,     0,     0,    91,
      92,    93,    94,    95,    96,     0,     0,     0,     0,     0,
      86,    87,     0,     0,   201,   189,   190,     0,     0,   191,
     192,   193,     0,     0,     0,   247,     0,     0,   194,   195,
     196,     0,     0,     0,     0,     0,   197,     0,     0,    89,
       0,     0,   198,     0,     0,     0,     0,    56,   199,    79,
      80,    81,    82,    83,    84,    85,     0,     0,     0,    90,
       0,   122,     0,     0,     0,     0,     0,    91,    92,    93,
      94,    95,    96,     0,     0,    86,    87,     0,     0,     0,
       0,     0,   201,     0,     0,     0,     0,     0,     0,     0,
     247,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    89,     0,     0,     0,     0,     0,
      56,     0,    79,    80,    81,    82,    83,    84,    85,     0,
       0,     0,     0,     0,    90,     0,     0,     0,     0,     0,
       0,     0,    91,    92,    93,    94,    95,    96,    86,    87,
       0,     0,     0,     0,     0,     0,     0,   305,     0,     0,
       0,     0,     0,   247,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    89,     0,     0,
       0,     0,     0,    56,     0,    79,    80,    81,    82,    83,
      84,    85,     0,     0,     0,     0,     0,    90,     0,     0,
       0,     0,     0,     0,     0,    91,    92,    93,    94,    95,
      96,    86,    87,     0,     0,     0,     0,     0,     0,     0,
     356,     0,     0,     0,     0,     0,   247,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      89,     0,     0,     0,     0,     0,    56,     0,    79,    80,
      81,    82,    83,    84,    85,     0,     0,     2,     0,     0,
      90,     0,     0,     0,     0,     0,     0,     0,    91,    92,
      93,    94,    95,    96,    86,    87,     0,     0,     0,     0,
       0,     0,     0,   383,     0,     0,     0,     0,     4,   247,
       0,     5,     6,     0,     0,     0,     7,     0,     8,     9,
       0,    11,     0,    89,     0,     0,    13,    14,     2,    16,
       0,    17,    18,     0,     0,    20,     0,     0,    22,    23,
      24,    25,     0,    90,     0,     0,     0,     0,     0,     0,
       0,    91,    92,    93,    94,    95,    96,     0,     3,     4,
       0,     0,     5,     6,     0,     0,   398,     7,     0,     8,
       9,    10,    11,     0,     0,     0,    12,    13,    14,    15,
      16,     0,    17,    18,     0,    19,    20,     0,    21,    22,
      23,    24,    25,    56,     2,    79,    80,    81,    82,    83,
      84,    85,     0,     0,     0,     0,   122,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    86,    87,     0,     0,     4,   123,     0,     5,     6,
       0,     0,     0,     7,     0,     8,   150,     0,    11,     0,
       0,     0,     0,    13,    14,     0,    16,     0,    17,    18,
      89,     0,    20,     0,     0,    22,    23,    24,    25,    56,
       2,    79,    80,    81,    82,    83,    84,    85,     0,     0,
      90,     0,   248,     0,     0,     0,     0,     0,    91,    92,
      93,    94,    95,    96,     0,     0,     0,    86,    87,     0,
       0,     4,     0,     0,     5,     6,     0,     0,     0,     7,
       0,     8,   150,     0,    11,     0,     0,     0,     0,    13,
      14,     0,    16,     0,    17,    18,    89,     0,    20,     0,
       0,    22,    23,    24,    25,    56,     0,    79,    80,    81,
      82,    83,    84,    85,     0,     0,    90,     0,     0,     0,
       0,     0,     0,     0,    91,    92,    93,    94,    95,    96,
       0,     0,     0,    86,    87,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    88,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    89,     0,     0,     0,     0,     0,    56,     0,
      79,    80,    81,    82,    83,    84,    85,     0,     0,     0,
       0,     0,    90,     0,   216,   389,     0,     0,     0,     0,
      91,    92,    93,    94,    95,    96,    86,    87,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    88,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    89,     0,     0,     0,     0,
       0,    56,     0,    79,    80,    81,    82,    83,    84,    85,
       0,     0,     0,     0,     0,    90,     0,   216,     0,     0,
       0,     0,     0,    91,    92,    93,    94,    95,    96,    86,
      87,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    88,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    89,     0,
       0,     0,     0,     0,    56,     0,    79,    80,    81,    82,
      83,    84,    85,     0,     0,     0,     0,     0,    90,     0,
       0,     0,     0,   227,     0,     0,    91,    92,    93,    94,
      95,    96,    86,    87,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    88,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    89,     0,     0,     0,     0,     0,    56,     0,    79,
      80,    81,    82,    83,    84,    85,     0,     0,     0,     0,
       0,    90,   273,     0,     0,     0,     0,     0,     0,    91,
      92,    93,    94,    95,    96,    86,    87,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      88,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    89,     0,     0,     0,     0,     0,
      56,     0,    79,    80,    81,    82,    83,    84,    85,     0,
       0,     0,     0,     0,    90,     0,     0,     0,     0,   343,
       0,     0,    91,    92,    93,    94,    95,    96,    86,    87,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    88,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    89,     0,     0,
       0,     0,     0,    56,     0,    79,    80,    81,    82,    83,
      84,    85,     0,     0,     0,     0,     0,    90,     0,     0,
       0,     0,   377,     0,     0,    91,    92,    93,    94,    95,
      96,    86,    87,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   247,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      89,     0,     0,     0,     0,     0,    56,     0,    79,    80,
      81,    82,    83,    84,    85,     0,     0,     0,     0,     0,
      90,   395,     0,     0,     0,     0,     0,     0,    91,    92,
      93,    94,    95,    96,    86,    87,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   247,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    89,     0,     0,     0,     0,     0,    56,
       0,    79,    80,    81,    82,    83,    84,    85,     0,     0,
       0,     0,     0,    90,   406,     0,     0,     0,     0,     0,
       0,    91,    92,    93,    94,    95,    96,    86,    87,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   247,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    89,     0,     0,     0,
       0,     0,    56,     0,    79,    80,    81,    82,    83,    84,
      85,     0,     0,     0,     0,     0,    90,   408,     0,     0,
       0,     0,     0,     0,    91,    92,    93,    94,    95,    96,
      86,    87,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   247,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    89,
       0,     0,     0,     0,     0,    56,     0,    79,    80,    81,
      82,    83,    84,    85,     0,     0,     0,     0,     0,    90,
     418,     0,     0,     0,     0,     0,     0,    91,    92,    93,
      94,    95,    96,    86,    87,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    88,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    89,     0,     0,     0,     0,     0,    56,     0,
      79,    80,    81,    82,    83,    84,    85,     0,     0,     0,
       0,     0,    90,     0,     0,     0,     0,     0,     0,     0,
      91,    92,    93,    94,    95,    96,    86,    87,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    88,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    89,     0,     0,     0,     0,
       0,    56,     0,    79,    80,    81,    82,    83,    84,    85,
       0,     0,     0,     0,     0,   144,     0,     0,     0,     0,
       0,     0,     0,    91,    92,    93,    94,    95,    96,    86,
      87,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    88,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    89,     0,
       0,     0,     0,     0,    56,     0,    79,    80,    81,    82,
      83,    84,    85,     0,     0,     0,     0,     0,   148,     0,
       0,     0,     0,     0,     0,     0,    91,    92,    93,    94,
      95,    96,    86,    87,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   247,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    89,     0,     0,     0,     0,     0,    56,     0,    79,
      80,    81,    82,    83,    84,    85,     0,     0,     0,     0,
       0,    90,     0,     0,     0,     0,     0,     0,     0,    91,
      92,    93,    94,    95,    96,    86,    87,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     247,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    89,     0,     0,    56,     2,     0,
       0,     0,     0,     0,     0,     0,   221,     0,     0,     0,
       0,     0,     0,     0,   250,     0,     0,     0,     0,     0,
       0,     0,    91,    92,    93,    94,    95,    96,     3,     4,
       0,     0,     5,     6,     0,     0,     0,     7,     0,     8,
       9,    10,    11,     0,     0,     0,    12,    13,    14,    15,
      16,     0,    17,    18,     0,    19,    20,     2,    21,    22,
      23,    24,    25,     0,     0,   221,     0,     0,     0,     0,
       0,     0,     0,     0,   315,   340,     0,     0,   267,     0,
       0,     0,     0,    58,     0,     0,     0,     3,     4,     0,
       0,     5,     6,    76,     1,     0,     7,     2,     8,     9,
      10,    11,     0,     0,     0,    12,    13,    14,    15,    16,
       0,    17,    18,     0,    19,    20,     0,    21,    22,    23,
      24,    25,     0,     0,     0,     0,     0,     3,     4,     0,
       0,     5,     6,   266,   340,     0,     7,   267,     8,     9,
      10,    11,    58,     2,     0,    12,    13,    14,    15,    16,
       0,    17,    18,     0,    19,    20,     0,    21,    22,    23,
      24,    25,     0,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,     0,     4,     0,     0,     5,     6,     2,
       0,     0,     7,     0,     8,     9,     0,    11,     0,     0,
       0,     0,    13,    14,     0,    16,     0,    17,    18,     0,
       0,    20,     0,     0,    22,    23,    24,    25,     0,     0,
       4,     0,     0,     5,     6,     0,     0,     0,     7,     0,
       8,     9,   230,    11,     0,     0,     0,     1,    13,    14,
       2,    16,     0,    17,    18,     0,     0,    20,     0,     0,
      22,    23,    24,    25,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   327,     0,
       3,     4,     0,     0,     5,     6,     0,     0,     0,     7,
       0,     8,     9,    10,    11,     0,     0,     0,    12,    13,
      14,    15,    16,     0,    17,    18,     0,    19,    20,     0,
      21,    22,    23,    24,    25,     0,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    56,     2,     0,     0,
       0,     0,     0,     0,     0,   221,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     3,     4,     0,
       0,     5,     6,     0,     2,     0,     7,     0,     8,     9,
      10,    11,     0,     0,     0,    12,    13,    14,    15,    16,
       0,    17,    18,     0,    19,    20,     0,    21,    22,    23,
      24,    25,     0,     0,     3,     4,     0,     0,     5,     6,
       0,     0,     2,     7,   222,     8,     9,    10,    11,     0,
     221,     0,    12,    13,    14,    15,    16,     0,    17,    18,
       0,    19,    20,     0,    21,    22,    23,    24,    25,     0,
       0,     0,     3,     4,     0,     0,     5,     6,     0,     2,
       0,     7,   122,     8,     9,    10,    11,   221,     0,     0,
      12,    13,    14,    15,    16,     0,    17,    18,     0,    19,
      20,     0,    21,    22,    23,    24,    25,     0,     0,     3,
       4,     0,     0,     5,     6,     2,     0,     0,     7,   375,
       8,     9,    10,    11,     0,     0,     0,    12,    13,    14,
      15,    16,     0,    17,    18,     0,    19,    20,     0,    21,
      22,    23,    24,    25,     0,     3,     4,     0,     0,     5,
       6,     0,     0,     0,     7,     0,     8,     9,    10,    11,
       0,     0,     0,    12,    13,    14,    15,    16,     0,    17,
      18,     0,    19,    20,     0,    21,    22,    23,    24,    25
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-234)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      37,    65,    51,   210,    41,    58,    43,     0,    41,    68,
      43,   216,    90,   132,   190,     3,   102,    80,     3,     3,
      57,   128,    37,   123,     0,   155,     3,    82,    65,   129,
      41,    90,    43,    30,     3,   268,     3,    82,     3,    87,
      90,    78,     3,     4,    63,    38,    39,    87,     3,     3,
       4,    44,    45,   131,    47,   103,   232,   135,    87,    87,
      80,   161,    87,   103,    84,     9,   119,     3,    27,    28,
     148,    47,   131,   132,   103,   103,   135,   136,   103,   165,
     166,   167,    83,   120,   317,   122,    87,    63,   125,   148,
      80,   128,    80,   223,   144,    80,    84,   134,   148,    83,
     150,   138,   155,   100,    51,   120,    83,    85,   127,    87,
     125,   122,   162,    80,    80,    80,   216,    87,   237,   134,
      80,    82,    89,   160,    89,    80,   163,   160,    82,   336,
     163,   101,    88,   183,    89,   128,   103,    96,    97,    86,
      87,   190,    89,    29,    80,    87,   101,   197,    84,   160,
     326,   127,   163,    89,   330,   102,   193,    98,   195,    39,
     365,   103,   195,   263,    87,   265,    46,   267,    99,    89,
     223,    81,   250,   210,    94,    95,    56,    87,   237,    81,
     103,    81,   193,   232,   195,   271,   223,    87,    68,    80,
      83,   250,    82,    84,    87,   142,   143,   247,    89,   210,
     250,    80,   239,    81,    81,    84,    81,   244,   223,    89,
      87,   248,    87,   266,   102,    31,    32,    33,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   193,   248,    81,   346,
      81,   101,    81,   190,    87,    81,    87,   347,    87,    81,
     350,    87,   302,   317,   304,    87,   103,   307,   308,   103,
      81,    81,   315,   300,    80,   365,    87,    87,    84,    81,
      86,    80,   309,   266,    80,    87,    81,   326,   315,    80,
     317,   330,    87,    84,    81,   232,    81,   324,    80,   300,
      87,    80,    87,    83,   101,   332,    81,    87,   309,   336,
      21,    22,   352,    90,    91,   101,   356,    25,    26,   324,
     172,   173,   174,   175,     3,     4,   353,   168,   169,   101,
     170,   171,   315,    85,   271,   336,   101,   320,   176,   177,
     102,    81,   382,   383,    81,   385,    87,   101,    69,    81,
     103,    85,   353,   300,    80,    85,    81,   397,   398,   386,
     387,   388,   309,   346,    44,   103,   178,   180,   395,   120,
     410,   179,   181,   136,   138,   182,   324,   320,   405,   406,
     139,   408,   128,    47,   411,   386,   387,   388,   415,   326,
     417,   418,   148,   330,   395,   248,    -1,   424,    -1,    -1,
      -1,    58,    -1,    -1,   405,   406,   353,   408,    -1,    -1,
     411,    68,    -1,    -1,   415,    -1,   417,   418,    -1,    -1,
      -1,    -1,    -1,   424,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    90,    -1,    -1,    -1,    -1,    -1,   386,
     387,   388,    -1,    -1,    -1,    -1,    -1,    -1,   395,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   405,   406,
      -1,   408,   119,    -1,   411,    -1,    -1,    -1,   415,    -1,
     417,   418,    -1,    -1,   131,   132,    -1,   424,   135,   136,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      -1,   148,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      32,    -1,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    -1,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,    -1,
      82,    83,    -1,    -1,    -1,    -1,    88,    89,    90,    91,
      92,    93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     237,   103,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    -1,    -1,   250,    13,    14,    15,    16,    17,    18,
      19,    20,    -1,    -1,    23,    24,    -1,    -1,    -1,    -1,
      31,    32,    -1,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    -1,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    80,
      -1,    82,    83,    -1,    -1,    -1,    -1,    88,    89,    90,
      91,    92,    93,     3,     4,     5,     6,     7,     8,     9,
      10,    11,   103,   102,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    32,    -1,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      80,    -1,    82,    83,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    92,    93,     3,     4,     5,     6,     7,     8,
       9,    10,    11,   103,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    32,    -1,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    -1,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    80,    -1,    82,    -1,    -1,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    -1,    -1,    -1,    -1,    -1,
      31,    32,    -1,    -1,   103,    36,    37,    -1,    -1,    40,
      41,    42,    -1,    -1,    -1,    46,    -1,    -1,    49,    50,
      51,    -1,    -1,    -1,    -1,    -1,    57,    -1,    -1,    60,
      -1,    -1,    63,    -1,    -1,    -1,    -1,     3,    69,     5,
       6,     7,     8,     9,    10,    11,    -1,    -1,    -1,    80,
      -1,    82,    -1,    -1,    -1,    -1,    -1,    88,    89,    90,
      91,    92,    93,    -1,    -1,    31,    32,    -1,    -1,    -1,
      -1,    -1,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,    -1,
       3,    -1,     5,     6,     7,     8,     9,    10,    11,    -1,
      -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    89,    90,    91,    92,    93,    31,    32,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   103,    -1,    -1,
      -1,    -1,    -1,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,
      -1,    -1,    -1,     3,    -1,     5,     6,     7,     8,     9,
      10,    11,    -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    89,    90,    91,    92,
      93,    31,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     103,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      60,    -1,    -1,    -1,    -1,    -1,     3,    -1,     5,     6,
       7,     8,     9,    10,    11,    -1,    -1,     4,    -1,    -1,
      80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    92,    93,    31,    32,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   103,    -1,    -1,    -1,    -1,    35,    46,
      -1,    38,    39,    -1,    -1,    -1,    43,    -1,    45,    46,
      -1,    48,    -1,    60,    -1,    -1,    53,    54,     4,    56,
      -1,    58,    59,    -1,    -1,    62,    -1,    -1,    65,    66,
      67,    68,    -1,    80,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    89,    90,    91,    92,    93,    -1,    34,    35,
      -1,    -1,    38,    39,    -1,    -1,   103,    43,    -1,    45,
      46,    47,    48,    -1,    -1,    -1,    52,    53,    54,    55,
      56,    -1,    58,    59,    -1,    61,    62,    -1,    64,    65,
      66,    67,    68,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    32,    -1,    -1,    35,   102,    -1,    38,    39,
      -1,    -1,    -1,    43,    -1,    45,    46,    -1,    48,    -1,
      -1,    -1,    -1,    53,    54,    -1,    56,    -1,    58,    59,
      60,    -1,    62,    -1,    -1,    65,    66,    67,    68,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    -1,    -1,
      80,    -1,    82,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    92,    93,    -1,    -1,    -1,    31,    32,    -1,
      -1,    35,    -1,    -1,    38,    39,    -1,    -1,    -1,    43,
      -1,    45,    46,    -1,    48,    -1,    -1,    -1,    -1,    53,
      54,    -1,    56,    -1,    58,    59,    60,    -1,    62,    -1,
      -1,    65,    66,    67,    68,     3,    -1,     5,     6,     7,
       8,     9,    10,    11,    -1,    -1,    80,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    89,    90,    91,    92,    93,
      -1,    -1,    -1,    31,    32,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    -1,    -1,    -1,    -1,    -1,     3,    -1,
       5,     6,     7,     8,     9,    10,    11,    -1,    -1,    -1,
      -1,    -1,    80,    -1,    82,    83,    -1,    -1,    -1,    -1,
      88,    89,    90,    91,    92,    93,    31,    32,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,
      -1,     3,    -1,     5,     6,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    -1,    -1,    80,    -1,    82,    -1,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    92,    93,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,
      -1,    -1,    -1,    -1,     3,    -1,     5,     6,     7,     8,
       9,    10,    11,    -1,    -1,    -1,    -1,    -1,    80,    -1,
      -1,    -1,    -1,    85,    -1,    -1,    88,    89,    90,    91,
      92,    93,    31,    32,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    -1,    -1,    -1,    -1,    -1,     3,    -1,     5,
       6,     7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,
      -1,    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    31,    32,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,    -1,
       3,    -1,     5,     6,     7,     8,     9,    10,    11,    -1,
      -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,    85,
      -1,    -1,    88,    89,    90,    91,    92,    93,    31,    32,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,
      -1,    -1,    -1,     3,    -1,     5,     6,     7,     8,     9,
      10,    11,    -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,
      -1,    -1,    85,    -1,    -1,    88,    89,    90,    91,    92,
      93,    31,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      60,    -1,    -1,    -1,    -1,    -1,     3,    -1,     5,     6,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,
      80,    81,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    92,    93,    31,    32,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,    -1,     3,
      -1,     5,     6,     7,     8,     9,    10,    11,    -1,    -1,
      -1,    -1,    -1,    80,    81,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    89,    90,    91,    92,    93,    31,    32,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,
      -1,    -1,     3,    -1,     5,     6,     7,     8,     9,    10,
      11,    -1,    -1,    -1,    -1,    -1,    80,    81,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    89,    90,    91,    92,    93,
      31,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      -1,    -1,    -1,    -1,    -1,     3,    -1,     5,     6,     7,
       8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,    80,
      81,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,    90,
      91,    92,    93,    31,    32,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    -1,    -1,    -1,    -1,    -1,     3,    -1,
       5,     6,     7,     8,     9,    10,    11,    -1,    -1,    -1,
      -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    89,    90,    91,    92,    93,    31,    32,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,
      -1,     3,    -1,     5,     6,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    92,    93,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,
      -1,    -1,    -1,    -1,     3,    -1,     5,     6,     7,     8,
       9,    10,    11,    -1,    -1,    -1,    -1,    -1,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    89,    90,    91,
      92,    93,    31,    32,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    -1,    -1,    -1,    -1,    -1,     3,    -1,     5,
       6,     7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,
      -1,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    31,    32,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    -1,    -1,     3,     4,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    89,    90,    91,    92,    93,    34,    35,
      -1,    -1,    38,    39,    -1,    -1,    -1,    43,    -1,    45,
      46,    47,    48,    -1,    -1,    -1,    52,    53,    54,    55,
      56,    -1,    58,    59,    -1,    61,    62,     4,    64,    65,
      66,    67,    68,    -1,    -1,    12,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    80,    81,    -1,    -1,    84,    -1,
      -1,    -1,    -1,    89,    -1,    -1,    -1,    34,    35,    -1,
      -1,    38,    39,     0,     1,    -1,    43,     4,    45,    46,
      47,    48,    -1,    -1,    -1,    52,    53,    54,    55,    56,
      -1,    58,    59,    -1,    61,    62,    -1,    64,    65,    66,
      67,    68,    -1,    -1,    -1,    -1,    -1,    34,    35,    -1,
      -1,    38,    39,    80,    81,    -1,    43,    84,    45,    46,
      47,    48,    89,     4,    -1,    52,    53,    54,    55,    56,
      -1,    58,    59,    -1,    61,    62,    -1,    64,    65,    66,
      67,    68,    -1,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    -1,    35,    -1,    -1,    38,    39,     4,
      -1,    -1,    43,    -1,    45,    46,    -1,    48,    -1,    -1,
      -1,    -1,    53,    54,    -1,    56,    -1,    58,    59,    -1,
      -1,    62,    -1,    -1,    65,    66,    67,    68,    -1,    -1,
      35,    -1,    -1,    38,    39,    -1,    -1,    -1,    43,    -1,
      45,    46,    83,    48,    -1,    -1,    -1,     1,    53,    54,
       4,    56,    -1,    58,    59,    -1,    -1,    62,    -1,    -1,
      65,    66,    67,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    -1,
      34,    35,    -1,    -1,    38,    39,    -1,    -1,    -1,    43,
      -1,    45,    46,    47,    48,    -1,    -1,    -1,    52,    53,
      54,    55,    56,    -1,    58,    59,    -1,    61,    62,    -1,
      64,    65,    66,    67,    68,    -1,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,     3,     4,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    -1,
      -1,    38,    39,    -1,     4,    -1,    43,    -1,    45,    46,
      47,    48,    -1,    -1,    -1,    52,    53,    54,    55,    56,
      -1,    58,    59,    -1,    61,    62,    -1,    64,    65,    66,
      67,    68,    -1,    -1,    34,    35,    -1,    -1,    38,    39,
      -1,    -1,     4,    43,    81,    45,    46,    47,    48,    -1,
      12,    -1,    52,    53,    54,    55,    56,    -1,    58,    59,
      -1,    61,    62,    -1,    64,    65,    66,    67,    68,    -1,
      -1,    -1,    34,    35,    -1,    -1,    38,    39,    -1,     4,
      -1,    43,    82,    45,    46,    47,    48,    12,    -1,    -1,
      52,    53,    54,    55,    56,    -1,    58,    59,    -1,    61,
      62,    -1,    64,    65,    66,    67,    68,    -1,    -1,    34,
      35,    -1,    -1,    38,    39,     4,    -1,    -1,    43,    81,
      45,    46,    47,    48,    -1,    -1,    -1,    52,    53,    54,
      55,    56,    -1,    58,    59,    -1,    61,    62,    -1,    64,
      65,    66,    67,    68,    -1,    34,    35,    -1,    -1,    38,
      39,    -1,    -1,    -1,    43,    -1,    45,    46,    47,    48,
      -1,    -1,    -1,    52,    53,    54,    55,    56,    -1,    58,
      59,    -1,    61,    62,    -1,    64,    65,    66,    67,    68
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     4,    34,    35,    38,    39,    43,    45,    46,
      47,    48,    52,    53,    54,    55,    56,    58,    59,    61,
      62,    64,    65,    66,    67,    68,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,   129,   130,   133,   134,
     135,   136,   142,   143,   147,   148,   159,   171,   172,   173,
     175,   176,   177,   178,   179,   180,     3,    80,    89,   103,
     107,   131,   132,   149,   150,   151,   130,   130,    82,   107,
     108,   159,    82,   108,   130,   130,     0,   172,    80,     5,
       6,     7,     8,     9,    10,    11,    31,    32,    46,    60,
      80,    88,    89,    90,    91,    92,    93,   105,   106,   107,
     109,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   128,   149,   147,   151,   152,
      87,   103,    82,   102,   129,   130,   164,   174,    80,    84,
     150,   134,   137,   138,   139,   147,    82,   144,   145,    82,
     107,   155,    80,    80,    80,   111,   111,    80,    80,   111,
      46,   111,   124,   125,   127,   139,   156,     9,    31,    32,
      33,    80,    84,    86,   113,    89,    94,    95,    90,    91,
      21,    22,    27,    28,    96,    97,    25,    26,    88,    98,
      99,    29,    30,   100,    81,   147,   151,   132,   149,    36,
      37,    40,    41,    42,    49,    50,    51,    57,    63,    69,
      83,   103,   107,   108,   127,   129,   159,   162,   163,   164,
     165,   166,   167,   168,   169,   170,    82,   125,   160,   129,
     164,    12,    81,   130,   153,   154,   155,    85,   125,   139,
      83,   138,   101,   140,   141,   149,   139,   137,    83,    87,
     107,   146,   144,    81,    87,   111,   111,    46,    82,   156,
      80,   127,    13,    14,    15,    16,    17,    18,    19,    20,
      23,    24,   102,   126,    81,    87,    80,    84,   151,   157,
     158,    81,   108,    81,   110,   125,   127,   108,   113,   113,
     113,   114,   114,   115,   115,   116,   116,   116,   116,   117,
     117,   118,   119,   120,   121,   122,   127,   103,   128,   103,
     101,   162,    80,   108,    80,   103,   127,    80,    80,   101,
     103,    83,   166,   160,   161,    80,   149,   151,   157,    81,
      87,    81,    85,   128,    87,   103,   101,    83,    83,   146,
     102,    83,    87,   107,    81,    81,   165,    81,   125,   125,
      81,   153,   157,    85,   125,   158,    80,    84,   113,    81,
      87,    85,   101,   101,   162,    69,   103,   127,   103,   127,
     103,   127,   127,   162,    83,    87,   154,   141,   128,   128,
      83,    83,    81,    81,    85,    81,   153,    85,   125,   125,
     127,   162,    80,   103,   127,   103,    81,    81,    81,    83,
     160,    81,    81,    85,   127,    81,   127,   103,   103,   127,
     162,   162,   162,    81,   162,    81,    81,   127,    81,   127,
     103,    44,   103,   162,   162,    81,   162,    81,    81,   127,
     162,   162,   162,   162,    81,   162
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
      yyerror (scanner, YY_("syntax error: cannot back up")); \
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
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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
        case 2:
/* Line 1792 of yacc.c  */
#line 305 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = g_hash_table_lookup (const_table, (yyvsp[(1) - (1)].str));
		if ((yyval.symbol) == NULL) {
			(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_file, lineno);
		} else {
			(yyval.symbol) = gi_source_symbol_ref ((yyval.symbol));
		}
	  }
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 314 "giscanner/scannerparser.y"
    {
		char *rest;
		guint64 value;
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_file, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		if (g_str_has_prefix (yytext, "0x") && strlen (yytext) > 2) {
			value = g_ascii_strtoull (yytext + 2, &rest, 16);
		} else if (g_str_has_prefix (yytext, "0") && strlen (yytext) > 1) {
			value = g_ascii_strtoull (yytext + 1, &rest, 8);
		} else {
			value = g_ascii_strtoull (yytext, &rest, 10);
		}
		(yyval.symbol)->const_int = value;
		(yyval.symbol)->const_int_is_unsigned = (rest && (rest[0] == 'U'));
	  }
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 330 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_file, lineno);
		(yyval.symbol)->const_boolean_set = TRUE;
		(yyval.symbol)->const_boolean = g_ascii_strcasecmp (yytext, "true") == 0 ? TRUE : FALSE;
	  }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 336 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_file, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = g_utf8_get_char(yytext + 1);
	  }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 342 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_file, lineno);
		(yyval.symbol)->const_double_set = TRUE;
		(yyval.symbol)->const_double = 0.0;
        sscanf (yytext, "%lf", &((yyval.symbol)->const_double));
	  }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 350 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = (yyvsp[(2) - (3)].symbol);
	  }
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 354 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_file, lineno);
	  }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 362 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_file, lineno);
		yytext[strlen (yytext) - 1] = '\0';
		(yyval.symbol)->const_string = parse_c_string_literal (yytext + 1);
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

  case 11:
/* Line 1792 of yacc.c  */
#line 377 "giscanner/scannerparser.y"
    {
		char *strings, *string2;
		(yyval.symbol) = (yyvsp[(1) - (2)].symbol);
		yytext[strlen (yytext) - 1] = '\0';
		string2 = parse_c_string_literal (yytext + 1);
		strings = g_strconcat ((yyval.symbol)->const_string, string2, NULL);
		g_free ((yyval.symbol)->const_string);
		g_free (string2);
		(yyval.symbol)->const_string = strings;
	  }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 391 "giscanner/scannerparser.y"
    {
		(yyval.str) = g_strdup (yytext);
	  }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 404 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_file, lineno);
	  }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 408 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_file, lineno);
	  }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 412 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_file, lineno);
	  }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 416 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_file, lineno);
	  }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 420 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_file, lineno);
	  }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 424 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_file, lineno);
	  }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 428 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_file, lineno);
	  }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 441 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_file, lineno);
	  }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 445 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_file, lineno);
	  }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 449 "giscanner/scannerparser.y"
    {
		switch ((yyvsp[(1) - (2)].unary_operator)) {
		case UNARY_PLUS:
			(yyval.symbol) = (yyvsp[(2) - (2)].symbol);
			break;
		case UNARY_MINUS:
			(yyval.symbol) = gi_source_symbol_copy ((yyvsp[(2) - (2)].symbol));
			(yyval.symbol)->const_int = -(yyvsp[(2) - (2)].symbol)->const_int;
			break;
		case UNARY_BITWISE_COMPLEMENT:
			(yyval.symbol) = gi_source_symbol_copy ((yyvsp[(2) - (2)].symbol));
			(yyval.symbol)->const_int = ~(yyvsp[(2) - (2)].symbol)->const_int;
			break;
		case UNARY_LOGICAL_NEGATION:
			(yyval.symbol) = gi_source_symbol_copy ((yyvsp[(2) - (2)].symbol));
			(yyval.symbol)->const_int = !gi_source_symbol_get_const_boolean ((yyvsp[(2) - (2)].symbol));
			break;
		default:
			(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_file, lineno);
			break;
		}
	  }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 472 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = (yyvsp[(3) - (4)].symbol);
		if ((yyval.symbol)->const_int_set) {
			(yyval.symbol)->base_type = gi_source_basic_type_new ((yyval.symbol)->const_int_is_unsigned ? "guint64" : "gint64");
		}
	  }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 479 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = (yyvsp[(3) - (4)].symbol);
		if ((yyval.symbol)->const_int_set) {
			(yyval.symbol)->base_type = gi_source_basic_type_new ("guint64");
		}
	  }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 486 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_file, lineno);
	  }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 490 "giscanner/scannerparser.y"
    {
		ctype_free ((yyvsp[(3) - (4)].ctype));
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_file, lineno);
	  }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 498 "giscanner/scannerparser.y"
    {
		(yyval.unary_operator) = UNARY_ADDRESS_OF;
	  }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 502 "giscanner/scannerparser.y"
    {
		(yyval.unary_operator) = UNARY_POINTER_INDIRECTION;
	  }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 506 "giscanner/scannerparser.y"
    {
		(yyval.unary_operator) = UNARY_PLUS;
	  }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 510 "giscanner/scannerparser.y"
    {
		(yyval.unary_operator) = UNARY_MINUS;
	  }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 514 "giscanner/scannerparser.y"
    {
		(yyval.unary_operator) = UNARY_BITWISE_COMPLEMENT;
	  }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 518 "giscanner/scannerparser.y"
    {
		(yyval.unary_operator) = UNARY_LOGICAL_NEGATION;
	  }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 526 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = (yyvsp[(4) - (4)].symbol);
		if ((yyval.symbol)->const_int_set || (yyval.symbol)->const_double_set || (yyval.symbol)->const_string != NULL) {
			(yyval.symbol)->base_type = (yyvsp[(2) - (4)].ctype);
		} else {
			ctype_free ((yyvsp[(2) - (4)].ctype));
		}
	  }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 539 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_file, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int * (yyvsp[(3) - (3)].symbol)->const_int;
	  }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 545 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_file, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		if ((yyvsp[(3) - (3)].symbol)->const_int != 0) {
			(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int / (yyvsp[(3) - (3)].symbol)->const_int;
		}
	  }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 553 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_file, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		if ((yyvsp[(3) - (3)].symbol)->const_int != 0) {
			(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int % (yyvsp[(3) - (3)].symbol)->const_int;
		}
	  }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 565 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_file, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int + (yyvsp[(3) - (3)].symbol)->const_int;
	  }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 571 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_file, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int - (yyvsp[(3) - (3)].symbol)->const_int;
	  }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 581 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_file, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int << (yyvsp[(3) - (3)].symbol)->const_int;

		/* assume this is a bitfield/flags declaration
		 * if a left shift operator is sued in an enum value
                 * This mimics the glib-mkenum behavior.
		 */
		is_bitfield = TRUE;
	  }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 593 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_file, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int >> (yyvsp[(3) - (3)].symbol)->const_int;
	  }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 603 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_file, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int < (yyvsp[(3) - (3)].symbol)->const_int;
	  }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 609 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_file, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int > (yyvsp[(3) - (3)].symbol)->const_int;
	  }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 615 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_file, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int <= (yyvsp[(3) - (3)].symbol)->const_int;
	  }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 621 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_file, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int >= (yyvsp[(3) - (3)].symbol)->const_int;
	  }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 631 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_file, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int == (yyvsp[(3) - (3)].symbol)->const_int;
	  }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 637 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_file, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int != (yyvsp[(3) - (3)].symbol)->const_int;
	  }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 647 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_file, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int & (yyvsp[(3) - (3)].symbol)->const_int;
	  }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 657 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_file, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int ^ (yyvsp[(3) - (3)].symbol)->const_int;
	  }
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 667 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_file, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = (yyvsp[(1) - (3)].symbol)->const_int | (yyvsp[(3) - (3)].symbol)->const_int;
	  }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 677 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_file, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int =
		  gi_source_symbol_get_const_boolean ((yyvsp[(1) - (3)].symbol)) &&
		  gi_source_symbol_get_const_boolean ((yyvsp[(3) - (3)].symbol));
	  }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 689 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_CONST, scanner->current_file, lineno);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int =
		  gi_source_symbol_get_const_boolean ((yyvsp[(1) - (3)].symbol)) ||
		  gi_source_symbol_get_const_boolean ((yyvsp[(3) - (3)].symbol));
	  }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 701 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_get_const_boolean ((yyvsp[(1) - (5)].symbol)) ? (yyvsp[(3) - (5)].symbol) : (yyvsp[(5) - (5)].symbol);
	  }
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 709 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_file, lineno);
	  }
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 732 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_file, lineno);
	  }
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 745 "giscanner/scannerparser.y"
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

  case 89:
/* Line 1792 of yacc.c  */
#line 763 "giscanner/scannerparser.y"
    {
		ctype_free ((yyvsp[(1) - (2)].ctype));
	  }
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 770 "giscanner/scannerparser.y"
    {
		(yyval.ctype) = (yyvsp[(2) - (2)].ctype);
		(yyval.ctype)->storage_class_specifier |= (yyvsp[(1) - (2)].storage_class_specifier);
	  }
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 775 "giscanner/scannerparser.y"
    {
		(yyval.ctype) = gi_source_type_new (CTYPE_INVALID);
		(yyval.ctype)->storage_class_specifier |= (yyvsp[(1) - (1)].storage_class_specifier);
	  }
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 780 "giscanner/scannerparser.y"
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

  case 94:
/* Line 1792 of yacc.c  */
#line 794 "giscanner/scannerparser.y"
    {
		(yyval.ctype) = (yyvsp[(2) - (2)].ctype);
		(yyval.ctype)->type_qualifier |= (yyvsp[(1) - (2)].type_qualifier);
	  }
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 799 "giscanner/scannerparser.y"
    {
		(yyval.ctype) = gi_source_type_new (CTYPE_INVALID);
		(yyval.ctype)->type_qualifier |= (yyvsp[(1) - (1)].type_qualifier);
	  }
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 804 "giscanner/scannerparser.y"
    {
		(yyval.ctype) = (yyvsp[(2) - (2)].ctype);
		(yyval.ctype)->function_specifier |= (yyvsp[(1) - (2)].function_specifier);
	  }
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 809 "giscanner/scannerparser.y"
    {
		(yyval.ctype) = gi_source_type_new (CTYPE_INVALID);
		(yyval.ctype)->function_specifier |= (yyvsp[(1) - (1)].function_specifier);
	  }
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 817 "giscanner/scannerparser.y"
    {
		(yyval.list) = g_list_append (NULL, (yyvsp[(1) - (1)].symbol));
	  }
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 821 "giscanner/scannerparser.y"
    {
		(yyval.list) = g_list_append ((yyvsp[(1) - (3)].list), (yyvsp[(3) - (3)].symbol));
	  }
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 833 "giscanner/scannerparser.y"
    {
		(yyval.storage_class_specifier) = STORAGE_CLASS_TYPEDEF;
	  }
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 837 "giscanner/scannerparser.y"
    {
		(yyval.storage_class_specifier) = STORAGE_CLASS_EXTERN;
	  }
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 841 "giscanner/scannerparser.y"
    {
		(yyval.storage_class_specifier) = STORAGE_CLASS_STATIC;
	  }
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 845 "giscanner/scannerparser.y"
    {
		(yyval.storage_class_specifier) = STORAGE_CLASS_AUTO;
	  }
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 849 "giscanner/scannerparser.y"
    {
		(yyval.storage_class_specifier) = STORAGE_CLASS_REGISTER;
	  }
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 856 "giscanner/scannerparser.y"
    {
		(yyval.ctype) = gi_source_type_new (CTYPE_VOID);
	  }
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 860 "giscanner/scannerparser.y"
    {
		(yyval.ctype) = gi_source_basic_type_new ("char");
	  }
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 864 "giscanner/scannerparser.y"
    {
		(yyval.ctype) = gi_source_basic_type_new ("short");
	  }
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 868 "giscanner/scannerparser.y"
    {
		(yyval.ctype) = gi_source_basic_type_new ("int");
	  }
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 872 "giscanner/scannerparser.y"
    {
		(yyval.ctype) = gi_source_basic_type_new ("long");
	  }
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 876 "giscanner/scannerparser.y"
    {
		(yyval.ctype) = gi_source_basic_type_new ("float");
	  }
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 880 "giscanner/scannerparser.y"
    {
		(yyval.ctype) = gi_source_basic_type_new ("double");
	  }
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 884 "giscanner/scannerparser.y"
    {
		(yyval.ctype) = gi_source_basic_type_new ("signed");
	  }
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 888 "giscanner/scannerparser.y"
    {
		(yyval.ctype) = gi_source_basic_type_new ("unsigned");
	  }
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 892 "giscanner/scannerparser.y"
    {
		(yyval.ctype) = gi_source_basic_type_new ("bool");
	  }
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 898 "giscanner/scannerparser.y"
    {
		(yyval.ctype) = gi_source_typedef_new ((yyvsp[(1) - (1)].str));
		g_free ((yyvsp[(1) - (1)].str));
	  }
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 906 "giscanner/scannerparser.y"
    {
		GISourceSymbol *sym;
		(yyval.ctype) = (yyvsp[(1) - (5)].ctype);
		(yyval.ctype)->name = (yyvsp[(2) - (5)].str);
		(yyval.ctype)->child_list = (yyvsp[(4) - (5)].list);

		sym = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_file, lineno);
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

  case 121:
/* Line 1792 of yacc.c  */
#line 926 "giscanner/scannerparser.y"
    {
		(yyval.ctype) = (yyvsp[(1) - (4)].ctype);
		(yyval.ctype)->child_list = (yyvsp[(3) - (4)].list);
	  }
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 931 "giscanner/scannerparser.y"
    {
		(yyval.ctype) = (yyvsp[(1) - (2)].ctype);
		(yyval.ctype)->name = (yyvsp[(2) - (2)].str);
	  }
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 939 "giscanner/scannerparser.y"
    {
                scanner->private = FALSE;
		(yyval.ctype) = gi_source_struct_new (NULL);
	  }
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 944 "giscanner/scannerparser.y"
    {
                scanner->private = FALSE;
		(yyval.ctype) = gi_source_union_new (NULL);
	  }
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 953 "giscanner/scannerparser.y"
    {
		(yyval.list) = g_list_concat ((yyvsp[(1) - (2)].list), (yyvsp[(2) - (2)].list));
	  }
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 960 "giscanner/scannerparser.y"
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
                sym->private = scanner->private;
                (yyval.list) = g_list_append ((yyval.list), sym);
	      }
	    ctype_free ((yyvsp[(1) - (3)].ctype));
	  }
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 980 "giscanner/scannerparser.y"
    {
		(yyval.ctype) = (yyvsp[(1) - (2)].ctype);
		(yyval.ctype)->base_type = (yyvsp[(2) - (2)].ctype);
	  }
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 986 "giscanner/scannerparser.y"
    {
		(yyval.ctype) = (yyvsp[(2) - (2)].ctype);
		(yyval.ctype)->type_qualifier |= (yyvsp[(1) - (2)].type_qualifier);
	  }
    break;

  case 131:
/* Line 1792 of yacc.c  */
#line 991 "giscanner/scannerparser.y"
    {
		(yyval.ctype) = gi_source_type_new (CTYPE_INVALID);
		(yyval.ctype)->type_qualifier |= (yyvsp[(1) - (1)].type_qualifier);
	  }
    break;

  case 132:
/* Line 1792 of yacc.c  */
#line 999 "giscanner/scannerparser.y"
    {
		(yyval.list) = g_list_append (NULL, (yyvsp[(1) - (1)].symbol));
	  }
    break;

  case 133:
/* Line 1792 of yacc.c  */
#line 1003 "giscanner/scannerparser.y"
    {
		(yyval.list) = g_list_append ((yyvsp[(1) - (3)].list), (yyvsp[(3) - (3)].symbol));
	  }
    break;

  case 134:
/* Line 1792 of yacc.c  */
#line 1010 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_file, lineno);
	  }
    break;

  case 136:
/* Line 1792 of yacc.c  */
#line 1015 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_file, lineno);
	  }
    break;

  case 137:
/* Line 1792 of yacc.c  */
#line 1019 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = (yyvsp[(1) - (3)].symbol);
		if ((yyvsp[(3) - (3)].symbol)->const_int_set) {
		  (yyval.symbol)->const_int_set = TRUE;
		  (yyval.symbol)->const_int = (yyvsp[(3) - (3)].symbol)->const_int;
		}
	  }
    break;

  case 138:
/* Line 1792 of yacc.c  */
#line 1030 "giscanner/scannerparser.y"
    {
		(yyval.ctype) = gi_source_enum_new ((yyvsp[(2) - (5)].str));
		(yyval.ctype)->child_list = (yyvsp[(4) - (5)].list);
		(yyval.ctype)->is_bitfield = is_bitfield || scanner->flags;
		last_enum_value = -1;
	  }
    break;

  case 139:
/* Line 1792 of yacc.c  */
#line 1037 "giscanner/scannerparser.y"
    {
		(yyval.ctype) = gi_source_enum_new (NULL);
		(yyval.ctype)->child_list = (yyvsp[(3) - (4)].list);
		(yyval.ctype)->is_bitfield = is_bitfield || scanner->flags;
		last_enum_value = -1;
	  }
    break;

  case 140:
/* Line 1792 of yacc.c  */
#line 1044 "giscanner/scannerparser.y"
    {
		(yyval.ctype) = gi_source_enum_new ((yyvsp[(2) - (6)].str));
		(yyval.ctype)->child_list = (yyvsp[(4) - (6)].list);
		(yyval.ctype)->is_bitfield = is_bitfield || scanner->flags;
		last_enum_value = -1;
	  }
    break;

  case 141:
/* Line 1792 of yacc.c  */
#line 1051 "giscanner/scannerparser.y"
    {
		(yyval.ctype) = gi_source_enum_new (NULL);
		(yyval.ctype)->child_list = (yyvsp[(3) - (5)].list);
		(yyval.ctype)->is_bitfield = is_bitfield || scanner->flags;
		last_enum_value = -1;
	  }
    break;

  case 142:
/* Line 1792 of yacc.c  */
#line 1058 "giscanner/scannerparser.y"
    {
		(yyval.ctype) = gi_source_enum_new ((yyvsp[(2) - (2)].str));
	  }
    break;

  case 143:
/* Line 1792 of yacc.c  */
#line 1065 "giscanner/scannerparser.y"
    {
                scanner->flags = FALSE;
                scanner->private = FALSE;
          }
    break;

  case 144:
/* Line 1792 of yacc.c  */
#line 1073 "giscanner/scannerparser.y"
    {
		/* reset flag before the first enum value */
		is_bitfield = FALSE;
	  }
    break;

  case 145:
/* Line 1792 of yacc.c  */
#line 1078 "giscanner/scannerparser.y"
    {
            (yyvsp[(2) - (2)].symbol)->private = scanner->private;
            (yyval.list) = g_list_append (NULL, (yyvsp[(2) - (2)].symbol));
	  }
    break;

  case 146:
/* Line 1792 of yacc.c  */
#line 1083 "giscanner/scannerparser.y"
    {
            (yyvsp[(3) - (3)].symbol)->private = scanner->private;
            (yyval.list) = g_list_append ((yyvsp[(1) - (3)].list), (yyvsp[(3) - (3)].symbol));
	  }
    break;

  case 147:
/* Line 1792 of yacc.c  */
#line 1091 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_OBJECT, scanner->current_file, lineno);
		(yyval.symbol)->ident = (yyvsp[(1) - (1)].str);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = ++last_enum_value;
		g_hash_table_insert (const_table, g_strdup ((yyval.symbol)->ident), gi_source_symbol_ref ((yyval.symbol)));
	  }
    break;

  case 148:
/* Line 1792 of yacc.c  */
#line 1099 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_OBJECT, scanner->current_file, lineno);
		(yyval.symbol)->ident = (yyvsp[(1) - (3)].str);
		(yyval.symbol)->const_int_set = TRUE;
		(yyval.symbol)->const_int = (yyvsp[(3) - (3)].symbol)->const_int;
		last_enum_value = (yyval.symbol)->const_int;
		g_hash_table_insert (const_table, g_strdup ((yyval.symbol)->ident), gi_source_symbol_ref ((yyval.symbol)));
	  }
    break;

  case 149:
/* Line 1792 of yacc.c  */
#line 1111 "giscanner/scannerparser.y"
    {
		(yyval.type_qualifier) = TYPE_QUALIFIER_CONST;
	  }
    break;

  case 150:
/* Line 1792 of yacc.c  */
#line 1115 "giscanner/scannerparser.y"
    {
		(yyval.type_qualifier) = TYPE_QUALIFIER_RESTRICT;
	  }
    break;

  case 151:
/* Line 1792 of yacc.c  */
#line 1119 "giscanner/scannerparser.y"
    {
		(yyval.type_qualifier) = TYPE_QUALIFIER_EXTENSION;
	  }
    break;

  case 152:
/* Line 1792 of yacc.c  */
#line 1123 "giscanner/scannerparser.y"
    {
		(yyval.type_qualifier) = TYPE_QUALIFIER_VOLATILE;
	  }
    break;

  case 153:
/* Line 1792 of yacc.c  */
#line 1130 "giscanner/scannerparser.y"
    {
		(yyval.function_specifier) = FUNCTION_INLINE;
	  }
    break;

  case 154:
/* Line 1792 of yacc.c  */
#line 1137 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = (yyvsp[(2) - (2)].symbol);
		gi_source_symbol_merge_type ((yyval.symbol), (yyvsp[(1) - (2)].ctype));
	  }
    break;

  case 156:
/* Line 1792 of yacc.c  */
#line 1146 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_file, lineno);
		(yyval.symbol)->ident = (yyvsp[(1) - (1)].str);
	  }
    break;

  case 157:
/* Line 1792 of yacc.c  */
#line 1151 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = (yyvsp[(2) - (3)].symbol);
	  }
    break;

  case 158:
/* Line 1792 of yacc.c  */
#line 1155 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = (yyvsp[(1) - (4)].symbol);
		gi_source_symbol_merge_type ((yyval.symbol), gi_source_array_new ((yyvsp[(3) - (4)].symbol)));
	  }
    break;

  case 159:
/* Line 1792 of yacc.c  */
#line 1160 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = (yyvsp[(1) - (3)].symbol);
		gi_source_symbol_merge_type ((yyval.symbol), gi_source_array_new (NULL));
	  }
    break;

  case 160:
/* Line 1792 of yacc.c  */
#line 1165 "giscanner/scannerparser.y"
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

  case 161:
/* Line 1792 of yacc.c  */
#line 1175 "giscanner/scannerparser.y"
    {
		GISourceType *func = gi_source_function_new ();
		func->child_list = (yyvsp[(3) - (4)].list);
		(yyval.symbol) = (yyvsp[(1) - (4)].symbol);
		gi_source_symbol_merge_type ((yyval.symbol), func);
	  }
    break;

  case 162:
/* Line 1792 of yacc.c  */
#line 1182 "giscanner/scannerparser.y"
    {
		GISourceType *func = gi_source_function_new ();
		(yyval.symbol) = (yyvsp[(1) - (3)].symbol);
		gi_source_symbol_merge_type ((yyval.symbol), func);
	  }
    break;

  case 163:
/* Line 1792 of yacc.c  */
#line 1191 "giscanner/scannerparser.y"
    {
		(yyval.ctype) = gi_source_pointer_new (NULL);
		(yyval.ctype)->type_qualifier = (yyvsp[(2) - (2)].type_qualifier);
	  }
    break;

  case 164:
/* Line 1792 of yacc.c  */
#line 1196 "giscanner/scannerparser.y"
    {
		(yyval.ctype) = gi_source_pointer_new (NULL);
	  }
    break;

  case 165:
/* Line 1792 of yacc.c  */
#line 1200 "giscanner/scannerparser.y"
    {
		GISourceType **base = &((yyvsp[(3) - (3)].ctype)->base_type);

		while (*base != NULL) {
			base = &((*base)->base_type);
		}
		*base = gi_source_pointer_new (NULL);
		(*base)->type_qualifier = (yyvsp[(2) - (3)].type_qualifier);
		(yyval.ctype) = (yyvsp[(3) - (3)].ctype);
	  }
    break;

  case 166:
/* Line 1792 of yacc.c  */
#line 1211 "giscanner/scannerparser.y"
    {
		GISourceType **base = &((yyvsp[(2) - (2)].ctype)->base_type);

		while (*base != NULL) {
			base = &((*base)->base_type);
		}
		*base = gi_source_pointer_new (NULL);
		(yyval.ctype) = (yyvsp[(2) - (2)].ctype);
	  }
    break;

  case 168:
/* Line 1792 of yacc.c  */
#line 1225 "giscanner/scannerparser.y"
    {
		(yyval.type_qualifier) = (yyvsp[(1) - (2)].type_qualifier) | (yyvsp[(2) - (2)].type_qualifier);
	  }
    break;

  case 169:
/* Line 1792 of yacc.c  */
#line 1232 "giscanner/scannerparser.y"
    {
		(yyval.list) = g_list_append (NULL, (yyvsp[(1) - (1)].symbol));
	  }
    break;

  case 170:
/* Line 1792 of yacc.c  */
#line 1236 "giscanner/scannerparser.y"
    {
		(yyval.list) = g_list_append ((yyvsp[(1) - (3)].list), (yyvsp[(3) - (3)].symbol));
	  }
    break;

  case 171:
/* Line 1792 of yacc.c  */
#line 1243 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = (yyvsp[(2) - (2)].symbol);
		gi_source_symbol_merge_type ((yyval.symbol), (yyvsp[(1) - (2)].ctype));
	  }
    break;

  case 172:
/* Line 1792 of yacc.c  */
#line 1248 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = (yyvsp[(2) - (2)].symbol);
		gi_source_symbol_merge_type ((yyval.symbol), (yyvsp[(1) - (2)].ctype));
	  }
    break;

  case 173:
/* Line 1792 of yacc.c  */
#line 1253 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_file, lineno);
		(yyval.symbol)->base_type = (yyvsp[(1) - (1)].ctype);
	  }
    break;

  case 174:
/* Line 1792 of yacc.c  */
#line 1258 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_ELLIPSIS, scanner->current_file, lineno);
	  }
    break;

  case 175:
/* Line 1792 of yacc.c  */
#line 1265 "giscanner/scannerparser.y"
    {
		GISourceSymbol *sym = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_file, lineno);
		sym->ident = (yyvsp[(1) - (1)].str);
		(yyval.list) = g_list_append (NULL, sym);
	  }
    break;

  case 176:
/* Line 1792 of yacc.c  */
#line 1271 "giscanner/scannerparser.y"
    {
		GISourceSymbol *sym = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_file, lineno);
		sym->ident = (yyvsp[(3) - (3)].str);
		(yyval.list) = g_list_append ((yyvsp[(1) - (3)].list), sym);
	  }
    break;

  case 179:
/* Line 1792 of yacc.c  */
#line 1285 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_file, lineno);
		gi_source_symbol_merge_type ((yyval.symbol), (yyvsp[(1) - (1)].ctype));
	  }
    break;

  case 181:
/* Line 1792 of yacc.c  */
#line 1291 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = (yyvsp[(2) - (2)].symbol);
		gi_source_symbol_merge_type ((yyval.symbol), (yyvsp[(1) - (2)].ctype));
	  }
    break;

  case 182:
/* Line 1792 of yacc.c  */
#line 1299 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = (yyvsp[(2) - (3)].symbol);
	  }
    break;

  case 183:
/* Line 1792 of yacc.c  */
#line 1303 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_file, lineno);
		gi_source_symbol_merge_type ((yyval.symbol), gi_source_array_new (NULL));
	  }
    break;

  case 184:
/* Line 1792 of yacc.c  */
#line 1308 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_file, lineno);
		gi_source_symbol_merge_type ((yyval.symbol), gi_source_array_new ((yyvsp[(2) - (3)].symbol)));
	  }
    break;

  case 185:
/* Line 1792 of yacc.c  */
#line 1313 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = (yyvsp[(1) - (3)].symbol);
		gi_source_symbol_merge_type ((yyval.symbol), gi_source_array_new (NULL));
	  }
    break;

  case 186:
/* Line 1792 of yacc.c  */
#line 1318 "giscanner/scannerparser.y"
    {
		(yyval.symbol) = (yyvsp[(1) - (4)].symbol);
		gi_source_symbol_merge_type ((yyval.symbol), gi_source_array_new ((yyvsp[(3) - (4)].symbol)));
	  }
    break;

  case 187:
/* Line 1792 of yacc.c  */
#line 1323 "giscanner/scannerparser.y"
    {
		GISourceType *func = gi_source_function_new ();
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_file, lineno);
		gi_source_symbol_merge_type ((yyval.symbol), func);
	  }
    break;

  case 188:
/* Line 1792 of yacc.c  */
#line 1329 "giscanner/scannerparser.y"
    {
		GISourceType *func = gi_source_function_new ();
		// ignore (void) parameter list
		if ((yyvsp[(2) - (3)].list) != NULL && ((yyvsp[(2) - (3)].list)->next != NULL || ((GISourceSymbol *) (yyvsp[(2) - (3)].list)->data)->base_type->type != CTYPE_VOID)) {
			func->child_list = (yyvsp[(2) - (3)].list);
		}
		(yyval.symbol) = gi_source_symbol_new (CSYMBOL_TYPE_INVALID, scanner->current_file, lineno);
		gi_source_symbol_merge_type ((yyval.symbol), func);
	  }
    break;

  case 189:
/* Line 1792 of yacc.c  */
#line 1339 "giscanner/scannerparser.y"
    {
		GISourceType *func = gi_source_function_new ();
		(yyval.symbol) = (yyvsp[(1) - (3)].symbol);
		gi_source_symbol_merge_type ((yyval.symbol), func);
	  }
    break;

  case 190:
/* Line 1792 of yacc.c  */
#line 1345 "giscanner/scannerparser.y"
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

  case 191:
/* Line 1792 of yacc.c  */
#line 1358 "giscanner/scannerparser.y"
    {
		(yyval.str) = g_strdup (yytext);
	  }
    break;

  case 241:
/* Line 1792 of yacc.c  */
#line 1465 "giscanner/scannerparser.y"
    {
		(yyval.str) = g_strdup (yytext + strlen ("#define "));
	  }
    break;

  case 242:
/* Line 1792 of yacc.c  */
#line 1472 "giscanner/scannerparser.y"
    {
		(yyval.str) = g_strdup (yytext + strlen ("#define "));
	  }
    break;

  case 244:
/* Line 1792 of yacc.c  */
#line 1483 "giscanner/scannerparser.y"
    {
		if ((yyvsp[(2) - (2)].symbol)->const_int_set || (yyvsp[(2) - (2)].symbol)->const_boolean_set || (yyvsp[(2) - (2)].symbol)->const_double_set || (yyvsp[(2) - (2)].symbol)->const_string != NULL) {
			(yyvsp[(2) - (2)].symbol)->ident = (yyvsp[(1) - (2)].str);
			gi_source_scanner_add_symbol (scanner, (yyvsp[(2) - (2)].symbol));
			gi_source_symbol_unref ((yyvsp[(2) - (2)].symbol));
		}
	  }
    break;

  case 245:
/* Line 1792 of yacc.c  */
#line 1494 "giscanner/scannerparser.y"
    {
		push_conditional (scanner, FOR_GI_SCANNER);
		update_skipping (scanner);
	  }
    break;

  case 246:
/* Line 1792 of yacc.c  */
#line 1499 "giscanner/scannerparser.y"
    {
		push_conditional (scanner, NOT_GI_SCANNER);
		update_skipping (scanner);
	  }
    break;

  case 247:
/* Line 1792 of yacc.c  */
#line 1504 "giscanner/scannerparser.y"
    {
	 	warn_if_cond_has_gi_scanner (scanner, yytext);
		push_conditional (scanner, IRRELEVANT);
	  }
    break;

  case 248:
/* Line 1792 of yacc.c  */
#line 1509 "giscanner/scannerparser.y"
    {
		warn_if_cond_has_gi_scanner (scanner, yytext);
		push_conditional (scanner, IRRELEVANT);
	  }
    break;

  case 249:
/* Line 1792 of yacc.c  */
#line 1514 "giscanner/scannerparser.y"
    {
		warn_if_cond_has_gi_scanner (scanner, yytext);
		push_conditional (scanner, IRRELEVANT);
	  }
    break;

  case 250:
/* Line 1792 of yacc.c  */
#line 1519 "giscanner/scannerparser.y"
    {
		warn_if_cond_has_gi_scanner (scanner, yytext);
		pop_conditional (scanner);
		push_conditional (scanner, IRRELEVANT);
		update_skipping (scanner);
	  }
    break;

  case 251:
/* Line 1792 of yacc.c  */
#line 1526 "giscanner/scannerparser.y"
    {
		toggle_conditional (scanner);
		update_skipping (scanner);
	  }
    break;

  case 252:
/* Line 1792 of yacc.c  */
#line 1531 "giscanner/scannerparser.y"
    {
		pop_conditional (scanner);
		update_skipping (scanner);
	  }
    break;


/* Line 1792 of yacc.c  */
#line 4127 "scannerparser.c"
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
      yyerror (scanner, YY_("syntax error"));
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
        yyerror (scanner, yymsgp);
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
		  yystos[yystate], yyvsp, scanner);
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
  yyerror (scanner, YY_("memory exhausted"));
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
                  yytoken, &yylval, scanner);
    }
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


/* Line 2055 of yacc.c  */
#line 1544 "giscanner/scannerparser.y"

static void
yyerror (GISourceScanner *scanner, const char *s)
{
  /* ignore errors while doing a macro scan as not all object macros
   * have valid expressions */
  if (!scanner->macro_scan)
    {
      fprintf(stderr, "%s:%d: %s in '%s' at '%s'\n",
	      g_file_get_parse_name (scanner->current_file), lineno, s, linebuf, yytext);
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
pass_line (FILE * f, int c,
           FILE *out)
{
  while (c != EOF && c != '\n')
    {
      if (out)
        fputc (c, out);
      c = fgetc (f);
    }
  if (c == '\n')
    {
      if (out)
        fputc (c, out);
      c = fgetc (f);
      if (c == ' ' || c == '\t')
        {
          c = eat_hspace (f);
        }
    }
  return c;
}

static int
eat_line (FILE * f, int c)
{
  return pass_line (f, c, NULL);
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
  GList *l;
  g_unlink (tmp_name);

  for (l = filenames; l != NULL; l = l->next)
    {
      FILE *f = fopen (l->data, "r");
      int line = 1;

      GString *define_line;
      char *str;
      gboolean error_line = FALSE;
      gboolean end_of_word;
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
          end_of_word = (c == ' ' || c == '\t' || c == '\n' || c == EOF);
          if (end_of_word &&
              (g_str_equal (str, "if") ||
               g_str_equal (str, "endif") ||
               g_str_equal (str, "ifndef") ||
               g_str_equal (str, "ifdef") ||
               g_str_equal (str, "else") ||
               g_str_equal (str, "elif")))
            {
              fprintf (fmacros, "#%s ", str);
              g_free (str);
              c = pass_line (f, c, fmacros);
              line++;
              continue;
            }
          else if (strcmp (str, "define") != 0 || !end_of_word)
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
  lineno = 1;
  yyin = fopen (filename, "r");

  while (yylex (scanner) != YYEOF)
    ;

  fclose (yyin);

  return TRUE;
}
