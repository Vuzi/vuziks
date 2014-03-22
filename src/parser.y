%{
	#define YYERROR_VERBOSE

	#include <stdio.h>
	#include <stdlib.h>


	#include "variableOp.h"
	#include "operation.h"
	#include "unit.h"
	#include "debug.h"

	#include "hash/hash.h"
	#include "init/params.h"
	#include "constant.h"

	#include "parser.h"

	// Valeurs externes
	extern char *yytext;
	extern int yylineno;

	// Prototypes
	int yylex(void);
	int yyerror(const char *s);

	// Affichage erreur
	void beginToken(const char *t);
	void beginTokenNewLine();

	// Context courant
	Exec_context ec_tmp, ec_obj;
	Variable r_base, *r;
	
	// Variables locales
	static int goodbye = 0;

	static int tokenStart = 0;
	static int tokenLength = 0;

%}

%union {
  Operation *op;
  Unit *u;
  char *str;
  float value;
  char bool;
};

// Liste des terminaux pouvant être rencontrés
%token NUMBER BOOL
%token PLUS MINUS STAR SLASH DIV POW EQUAL POINT ADDR MODULO MORE LESS MORE_E LESS_E AND OR NOT EXIST D_EQUAL T_EQUAL DIF
%token P_LEFT P_RIGHT
%token COMMA
%token VAR ATTR NEW DELETE
%token IDENTIFIER
%token DUMP
%token EXPR_END

// Opérateur par ordre croissant de priorité
%left  RETURN BREAK                            // Mot clef return et break, évalués en dernier
%right DUMP                                    // Affichage de variable
%right EQUAL                                   // Affectation de variable
%left  COMMA                                   // Création de liste chainées

%left  OR AND                                  // Opérations de test logique, plus prioritaire que les opération logiques pour les rendre plus simple ( 'a<b or b>c' )
%left  DIF D_EQUAL T_EQUAL                     // Opérations logiques d'égalitées
%left  MORE LESS MORE_E LESS_E                 // Opérations logiques, plus prioritaire que les maths pour rendre plus simple ( '1+2 < 3'  par exemple)
%left  PLUS MINUS                              // Opérations mathématiques les moins prioritaires
%left  STAR SLASH DIV MODULO                   // Opérations mathématiques prioritaires

%right POW                                     // Puissance, supérieur aux opérations maths
%left  NEG POS                                 // Moins et Plus unaire, prioritaire sur les autres opérateurs
%left  NOT EXIST                               // Inversion logique & testeur d'existence
%left  POINT                                   // Opérateur d'accès, prioritaire sur les opérations mathématiques et logiques
%left  VAR ATTR                                // Nouvelle valeur
%left  P_LEFT P_RIGHT                          // Parenthèses
%left  ADDR ADDR_ACCESS                        // Accès valeurs et accès référence, priorité max en dessous de VAR
%left  IDENTIFIER                              // Accès variable, priorité max

// Type utilisé dans l'union suivant le type de terminal rencontré
%type <op>    RETURN BREAK EQUAL PLUS MINUS STAR SLASH DIV MODULO MORE LESS MORE_E LESS_E D_EQUAL T_EQUAL POW NEG POS POINT VAR ATTR NEW P_LEFT P_RIGHT ADDR ADDR_ACCESS Expression Function Statement
%type <str>   IDENTIFIER
%type <value> NUMBER
%type <bool>  BOOL

// Par où on commence
%start Input
%%

Input:
	  /* Vide */
	| Input Statement
	;

Statement:
	  EXPR_END {
			puts("[!] Empty statement\n");
			beginTokenNewLine();
	  }
	| Expression EXPR_END {
		// Initialisation valeur retour
		var_init_loc(&r_base, NULL, 0, T_NULL);
		r_base.deletable = 0;
		r = &r_base;

		if(p->show_operation) {
			puts("[>] Result in memory :"), op_dump($1);
			fputs("[*] Press enter to eval", stdout);
			getchar();
		}

		// Evaluation
		puts("\n[<] Evaluating the operations ...");
		switch(op_eval($1, &ec_obj, &ec_tmp, &r)) {
			case RC_WARNING :
				err_display_last(&e);
			case RC_BREAK :
			case RC_OK :
				break;
			case RC_ERROR :
				err_display_last(&e);
				break;
			case RC_CRITICAL:
				err_display_last(&e);
				printf("[x] Error, interpreter stopped with code %x \n", e.type);
				return e.type;
			case RC_RETURN :
				if(r->type == T_NUM)
					goodbye = (int)r->value.v_num;
				printf("[i] Interpreter stopped (%x) \n", goodbye);
				exit(goodbye);
			default:
				break;
		}

		puts("[<] Evaluation done");

		if(p->auto_dump) {
			puts("\n[>] Statement value :");
			var_dump(r);
		}

		// Suppression valeur temporaire
		var_delete(&r_base);
		beginTokenNewLine();
		puts("");
	}
	;

