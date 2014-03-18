#ifndef _H_VARIABLE
#define _H_VARIABLE

#include "variableOp.h"

// Prototypes
return_code var_init_loc(Variable *a, const char* name, hash_t name_h, language_type type);
return_code var_init(Variable **a, const char* name, hash_t name_h, language_type type);

Linked_list* var_copy_list(Linked_list *ll);
Variable* var_copy(Variable *a);

Variable* var_search(Exec_context *ec, const char* name, hash_t name_h);

return_code var_delete(Variable *v);
return_code var_empty(Variable *v);
return_code var_empty_object(Variable *v);
return_code var_empty_ref(Variable *v);
return_code var_empty_llist(Linked_list *v);

#endif // _H_VARIABLE
