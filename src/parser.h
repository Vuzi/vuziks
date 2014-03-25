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
     PLUS = 260,
     MINUS = 261,
     STAR = 262,
     SLASH = 263,
     DIV = 264,
     POW = 265,
     EQUAL = 266,
     POINT = 267,
     ADDR = 268,
     MODULO = 269,
     MORE = 270,
     LESS = 271,
     MORE_E = 272,
     LESS_E = 273,
     AND = 274,
     OR = 275,
     NOT = 276,
     EXIST = 277,
     D_EQUAL = 278,
     T_EQUAL = 279,
     DIF = 280,
     P_LEFT = 281,
     P_RIGHT = 282,
     BRACE_LEFT = 283,
     BRACE_RIGHT = 284,
     COMMA = 285,
     VAR = 286,
     ATTR = 287,
     NEW = 288,
     DELETE = 289,
     IDENTIFIER = 290,
     FUNCTION = 291,
     DUMP = 292,
     EXPR_END = 293,
     BREAK = 294,
     RETURN = 295,
     POS = 296,
     NEG = 297,
     ADDR_ACCESS = 298
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2058 of yacc.c  */
#line 45 "parser.y"

  Unit* function;
  Linked_list* list;
  Operation* op;
  Unit *u;
  char *str;
  float value;
  char bool;


/* Line 2058 of yacc.c  */
#line 111 "parser.tab.h"
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
