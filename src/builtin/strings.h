#ifndef _H_STRINGS
#define _H_STRINGS

#include "built-in.h"
#include "../variable.h"
#include "../unit.h"
#include "../err/err.h"

#define STRINGS_HASH 229483039272943ULL
#define STRING_HASH 6954031493116ULL

typedef struct s_Object Object;
typedef struct s_Exec_context Exec_context;

typedef struct s_VK_String {
    char* s;
    size_t n;
} VK_String;

// Prototypes
Object* strings_init(Exec_context* ec_obj);
void string_delete(Object *o);
return_code strings_string(Object* o, Linked_list *args, Variable* eval_value, int as_constructor);
return_code strings_string_append(Object* o, Linked_list *args, Variable* eval_value, int as_constructor);
return_code strings_string_length(Object* o, Linked_list *args, Variable* eval_value, int as_constructor);

#endif // _H_STRINGS
