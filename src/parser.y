%{
	#define YYERROR_VERBOSE
	#define YYDEBUG 1

	#include <stdio.h>
	#include <stdlib.h>


	#include "variable.h"
	#include "variableOp.h"
	#include "operation.h"
	#include "unit.h"
	#include "debug.h"

	#include "hash/hash.h"
	#include "init/params.h"
	#include "constant.h"

	#include "parser.h"

	#include "builtin/built-in.h"

	// Valeurs externes
	extern char* yytext;
	extern FILE* yyin;
	extern int yylineno;

	extern unsigned int inside;
	extern char show_prompt;

	// Prototypes
	int yylex(void);
	int yyerror(const char *s);

	// Affichage erreur
	void beginToken(const char *t);
	void beginTokenNewLine();
	void interactive(void* to_exec, ptr_type type);

	// Context courant pour le mode interactif
	Exec_context ec_tmp, ec_obj;
	Variable r_base, *r;

	// Variables locales
	static int goodbye = 0;

	static int tokenStart = 0;
	static int tokenLength = 0;

	// Tableau des fonctions built-in lancées de base avec le programme
	struct s_Object*(*func_builtin_tab[128])(Exec_context*);
	unsigned int func_builtin_tab_n;
%}

%union {
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
};

// Liste des terminaux pouvant être rencontrés
%token NUMBER BOOL TYPE STRING
%token PLUS MINUS STAR SLASH DIV POW EQUAL POINT ADDR MODULO MORE LESS MORE_E LESS_E AND OR NOT EXIST D_EQUAL T_EQUAL DIF
%token P_LEFT P_RIGHT BRACE_LEFT BRACE_RIGHT
%token COMMA
%token VAR ATTR NEW DELETE TYPEOF IS
%token IDENTIFIER FUNCTION IF ELSE FOR WHILE LOOP
%token DUMP
%token EXPR_END NEW_LINE

// Opérateur par ordre croissant de priorité
%left  RETURN BREAK                            // Mot clef return et break, évalués en dernier
%right DUMP                                    // Affichage de variable
%right EQUAL                                   // Affectation de variable
%left  COMMA                                   // Création de liste chainées

%left  OR AND                                  // Opérations de test logique, plus prioritaire que les opération logiques pour les rendre plus simple ( 'a<b or b>c' )
%left  DIF D_EQUAL T_EQUAL                     // Opérations logiques d'égalitées
%left TYPEOF IS                               // Opérations sur les types
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
%type <condition> Condition
%type <loop>      Loop
%type <function>  Function
%type <list>      Statements Unit Param_list Param_call_list
%type <op>        Expression Statement
%type <str>       IDENTIFIER STRING
%type <type>      TYPE
%type <value>     NUMBER
%type <bool>      BOOL

// Par où on commence
%start Input
%%

Input:
	  /* Vide */
	| Input Statements {
			Unit u;
			u.args = NULL;
			u.statements = $2;

			p.end_parsing = clock();

			if(p.show_operation) {
				puts("[>] Result in memory :"), unit_dump(&u);
				fputs("[*] Press enter to eval", stdout);
				getchar();
			}

			if(p.show_timer)
				printf("[i] Parsed in %.4fs\n", ((p.end_parsing-p.start_parsing)/(double)CLOCKS_PER_SEC));

			unit_main(&u);
	  }
	;

// Boucle (for/while)
Loop:
      FOR P_LEFT Expression EXPR_END Expression EXPR_END Expression P_RIGHT Unit {
	  	if($7) linked_list_append(&$9, LLT_OPERATION, (void*)$7);
    	$$ = unit_loop_new($5, NULL, $3, $9);
      }
    | WHILE P_LEFT Expression P_RIGHT Unit {
    	$$ = unit_loop_new($3, NULL, NULL, $5);
      }
    | LOOP Unit {
    	$$ = unit_loop_new(NULL, NULL, NULL, $2);
      }

