#include "unit.h"


return_code ec_init_loc(Exec_context *ec) {
    if(ec) {
        ec->caller = NULL;
        ec->caller_context = NULL;
        ec->variables = NULL;
        return RC_OK;
    } else {
        err_add(E_CRITICAL, NULL_VALUE, "Creation of an unit with a NULL value");
        return RC_CRITICAL;
    }
}

return_code ec_init(Exec_context **ec) {
    if(!(*ec))
        *ec = (Exec_context*)malloc(sizeof(Exec_context));

    return ec_init_loc(*ec);
}

return_code unit_function(Variable **r, Exec_context *ec_obj, Linked_list *args, Unit *u) {
    Exec_context ec_tmp;
    ec_init_loc(&ec_tmp);

    return_code rc = RC_OK;

    if(u && (*r) && ec_obj) {

        Linked_list* ll = u->args;

        // Arguments
        while(ll) {
            // Copie de la valeur
            Variable* v = (Variable*)malloc(sizeof(Variable));
            memcpy(v, ll->value, sizeof(Variable));

            // Si argument
            if(args) {
                v->type = ((Variable*)(args->value))->type;
                v->value = ((Variable*)(args->value))->value;
            }

            // Ajout
            linked_list_append(&(ec_tmp.variables), (void*)v);

            // Suivant
            ll = ll->next;
        }

        ll = u->operations;

        // Evaluation
        while(ll) {
            switch((rc = op_eval((Operation*)ll->value, ec_obj, &ec_tmp, r)) ) {
                case RC_WARNING :
                    err_display_last(&e);
                case RC_OK :
                case RC_BREAK :
                    break;
                case RC_CRITICAL :
                case RC_ERROR :
                case RC_RETURN :
                    linked_list_del(ec_tmp.variables, free);
                    return rc;
            }
            ll = ll->next;
        }

        linked_list_del(ec_tmp.variables, free);
        return RC_OK;

    } else {
        err_add(E_CRITICAL, NULL_VALUE, "NULL value in a function evaluation");
        return RC_CRITICAL;
    }
}

return_code unit_constructor(Exec_context *ec_obj, Linked_list *args,  Unit *u) {
    Variable r;
    Variable *r_link = &r;
    var_init_loc(r_link, NULL, 0, T_NULL);

    return unit_function(&r_link, ec_obj, args, u);
}

/*
return_code unit_constructor(Exec_context **ec_obj, Exec_context *ec_tmp, Unit *u); // Retourne le contexte du nouvel objet
return_code unit_cond_eval(Exec_context *ec_obj, Exec_context *ec_tmp, Unit_conditional *uc); // Evalue la condition
return_code unit_loop_eval(Exec_context *ec_obj, Exec_context *ec_tmp, Unit_loop *ul); // Evalue la boucle*/
