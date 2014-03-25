
/* ==       Fichier variable.c       == */

#include "variable.h"

// Initialise une variable
return_code var_init_loc(Variable *a, const char* name, hash_t name_h, language_type type) {

    if(a) {
        a->name = name;
        a->name_h = name_h;
        a->type = type;
        a->deletable = 0;
        a->container = NULL;

        switch(type) {
            case T_NULL :
                return RC_OK;
            case T_BOOL :
                a->value.v_bool = 0;
                return RC_OK;
            case T_NUM :
                a->value.v_num = 0.0;
                return RC_OK;
            case T_ARRAY :
                return RC_OK;
            case T_LINKEDLIST :
                a->value.v_llist = NULL;
                return RC_OK;
            case T_FUNCTION :
                a->value.v_func = NULL;
                return RC_OK;
            case T_OBJECT :
                a->value.v_obj = NULL;
                return RC_OK;
            default :
                err_add(E_CRITICAL, UNKOWN_TYPE, "Creation with an unknown type (%x) : the variable type cannot be resolved as a known type" , type);
                return RC_ERROR;
        }
    } else {
        err_add(E_CRITICAL, NULL_VALUE, "Creation of a variable with a null value");
        return RC_CRITICAL;
    }
}

// Initialise et alloue si necessaire une variable
return_code var_init(Variable **a, const char* name, hash_t name_h, language_type type) {

    return_code rc = RC_OK;

    if(!(*a))
        (*a) = (Variable*)xmalloc(sizeof(Variable));

    rc = var_init_loc(*a, name, name_h, type);
    (*a)->deletable = 1;
    return rc;
}

// Initialise et retourne un pointeur vers une variable
Variable* var_new(const char* name, hash_t name_h, language_type type) {

    Variable *a = (Variable*)xmalloc(sizeof(Variable));
    var_init_loc(a, name, name_h, type);
    a->deletable = 1;
    return a;
}

// Initialise et retourne un pointeur un objet
Object* var_new_object(Linked_list* variables) {

    Object *o = (Object*)xmalloc(sizeof(Object));

    o->n_links = 1;
    o->ec.caller = NULL;
    o->ec.caller_context = NULL;
    o->ec.variables = variables;

    return o;
}

// Copie une variable en mémoire - utilisé pour les paramètres de fonctions
Variable* var_copy(Variable *a) {

    Variable *b = NULL;

    if(var_init(&b, a->name, a->name_h, a->type) == RC_OK) {
        switch(b->type) {
            // Cas par recopie simple
            case T_NULL :
            case T_NUM :
            case T_BOOL :
            case T_FUNCTION :
                b->value = a->value;
                break;
            // Cas par recopie de référence
            case T_OBJECT :
                b->value.v_obj = a->value.v_obj;
                b->value.v_obj->n_links++;
                break;
            case T_LINKEDLIST :
                // A refaire
                //var_op_assign_llist(b, a);
                break;
            case T_ARRAY :
                // var_op_assign_array(a, b);
                break;
            case T_NONEXISTENT:
            default :
                break;
        }
    }

    return b;
}

// Cherche une variable dans un contexte d'execution
Variable* var_search_ec(Exec_context *ec, const char* name, hash_t name_h) {

    Variable* v = NULL;

    while(ec) {
        if((v = var_search(ec->variables, name, name_h)))
            break;
        ec = ec->caller_context;
    }

    return v;
}

// Cherche une variable dans une liste de variables
Variable* var_search(Linked_list *ll, const char* name, hash_t name_h) {

    while(ll) {
        if(( ((Variable*)ll->value)->name_h == name_h ) && !strcmp(((Variable*)ll->value)->name, name)) {
            return (Variable*)ll->value;
       } else
            ll = ll->next;
    }

    return NULL;
}

// Opération d'affichage des variable
return_code var_output(Variable *v, operation_type type) {
    if(v) {
        switch(type) {
            case OP_OUTPUT_VAR_DUMP :
                var_dump(v);
                return RC_OK;
            default :
                err_add(E_CRITICAL, UNKOWN_TYPE, "Unknown type of output (%x)", type);
                return RC_ERROR;
        }
    } else {
        err_add(E_CRITICAL, NULL_VALUE, "Output with a null variable");
        return RC_ERROR;
    }
}

// Supprime une variable de mémoire
return_code var_delete(Variable *v, char onlyAnonymous) {
    return_code rc = RC_OK;

    if((onlyAnonymous && !v->name_h) || !onlyAnonymous) {
        rc = var_empty(v);
        if(v->deletable) xfree(v);
    }

    return rc;
}

// Vide le contenu d'une variable avant suppression
return_code var_empty(Variable *v) {

    switch(v->type) {
        case T_NUM :
        case T_BOOL :
        case T_FUNCTION :
        case T_NONEXISTENT :
        case T_NULL :
            return RC_OK;
        case T_OBJECT :
            return var_empty_object(v->value.v_obj);
        case T_ARGS :
            return var_empty_args(v->value.v_llist);
        case T_LINKEDLIST :
            return var_empty_llist(v->value.v_llist); // En attendant mieux
        case T_ARRAY :
            return /* var_empty_array(v); */ RC_OK;
        default :
            err_add(E_CRITICAL, UNKOWN_TYPE, "Unknown type(%x) of variable deleted", v->type);
            return RC_ERROR;
    }
}

// Vide une liste de variable
return_code var_empty_llist(Linked_list *v) {

    Linked_list *tmp = NULL;

    // Si il contient des variables
    while(v) {
        tmp = v;
        v = v->next;

        var_delete((Variable*)tmp->value, 0);
        xfree(tmp);
    }

    return RC_OK;
}

// Vide une liste d'arguments
return_code var_empty_args(Linked_list *v) {

    Linked_list *tmp = NULL;

    // Si il contient des variables
    while(v) {
        tmp = v;
        v = v->next;

        op_delete((Operation*)tmp->value);
        xfree(tmp);
    }

    return RC_OK;
}

// Vide une variable de type object
return_code var_empty_object(Object *o) {
    if(--(o->n_links) <= 0) {
        var_empty_llist(o->ec.variables); // On vide les variables membres
        xfree(o);
    }
    return RC_OK;
}

// Retourne le nom d'une variable
const char* var_name(Variable *v) {
    return v->name ? v->name : "<anonymous>";
}

