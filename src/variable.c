
/* ==       Fichier variable.c       == */

#include "variable.h"

// Initialise une variable locale
return_code var_init_loc(Variable *a, char* name, hash_t name_h, language_type type) {

    if(a) {
        a->name = name;
        a->name_h = name_h;
        a->type = type;
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

// Raccourci pour variable locale nulle
void var_init_loc_null(Variable *a) {

    if(a) {
        a->name = NULL;
        a->name_h = 0;
        a->type = T_NULL;
        a->container = NULL;
    }
}

// Initialise et alloue si necessaire une variable
return_code var_init(Variable **a, char* name, hash_t name_h, language_type type) {

    return_code rc = RC_OK;

    if(!(*a))
        (*a) = (Variable*)xmalloc(sizeof(Variable));

    rc = var_init_loc(*a, name, name_h, type);
    return rc;
}

// Initialise et retourne un pointeur vers une variable
Variable* var_new(char* name, hash_t name_h, language_type type) {

    Variable *a = (Variable*)xmalloc(sizeof(Variable));
    var_init_loc(a, name, name_h, type);
    return a;
}

// Initialise et retourne un pointeur un objet
Object* var_new_object(Linked_list* variables) {

    Object *o = (Object*)xmalloc(sizeof(Object));

    o->n_links = 1;
    o->ec.container = NULL;
    o->ec.variables = variables;

    return o;
}

// Copie une variable en mémoire - utilisé pour les paramètres de fonctions
Variable* var_copy_data(Variable *a, Variable *b) {

    switch(a->type) {
        // Cas par recopie simple
        case T_NULL :
        case T_NUM :
        case T_BOOL :
        case T_FUNCTION :
            b->value = a->value;
            b->type = a->type;
            break;
        // Cas par recopie de référence
        case T_OBJECT :
            b->value.v_obj = a->value.v_obj;
            b->value.v_obj->n_links++;
            b->type = a->type;
            break;
        case T_LINKEDLIST :
            // A refaire
            //var_op_assign_llist(b, a);
            b->type = a->type;
            break;
        case T_ARRAY :
            // var_op_assign_array(a, b);
            b->type = a->type;
            break;
        case T_NONEXISTENT:
        default :
            break;
    }

    return b;
}

// Cherche une variable dans un contexte d'execution
Variable* var_search_ec(Exec_context *ec, const char* name, hash_t name_h) {

    Variable* v = NULL;

    while(ec) {
        if((v = var_search(ec->variables, name, name_h)))
            return v;
        ec = ec->container;
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

// vérifié
// Supprime une variable de mémoire
return_code var_delete(Variable *v) {
    return_code rc = RC_OK;

    var_empty(v);

    xfree(v);

    return rc;
}

// Vide le contenu d'une variable et la repasse à NULL
return_code var_empty(Variable *v) {

    return_code rc = RC_OK;

    switch(v->type) {
        case T_NUM :
        case T_BOOL :
        case T_FUNCTION :
        case T_NONEXISTENT :
        case T_NULL :
            break;
        case T_OBJECT :
            rc = var_delete_object(v->value.v_obj);
            break;
        case T_ARGS :
            rc = var_empty_args(v->value.v_llist);
            break;
        case T_LINKEDLIST :
            rc = var_empty_llist(v->value.v_llist); // En attendant mieux
            break;
        case T_ARRAY :
            rc = /* var_empty_array(v); */ RC_OK;
            break;
        default :
            err_add(E_CRITICAL, UNKOWN_TYPE, "Unknown type(%x) of variable deleted", v->type);
            err_display_last();
            rc = RC_ERROR;
    }

    v->type = T_NULL;

    return rc;
}

// Vide une liste de variable
return_code var_empty_llist(Linked_list *v) {

    Linked_list *tmp = NULL;

    // Si il contient des variables
    while(v) {
        tmp = v;
        NEXT(v);

        var_delete((Variable*)tmp->value);
        xfree(tmp);
    }

    return RC_OK;
}

// Vide une liste d'arguments
return_code var_empty_args(Linked_list *v) {

    Linked_list *tmp = NULL;

    while(v) {
        tmp = v;
        v = v->next;

        op_delete((Operation*)tmp->value);
        xfree(tmp);
    }

    return RC_OK;
}

// Vide une variable de type object
return_code var_delete_object(Object *o) {
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

