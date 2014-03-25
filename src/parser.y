%{
	#define YYERROR_VERBOSE
	#define YYDEBUG 1

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
	extern char* yytext;
	extern FILE* yyin;
	extern int yylineno;

	// Prototypes
	int yylex(void);
	int yyerror(const char *s);

	// Affichage erreur
	void beginToken(const char *t);
	void beginTokenNewLine();

	// Context courant pour le mode interactif
	Exec_context ec_tmp, ec_obj;
	Variable r_base, *r;
	
	// Variables locales
	static int goodbye = 0;

	static int tokenStart = 0;
	static int tokenLength = 0;

%}

%union {
  Unit* function;
  Linked_list* list;
  Operation* op;
  Unit *u;
  char *str;
  float value;
  char bool;
};

// Liste des terminaux pouvant être rencontrés
%token NUMBER BOOL
%token PLUS MINUS STAR SLASH DIV POW EQUAL POINT ADDR MODULO MORE LESS MORE_E LESS_E AND OR NOT EXIST D_EQUAL T_EQUAL DIF
%token P_LEFT P_RIGHT BRACE_LEFT BRACE_RIGHT
%token COMMA
%token VAR ATTR NEW DELETE
%token IDENTIFIER FUNCTION
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
%type <function> Function
%type <list>     Statements Unit Param_list Param_call_list
%type <op>       RETURN BREAK EQUAL PLUS MINUS STAR SLASH DIV MODULO MORE LESS MORE_E LESS_E D_EQUAL T_EQUAL POW NEG POS POINT VAR ATTR NEW P_LEFT P_RIGHT ADDR ADDR_ACCESS Expression Statement
%type <str>      IDENTIFIER
%type <value>    NUMBER
%type <bool>     BOOL

// Par où on commence
%start Input
%%

Input:
	  /* Vide */
	| Input Statements {
			Unit u;
			u.args = NULL;
			u.operations = $2;

			p.end_parsing = clock();

			if(p.show_operation) {
				puts("[>] Result in memory :"), unit_dump(&u);
				fputs("[*] Press enter to eval", stdout);
				getchar();
			}

			if(p.show_timer)
				printf("[i] Parsed in %.4fs\n", ((p.end_parsing-p.start_parsing)/(double)CLOCKS_PER_SEC));

			eval_main(&u);
	  }
	;

// Déclaration de fonction
Function:
	  FUNCTION P_LEFT P_RIGHT Unit {
	  	$$ = unit_new($4, NULL);
	  }
	|  
	  FUNCTION P_LEFT Param_list P_RIGHT Unit {
	  	// A faire les paramètres
	  	$$ = unit_new($5, $3);
	  }
	;

// Paramètres de déclaration
Param_list:
	  IDENTIFIER {
		Variable *v = var_new(NULL, 0, T_NULL);
	  	v->name = $1;
	  	v->name_h = str_hash($1);
	  	v->deletable = 1;

		$$ = NULL;
		linked_list_append(&$$, (void*)v);
	  }
	| Param_list COMMA IDENTIFIER {
		Variable *v = var_new(NULL, 0, T_NULL);
	  	v->name = $3;
	  	v->name_h = str_hash($3);
	  	v->deletable = 1;

		linked_list_append(&$1, (void*)v);
		$$ = $1;
	  }
	;

// Paramètres d'appel
Param_call_list:
	  Expression {
		$$ = NULL;
		linked_list_append(&$$, (void*)$1);
	  }
	| Param_call_list COMMA Expression {
		linked_list_append(&$1, (void*)$3);
		$$ = $1;
	  }
	;

// Unité de code (Fonction, boucle, etc..)
Unit:
	  BRACE_LEFT Statements BRACE_RIGHT {
		$$ = $2;
	  }
	;

// Un ensemble de lignes de code (Par exemple le contenu d'une fonction ou une boucle)
Statements:
	  Statements Statement {
	  	$$ = $1; // Il faut ajouter le statement à la liste des statement
	  	if($2) linked_list_append(&$1, (void*)$2);
	  }
	| Statement {
		$$ = NULL; // Pas encore de liste, il faut la créer
	  	if($1) linked_list_append(&$$, (void*)$1); // On met notre statement dedans
	  }
	;

