#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Pour la mise en page des dumps et aux affichages de debug
int debug_lvl = 0;

void debug_pr_lvl() {
    int i = 0;
    for(; i < debug_lvl; i++)
        fputs("|  ", stdout);
}

//=====================================================================//
//                   Node de l'arbre binaire (Opération)

// Représente les différents types possibles d'une operation
typedef enum e_operation_type {
	OP_NOTHING = 0,

	OP_FUNC_CALL = 0x1,

	OP_MATH_PLUS = 0x10, OP_MATH_MINUS = 0x11, OP_MATH_MULT = 0x12, OP_MATH_POW = 0x13, OP_MATH_DIV = 0x14, OP_MATH_MODULO = 0x15,

	OP_MATH_P_UNARY = 0x20, OP_MATH_N_UNARY = 0x21,

	OP_MATH_AFF = 0x30,

	OP_MATH_GT = 0x40, OP_MATH_GE = 0x41, OP_MATH_LT = 0x42, OP_MATH_LE = 0x43, OP_MATH_EQ = 0x44, OP_MATH_DIF = 0x45, OP_MATH_NOT = 0x46, OP_MATH_AND = 0x47, OP_MATH_OR = 0x48,

    OP_MATH_PARENTH = 0x50,

	OP_VALUE = 0x60

} operation_type;


//=====================================================================//
//                         Fonction de hashage

// Hashage
typedef size_t hash_t;
#define HASH_START 5381

hash_t hash(hash_t h_val, char c) {
    return (((h_val << 5) + h_val) + c); // hash * 33 + c
}

hash_t str_hash(const char* s) {
    hash_t h = HASH_START;

    while(*s)
        h = hash(h, *(s++));

    return h;
}


//=====================================================================//
//                           Type booléen

// Type booleen
typedef char boolean_;
#define true_ 1
#define false_ 0


//=====================================================================//
//                         Langage en lui-même

// Type de donnée possibles
typedef enum e_language_type {
	T_VOID = 0, T_BOOL = 1, T_CHAR = 2, T_INT = 3, T_LINT = 4, T_FLOAT = 5, T_DOUBLE = 6
} language_type;

// Représente une valeur possible
typedef union u_Language_value {
	int v_int;
	long int v_lint;
	float v_float;
	double v_double;
	char v_char;
	char v_bool;
} Language_value;


//=====================================================================//
//               variable : variable utilisable

// Variable en mémoire
typedef struct s_Variale {
	char* name;            // Nom de la variable (en toute lettre)
	hash_t name_h;            // Hashage du nom de la variable, pour la trouver plus vite
	language_type type;    // Type de la variable
	Language_value value;  // Valeur de la variable
} Variable;

// Liste de variables
typedef struct s_Variale_list {
	struct s_Variale_list* next;
	Variable* var;
} Variable_list;


//=====================================================================//
//                     Buffer d'erreur - provisoir

typedef enum e_error_type {
    CAST_IMPOSSIBLE, NULL_VALUE, UNKOWN_TYPE, OP_IMPOSSIBLE
} error_type;

typedef enum e_error_level {
    E_INFO=0, E_DEBUG=1, E_WARNING=2, E_ERROR=3, E_CRITICAL=4
} error_level;

typedef struct s_Error {
    char msg[512];
    error_type type;
    error_level level;
} Error;

Error e;

// Affichage d'erreur
void err_display_last(Error *e) {
    printf("#error\n  %s\n  level %d and type %d\n", e->msg, e->level, e->type);
}

// Ajout d'erreur
void err_add(const char* msg, error_level lvl, error_type type) {
    strncpy(e.msg, msg, 511);
    e.level = lvl;
    e.type = type;
}


//=====================================================================//
//                    Fonctions testées - Variables

// copy de chaine
char* str_copy(const char* s) {
	char* copy = (char*) malloc(sizeof(char)*(strlen(s)+1));
	return strcpy(copy, s);
}

// Gestion variables
// Initialisations
Variable* var_init(Variable *v, char* name, language_type type) {

    if(v) {
        v->name = str_copy(name);
        v->name_h = str_hash(name);
        v->type = type;
    }

	return v;
}

Variable* var_init_int(Variable *v, char* name, int i) {
    if(v) var_init(v, name, T_INT)->value.v_int = i;
    return v;
}

Variable* var_init_lint(Variable *v, char* name, long int li) {
    if(v) var_init(v, name, T_LINT)->value.v_lint = li;
    return v;
}

Variable* var_init_float(Variable *v, char* name, float f) {
    if(v) var_init(v, name, T_FLOAT)->value.v_float = f;
    return v;
}

Variable* var_init_double(Variable *v, char* name, double d) {
    if(v) var_init(v, name, T_DOUBLE)->value.v_double = d;
    return v;
}

Variable* var_init_char(Variable *v, char* name, char c) {
    if(v) var_init(v, name, T_CHAR)->value.v_char = c;
    return v;
}

