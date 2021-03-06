#ifndef _H_VARIABLE
#define _H_VARIABLE

/* ==       Fichier variable.h       ==
   Contient les structure, �num�rations
   et fonctions li�es � la cr�ation et �
   la manipulation des variables         */

// Includes
#include <string.h>
#include "linkedList/linkedList.h"
#include "hash/hash.h"
#include "unit.h"

// Repr�sente un objet instanci� en m�moire
typedef struct s_Object {
    Exec_context ec;        // Liste des variables qu'il contient
    unsigned int n_links;   // Nombre de liens sur cet objet
    char* name;             // Type d'objet
    hash_t name_h;          // Hash type d'objet
    void* data;             // Donn�es si utilis� par une biblioth�que ext�rieure
} Object;

// Type de donn�e possibles
typedef enum e_language_type {
	T_NONEXISTENT = -1,
	T_NULL = 0,
	T_TYPE = 1,
	T_BOOL = 2,
	T_NUM = 3,
	T_ARRAY = 4,
	T_LINKEDLIST = 5,
	T_FUNCTION = 6,
	T_FUNCTION_BUILTIN = 7,
	T_OBJECT = 8,
	T_ARGS = 9
} language_type;

// Repr�sente une valeur possible (null n'ayant pas de repr�sentation)
typedef union u_Language_value {
    language_type v_type;
	char v_bool;
	double v_num;
	Linked_list *v_llist;
	struct s_Variable *v_ref;
	Unit *v_func;
	return_code (*v_func_builtin)(Object*, Linked_list*, struct s_Variable*, int);
	Object *v_obj;

} Language_value;

// Variable en m�moire
typedef struct s_Variable {
	char* name;              // Nom de la variable (en toute lettre)
	hash_t name_h;           // Hashage du nom de la variable, pour la trouver plus vite (si 0 alors lib�rable)
	language_type type;      // Type de la variable
	Language_value value;    // Valeur de la variable
	Exec_context* container; // Element contenant (uniquement quand attribut)
} Variable;

#include "operation.h"
#include "debug.h"
#include "builtin/built-in.h"

// Prototypes
return_code var_init_loc(Variable *a, char* name, hash_t name_h, language_type type);
void var_init_loc_null(Variable *a);
return_code var_init(Variable **a, char* name, hash_t name_h, language_type type);
Variable* var_new(char* name, hash_t name_h, language_type type);
Object* var_new_object(Linked_list* variables);
Variable* var_copy_data(Variable *a, Variable *b);
Variable* var_search_ec(Exec_context *ec, const char* name, hash_t name_h);
Variable* var_search(Linked_list *ll, const char* name, hash_t name_h);
return_code var_output(Variable *v, operation_type type);
return_code var_delete(Variable *v);
return_code var_empty(Variable *v);
return_code var_empty_llist(Linked_list *v);
return_code var_empty_args(Linked_list *v);
return_code var_delete_object(Object *o);

const char* var_name(Variable *v);

#endif // _H_VARIABLE
