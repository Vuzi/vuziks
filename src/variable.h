#ifndef _H_VARIABLE
#define _H_VARIABLE

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
	T_NONEXISTENT = -1, T_NULL = 0, T_BOOL = 1, T_NUM = 2, T_ARRAY = 3, T_LINKEDLIST = 4, T_REF = 5, T_OBJECT = 6
} language_type;


// Représente une valeur possible (null n'ayant pas de représentation)
typedef union u_Language_value {
	char v_bool;
	double v_num;
	// Array
	Linked_list *v_llist;
	Unit v_ref;
	Exec_context v_obj;
} Language_value;


//=====================================================================//
//               variable : variable utilisable

// Variable en mémoire
typedef struct s_Variale {
	const char* name;            // Nom de la variable (en toute lettre)
	hash_t name_h;         // Hashage du nom de la variable, pour la trouver plus vite
	language_type type;    // Type de la variable
	Language_value value;  // Valeur de la variable
} Variable;


// Prototypes

void debug_pr_lvl(void);
void var_dump(Variable *v);
const char* language_type_debug(language_type l);

return_code var_init_loc(Variable *a, const char* name, hash_t name_h, language_type type);
return_code var_init(Variable **a, const char* name, hash_t name_h, language_type type);

return_code var_op(Variable *a, Variable *b, Variable **r, operation_type type);
return_code var_op_add(Variable *a, Variable *b, Variable *r);
return_code var_op_min(Variable *a, Variable *b, Variable *r);
return_code var_op_mult(Variable *a, Variable *b, Variable *r);
return_code var_op_pow(Variable *a, Variable *b, Variable *r);
return_code var_op_div(Variable *a, Variable *b, Variable *r);
return_code var_op_intdiv(Variable *a, Variable *b, Variable *r);
return_code var_op_modulo(Variable *a, Variable *b, Variable *r);
return_code var_op_math(Variable *a, Variable *b, Variable *r, operation_type type);
return_code var_op_un_p(Variable *a, Variable *r);
return_code var_op_un_m(Variable *a, Variable *r);
return_code var_op_math_unary(Variable *a,Variable *r, operation_type type);
return_code var_op_comp(Variable *a, Variable *b, Variable *r, operation_type type);
return_code var_op_equal(Variable *a, Variable *b, Variable *r, operation_type type);
return_code var_op_type(Variable *a, Variable *b, Variable *r);
return_code var_op_or_and(Variable *a, Variable *b, Variable *r, operation_type type);
return_code var_op_not(Variable *a, Variable *r);
return_code var_op_log(Variable *a, Variable *b, Variable *r, operation_type type);

Variable* var_search(Exec_context *ec, const char* name, hash_t name_h);

#endif // _H_VARIABLE