// Une 'ligne' de code
Statement:
	  EXPR_END {
	  	if(p.interactive_mod) {
			puts("[!] Empty statement\n");
			beginTokenNewLine();
		} else {
			$$ = NULL;
		}
	  }
	| Expression EXPR_END {
	  	if(p.interactive_mod) {
			// Initialisation valeur retour
			var_init_loc(&r_base, NULL, 0, T_NULL);
			r_base.deletable = 0;
			r = &r_base;

			if(p.show_operation) {
				puts("[>] Result in memory :"), op_dump($1);
				fputs("[*] Press enter to eval", stdout);
				getchar();
			}

			// Evaluation
			puts("\n[<] Evaluating the operations ...");
			switch(op_eval($1, &ec_obj, &ec_tmp, &r)) {
				case RC_WARNING :
					err_display_last();
				case RC_BREAK :
				case RC_OK :
					break;
				case RC_ERROR :
					err_display_last();
					break;
				case RC_CRITICAL:
					err_display_last();
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

			if(p.auto_dump) {
				puts("\n[>] Statement value :");
				var_dump(r);
			}

			// Suppression valeur temporaire
			var_delete(&r_base, 1);
			beginTokenNewLine();
			puts("");
		} else {
			$$ = $1;
			$$->info.line = yylineno;
		}
	}
	;

// Représente une expression (Un 'morceau' d'opération)
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
    | NEW Expression P_LEFT Param_call_list P_RIGHT {              // Appel d'unit comme fonction (OP_UNIT_NEW)
		Variable *v = var_new(NULL, 0, T_ARGS);
		v->value.v_llist = $4;
	  	$$ = op_new(OP_UNIT_NEW, $2, NULL, v);
	  }
	| NEW Expression P_LEFT P_RIGHT {                              // Appel d'unit comme fonction (OP_UNIT_NEW)
	  	$$ = op_new(OP_UNIT_NEW, $2, NULL, NULL);
	  }
    | Expression P_LEFT Param_call_list P_RIGHT {                  // Appel d'unit comme fonction (OP_UNIT_CALL)
		Variable *v = var_new(NULL, 0, T_ARGS);
		v->value.v_llist = $3;
	  	$$ = op_new(OP_UNIT_CALL, $1, NULL, v);
	  }
	| Expression P_LEFT P_RIGHT {                                  // Appel d'unit comme fonction (OP_UNIT_CALL)
	  	$$ = op_new(OP_UNIT_CALL, $1, NULL, NULL);
	  }
	| IDENTIFIER {                                                 // Accès à une variable (OP_ACCES)
	  	$$ = op_new(OP_ACCES, NULL, NULL, NULL);
	  	$$->info.val = $1;
	  	$$->info.val_h = str_hash($1);
	  }
	| VAR IDENTIFIER {                                             // Accès à une variable (OP_ACCES)
	  	$$ = op_new(OP_ACCES_VAR, NULL, NULL, NULL);
	  	$$->info.val = $2;
	  	$$->info.val_h = str_hash($2);
	  }
	| ATTR IDENTIFIER {                                            // Accès à une variable (OP_ACCES)
	  	$$ = op_new(OP_ACCES_ATTR, NULL, NULL, NULL);
	  	$$->info.val = $2;
	  	$$->info.val_h = str_hash($2);
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
	| Function {                                                   // Déclaration de fonction (OP_UNIT)
	  	$$ = op_new(OP_UNIT, NULL, NULL, var_new(NULL, 0, T_FUNCTION));
	  	$$->value->value.v_func = $1; 
	}
	;

%%

// Erreur durant l'analyse lexicale (flex) ou syntaxique (yacc)
int yyerror(const char *s) {
	int start = tokenStart;
	int i = 1;

	if(!p.interactive_mod) {
		int c = '*';

		rewind(yyin);
		while(i < yylineno) {
			while((c = getc(yyin)) != '\n' && c != EOF);
			i++;
			if(c == EOF) {
  				printf("[x] Error | %d: %s: '%s'\n", yylineno, s, yytext);
  				return 0;
			}
		}

	    fputs("> ", stdout);

		while((c = getc(yyin)) != '\n' && c != EOF) {
			putc(c, stdout);
		}
		putc('\n', stdout);
	}

	fputs("...", stdout);
    for (i = 1; i < start; i++)
    	putc('.', stdout);
    puts("^");

  	printf("[x] Error | %d: %s: '%s'\n", yylineno, s, yytext);
  	
  	return 0;
}

// Début d'un token 
void beginToken(const char *t) {
	// Avant le token
	tokenStart += tokenLength;
	// Longueur du token
	tokenLength = strlen(t);

}

// Nouvelle ligne
void beginTokenNewLine() {
	// Remise à zéro
	tokenStart = 0;
	tokenLength = 0;
}

// Main
int main(int argc, char **argv) {

	// Init des args
	params_init();
	params_make(argc, argv);

	if(p.interactive_mod) {
		puts("[i] Starting in interactive mode");
		ec_init_loc(&ec_obj);
		ec_init_loc(&ec_tmp);
		yyparse();
	} else {
		puts("[i] Starting in file mode");
		if(p.file) {
			yyin = p.file;
			p.start_parsing = clock();
			yyparse();
		} else {
			puts("[x] No file to read");
			return 1;
		}
	}
	return 0;
}

