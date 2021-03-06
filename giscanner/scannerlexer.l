/* -*- Mode: C -*-
 * GObject introspection: C lexer
 *
 * Copyright (c) 1997 Sandro Sigala  <ssigala@globalnet.it>
 * Copyright (c) 2007-2008 Jürg Billeter  <j@bitron.ch>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

%{
#include <ctype.h>
#include <stdio.h>

#include <glib.h>
#include "sourcescanner.h"
#include "scannerparser.h"
#include "grealpath.h"

int lineno;
char linebuf[2000];

#undef YY_BUF_SIZE
#define YY_BUF_SIZE 1048576

extern int yylex (GISourceScanner *scanner);
#define YY_DECL int yylex (GISourceScanner *scanner)
static int yywrap (void);
static void parse_comment (GISourceScanner *scanner);
static void process_directive (GISourceScanner *scanner);
static int check_identifier (GISourceScanner *scanner, const char *);
static int parse_ignored_macro (void);
%}

%option nounput

intsuffix				([uU][lL]?[lL]?)|([lL][lL]?[uU]?)
fracconst				([0-9]*\.[0-9]+)|([0-9]+\.)
exppart					[eE][-+]?[0-9]+
floatsuffix				[fFlL]
chartext				([^\\\'])|(\\.) 
stringtext				([^\\\"])|(\\.)

%%

\n.*					{ strncpy(linebuf, yytext+1, sizeof(linebuf)); /* save the next line */
						linebuf[sizeof(linebuf)-1]='\0';
						/* printf("%4d:%s\n",lineno,linebuf); */
						yyless(1);      /* give back all but the \n to rescan */
						++lineno;
					}
"\\\n"					{ ++lineno; }
[\t\f\v\r ]+				{ /* Ignore whitespace. */ }

"/*"					{ parse_comment(scanner); }
"//".*					{ }

"#define "[a-zA-Z_][a-zA-Z_0-9]*"("	{ yyless (yyleng - 1); return FUNCTION_MACRO; }
"#define "[a-zA-Z_][a-zA-Z_0-9]*	{ return OBJECT_MACRO; }

"#"					{ process_directive(scanner); }

"{"					{ return '{'; }
"<%"					{ return '{'; }
"}"					{ return '}'; }
"%>"					{ return '}'; }
"["					{ return '['; }
"<:"					{ return '['; }
"]"					{ return ']'; }
":>"					{ return ']'; }
"("					{ return '('; }
")"					{ return ')'; }
";"					{ return ';'; }
":"					{ return ':'; }
"..."					{ return ELLIPSIS; }
"?"					{ return '?'; }
"."					{ return '.'; }
"+"					{ return '+'; }
"-"					{ return '-'; }
"*"					{ return '*'; }
"/"					{ return '/'; }
"%"					{ return '%'; }
"^"					{ return '^'; }
"&"					{ return '&'; }
"|"					{ return '|'; }
"~"					{ return '~'; }
"!"					{ return '!'; }
"="					{ return '='; }
"<"					{ return '<'; }
">"					{ return '>'; }
"+="					{ return ADDEQ; }
"-="					{ return SUBEQ; }
"*="					{ return MULEQ; }
"/="					{ return DIVEQ; }
"%="					{ return MODEQ; }
"^="					{ return XOREQ; }
"&="					{ return ANDEQ; }
"|="					{ return OREQ; }
"<<"					{ return SL; }
">>"					{ return SR; }
"<<="					{ return SLEQ; }
">>="					{ return SREQ; }
"=="					{ return EQ; }
"!="					{ return NOTEQ; }
"<="					{ return LTEQ; }
">="					{ return GTEQ; }
"&&"					{ return ANDAND; }
"||"					{ return OROR; }
"++"					{ return PLUSPLUS; }
"--"					{ return MINUSMINUS; }
","					{ return ','; }
"->"					{ return ARROW; }

"__asm" 	        	        { if (!parse_ignored_macro()) REJECT; }
"__asm__" 	        	        { if (!parse_ignored_macro()) REJECT; }
"__attribute__" 		        { if (!parse_ignored_macro()) REJECT; }
"__attribute" 		                { if (!parse_ignored_macro()) REJECT; }
"__const"                               { return CONST; }
"__extension__"                         { return EXTENSION; }
"__inline"				{ return INLINE; }
"__nonnull" 			        { if (!parse_ignored_macro()) REJECT; }
"__signed__"				{ return SIGNED; }
"__restrict"				{ return RESTRICT; }
"__typeof"				{ if (!parse_ignored_macro()) REJECT; }
"_Bool"					{ return BOOL; }

[a-zA-Z_][a-zA-Z_0-9]*			{ if (scanner->macro_scan) return IDENTIFIER; else REJECT; }