// Condition (if/else if/else)
Condition:
	  IF P_LEFT Expression P_RIGHT Unit {
	  	$$ = unit_cond_new($3, NULL, $5);
	  }
	| IF P_LEFT Expression P_RIGHT Statement {
		Linked_list* ll = NULL;
	  	linked_list_append(&ll, LLT_OPERATION, (void*)$5);
	  	$$ = unit_cond_new($3, NULL, ll);
	  }
	| Condition ELSE IF P_LEFT Expression P_RIGHT Unit {
		Unit_conditional *uc = $1;
		while(uc->next)
			uc = uc->next;
		uc->next = unit_cond_new($5, uc, $7);
		$$ = $1;
	  }
	| Condition ELSE IF P_LEFT Expression P_RIGHT Statement {
		Linked_list* ll = NULL;
	  	linked_list_append(&ll, LLT_OPERATION, (void*)$7);

		Unit_conditional *uc = $1;
		while(uc->next)
			uc = uc->next;
		uc->next = unit_cond_new($5, uc, ll);
		$$ = $1;
	  }
	| Condition ELSE Unit {
		Unit_conditional *uc = $1;
		while(uc->next)
			uc = uc->next;
		uc->next = unit_cond_new(NULL, uc, $3);
		$$ = $1;
	  }
	| Condition ELSE Statement {
		Linked_list* ll = NULL;
	  	linked_list_append(&ll, LLT_OPERATION, (void*)$3);

		Unit_conditional *uc = $1;
		while(uc->next)
			uc = uc->next;
		uc->next = unit_cond_new(NULL, uc, ll);
		$$ = $1;
	  }

// Déclaration de fonction
Function:
	  FUNCTION P_LEFT P_RIGHT Unit {
	  	$$ = unit_new($4, NULL);
	  }
	| FUNCTION P_LEFT Param_list P_RIGHT Unit {
	  	$$ = unit_new($5, $3);
	  }
	;

// Paramètres de déclaration
Param_list:
	  IDENTIFIER {
		$$ = NULL;
		linked_list_append(&$$, LLT_VARIABLE, (void*)var_new($1, str_hash($1), T_NULL));
	  }
	| Param_list COMMA IDENTIFIER {
		$$ = $1;
		linked_list_append(&$1, LLT_VARIABLE, (void*)var_new($3, str_hash($3), T_NULL));
	  }
	;

// Paramètres d'appel
Param_call_list:
	  Expression {
		$$ = NULL;
		linked_list_append(&$$, LLT_OPERATION, (void*)$1);
	  }
	| Param_call_list COMMA Expression {
		$$ = $1;
		linked_list_append(&$1, LLT_OPERATION, (void*)$3);
	  }
	;

// Unité de code (Fonction, boucle, etc..)
Unit:
	  BRACE_LEFT Statements BRACE_RIGHT {
		$$ = $2;
	  }
	;

// Un ensemble de lignes de code (Par exemple le contenu d'une fonction ou une boucle)
// Peut contenir de statement/boucle/condition
Statements:
	  Statements Statement {
	  	$$ = $1; // Il faut ajouter le statement à la liste
	  	if($2) linked_list_append(&$1, LLT_OPERATION, (void*)$2);
	  	if($2 && p.interactive_mod && !inside) interactive((void*)$2, LLT_OPERATION);
	  }
	| Statements Unit {
	  	$$ = $1; // Il faut ajouter l'unit à la liste
	  	if($2) linked_list_append(&$1, LLT_UNIT, (void*)$2);
	  	if($2 && p.interactive_mod && !inside) interactive((void*)$2, LLT_UNIT);
	  }
	| Statements Condition {
	  	$$ = $1; // Il faut ajouter la condition à la liste
	  	if($2) linked_list_append(&$1, LLT_CONDITION, (void*)$2);
	  	if($2 && p.interactive_mod && !inside) interactive((void*)$2, LLT_CONDITION);
	  }
	| Statements Loop {
	  	$$ = $1; // Il faut ajouter la boucle à la liste
	  	if($2) linked_list_append(&$1, LLT_LOOP, (void*)$2);
	  	if($2 && p.interactive_mod && !inside) interactive((void*)$2, LLT_LOOP);
	  }
	| Statement {
		$$ = NULL; // Pas encore de liste, il faut la créer
	  	if($1) linked_list_append(&$$, LLT_OPERATION, (void*)$1); // On met notre statement dedans
	  	if($1 && p.interactive_mod && !inside) interactive((void*)$1, LLT_OPERATION);
	  }
	| Unit {
		$$ = NULL; // Pas encore de liste, il faut la créer
	  	if($1) linked_list_append(&$$, LLT_UNIT, (void*)$1); // On met notre unit dedans
	  	if($1 && p.interactive_mod && !inside) interactive((void*)$1, LLT_UNIT);
	  }
	| Condition {
		$$ = NULL; // Pas encore de liste, il faut la créer
	  	if($1) linked_list_append(&$$, LLT_CONDITION, (void*)$1); // On met notre condition dedans
	  	if($1 && p.interactive_mod && !inside) interactive((void*)$1, LLT_CONDITION);
	  }
	| Loop {
		$$ = NULL; // Pas encore de liste, il faut la créer
	  	if($1) linked_list_append(&$$, LLT_LOOP, (void*)$1); // On met notre boucle dedans
	  	if($1 && p.interactive_mod && !inside) interactive((void*)$1, LLT_LOOP);
	  }
	;

