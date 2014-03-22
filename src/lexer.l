%option noyywrap
%option nounput
%option noinput
%{
	
	#include <stdio.h>
	#include <stdlib.h>

	#include "constant.h"

	#include "variableOp.h"
	#include "operation.h"
	#include "unit.h"
	#include "debug.h"

	#include "hash/hash.h"

	#include "parser.h"

	// Affichage erreur
	void beginToken(const char *t);
	void beginTokenNewLine();

	// Redéfinition de la fonction de lecture de yacc (basé sur celle générée)
	#undef  YY_INPUT
	#define YY_INPUT(buf,result,max_size) \
		if ( YY_CURRENT_BUFFER_LVALUE->yy_is_interactive ) { \
			int c = '*'; size_t n; \
			fputs("[*] Enter any statement\n> ", stdout); \
			for ( n = 0; \
				  n < max_size && (c = getc( yyin )) != EOF && c != '\n'; \
				  ++n ) \
				buf[n] = (char) c; \
			if ( c == '\n' ) { \
				if( (n > 0 && buf[n-1] != ';') || n == 0) \
					buf[n++] = (char) c; \
			} \
			if ( c == EOF && ferror( yyin ) ) \
				YY_FATAL_ERROR( "input in flex scanner failed" ); \
			result = n; \
		} else { \
			errno=0; \
			while ( (result = fread(buf, 1, max_size, yyin))==0 && ferror(yyin)) { \
				if( errno != EINTR) { \
					YY_FATAL_ERROR( "input in flex scanner failed" ); \
					break; \
				} \
				errno=0; \
				clearerr(yyin); \
			} \
		}

%}

blanc     [ \t]+

chiffre   [0-9]
entier    {chiffre}+
exposant  [eE][+-]?{entier}

reel      {entier}?("."?{entier}){exposant}?

char      [_a-zA-Z]
var       {char}({char}|{chiffre})*

%%

{blanc}           { /* Rien */ }

{reel}            { yylval.value = atof(yytext);
		        	beginToken(yytext); return(NUMBER);
		          }

"="               { beginToken(yytext); return(EQUAL); }

"+"		          { beginToken(yytext); return(PLUS); }
"-"		          { beginToken(yytext); return(MINUS); }

"*"		          { beginToken(yytext); return(STAR); }
"/"		          { beginToken(yytext); return(SLASH); }
":"		          { beginToken(yytext); return(DIV); }
"%"	              { beginToken(yytext); return(MODULO); }

"?"	              { beginToken(yytext); return(EXIST); }
"!"	              { beginToken(yytext); return(NOT); }
">"	              { beginToken(yytext); return(MORE); }
"<"	              { beginToken(yytext); return(LESS); }
">="	          { beginToken(yytext); return(MORE_E); }
"<="	          { beginToken(yytext); return(LESS_E); }
"=="	          { beginToken(yytext); return(D_EQUAL); }
"!="	          { beginToken(yytext); return(DIF); }
"==="	          { beginToken(yytext); return(T_EQUAL); }

"and"|"AND"	      { beginToken(yytext); return(AND); }
"or"|"OR"	      { beginToken(yytext); return(OR); }

"true"|"TRUE"     { beginToken(yytext); yylval.bool = 1; return(BOOL); }
"false"|"FALSE"	  { beginToken(yytext); yylval.bool = 0; return(BOOL); }

"^"		          { beginToken(yytext); return(POW); }
"."		          { beginToken(yytext); return(POINT); }
"@"|"&"		      { beginToken(yytext); return(ADDR); }
  
"new"|"NEW"	      { beginToken(yytext); return(NEW); }
"delete"|"DELETE" { beginToken(yytext); return(DELETE); }
"var"|"VAR"	      { beginToken(yytext); return(VAR); }
"attr"|"ATTR"	  { beginToken(yytext); return(ATTR); }

"dump"|"DUMP"	  { beginToken(yytext); return(DUMP); }

"return"|"RETURN" { beginToken(yytext); return(RETURN); }
"break"|"BREAK"	  { beginToken(yytext); return(BREAK); }
 
"("		          { beginToken(yytext); return(P_LEFT); }
")"		          { beginToken(yytext); return(P_RIGHT); }

";"|"\n"          { beginToken(yytext); return(EXPR_END); }

{var}             { yylval.str = strdup(yytext);
					beginToken(yytext); return(IDENTIFIER);
				  }
