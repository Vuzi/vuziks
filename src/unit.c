#include "unit.h"

static return_code op_cond_eval(Variable **r, Exec_context *ec_obj, Exec_context *ec_tmp, struct s_Operation *op, char *go);


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
    Variable r; // Valeur de retour ignorée
    Variable *r_link = &r;
    var_init_loc(r_link, NULL, 0, T_NULL);

    return unit_function(&r_link, ec_obj, args, u);
}

return_code unit_cond_eval(Variable **r, Exec_context *ec_obj, Exec_context *ec_tmp, Unit_conditional *uc) {
    return_code rc = RC_OK;

    while(uc) {
        // Si on a une condition
        if(uc->condition) {
            switch((rc = op_eval(uc->condition, ec_obj, ec_tmp, r))) {
                case RC_WARNING :
                    err_display_last(&e);
                case RC_OK :
                    if((*r)->type == T_BOOL) {
                        // Si condition valide
                        if((*r)->value.v_bool) {
                            Linked_list *ll = uc->operations;
                            while(ll) {
                                switch((rc = op_eval((Operation*)ll->value, ec_obj, ec_tmp, r)) ) {
                                    case RC_WARNING :
                                        err_display_last(&e);
                                    case RC_OK :
                                        break;
                                    case RC_BREAK :
                                    case RC_CRITICAL :
                                    case RC_ERROR :
                                    case RC_RETURN :
                                        return rc;
                                }
                                ll = ll->next;
                            }
                            return RC_OK;
                        }
                    } else {
                        err_add(E_ERROR, FORBIDDEN_TYPE, "Only boolean value can be used in a condition");
                        return E_ERROR;
                    }
                    break;
                case RC_BREAK :
                case RC_CRITICAL :
                case RC_ERROR :
                case RC_RETURN :
                    return rc;
            }
        }
        uc = uc->next;
    }
    return RC_OK;
}

static return_code op_cond_eval(Variable **r, Exec_context *ec_obj, Exec_context *ec_tmp, struct s_Operation *op, char *go) {
    return_code rc = RC_OK;

    switch((rc = op_eval(op, ec_obj, ec_tmp, r))) {
        case RC_WARNING :
            err_display_last(&e);
        case RC_OK :
            if((*r)->type == T_BOOL) {
                // Si condition valide
                if((*r)->value.v_bool)
                    *go = 1;
                else
                    *go = 0;
            } else {
                err_add(E_ERROR, FORBIDDEN_TYPE, "Only boolean value can be used in a loop condition");
                return E_ERROR;
            }
            return RC_OK;
        case RC_BREAK :
        case RC_RETURN :
            err_add(E_ERROR, OP_IMPOSSIBLE, "Cannot use return or break inside a condition");
            return E_ERROR;
        case RC_CRITICAL :
        case RC_ERROR :
        default :
            return rc;
    }

}

return_code unit_loop_eval(Variable **r, Exec_context *ec_obj, Exec_context *ec_tmp, Unit_loop *ul) {
    return_code rc = RC_OK;
    char go = 0;

    if(ul) {
        do {
            // Action de début de boucle
            if(ul->start_action) {
                switch((rc = op_eval(ul->start_action, ec_obj, ec_tmp, r))) {
                    case RC_WARNING :
                        err_display_last(&e);
                    case RC_OK :
                        break;
                    case RC_BREAK :
                    case RC_CRITICAL :
                    case RC_ERROR :
                    case RC_RETURN :
                        return rc;
                }
            }

            // Existe-il une condition (au moins) ?
            if(ul->start_condition || ul->end_condition) {
                // Condition au lancement de la boucle
                if(ul->start_condition) {
                     switch((rc = op_cond_eval(r, ec_obj, ec_tmp, ul->start_condition, &go))) {
                        case RC_WARNING :
                        case RC_OK :
                            break;
                        case RC_BREAK :
                        case RC_CRITICAL :
                        case RC_ERROR :
                        case RC_RETURN :
                        default :
                            return rc;
                     }
                } else
                    go = 1;

                if(go) {
                    // Evaluation
                    Linked_list *ll = ul->operations;
                    while(ll) {
                        switch((rc = op_eval((Operation*)ll->value, ec_obj, ec_tmp, r)) ) {
                            case RC_WARNING :
                                err_display_last(&e);
                            case RC_OK :
                                break;
                            case RC_BREAK :
                            case RC_CRITICAL :
                            case RC_ERROR :
                            case RC_RETURN :
                                return rc;
                        }
                        ll = ll->next;
                    }

                    // Opération de fin de boucle
                    if(ul->end_action) {
                        switch((rc = op_eval(ul->end_action, ec_obj, ec_tmp, r))) {
                            case RC_WARNING :
                                err_display_last(&e);
                            case RC_OK :
                                break;
                            case RC_BREAK :
                            case RC_CRITICAL :
                            case RC_ERROR :
                            case RC_RETURN :
                                return rc;
                        }
                    }

                    // Condition de fin de boucle
                    if(ul->end_condition) {
                         switch((rc = op_cond_eval(r, ec_obj, ec_tmp, ul->end_condition, &go))) {
                            case RC_WARNING :
                            case RC_OK :
                                break;
                            case RC_BREAK :
                            case RC_CRITICAL :
                            case RC_ERROR :
                            case RC_RETURN :
                            default :
                                return rc;
                         }
                    } else
                        go = 1;
                }
            }
        } while(go);
    }
    return RC_OK;
}
