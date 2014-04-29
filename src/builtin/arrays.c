#include "arrays.h"

// Initialisation de l'objet built-in string
Object* arrays_init(Exec_context* ec_obj) {
    // Création de l'objet
    Object* o = var_new_object(NULL);

    (void)ec_obj;

    // Définition du type
    o->name = "arrays";
    o->name_h = str_hash(o->name);

    // Ajout des fonctions
    Variable* v = var_new("arrays", str_hash("arrays"), T_FUNCTION_BUILTIN);
    v->value.v_func_builtin = strings_string;
    v->container = &o->ec; v->container->object = o;
    linked_list_push(&(o->ec.variables), LLT_VARIABLE, (void*)v);

    return o;
}

void array_delete(Object *o) {
    if(o) {
        Array* ar = (Array*) o->data;
        if(ar->tab_key) xfree(ar->tab_key); // A faire : libération des éléments du tableau, et non pas juste des pointeurs
        if(ar->tab_value) xfree(ar->tab_value);
        xfree(ar);
    }
}

return_code arrays_array(Object* o, Linked_list *args, Variable* eval_value, int as_constructor) {

    (void)o;
    (void)args;

    if(!as_constructor) {
        err_add(E_ERROR, OP_IMPOSSIBLE, "Can't use this built-in function (arrays.array) as a function");
        return RC_ERROR;
    }

    // Nouvel objet string
    eval_value->type = T_OBJECT;
    eval_value->value.v_obj = var_new_object(NULL);

    // Nom d'objet : string
    eval_value->value.v_obj->name = "array";
    eval_value->value.v_obj->name_h = str_hash(eval_value->value.v_obj->name);

    // String en lui même
    Array* ar = xcalloc(1, sizeof(Array));

    eval_value->value.v_obj->data = (void*)ar;

    // Initialisation de l'array
    array_init(ar);

    // Fonction des strings

    Variable *v = var_new("add", str_hash("add"), T_FUNCTION_BUILTIN);
    v->value.v_func_builtin = arrays_array_add;
    v->container = &eval_value->value.v_obj->ec;
    v->container->object = eval_value->value.v_obj;

    linked_list_push(&(eval_value->value.v_obj->ec.variables), LLT_VARIABLE, (void*)v);

    v = var_new("get", str_hash("get"), T_FUNCTION_BUILTIN);
    v->value.v_func_builtin = arrays_array_get;
    v->container = &eval_value->value.v_obj->ec;
    v->container->object = eval_value->value.v_obj;

    linked_list_push(&(eval_value->value.v_obj->ec.variables), LLT_VARIABLE, (void*)v);

    v = var_new("length", str_hash("length"), T_FUNCTION_BUILTIN);
    v->value.v_func_builtin = arrays_array_length;
    v->container = &eval_value->value.v_obj->ec;
    v->container->object = eval_value->value.v_obj;

    linked_list_push(&(eval_value->value.v_obj->ec.variables), LLT_VARIABLE, (void*)v);

    return RC_OK;
}

// Initialise un tableau
void array_init(Array* a) {

    unsigned int i = 0;

    a->nb_cases = 0;
    a->nb_cases_total = 5;

    a->tab_key = calloc(a->nb_cases_total, sizeof(int)); // clé
    a->tab_value = calloc(a->nb_cases_total, sizeof(Variable)); // valeur

    for(; i < a->nb_cases_total; i++) {
        var_init_loc_null(&(a->tab_value[i]));
    }
}

// Renvoit la valeur contenue dans une case du tableau
Variable* array_get(Array* a, int key){
    unsigned int i = 0;

    for(; i < a->nb_cases; i++) {
        if((KEY(a, i) == key)) {
            // Trouvé, copie dans le buffer
            /*r->type = (VAL(a, i))->type;
            r->value = (VAL(a, i))->value;
            if(r->type == T_OBJECT) // Si objet, nouveau lien
                r->value.v_obj->n_links++;*/
            return &(VAL(a, i));
        }
    }

    return NULL;
}

void array_resize(Array* a) {
    // Nouvelles cases
    int* tab_key = malloc(sizeof(int)*(a->nb_cases_total)*1.5);
    Variable* tab_value = malloc(sizeof(int)*(a->nb_cases_total)*1.5);
    unsigned int i = 0;

    // Recopie des données
    for(; i < a->nb_cases; i++) {
        tab_key[i] = KEY(a, i);
        tab_value[i] = VAL(a, i);
    }

    // Libération
    free(a->tab_key);
    free(a->tab_value);

    // Réafectation
    a->tab_key = tab_key;
    a->tab_value = tab_value;

    // Nouvelle taille
    a->nb_cases_total *= 1.5;
}

