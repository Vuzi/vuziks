#ifndef _H_ARRAYS
#define _H_ARRAYS

#include "built-in.h"
#include "../variable.h"
#include "../unit.h"
#include "../err/err.h"

// Bug GCC Windows..
#define ARRAYS_HASH 2936647663
//#define ARRAYS_HASH 229483039272943LL
#define ARRAY_HASH 479440892
//#define ARRAY_HASH 6954031493116LL

#define KEY(t, n) t->tab_key[n]
#define VAL(t, n) t->tab_value[n]

typedef struct s_Object Object;
typedef struct s_Exec_context Exec_context;

typedef struct t_Array {
    unsigned int nb_cases;
    unsigned int nb_cases_total;
    int* tab_key;
    Variable* tab_value;
} Array;

// Prototypes
Object* arrays_init(Exec_context* ec_obj);
void array_delete(Object *o);
return_code arrays_array(Object* o, Linked_list *args, Variable* eval_value, int as_constructor);

void array_init(Array* a);
Variable* array_get(Array* a, int key);
void array_resize(Array* a);
void array_add(Array* a, int key, Variable* value);

return_code arrays_array_get(Object* o, Linked_list *args, Variable* eval_value, int as_constructor);
return_code arrays_array_add(Object* o, Linked_list *args, Variable* eval_value, int as_constructor);
return_code arrays_array_length(Object* o, Linked_list *args, Variable* eval_value, int as_constructor);

#endif // _H_ARRAYS