Function:
	  Expression P_LEFT Expression P_RIGHT {                       // Appel d'unit comme fonction (OP_UNIT_CALL)
	  	$$ = op_new(OP_UNIT_CALL, $1, $3, NULL);
	  }
	| Expression P_LEFT P_RIGHT {                                  // Appel d'unit comme fonction (OP_UNIT_CALL)
	  	$$ = op_new(OP_UNIT_CALL, $1, NULL, NULL);
	  }
	  ;

Expression:
	  Expression EQUAL Expression {                                // Affectation (OP_ASSIGN)
	  	$$ = op_new(OP_ASSIGN, $1, $3, NULL);
	  }
	| NUMBER {                                                     // Nombre (OP_VALUE)
	  	$$ = op_new(OP_VALUE, NULL, NULL, var_new(NULL, 0, T_NUM));
	  	$$->value->value.v_num = $1;
	  }
	| BOOL {                                                       // Booléen (OP_VALUE)
	  	$$ = op_new(OP_VALUE, NULL, NULL, var_new(NULL, 0, T_BOOL));
	  	$$->value->value.v_bool = $1;
	  }
	| Expression POINT IDENTIFIER {                                // Accès a une variable membre (OP_ATTR_ACCESS)
	  	$$ = op_new(OP_ATTR_ACCESS, $1, NULL, NULL);
	  	$$->info.val = $3;
	  	$$->info.val_h = str_hash($3);
	  }
	| NEW VAR IDENTIFIER {                                         // Création d'une variable temporaire (OP_DEC_VAR)
		$$ = op_new(OP_DEC_VAR, NULL, NULL, NULL);
	  	$$->info.val = $3;
	  	$$->info.val_h = str_hash($3);
	  }
	| NEW ATTR IDENTIFIER {                                        // Création d'une variable membre (OP_DEC_ATTR)
		$$ = op_new(OP_DEC_ATTR, NULL, NULL, NULL);
	  	$$->info.val = $3;
	  	$$->info.val_h = str_hash($3);
	  }
	| DELETE VAR IDENTIFIER {                                      // Création d'une variable temporaire (OP_DEC_VAR)
		$$ = op_new(OP_DELETE_VAR, NULL, NULL, NULL);
	  	$$->info.val = $3;
	  	$$->info.val_h = str_hash($3);
	  }
	| DELETE ATTR IDENTIFIER {                                     // Création d'une variable membre (OP_DEC_ATTR)
		$$ = op_new(OP_DELETE_ATTR, NULL, NULL, NULL);
	  	$$->info.val = $3;
	  	$$->info.val_h = str_hash($3);
	  }
	| P_LEFT Expression P_RIGHT {                                  // Parenthèses, uniquement utile aux prioritées
		$$ = $2;
	  }
	| Function {                                                   // Appel d'unit comme fonction (OP_UNIT_CALL)
	  	$$ = $1;
	  }
	| NEW Function {                                               // Appel d'unit comme constructeur (OP_UNIT_NEW)
	  	$$ = $2;
	  	$$->type = OP_UNIT_NEW;
	  }/*
	| Expression COMMA Expression {                                // a,a construction liste chainée (OP_COMMA)
	  	$$ = op_new(OP_COMMA, $1, $3, NULL);
	  }*/
	| IDENTIFIER {                                                 // Accès à une variable (OP_ACCES)
	  	$$ = op_new(OP_ACCES, NULL, NULL, NULL);
	  	$$->info.val = $1;
	  	$$->info.val_h = str_hash($1);
	  }
	| ADDR Expression {                                            // Adresse d'une variable (OP_REF_GET)
	  	$$ = op_new(OP_REF_GET, $2, NULL, NULL);
	  }
	| STAR Expression %prec ADDR_ACCESS {                          // Variable à l'adresse de VAR (OP_REF_ACCESS)
	  	$$ = op_new(OP_REF_ACCESS, $2, NULL, NULL);
	  }
	| Expression POW Expression {                                  // Puissance (OP_MATH_POW)
	  	$$ = op_new(OP_MATH_POW, $1, $3, NULL);
	  }
	| Expression PLUS Expression {                                 // Addition (OP_MATH_PLUS)
	  	$$ = op_new(OP_MATH_PLUS, $1, $3, NULL);
	  }
	| Expression MINUS Expression {                                // Soustraction (OP_MATH_MINUS)
	  	$$ = op_new(OP_MATH_MINUS, $1, $3, NULL);
	  }
	| Expression STAR Expression {                                 // Multiplication (OP_MATH_MULT)
	  	$$ = op_new(OP_MATH_MULT, $1, $3, NULL);
	  }
	| Expression SLASH Expression {                                // Division (OP_MATH_DIV)
	  	$$ = op_new(OP_MATH_DIV, $1, $3, NULL);
	  }
	| Expression DIV Expression {                                  // Division entière (OP_MATH_INTDIV)
	  	$$ = op_new(OP_MATH_INTDIV, $1, $3, NULL);
	  }
	| Expression MODULO Expression {                               // Modulo (OP_MATH_MODULO)
	  	$$ = op_new(OP_MATH_MODULO, $1, $3, NULL);
	  }
	| MINUS Expression %prec POS {                                 // Moins unaire (OP_MATH_M_UNARY)
	  	$$ = op_new(OP_MATH_M_UNARY, $2, NULL, NULL);
	  }
	| PLUS Expression %prec NEG {                                  // Plus unaire (OP_MATH_P_UNARY)
	  	$$ = op_new(OP_MATH_P_UNARY, $2, NULL, NULL);
	  }
	| Expression MORE Expression {                                 // Supérieur (OP_LOG_GT)
	  	$$ = op_new(OP_LOG_GT, $1, $3, NULL);
	  }
	| Expression LESS Expression {                                 // inférieur (OP_LOG_LT)
		$$ = op_new(OP_LOG_LT, $1, $3, NULL);
	  }
	| Expression MORE_E Expression {                               // Supérieur ou égal (OP_LOG_GE)
	  	$$ = op_new(OP_LOG_GE, $1, $3, NULL);
	  }
	| Expression LESS_E Expression {                               // Supérieur (OP_LOG_LE)
	  	$$ = op_new(OP_LOG_LE, $1, $3, NULL);
	  }
	| Expression D_EQUAL Expression {                              // Egalité (OP_LOG_EQ)
	  	$$ = op_new(OP_LOG_EQ, $1, $3, NULL);
	  }
	| Expression T_EQUAL Expression {                              // Egalité de type (OP_LOG_TYPE)
		$$ = op_new(OP_LOG_TYPE, $1, $3, NULL);
	  }
	| Expression DIF Expression {                                  // Différence (OP_LOG_DIF)
	  	$$ = op_new(OP_LOG_DIF, $1, $3, NULL);
	  }
	| Expression AND Expression {                                  // ET (OP_LOG_AND)
	  	$$ = op_new(OP_LOG_AND, $1, $3, NULL);
	  }
	| Expression OR Expression {                                   // OU (OP_LOG_OR)
	  	$$ = op_new(OP_LOG_OR, $1, $3, NULL);
	  }
	| NOT Expression {                                             // Inversion logique (OP_LOG_NOT)
	  	$$ = op_new(OP_LOG_NOT, $2, NULL, NULL);
	  }
	| EXIST Expression {                                           // Test existance (OP_LOG_EXIST)
	  	$$ = op_new(OP_LOG_EXIST, $2, NULL, NULL);
	  }
	| RETURN Expression {                                          // Return (OP_RETURN)
	  	$$ = op_new(OP_RETURN, $2, NULL, NULL);
	  }
	| RETURN {                                                     // Return (seul) (OP_RETURN)
	  	$$ = op_new(OP_RETURN, NULL, NULL, NULL);
	  }
	| BREAK {                                                      // Break (OP_BREAK)
	  	$$ = op_new(OP_BREAK, NULL, NULL, NULL);
	  }
	| DUMP Expression {                                            // Dump (OP_OUTPUT_VAR_DUMP)	  	
		$$ = op_new(OP_OUTPUT_VAR_DUMP, $2, NULL, NULL);
	  }
	;

%%

int yyerror(const char *s) {
	int start = tokenStart;
	int i;

	fputs("..", stdout);
    for (i = 1; i < start; i++)
    	putc('.', stdout);
    puts("^");

  	printf("[x] Error | %d: %s: '%s'\n", yylineno, s, yytext);
  	
  	return 0;
}

void beginToken(const char *t) {
	// Avant le token
	tokenStart += tokenLength;
	// Longueur du token
	tokenLength = strlen(t);
}

void beginTokenNewLine() {
	tokenStart = 0;
	tokenLength = 0;
}

int main(int argc, char **argv) {

	params_init();
	params_make(argc, argv);

	if(p->interactive_mod) {
		ec_init_loc(&ec_obj);
		ec_init_loc(&ec_tmp);
		yyparse();
	} else {
		puts("[i] Only the interactive mode is now working");
	}
	return 0;
}

