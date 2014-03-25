#ifndef _H_VARIABLE
#define _H_VARIABLE

/* ==       Fichier variable.h       ==
   Contient les structure, énumérations
   et fonctions liées à la création et à
   la manipulation des variables         */

// Includes
#include "hash/hash.h"
#include "err/err.h"
#include "str/str.h"
#include "math/math.h"
#include "unit.h"
#include "operation.h"

// Type de donnée possibles
typedef enum e_language_type {
	T_NONEXISTENT = -1, T_NULL = 0, T_BOOL = 1, T_NUM = 2, T_ARRAY = 3, T_LINKEDLIST = 4, T_FUNCTION = 5, T_OBJECT = 6, T_ARGS = 7
} language_type;

// Représente un objet instancié en mémoire
typedef struct s_Object {
    Exec_context ec;        // Liste des variables qu'il contient
    unsigned int n_links;   // Nombre de liens sur cet objet
} Object;

// Représente une valeur possible (null n'ayant pas de représentation)
typedef union u_Language_value {
    // Variables naturelles
	char v_bool;
	double v_num;
	// Références
	// Array
	Linked_list *v_llist;
	Variable *v_ref;
	Unit *v_func;
	Object *v_obj;

} Language_value;

// Variable en mémoire
typedef struct s_Variale {
	const char* name;        // Nom de la variable (en toute lettre)
	hash_t name_h;           // Hashage du nom de la variable, pour la trouver plus vite (si 0 alors libérable)
	char deletable;          // Peut être libérée
	language_type type;      // Type de la variable
	Language_value value;    // Valeur de la variable
	Linked_list* container;  // Element contenant (uniquement quand attribut)
} Variable;

#include "variableOp.h"
#include "debug.h"

// Prototypes
Variable* var_new(const char* name, hash_t name_h, language_type type);
Object* var_new_object(Linked_list* variables);
return_code var_init_loc(Variable *a, const char* name, hash_t name_h, language_type type);
return_code var_init(Variable **a, const char* name, hash_t name_h, language_type type);

Linked_list* var_copy_list(Linked_list *ll);
Variable* var_copy(Variable *a);

Variable* var_search_ec(Exec_context *ec, const char* name, hash_t name_h);
Variable* var_search(Linked_list *ll, const char* name, hash_t name_h);
return_code var_output(Variable *v, operation_type type);

return_code var_delete(Variable *v, char onlyAnonymous);
return_code var_empty(Variable *v);
return_code var_empty_object(Object *o);
return_code var_empty_ref(Variable *v);
return_code var_empty_llist(Linked_list *v);
return_code var_empty_args(Linked_list *v);

const char* var_name(Variable *v);

#endif // _H_VARIABLE