"asm"           		        { if (!parse_ignored_macro()) REJECT; }
"auto"					{ return AUTO; }
"break"					{ return BREAK; }
"case"					{ return CASE; }
"char"					{ return CHAR; }
"const"					{ return CONST; }
"continue"				{ return CONTINUE; }
"default"				{ return DEFAULT; }
"do"					{ return DO; }
"double"				{ return DOUBLE; }
"else"					{ return ELSE; }
"enum"					{ return ENUM; }
"extern"				{ return EXTERN; }
"float"					{ return FLOAT; }
"for"					{ return FOR; }
"goto"					{ return GOTO; }
"if"					{ return IF; }
"inline"				{ return INLINE; }
"int"					{ return INT; }
"long"					{ return LONG; }
"register"				{ return REGISTER; }
"restrict"				{ return RESTRICT; }
"return"				{ return RETURN; }
"short"					{ return SHORT; }
"signed"				{ return SIGNED; }
"sizeof"				{ return SIZEOF; }
"static"				{ return STATIC; }
"struct"				{ return STRUCT; }
"switch"				{ return SWITCH; }
"typedef"				{ return TYPEDEF; }
"union"					{ return UNION; }
"unsigned"				{ return UNSIGNED; }
"void"					{ return VOID; }
"volatile"				{ return VOLATILE; }
"while"					{ return WHILE; }

[a-zA-Z_][a-zA-Z_0-9]*			{ return check_identifier(scanner, yytext); }

"0"[xX][0-9a-fA-F]+{intsuffix}?		{ return INTEGER; }
"0"[0-7]+{intsuffix}?			{ return INTEGER; }
[0-9]+{intsuffix}?			{ return INTEGER; }

{fracconst}{exppart}?{floatsuffix}?	{ return FLOATING; }
[0-9]+{exppart}{floatsuffix}?		{ return FLOATING; }

"'"{chartext}*"'"			{ return CHARACTER; }
"L'"{chartext}*"'"			{ return CHARACTER; }

"\""{stringtext}*"\""			{ return STRING; }
"L\""{stringtext}*"\""			{ return STRING; }

.					{ if (yytext[0]) fprintf(stderr, "%s:%d: unexpected character `%c'\n", scanner->current_filename, lineno, yytext[0]); }

%%

static int
yywrap (void)
{
  return 1;
}


static void
parse_comment (GISourceScanner *scanner)
{
  GString *comment;
  int c1, c2;

  c1 = input();
  c2 = input();

  comment = g_string_new ("");

  while (c2 != EOF && !(c1 == '*' && c2 == '/'))
    {
      g_string_append_c (comment, c1);

      if (c1 == '\n')
        lineno++;

      c1 = c2;
      c2 = input();

    }

  scanner->comments = g_slist_prepend (scanner->comments,
                                       g_string_free (comment, FALSE));
}

static int
check_identifier (GISourceScanner *scanner,
		  const char  *s)
{
	/*
	 * This function checks if `s' is a type name or an
	 * identifier.
	 */

	if (gi_source_scanner_is_typedef (scanner, s)) {
		return TYPEDEF_NAME;
	} else if (strcmp (s, "__builtin_va_list") == 0) {
		return TYPEDEF_NAME;
	}

	return IDENTIFIER;
}

static void
process_directive (GISourceScanner *scanner)
{
	/* extract current filename from #line directives */
	GString *filename_builder;
	gboolean in_string, found_filename;

	lineno = 0;
	found_filename = FALSE;
	in_string = FALSE;
	filename_builder = g_string_new ("");

	int c = input ();
	while (c != EOF && c != '\n') {
		if (!in_string) {
			if (c == '\"') {
				in_string = TRUE;
				found_filename = TRUE;
			} else if (c >= '0' && c <= '9') {
				if (!found_filename) {
					lineno = lineno * 10 + (c - '0');
				}
			}
		} else {
			if (c == '\"') {
				in_string = FALSE;
			} else if (c == '\\') {
				g_string_append_c (filename_builder, c);
				c = input ();
				g_string_append_c (filename_builder, c);
			} else {
				g_string_append_c (filename_builder, c);
			}
		}
		c = input ();
	}

	if (filename_builder->len > 0) {
		char *filename = g_strcompress (filename_builder->str);
		if (g_realpath (filename))
		  {
		    g_free (scanner->current_filename);
		    scanner->current_filename = g_realpath (filename);
		    g_assert (scanner->current_filename);
		    g_free(filename);
		  }
	}

	g_string_free (filename_builder, TRUE);
}

/*
 * This parses a macro which is ignored, such as
 * __attribute__((x)) or __asm__ (x)
 */
static int
parse_ignored_macro (void)
{
	int c;
	int nest;

	while ((c = input ()) != EOF && isspace (c))
		;
	if (c != '(')
		return FALSE;

	nest = 0;
	while ((c = input ()) != EOF && (nest > 0 || c != ')')) {
		if (c == '(')
			nest++;
		else if (c == ')')
			nest--;
		else if (c == '"') {
			while ((c = input ()) != EOF && c != '"') {
				if (c == '\\')
					c = input ();
			}
		} else if (c == '\'') {
			c = input ();
			if (c == '\\')
				c = input ();
			else if (c == '\'')
				return FALSE;
			c = input ();
			if (c != '\'')
				return FALSE;
		} else if (c == '\n')
			lineno++;
	}

	return TRUE;
}
