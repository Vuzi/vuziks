#include "console.h"

// Affichage de variable
static void console_print_var(Variable *v) {
    if(v) {
        switch(v->type) {
            case T_NONEXISTENT :
                fputs("non-existent", stdout); break;
            case T_NULL :
                fputs("null", stdout); break;
            case T_TYPE :
                fputs("type", stdout); break;
            case T_BOOL :
                if(v->value.v_bool)
                    fputs("true", stdout);
                else
                    fputs("false", stdout);
                break;
            case T_NUM :
                if(v->value.v_num == (int)v->value.v_num)
                    printf("%ld", (long int)v->value.v_num);
                else
                    printf("%lf", v->value.v_num);
                break;
            case T_ARRAY :
                fputs("array", stdout); break;
            case T_LINKEDLIST :
                fputs("linked-list", stdout); break;
            case T_FUNCTION :
                fputs("function", stdout); break;
            case T_FUNCTION_BUILTIN :
                fputs("built-in function", stdout); break;
            case T_OBJECT  :
                if(v->value.v_obj->name_h == STRING_HASH) {
                    fputs(((VK_String*)v->value.v_obj->data)->s ,stdout);
                } else
                    fputs("object", stdout);
                break;
            case T_ARGS :
                fputs("args", stdout); break;
            default :
                fputs("unknown", stdout); break;
        }
    } else
        fputs("null", stdout);
}

// Affiche une site de variables
return_code console_print(Object* o, Linked_list *args, Variable* eval_value, int as_constructor) {

    double i = 0.0;

    (void)o;

    if(as_constructor) {
        err_add(E_ERROR, OP_IMPOSSIBLE, "Can't use this built-in function (console.print) as a constructor");
        return RC_ERROR;
    }

    // Pour chaque argument
    while(args) {
        i++;
        console_print_var((Variable*)args->value);
        NEXT(args);
    }

    eval_value->type = T_NUM;
    eval_value->value.v_num = i;

    return RC_OK;
}

// Affiche une suite de variables, avec un saut de ligne à la fin
return_code console_println(Object* o, Linked_list *args, Variable* eval_value, int as_constructor) {

    return_code rc = RC_OK;

    if((rc = console_print(o, args, eval_value, as_constructor)) == RC_OK || rc == RC_WARNING) {
        putc('\n', stdout);
    }

    return rc;
}

// Affiche une suite de variables, avec un saut de ligne à la fin
return_code console_readln(Object* o, Linked_list *args, Variable* eval_value, int as_constructor) {

    (void)o;
    (void)args;

    if(as_constructor) {
        err_add(E_ERROR, OP_IMPOSSIBLE, "Can't use this built-in function (console.readln) as a constructor");
        return RC_ERROR;
    }

    return_code rc = RC_OK;

    unsigned int n = 0;
    char buffer[512];
    fgets(buffer, 512, stdin);
    n = strlen(buffer);

    buffer[n-1] = '\0';

    strings_string(NULL, NULL, eval_value, 1);
    ((VK_String*)eval_value->value.v_obj->data)->s = str_copy(buffer);
    ((VK_String*)eval_value->value.v_obj->data)->n = n;

    return rc;
}

// Initialisation de l'objet built-in console
Object* console_init(Exec_context* ec_obj) {
    // Création de l'objet
    Object* o = var_new_object(NULL);

    (void)ec_obj;

    // Définition du type
    o->name = "console";
    o->name_h = str_hash(o->name);

    // Ajout des fonctions
    Variable* v = var_new("print", str_hash("print"), T_FUNCTION_BUILTIN);
    v->value.v_func_builtin = console_print;
    v->container = &o->ec; v->container->object = o;
    linked_list_push(&(o->ec.variables), LLT_VARIABLE, (void*)v);

    v = var_new("log", str_hash("log"), T_FUNCTION_BUILTIN);
    v->value.v_func_builtin = console_println;
    v->container = &o->ec; v->container->object = o;
    linked_list_push(&(o->ec.variables), LLT_VARIABLE, (void*)v);

    v = var_new("println", str_hash("println"), T_FUNCTION_BUILTIN);
    v->value.v_func_builtin = console_println;
    v->container = &o->ec; v->container->object = o;
    linked_list_push(&(o->ec.variables), LLT_VARIABLE, (void*)v);

    v = var_new("readln", str_hash("readln"), T_FUNCTION_BUILTIN);
    v->value.v_func_builtin = console_readln;
    v->container = &o->ec; v->container->object = o;
    linked_list_push(&(o->ec.variables), LLT_VARIABLE, (void*)v);

    return o;
}
