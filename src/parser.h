/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
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

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
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
     NUMBER = 258,
     BOOL = 259,
     TYPE = 260,
     STRING = 261,
     PLUS = 262,
     MINUS = 263,
     STAR = 264,
     SLASH = 265,
     DIV = 266,
     POW = 267,
     EQUAL = 268,
     POINT = 269,
     ADDR = 270,
     MODULO = 271,
     MORE = 272,
     LESS = 273,
     MORE_E = 274,
     LESS_E = 275,
     AND = 276,
     OR = 277,
     NOT = 278,
     EXIST = 279,
     D_EQUAL = 280,
     T_EQUAL = 281,
     DIF = 282,
     P_LEFT = 283,
     P_RIGHT = 284,
     BRACE_LEFT = 285,
     BRACE_RIGHT = 286,
     BRACKET_LEFT = 287,
     BRACKET_RIGHT = 288,
     COMMA = 289,
     VAR = 290,
     ATTR = 291,
     NEW = 292,
     DELETE = 293,
     TYPEOF = 294,
     IS = 295,
     IDENTIFIER = 296,
     FUNCTION = 297,
     IF = 298,
     ELSE = 299,
     FOR = 300,
     WHILE = 301,
     LOOP = 302,
     DUMP = 303,
     EXPR_END = 304,
     NEW_LINE = 305,
     BREAK = 306,
     RETURN = 307,
     POS = 308,
     NEG = 309,
     ADDR_ACCESS = 310
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2058 of yacc.c  */
#line 55 "parser.y"

  Unit_conditional *condition;
  Unit_loop *loop;
  Unit* function;
  Linked_list* list;
  Operation* op;
  Unit *u;
  language_type type;
  char *str;
  float value;
  char bool;


/* Line 2058 of yacc.c  */
#line 126 "parser.tab.h"
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
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