// Ajoute une case avec la clef key, ou remplace celle existante de key
void array_add(Array* a, int key, Variable* value){
    //recherche si valeur existe
    unsigned i = 0;

    // on le trouve
    for(; i < a->nb_cases; i++) {
        if((KEY(a, i) == key)) {
            VAL(a, i).type = value->type;
            VAL(a, i).value = value->value;

            if(value->type == T_OBJECT) // Si objet, nouveau lien
                value->value.v_obj->n_links++;

            return;
        }
    }

    //on ne l'a pas trouvé
    if(a->nb_cases+1 > a->nb_cases_total){
        //pas la place
        array_resize(a);
    }

    // On ajoute la clef et la valeur
    KEY(a, a->nb_cases) = key;
    VAL(a, a->nb_cases).type = value->type;
    VAL(a, a->nb_cases).value = value->value;

    if(value->type == T_OBJECT) // Si objet, nouveau lien
        value->value.v_obj->n_links++;

    a->nb_cases++;
}

return_code arrays_array_get(Object* o, Linked_list *args, Variable* eval_value, int as_constructor) {

    if(!o) {
        err_add(E_ERROR, OP_IMPOSSIBLE, "Can't use this built-in function (array.get) out of its object");
        return RC_ERROR;
    }

    Array* a = (Array*) o->data;

    if(as_constructor) {
        err_add(E_ERROR, OP_IMPOSSIBLE, "Can't use this built-in function (array.get) as a constructor");
        return RC_ERROR;
    }

    if(args) {
        Variable *v = (Variable*)args->value;

        if(v->type == T_NUM) {
            Variable *ret = array_get(a, (int)v->value.v_num);

            if(ret) {
                // On copie dans le buffer
                eval_value->type = ret->type;
                eval_value->value = ret->value;

                if(eval_value->type == T_OBJECT)
                    eval_value->value.v_obj->n_links++;

            } else {
                // No value
                eval_value->type = T_NONEXISTENT;
            }

            return RC_OK;

        } else {
            err_add(E_WARNING, OP_IMPOSSIBLE, "arrays' key can only be numbers");
            return RC_WARNING;
        }

    } else {
        err_add(E_WARNING, OP_IMPOSSIBLE, "array.get use with no argument");
        return RC_WARNING;
    }
}

return_code arrays_array_add(Object* o, Linked_list *args, Variable* eval_value, int as_constructor) {

    if(!o) {
        err_add(E_ERROR, OP_IMPOSSIBLE, "Can't use this built-in function (array.add) out of its object");
        return RC_ERROR;
    }

    Array* a = (Array*) o->data;

    if(as_constructor) {
        err_add(E_ERROR, OP_IMPOSSIBLE, "Can't use this built-in function (array.add) as a constructor");
        return RC_ERROR;
    }

    eval_value->type = T_OBJECT;
    eval_value->value.v_obj = o;

    if(args) {
        Variable *key = (Variable*)args->value;
        NEXT(args);

        if(args) {
            Variable *val = (Variable*)args->value;

            if(key->type == T_NUM) {
                array_add(a, (int)key->value.v_num, val);
                return RC_OK;
            } else {
                err_add(E_WARNING, OP_IMPOSSIBLE, "arrays' key can only be numbers");
                return RC_WARNING;
            }

        } else {
            err_add(E_WARNING, OP_IMPOSSIBLE, "array.add use with no value to insert");
            return RC_WARNING;
        }
    } else {
        err_add(E_WARNING, OP_IMPOSSIBLE, "array.add use with no argument");
        return RC_WARNING;
    }

}

// A faire : length / delete / push / pop
// Et tout tester



return_code arrays_array_length(Object* o, Linked_list *args, Variable* eval_value, int as_constructor) {

    (void)args;

    if(!o) {
        err_add(E_ERROR, OP_IMPOSSIBLE, "Can't use this built-in function (array.length) out of its object");
        return RC_ERROR;
    }

    Array* a = (Array*) o->data;

    if(as_constructor) {
        err_add(E_ERROR, OP_IMPOSSIBLE, "Can't use this built-in function (array.length) as a constructor");
        return RC_ERROR;
    }

    eval_value->type = T_NUM;
    eval_value->value.v_num = (double)a->nb_cases;

    return RC_OK;
}

/*
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
*/
