#include "strings.h"

// Initialisation de l'objet built-in string
Object* strings_init(Exec_context* ec_obj) {
    // Création de l'objet
    Object* o = var_new_object(NULL);

    (void)ec_obj;

    // Définition du type
    o->name = "strings";
    o->name_h = str_hash(o->name);

    // Ajout des fonctions
    Variable* v = var_new("string", str_hash("string"), T_FUNCTION_BUILTIN);
    v->value.v_func_builtin = strings_string;
    v->container = &o->ec; v->container->object = o;
    linked_list_push(&(o->ec.variables), LLT_VARIABLE, (void*)v);

    return o;
}

void string_delete(Object *o) {

    if(o) {
        VK_String* vks = (VK_String*) o->data;
        if(vks->s) xfree(vks->s);
        xfree(vks);
    }
}

return_code strings_string(Object* o, Linked_list *args, Variable* eval_value, int as_constructor) {

    (void)o;
    (void)args;

    if(!as_constructor) {
        err_add(E_ERROR, OP_IMPOSSIBLE, "Can't use this built-in function (strings.string) as a function");
        return RC_ERROR;
    }

    // Nouvel objet string
    eval_value->type = T_OBJECT;
    eval_value->value.v_obj = var_new_object(NULL);

    // Nom d'objet : string
    eval_value->value.v_obj->name = "string";
    eval_value->value.v_obj->name_h = str_hash(eval_value->value.v_obj->name);

    // String en lui même
    VK_String* vks = xcalloc(1, sizeof(VK_String));

    eval_value->value.v_obj->data = (void*)vks;

    // Fonction des strings
    Variable *v = var_new("append", str_hash("append"), T_FUNCTION_BUILTIN);
    v->value.v_func_builtin = strings_string_append;
    v->container = &eval_value->value.v_obj->ec;
    v->container->object = eval_value->value.v_obj;

    linked_list_push(&(eval_value->value.v_obj->ec.variables), LLT_VARIABLE, (void*)v);

    v = var_new("length", str_hash("length"), T_FUNCTION_BUILTIN);
    v->value.v_func_builtin = strings_string_length;
    v->container = &eval_value->value.v_obj->ec;
    v->container->object = eval_value->value.v_obj;

    linked_list_push(&(eval_value->value.v_obj->ec.variables), LLT_VARIABLE, (void*)v);

    return RC_OK;
}

return_code strings_string_append(Object* o, Linked_list *args, Variable* eval_value, int as_constructor) {

    if(!o) {
        err_add(E_ERROR, OP_IMPOSSIBLE, "Can't use this built-in function (string.append) out of its object");
        return RC_ERROR;
    }

    VK_String* vks = (VK_String*) o->data;

    if(as_constructor) {
        err_add(E_ERROR, OP_IMPOSSIBLE, "Can't use this built-in function (string.append) as a constructor");
        return RC_ERROR;
    }

    while(args) {
        Variable *v = (Variable*)args->value;

        switch(v->type) {
            // Type autorisées : bool, num, string
            case T_BOOL :
                if(v->value.v_bool) {
                    // Nouvelle alloc et recopie
                    char* tmp = xmalloc((vks->n + 4 + 1)*sizeof(char));
                    strcpy(tmp, vks->s); strcat(tmp, "true");

                    if(vks->s) xfree(vks->s);

                    vks->s = tmp;
                    vks->n = vks->n + 4;
                } else {
                    // Nouvelle alloc et recopie
                    char* tmp = xmalloc((vks->n + 5 + 1)*sizeof(char));
                    strcpy(tmp, vks->s); strcat(tmp, "false");

                    if(vks->s) xfree(vks->s);

                    vks->s = tmp;
                    vks->n = vks->n + 5;
                }
                break;
            case T_NUM : {
                    char buffer[256], *tmp;

                    if(v->value.v_num == (int)v->value.v_num)
                        sprintf(buffer, "%ld", (long int)v->value.v_num);
                    else
                        sprintf(buffer, "%lf", v->value.v_num);

                    // Nouvelle alloc et recopie
                    tmp = xmalloc((vks->n + strlen(buffer) + 1)*sizeof(char));
                    strcpy(tmp, vks->s); strcat(tmp, buffer);

                    if(vks->s) xfree(vks->s);
                    vks->s = tmp;
                    vks->n = vks->n + strlen(buffer);
                    break;
                }
            case T_OBJECT  :
                // Si c'est un string aussi
                if(v->value.v_obj->name_h == o->name_h && !strcmp(v->value.v_obj->name, o->name)) {

                    VK_String* app = (VK_String*)v->value.v_obj->data;

                    // Nouvelle alloc et recopie
                    char* tmp = xmalloc((vks->n + app->n + 1)*sizeof(char));
                    strcpy(tmp, vks->s); strcat(tmp, app->s);

                    if(vks->s) xfree(vks->s);

                    vks->s = tmp;
                    vks->n = vks->n + app->n;

                    break;
                }
            default :
                err_add(E_ERROR, OP_IMPOSSIBLE, "Can't append a %s to a string", language_type_debug(v->type));
                return RC_ERROR;
        }

        NEXT(args);
    }

    // Pour des raisons de chainage on fait faire retourner l'objet à la méthode
    eval_value->type = T_OBJECT;
    eval_value->value.v_obj = o;
    o->n_links++;

    return RC_OK;
}

return_code strings_string_length(Object* o, Linked_list *args, Variable* eval_value, int as_constructor) {

    (void)args;

    if(!o) {
        err_add(E_ERROR, OP_IMPOSSIBLE, "Can't use this built-in function (string.length) out of its object");
        return RC_ERROR;
    }

    VK_String* vks = (VK_String*) o->data;

    if(as_constructor) {
        err_add(E_ERROR, OP_IMPOSSIBLE, "Can't use this built-in function (string.length) as a constructor");
        return RC_ERROR;
    }

    eval_value->type = T_NUM;
    eval_value->value.v_num = (double)vks->n;

    return RC_OK;
}