// Une 'ligne' de code
Statement:
	  EXPR_END {
		$$ = NULL;
	  }
	| NEW_LINE {
		$$ = NULL;
	}
	| Expression EXPR_END {
		$$ = $1;
	}
	| Expression NEW_LINE {
		$$ = $1;
	}
	;

// Représente une expression (Un 'morceau' d'opération)
Expression:
	  Expression EQUAL Expression {                                // Affectation (OP_ASSIGN)
	  	$$ = op_new(OP_ASSIGN, $1, $3, NULL);
	  }
	| TYPE {                                                       // Type (OP_VALUE)
	  	$$ = op_new(OP_VALUE, NULL, NULL, var_new(NULL, 0, T_TYPE));
	  	$$->value->value.v_type = $1;
	  }
	| NUMBER {                                                     // Nombre (OP_VALUE)
	  	$$ = op_new(OP_VALUE, NULL, NULL, var_new(NULL, 0, T_NUM));
	  	$$->value->value.v_num = $1;
	  }
	| BOOL {                                                       // Booléen (OP_VALUE)
	  	$$ = op_new(OP_VALUE, NULL, NULL, var_new(NULL, 0, T_BOOL));
	  	$$->value->value.v_bool = $1;
	  }
	| STRING {                                                      // String (OP_VALUE)
	  	$$ = op_new(OP_VALUE, NULL, NULL, var_new(NULL, 0, T_OBJECT));

	  	strings_string(NULL, NULL, $$->value, 1);
	  	((VK_String*)$$->value->value.v_obj->data)->s = $1;
	  	((VK_String*)$$->value->value.v_obj->data)->n = strlen($1);
	  }
	| Expression POINT IDENTIFIER {                                // Accès a une variable membre (OP_ATTR_ACCESS)
	  	$$ = op_new(OP_ATTR_ACCESS, $1, NULL, NULL);
	  	$$->identifier.s = $3;
	  	$$->identifier.s_h = str_hash($3);
	  }
	| NEW VAR IDENTIFIER {                                         // Création d'une variable temporaire (OP_DEC_VAR)
		$$ = op_new(OP_DEC_VAR, NULL, NULL, NULL);
	  	$$->identifier.s = $3;
	  	$$->identifier.s_h = str_hash($3);
	  }
	| NEW ATTR IDENTIFIER {                                        // Création d'une variable membre (OP_DEC_ATTR)
		$$ = op_new(OP_DEC_ATTR, NULL, NULL, NULL);
	  	$$->identifier.s = $3;
	  	$$->identifier.s_h = str_hash($3);
	  }
	| DELETE VAR IDENTIFIER {                                      // Création d'une variable temporaire (OP_DEC_VAR)
		$$ = op_new(OP_DELETE_VAR, NULL, NULL, NULL);
	  	$$->identifier.s = $3;
	  	$$->identifier.s_h = str_hash($3);
	  }
	| DELETE ATTR IDENTIFIER {                                     // Création d'une variable membre (OP_DEC_ATTR)
		$$ = op_new(OP_DELETE_ATTR, NULL, NULL, NULL);
	  	$$->identifier.s = $3;
	  	$$->identifier.s_h = str_hash($3);
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
	  	$$->identifier.s = $1;
	  	$$->identifier.s_h = str_hash($1);
	  }
	| VAR IDENTIFIER {                                             // Accès à une variable (OP_ACCES)
	  	$$ = op_new(OP_ACCES_VAR, NULL, NULL, NULL);
	  	$$->identifier.s = $2;
	  	$$->identifier.s_h = str_hash($2);
	  }
	| ATTR IDENTIFIER {                                            // Accès à une variable (OP_ACCES)
	  	$$ = op_new(OP_ACCES_ATTR, NULL, NULL, NULL);
	  	$$->identifier.s = $2;
	  	$$->identifier.s_h = str_hash($2);
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
	| TYPEOF Expression {                                          // Typeof (OP_TYPE_TYPEOF)
		$$ = op_new(OP_TYPE_TYPEOF, $2, NULL, NULL);
	  }
	| Expression IS Expression {                                   // Typeof (OP_TYPE_IS)
		$$ = op_new(OP_TYPE_IS, $1, $3, NULL);
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
	if(*t != '\t')
		tokenLength = strlen(t);
	else
		tokenLength = 4;
}

// Nouvelle ligne
void beginTokenNewLine() {
	// Remise à zéro
	tokenStart = 0;
	tokenLength = 0;
}

// Lecture interactive (condition/boucle/statement)
void interactive(void* to_exec, ptr_type type) {

	return_code rc = RC_OK;

	// Initialisation valeur retour
	var_init_loc(&r_base, NULL, 0, T_NULL);
	r = &r_base;


	// Opération simple
	if(type == LLT_OPERATION) {

		if(p.show_operation) {
			puts("[>] Result in memory :"), op_dump((Operation*)to_exec);
			fputs("[*] Press enter to eval", stdout);
			getchar();
		}

		// Evaluation
		if(p.verbose) puts("\n[<] Evaluating the statement ...");
		rc = op_eval(&ec_obj, &ec_tmp, (Operation*)to_exec, &r);

	} else if(type == LLT_CONDITION) {

		if(p.show_operation) {
			puts("[>] Result in memory :"), unit_cond_dump((Unit_conditional*)to_exec);
			fputs("[*] Press enter to eval", stdout);
			getchar();
		}

		// Evaluation
		if(p.verbose) puts("\n[<] Evaluating the condition ...");
		rc = unit_cond_eval(&ec_obj, &ec_tmp, (Unit_conditional*)to_exec, r);
	} else if(type == LLT_LOOP) {

		if(p.show_operation) {
			puts("[>] Result in memory :"), unit_loop_dump((Unit_loop*)to_exec);
			fputs("[*] Press enter to eval", stdout);
			getchar();
		}

		// Evaluation
		if(p.verbose) puts("\n[<] Evaluating the loop ...");
		rc = unit_loop_eval(&ec_obj, &ec_tmp, (Unit_loop*)to_exec, r);
	} else if(type == LLT_UNIT) {

		if(p.show_operation) {
			puts("[>] Result in memory :"), unit_dump((Unit*)to_exec);
			fputs("[*] Press enter to eval", stdout);
			getchar();
		}

		// Evaluation
		if(p.verbose) puts("\n[<] Evaluating the unit ...");
		rc = unit_eval(&ec_obj, &ec_tmp, ((Unit*)to_exec)->statements, r);
	}

	// Analyse
	switch(rc) {
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
			exit(e.type);
		case RC_RETURN :
			if(r_base.type == T_NUM)
				goodbye = (int)r_base.value.v_num;
			printf("[i] Interpreter stopped (%x) \n", goodbye);
			exit(goodbye);
		default:
			break;
	}

	if(p.verbose) puts("[<] Evaluation done");

	if(p.auto_dump && type == LLT_OPERATION) {
		puts("\n[>] Statement value :");
		var_dump(&r_base);
	}

	// Suppression valeur temporaire
	if(r_base.type != T_NULL)
		var_empty(&r_base);
	else
		r = &r_base;

	beginTokenNewLine();
	if(p.verbose) puts("");
}

// Main
int main(int argc, char **argv) {

	// Init des args
	params_init();
	params_make(argc, argv);

	// Init des fonctions built-in
	func_builtin_tab[0] = console_init;
	func_builtin_tab[1] = strings_init;
	func_builtin_tab[2] = arrays_init;
	func_builtin_tab_n = 3;


	if(p.interactive_mod) {
		puts("[i] Starting in interactive mode");
		inside = 0; show_prompt = 1;

		// Contexte
		ec_init_loc(&ec_obj);
		ec_init_loc(&ec_tmp);

		// Initialisation des fonctions built-in
    	unit_init_builtin(&ec_obj);

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

