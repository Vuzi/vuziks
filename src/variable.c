#include "variable.h"



// Initialise une variable
return_code var_init_loc(Variable *a, const char* name, hash_t name_h, language_type type) {

    if(a) {
        a->name = name;
        a->name_h = name_h;
        a->type = type;
        a->n_links = 1; // Lien par défaut
        a->deletable = 1;

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
            case T_REF :
                a->value.v_ref = NULL;
                return RC_OK;
            case T_FUNCTION :
                a->value.v_func = NULL;
                return RC_OK;
            case T_OBJECT :
                return RC_OK;
            default :
                err_add(E_CRITICAL, UNKOWN_TYPE, "Creation with an unknown type : the variable type cannot be resolved as a known type");
                return RC_ERROR;
        }
    } else {
        err_add(E_CRITICAL, NULL_VALUE, "Creation of a variable with a NULL value");
        return RC_CRITICAL;
    }
}

// Initialise et alloue si necessaire une variable
return_code var_init(Variable **a, const char* name, hash_t name_h, language_type type) {

    if(!(*a))
        (*a) = (Variable*)malloc(sizeof(Variable));

    return var_init_loc(*a, name, name_h, type);

}


Variable* var_new(const char* name, hash_t name_h, language_type type) {

    Variable *a = (Variable*)malloc(sizeof(Variable));
    var_init_loc(a, name, name_h, type);
    return a;
}

// Copie une liste de variable en mémoire
Linked_list* var_copy_list(Linked_list *ll) {

    Linked_list *r = NULL;

    // Pour chaque variable de la liste
    while(ll) {
        // On ajoute une copie
        linked_list_append(&r, var_copy((Variable*)ll->value));
        ll = ll->next;
    }

    return r;
}

// Copie une variable en mémoire
Variable* var_copy(Variable *a) {

    Variable *b = NULL;

    if(var_init(&b, a->name, a->name_h, a->type) == RC_OK) {

        switch(b->type) {
            case T_NULL :
            case T_NONEXISTENT :
            case T_NUM :
            case T_BOOL :
            case T_FUNCTION :
            case T_REF :
                b->value = a->value;
                break;
            case T_OBJECT :
                b->value.v_obj.caller = a->value.v_obj.caller;
                b->value.v_obj.caller_context = a->value.v_obj.caller_context;
                b->value.v_obj.variables = var_copy_list(a->value.v_obj.variables);
                break;
            case T_LINKEDLIST :
                b->value.v_llist = var_copy_list(a->value.v_llist);
                break;
            case T_ARRAY :
                // A faire
                break;
            default :
                break;
        }

    }

    return b;
}

// Cherche une variable dans un contexte d'execution
Variable* var_search(Exec_context *ec, const char* name, hash_t name_h) {

    Linked_list *ll;

    while(ec) {
        ll = ec->variables;
        while(ll) {
            if(( ((Variable*)ll->value)->name_h == name_h ) && !strcmp(((Variable*)ll->value)->name, name)) {
                return (Variable*)ll->value;
           } else
                ll = ll->next;
        }
        ec = ec->caller_context;
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
                err_add(E_CRITICAL, UNKOWN_TYPE, "Unknown type of output");
                return RC_ERROR;
        }
    } else {
        err_add(E_CRITICAL, NULL_VALUE, "Output with a null variable");
        return RC_ERROR;
    }
}

// Supprime une variable de mémoire
return_code var_delete(Variable *v) {
    return_code rc = RC_OK;

    if(--(v->n_links) <= 0) {
        // Si le nombre de lien de la variable est à zéro, on vire (Sinon on laisse)
        rc = var_empty(v);
        if(v->deletable) free(v);
    }

    return rc;
}

// Vide le contenu d'une mémoire avant suppression
return_code var_empty(Variable *v) {

    switch(v->type) {
        case T_NUM :
        case T_BOOL :
        case T_FUNCTION :
        case T_NONEXISTENT :
        case T_NULL :
            return RC_OK;
        case T_REF :
            return var_empty_ref(v);
        case T_OBJECT :
            return var_empty_object(v);
        case T_LINKEDLIST :
            return var_empty_llist(v->value.v_llist);
        case T_ARRAY :
            return /* var_empty_array(v); */ RC_OK;
        default :
            err_add(E_CRITICAL, UNKOWN_TYPE, "Unknown type of variable deleted");
            return RC_ERROR;
    }
}

// Vide une variable de type object
return_code var_empty_llist(Linked_list *v) {

    Linked_list *tmp = NULL;

    // Si il contient des variables
    while(v) {
        tmp = v;
        v = v->next;

        var_delete((Variable*)tmp->value);
        free(tmp);
    }

    return RC_OK;
}

// Vide une variable de type object
return_code var_empty_object(Variable *v) {
    return var_empty_llist(v->value.v_obj.variables);
}

// Vide une variable de type référence
return_code var_empty_ref(Variable *v) {
    // Est ce qu'elle référence une valeur
    if(v->value.v_ref) {
        // On relance la suppression pour l'élément référencé
        var_delete(v->value.v_ref);
    }

    return RC_OK;
}

