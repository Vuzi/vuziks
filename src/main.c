#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	T_INT, T_LINT, T_FLOAT, T_DOUBLE, T_CHAR, T_BOOL, T_VOID
} language_type;

// Représente une valeur possible
typedef union u_language_value {
	int v_int;
	long int v_lint;
	float v_float;
	double v_double;
	char v_char;
	char v_bool;
} language_value;


//=====================================================================//
//               variable : variable utilisable

// Variable en mémoire
typedef struct s_variale {
	char* name;            // Nom de la variable (en toute lettre)
	hash_t name_h;            // Hashage du nom de la variable, pour la trouver plus vite
	language_type type;    // Type de la variable
	language_value value;  // Valeur de la variable
} variable;

// Liste de variables
typedef struct s_variale_list {
	struct s_variale_list* next;
	variable var;
} variable_list;



//=====================================================================//
//                         Fonctions testées

// copy de chaine
char* str_copy(const char* s) {
	char* copy = (char*) malloc(sizeof(char)*(strlen(s)+1));
	return strcpy(copy, s);
}

// Gestion variables
// Initialisations
variable* var_init(variable *v, char* name, language_type type) {

    if(v) {
        if(name) {
            v->name = str_copy(name);
	    v->name_h = str_hash(name);
        } else {
            v->name = NULL;
            v->name_h = (hash_t)0;
        }
        v->type = type;
    }

	return v;
}

variable* var_init_int(variable *v, char* name, int i) {

    if(v) var_init(v, name, T_INT)->value.v_int = i;

    return v;
}

variable* var_init_lint(variable *v, char* name, long int li) {

    if(v) var_init(v, name, T_LINT)->value.v_lint = li;

    return v;
}

// Allocations
variable* var_new(char* name, language_type type) {
    return var_init((variable*)malloc(sizeof(variable)), name, type);
}

variable* var_new_int(char* name, int i) {
    return var_init_int((variable*)malloc(sizeof(variable)), name, i);
}

variable* var_new_lint(char* name, long int li) {
    return var_init_lint((variable*)malloc(sizeof(variable)), name, li);
}

// Libération
void var_del(variable *v) {
    if(v) {
        if(v->name) free(v->name);
        free(v);
    }
}

void var_empty(variable *v) {
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
void var_dump(variable *v) {
    puts("\nvariable :");
    if(v) {
        printf("\tname : %s\n\tname_h : %lu\n\ttype : %s\n\tvalue : ", v->name, (long unsigned)v->name_h, language_type_debug(v->type));
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
    } else {
        puts("\t(null)");
    }
}

int main(void) {

    variable v;
    variable *v_ptr = NULL;

    var_init_int(&v, "test", 12);
    v_ptr = var_new_int("coucou", 23);

    var_dump(&v);
    var_dump(v_ptr);

    var_empty(&v);
    var_del(v_ptr);

    return 0;
}
