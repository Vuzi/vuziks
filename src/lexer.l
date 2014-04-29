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
	#include "str/str.h"

	#include "parser.h"

	// Affichage erreur
	void beginToken(const char *t);
	void beginTokenNewLine();

	unsigned int inside;
	char show_prompt;

	// Redéfinition de la fonction de lecture de yacc (basé sur celle générée)
	#undef  YY_INPUT
	#define YY_INPUT(buf,result,max_size) \
		if ( YY_CURRENT_BUFFER_LVALUE->yy_is_interactive ) { \
			int c = '*'; size_t n; \
			if(show_prompt) \
				if(p.verbose) fputs("[*] Enter any statement\n", stdout); \
			if(!inside) { \
				fputs(" > ", stdout); \
				show_prompt = 1; \
			} else { \
				fputs("|> ", stdout); \
				for(n = 0; n < inside; n++) \
					 fputs("__", stdout); \
			} \
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

newline   "\n"|"\r"|"\r\n"

chiffre   [0-9]
entier    {chiffre}+
exposant  [eE][+-]?{entier}

reel      {entier}?("."?{entier}){exposant}?

char      [_a-zA-Z]
var       {char}({char}|{chiffre})*

string    "\""(\\.|[^"])*"\""|"\'"(\\.|[^'])*"\'"'

/* règles */
%x IN_COMMENT
%x IN_COMMENT_LINE

%%

<INITIAL>{

"<#"              { BEGIN(IN_COMMENT); }
"#"               { BEGIN(IN_COMMENT_LINE); }

{blanc}           { beginToken(yytext); }

{reel}            { yylval.value = atof(yytext);
		        	beginToken(yytext); return(NUMBER);
		          }

(?i:true)         { beginToken(yytext); yylval.bool = 1; return(BOOL); }
(?i:false)	      { beginToken(yytext); yylval.bool = 0; return(BOOL); }

{string} 		  { beginToken(yytext);
					yytext++; yytext[strlen(yytext) - 1] = '\0';
	                yylval.str = str_copy(yytext); 
	                return(STRING); }

(?i:nonexistent)  { beginToken(yytext); yylval.type = T_NONEXISTENT; return(TYPE); }
(?i:undefined)    { beginToken(yytext); yylval.type = T_NONEXISTENT; return(TYPE); }

(?i:null)         { beginToken(yytext); yylval.type = T_NULL; return(TYPE); }

(?i:num(ber)?)    { beginToken(yytext); yylval.type = T_NUM; return(TYPE); }
(?i:digit(al)?)   { beginToken(yytext); yylval.type = T_NUM; return(TYPE); }

(?i:bool(ean)?)   { beginToken(yytext); yylval.type = T_BOOL; return(TYPE); }

(?i:unit)         { beginToken(yytext); yylval.type = T_FUNCTION; return(TYPE); }

(?i:object)       { beginToken(yytext); yylval.type = T_OBJECT; return(TYPE); }

(?i:list)         { beginToken(yytext); yylval.type = T_LINKEDLIST; return(TYPE); }

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
"["               { beginToken(yytext); return(BRACKET_LEFT); }
"]"               { beginToken(yytext); return(BRACKET_RIGHT); }

(?i:and)	      { beginToken(yytext); return(AND); }
(?i:or)   	      { beginToken(yytext); return(OR); }

"^"		          { beginToken(yytext); return(POW); }
"."		          { beginToken(yytext); return(POINT); }
"@"|"&"		      { beginToken(yytext); return(ADDR); }
  
(?i:new)	      { beginToken(yytext); return(NEW); }
(?i:delete)       { beginToken(yytext); return(DELETE); }
(?i:var)	      { beginToken(yytext); return(VAR); }
(?i:attr)    	  { beginToken(yytext); return(ATTR); }

(?i:dump)   	  { beginToken(yytext); return(DUMP); }

(?i:return)       { beginToken(yytext); return(RETURN); }
(?i:break)  	  { beginToken(yytext); return(BREAK); }

(?i:typeof)  	  { beginToken(yytext); return(TYPEOF); }
(?i:is)  	      { beginToken(yytext); return(IS); }

(?i:if)           { beginToken(yytext); return(IF); }
(?i:else)         { beginToken(yytext); return(ELSE); }
(?i:for)          { beginToken(yytext); return(FOR); }
(?i:while)        { beginToken(yytext); return(WHILE); }
(?i:loop)         { beginToken(yytext); return(LOOP); }

(?i:function)	  { beginToken(yytext); return(FUNCTION); }
 
"("		          { beginToken(yytext); return(P_LEFT); }
")"		          { beginToken(yytext); return(P_RIGHT); }

"{"		          { beginToken(yytext); inside++; show_prompt = 0; return(BRACE_LEFT); }
"}" 	          { beginToken(yytext); inside--; return(BRACE_RIGHT); }

";"               { beginToken(yytext); return(EXPR_END); }
","               { beginToken(yytext); return(COMMA); }

{var}             { yylval.str = str_copy(yytext);
					beginToken(yytext); return(IDENTIFIER);
				  }

{newline}         { yylineno++; beginTokenNewLine(); /*if(p.interactive_mod) return(NEW_LINE);*/ }

.                 { beginToken(yytext); 
	                printf("[!] Unkown symbol read : '%s'\n", yytext);
	              }

}

<IN_COMMENT>{
"#>"              { BEGIN(INITIAL); }
[^#\n]+
"#"
\n                { yylineno++; } 
}

<IN_COMMENT_LINE>{
"\n"              { yylineno++; BEGIN(INITIAL); }
<<EOF>>           { BEGIN(INITIAL); }
.+
}
