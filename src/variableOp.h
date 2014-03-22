#ifndef _H_VARIABLEOP
#define _H_VARIABLEOP

#include <math.h>

#include "hash/hash.h"
#include "err/err.h"
#include "str/str.h"
#include "math/math.h"
#include "unit.h"
#include "operation.h"

//=====================================================================//
//                         Langage en lui-même

// Type de donnée possibles
typedef enum e_language_type {
	T_NONEXISTENT = -1, T_NULL = 0, T_BOOL = 1, T_NUM = 2, T_ARRAY = 3, T_LINKEDLIST = 4, T_REF = 5, T_FUNCTION = 6, T_OBJECT = 7
} language_type;


// Représente une valeur possible (null n'ayant pas de représentation)
typedef union u_Language_value {
	char v_bool;
	double v_num;
	// Array
	Linked_list *v_llist;
	Variable *v_ref;
	Unit *v_func;
	Exec_context v_obj;

} Language_value;


//=====================================================================//
//               variable : variable utilisable

// Variable en mémoire
typedef struct s_Variale {
	const char* name;      // Nom de la variable (en toute lettre)
	hash_t name_h;         // Hashage du nom de la variable, pour la trouver plus vite
	unsigned int n_links;  // Nombre d'éléments pointant vers la variable
	char deletable;        // Can be free'd
	language_type type;    // Type de la variable
	Language_value value;  // Valeur de la variable
} Variable;

#include "variable.h"

typedef struct s_Operation Operation;

// Prototypes
return_code var_op(Variable *a, Variable *b, Variable **r, operation_type type);
return_code var_op_comma(Variable *a, Variable *b, Operation *op, Variable **r);
return_code var_op_attr_access(Variable *a, const char* name, hash_t name_h, Variable **r);

#endif // _H_VARIABLEOP
