#ifndef _H_CONSOLE
#define _H_CONSOLE

#include "built-in.h"
#include "../variable.h"
#include "../unit.h"
#include "strings.h"
#include "../str/str.h"

// Bug GCC Windows..
#define CONSOLE_HASH 3547936600
//#define CONSOLE_HASH 229462175725400LL

typedef struct s_Object Object;
typedef struct s_Exec_context Exec_context;

// Prototypes
return_code console_print(Object* o, Linked_list *args, Variable* eval_value, int as_constructor);
return_code console_println(Object* o, Linked_list *args, Variable* eval_value, int as_constructor);
return_code console_readln(Object* o, Linked_list *args, Variable* eval_value, int as_constructor);
Object* console_init(Exec_context* ec_obj);

#endif // _H_CONSOLE