Variable* var_init_bool(Variable *v, char* name, boolean_ b) {
    if(v) var_init(v, name, T_BOOL)->value.v_bool = b;
    return v;
}

// Allocations
Variable* var_new(char* name, language_type type) {
    return var_init((Variable*)malloc(sizeof(Variable)), name, type);
}

Variable* var_new_int(char* name, int i) {
    return var_init_int((Variable*)malloc(sizeof(Variable)), name, i);
}

Variable* var_new_lint(char* name, long int li) {
    return var_init_lint((Variable*)malloc(sizeof(Variable)), name, li);
}

Variable* var_new_float(char* name, float f) {
    return var_init_float((Variable*)malloc(sizeof(Variable)), name, f);
}

Variable* var_new_double(char* name, double d) {
    return var_init_double((Variable*)malloc(sizeof(Variable)), name, d);
}

Variable* var_new_char(char* name, char c) {
    return var_init_char((Variable*)malloc(sizeof(Variable)), name, c);
}

Variable* var_new_bool(char* name, boolean_ b) {
    return var_init_bool((Variable*)malloc(sizeof(Variable)), name, b);
}

// Libération
void var_del(Variable *v) {
    if(v) {
        if(v->name) free(v->name);
        free(v);
    }
}

void var_empty(Variable *v) {
    if(v && v->name) free(v->name);
}

// Type de variable
const char* language_type_debug(language_type l) {
    switch(l) {
        case T_INT:
            return "T_INT";
        case T_LINT:
            return "T_LINT";
        case T_FLOAT:
            return "T_FLOAT";
        case T_DOUBLE:
            return "T_DOUBLE";
        case T_CHAR:
            return "T_CHAR";
        case T_BOOL:
            return "T_BOOL";
        case T_VOID:
            return "T_VOID";
        default :
            return "(Error type)";
    }
}

// Affichage debug
void var_dump(Variable *v) {
    debug_pr_lvl(), puts(">variable :");
    if(v) {
        debug_pr_lvl(), printf("  name : %s\n", v->name);
        debug_pr_lvl(), printf("  name_h : %lu\n", (long unsigned)v->name_h);
        debug_pr_lvl(), printf("  type : %s\n", language_type_debug(v->type));
        debug_pr_lvl(), fputs("  value : ", stdout);

        switch(v->type) {
            case T_INT:
                printf("%d\n", v->value.v_int);
                break;
            case T_LINT:
                printf("%ld\n", v->value.v_lint);
                break;
            case T_FLOAT:
                printf("%f\n", v->value.v_float);
                break;
            case T_DOUBLE:
                printf("%lf\n", v->value.v_double);
                break;
            case T_CHAR:
                printf("%c\n", v->value.v_char);
                break;
            case T_BOOL:
                v->value.v_bool ? puts("True") : puts("False");
                break;
            case T_VOID:
                puts("void");
                break;
            default :
                puts("(Error type)");
        }
    } else
        debug_pr_lvl(), puts("\t(null)");
}



//=====================================================================//
//               Fonctions testées - liste de variables


void var_list_append(Variable_list **vl, Variable *v) {
    Variable_list *new_vl = (Variable_list*) malloc(sizeof(Variable_list));
    new_vl->var = v;

    if(*vl) {
        new_vl->next = (*vl)->next;
        (*vl)->next = new_vl;
    } else
        new_vl->next = new_vl;

    *vl = new_vl;
}

void var_list_del(Variable_list *vl) {
    Variable_list *last_vl = vl;

    if(vl) {
        do {
            vl = vl->next;
            var_del(vl->var);
        }while(vl != last_vl);
    }
}

void var_list_dump(Variable_list *vl) {
    Variable_list *last_vl = vl;
    debug_pr_lvl(), puts(">list variables :");
    debug_lvl++;

    if(vl) {
        do {
            vl = vl->next;
            var_dump(vl->var);
        }while(vl != last_vl);
    } else
        debug_pr_lvl(), puts("  (null)");

    debug_lvl--;
}


//=====================================================================//
//               Fonctions testées - opérations sur variables

/*

    Pour des raisons de facilité, les opérations ont été découpées en plusieurs familles, suivant les types d'opérations :
        - opération arithmétique : calcul entre deux valeurs, classique
        - opération airthmétique unaire : calcul sur une seule valeur, par exemple +/- unaire
        - opération logique : test entre deux valeurs
        - opération logique unaires : test logique sur une seule valeur, par exzmple !
        - opération d'affectation : affectation d'une valeur à une variable

    Pour pouvoir effectuer ces calculs, il est obligatoire d'avoir un exemplaire de chaque opération pour chaque type géré, ce
    qui peut vite beaucoup faire de fonctions, même après découpage. C'est pourquoi on utilise un tableau de pointeurs de fonctions
    à deux dimension pour pouvoir aller directement dans la fonction correspondant au bon type, sans avoir besoin de beaucoup de test
    (et cela permet d'ajouter plus facilement par la suite de nouvelles opération ou types).

    Si une opération n'est pas possible pour un type (Addition de booléen, etc...), alors le pointeur correspondant à l'opération est
    à NULL, et son test dans la fonction dédié à ce type d'opération enverra une erreur (Car on essait de faire quelque chose qui est
    incorrect/illogique/impossible).


    Le cast des valeurs s'effectue avant les opérations, et est dédié encore une fois à un grand nombre de fonctions pour pouvoir
    fonctionner (du type int_to_float, int_to_lint, etc...) et certainement avec le même principe de fonctionnement (Tableau de pointeurs)
    mais pas commencé.


*/


/*
Variable* operation(Variable *a, Variable *b);*/

// Calcule le type de retour suivant les priorité (tès simple donc)
language_type var_op_compute_type(language_type a, language_type b) {
    if( a > b ) return a;
    else        return b;
}

Variable* var_op_cast(Variable *v, language_type type) {
    return v;
}

Variable* var_op_add_int(Variable *a, Variable *b) {
    return a;
}

Variable* var_op_add_lint(Variable *a, Variable *b) {
    return a;
}

Variable* var_op_add_float(Variable *a, Variable *b) {
    return a;
}

Variable* var_op_add_double(Variable *a, Variable *b) {
    return a;
}

Variable* var_op_minus_int(Variable *a, Variable *b) {
    return a;
}

Variable* var_op_minus_lint(Variable *a, Variable *b) {
    return a;
}

Variable* var_op_minus_float(Variable *a, Variable *b) {
    return a;
}

Variable* var_op_minus_double(Variable *a, Variable *b) {
    return a;
}

// Format des fonctions de traitement
typedef Variable* (*var_op_func_format) (Variable*, Variable*);

// Tableau des fonctions airthmétiques (+, -, etc...)
var_op_func_format var_op_func_arithmetic[][6] = {
    {NULL, NULL, var_op_add_int  , var_op_add_lint  , var_op_add_float  , var_op_add_double  },  // Additions
    {NULL, NULL, var_op_minus_int, var_op_minus_lint, var_op_minus_float, var_op_minus_double}   // Subtractions
   /* var_op_mult,
    var_op_pow,
    var_op_div,
    var_op_modulo,
    var_op_p_unary,
    var_op_n_unary,
    var_op_aff*/
};

unsigned int var_op_func_arithmetic_id = 0x10; // Valeur pour rammener à zéro le premier index

// Fonctions représentant des opérations mathématiques
Variable* var_op_arithmetic(Variable *a, Variable *b, operation_type type) {
    Variable loc_a, loc_b;

    if(a && b) {
        // Never work on the real var if there are declared variables
        if(a->name) memcpy(&loc_a, a, sizeof(Variable)); else loc_a = *a;
        if(b->name) memcpy(&loc_b, b,sizeof(Variable)); else loc_b = *b;

        // Need a cast
        if(loc_a.type != loc_b.type) {
            language_type new_type = var_op_compute_type(loc_a.type, loc_b.type);
            Variable *tmp = NULL;

            if(new_type != loc_a.type) {
                if(!(tmp = var_op_cast(&loc_a, new_type)))
                    return NULL;
                else
                    loc_a = *tmp; // Error while casting !
            }
            else {
                if(!(tmp = var_op_cast(&loc_b, new_type)))
                    return NULL;
                else
                    loc_b = *tmp; // Error while casting !
            }
        }

        if(var_op_func_arithmetic[type - var_op_func_arithmetic_id][loc_a.type])
            return var_op_func_arithmetic[type - var_op_func_arithmetic_id][loc_a.type](a, b);
        else {
            err_add("Impossible operation for the current type of variable", E_CRITICAL, OP_IMPOSSIBLE);
            return NULL;
        }
    } else {
        err_add("One of the value computed in the arithmetic operation is not defined properly in the memory", E_CRITICAL, NULL_VALUE);
        return NULL;
    }
}


Variable* var_op_assignment(Variable *a, Variable *b) {
    return a;
}

Variable* var_op_logical(Variable *a, Variable *b) {
    return a;
}


// Effectuer une opération mathématique
Variable* var_op(Variable *a, Variable *b, operation_type type) {
    if(var_op_func_arithmetic_id & type)
        return var_op_arithmetic(a, b, type);
    else {
        err_add("Unknown type of operation between two variable", E_CRITICAL, UNKOWN_TYPE);
        return NULL;
    }
}

int main(void) {

    // Variables
    Variable v;
    Variable *v_ptr = NULL, *v_ptr2 = NULL;

    var_init_int(&v, "test", 12);
    v_ptr = var_new_int("coucou", 23);
    v_ptr2 = var_new_lint("long", (long int)42);

    var_dump(&v);
    puts("");
    var_empty(&v);

    // Liste de variables
    Variable_list *var_l = NULL;

    var_list_append(&var_l, v_ptr);
    var_list_append(&var_l, v_ptr2);

    var_list_dump(var_l);

    var_list_del(var_l);

    return 0;
}
