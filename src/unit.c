
/* ==       Fichier unit.c       ==  */

#include "unit.h"

// Prototypes statiques
static return_code op_cond_eval(Variable **r, Exec_context *ec_obj, Exec_context *ec_tmp, struct s_Operation *op, char *go);

// Point d'entrée principal du programme
void eval_main(Unit* start) {
    int goodbye = 0;

    // Retour & contexte
    Exec_context ec_obj;
    Variable var, *var_ref;

    var_init_loc(&var, NULL, 0, T_NULL);
    var_ref = &var;

    ec_init_loc(&ec_obj);

	if(start) {
        p.start_exec = clock();
        switch(unit_function(&var_ref, &ec_obj, NULL, NULL, start)) {
            case RC_WARNING :
                err_display_last();
            case RC_BREAK :
            case RC_OK :
                puts("[i] Interpreter stopped (No return value)");
                break;
            case RC_ERROR :
            case RC_CRITICAL:
                err_display_last();
                printf("[x] Error, interpreter stopped with code '%d' \n", e.type);
                goodbye = (int)e.type;
            case RC_RETURN :
                if(var_ref->type == T_NUM)
                    goodbye = (int)(var_ref->value.v_num);
                printf("[i] Interpreter stopped (%d) \n", goodbye);
            default:
                break;
        }
        p.end_exec = clock();

        unit_empty(start);
        var_delete(var_ref, 1);
        ec_empty(&ec_obj);

        if(p.show_timer)
            printf("[i] Executed in %.4fs\n", ((p.end_exec-p.start_exec)/(double)CLOCKS_PER_SEC));
	}

	exit(goodbye);
}

// Initialise un ec
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

// Alloue et initialisez un ec
/*
return_code ec_init(Exec_context **ec) {
    if(!(*ec))
        *ec = (Exec_context*)xmalloc(sizeof(Exec_context));

    return ec_init_loc(*ec);
}*/

// Vide un ec
return_code ec_empty(Exec_context *ec) {
    var_empty_llist(ec->variables);
    return RC_OK;
}

// Ajoute une variable dans un ec
return_code ec_add_var(Exec_context* ec, char* name, hash_t name_h, Variable **r) {

    Variable *new_v = NULL;
    return_code rc = RC_OK;

    rc = var_init(&new_v, name, name_h, T_NULL);
    new_v->deletable = 1;

    if(rc == RC_OK || rc == RC_WARNING) {
        linked_list_push(&(ec->variables), (void*)new_v);
        *r = new_v;
    } else
        var_delete(new_v, 0);

    return rc;
}

// Retourne une variable contenue dans un des deux ec courants
return_code ec_var_access(Exec_context* ec_obj, Exec_context* ec_tmp, operation_type type, char* name, hash_t name_h, Variable **r) {
    Variable *tmp = NULL;

    if(type == OP_ACCES || type == OP_ACCES_ATTR)
        tmp = var_search_ec(ec_obj, name, name_h);

    if((!tmp) && (type == OP_ACCES || type == OP_ACCES_VAR))
        tmp = var_search_ec(ec_tmp, name, name_h);

    if(!tmp) (*r)->type = T_NONEXISTENT, (*r)->name = name;
    else     (*r) = tmp;

    return RC_OK;
}

// Supprime une variable d'un ec, et la met dans r
return_code ec_pop_var(Exec_context* ec, char* name, hash_t name_h, Variable** r) {

    Linked_list *ll = ec->variables, *prec = NULL;

    while(ll) {
        if(( ((Variable*)ll->value)->name_h == name_h ) && !strcmp(((Variable*)ll->value)->name, name)) {
            // On sort la valeur
            *r = (Variable*)ll->value;
            // On supprime son maillon
            if(prec) prec->next = ll->next;
            else     ec->variables = ll->next;
            xfree(ll);

            return RC_OK;
        }
        prec = ll;
        ll = ll->next;
    }

			if(p.show_timer)
				printf("[i] Parsed in %.4fs\n", ((p.end_parsing-p.start_parsing)/(double)CLOCKS_PER_SEC));
    if(ec->caller_context)
        return ec_pop_var(ec->caller_context, name, name_h, r);
    else {
        (*r)->type = T_NONEXISTENT;
        err_add(E_WARNING, CANT_ACCESS, "Couldn't find var '%s' for deletion", name);
        return RC_WARNING;
    }
}

// Alloue et initialise une nouvelle unité
Unit* unit_new(Linked_list *operations, Linked_list *args) {
    Unit* u = (Unit*)xmalloc(sizeof(Unit));

    u->args = args;
    u->operations = operations;

    return u;
}

// Vide une unité
return_code unit_empty(Unit *u) {
    var_empty_args(u->operations);
    var_empty_llist(u->args);

    return RC_OK;
}

// Unit comme une fonction
return_code unit_function(Variable **r, Exec_context *ec_obj, Exec_context *caller_tmp, Linked_list *args, Unit *u) {
    Exec_context ec_tmp;
    return_code rc = RC_OK;
    Variable *r_save = *r;

    ec_init_loc(&ec_tmp);
    ec_tmp.caller_context = caller_tmp;

    if(u && (*r) && ec_obj) {
        Linked_list* ll = u->args;
        Variable *v = NULL;

        // Arguments (liste d'opérations)
        while(ll) {
            if(args) {
                // Variable buffer
                Variable tmp;
                Variable *tmp_ref = &tmp;
                var_init_loc(tmp_ref, NULL, 0, T_NULL);

                // Evaluation de la branche
                op_eval((Operation*)args->value, ec_obj, caller_tmp, &tmp_ref);

                // On copie la valeur dans le buffer de la fonction (avec le nom)
                v = var_copy(tmp_ref);

                v->name = ((Variable*)ll->value)->name;
                v->name_h = ((Variable*)ll->value)->name_h;

                // On supprime le premier buffer
                var_delete(tmp_ref,1);

                args = args->next;
            } else {
                // Sinon celui par défaut (en copie)
                v = var_copy((Variable*)ll->value);
            }
            // Ajout
            linked_list_push(&(ec_tmp.variables), (void*)v);
            // Suivant
            ll = ll->next;
        }

        ll = u->operations;

        // Evaluation (pour chaque opération)
        while(ll) {
            switch((rc = op_eval((Operation*)ll->value, ec_obj, &ec_tmp, r)) ) {
                case RC_WARNING :
                    err_display_last();
                case RC_OK :
                case RC_BREAK :
                    var_delete(*r, 1);
                   *r = r_save;
                    break;
                case RC_CRITICAL :
                case RC_ERROR :
                    var_delete(*r, 1);
                    *r = r_save;
                case RC_RETURN :
                    ec_empty(&ec_tmp);
                    return rc;
                default :
                    err_add(E_CRITICAL, NULL_VALUE, "Unknown type of operation return");
                    var_delete(*r, 1);
                    *r = r_save;
                    ec_empty(&ec_tmp);
                    return RC_CRITICAL;
            }
            var_init_loc(*r, NULL, 0, T_NULL);

            ll = ll->next;
        }

        ec_empty(&ec_tmp);

        return RC_OK;

    } else {
        err_add(E_CRITICAL, NULL_VALUE, "NULL value in a function evaluation");
        return RC_CRITICAL;
    }
}

// Unit comme un constructeur
return_code unit_constructor(Exec_context *ec_obj, Exec_context *caller_obj, Exec_context *caller_tmp, Linked_list *args,  Unit *u) {

    return_code rc = RC_OK;
    Variable r; // Valeur de retour ignorée
    Variable *r_link = &r;
    var_init_loc(r_link, NULL, 0, T_NULL);
    r_link->deletable = 0;

    ec_obj->caller_context = caller_obj;

    rc = unit_function(&r_link, ec_obj, caller_tmp, args, u);
    var_delete(&r, 1);

    ec_obj->caller_context = NULL;

    return rc;
}

// Evaluation d'unit conditonnel
return_code unit_cond_eval(Variable **r, Exec_context *ec_obj, Exec_context *caller_tmp, Unit_conditional *uc) {
    Exec_context ec_tmp;
    return_code rc = RC_OK;
    Variable *r_save = *r;

    ec_init_loc(&ec_tmp);
    ec_tmp.caller_context = caller_tmp;

    while(uc) {
        // Si on a une condition
        if(uc->condition) {
            switch((rc = op_eval(uc->condition, ec_obj, &ec_tmp, r))) {
                case RC_WARNING :
                    err_display_last();
                case RC_OK :
                    var_delete(*r, 1); *r = r_save;

                    if((*r)->type == T_BOOL) {
                        // Si condition valide
                        if((*r)->value.v_bool) {
                            Linked_list *ll = uc->operations;
                            while(ll) {
                                switch((rc = op_eval((Operation*)ll->value, ec_obj, &ec_tmp, r)) ) {
                                    case RC_WARNING :
                                        err_display_last();
                                    case RC_OK :
                                        break;
                                    case RC_BREAK :
                                    case RC_CRITICAL :
                                    case RC_ERROR :
                                    case RC_RETURN :
                                    default :
                                        var_delete(*r, 1); *r = r_save;
                                        ec_empty(&ec_tmp);
                                        return rc;
                                }
                                var_delete(*r, 1); *r = r_save; // On restaure r pour ne pas écrire n'importe où

                                ll = ll->next;
                            }
                            return RC_OK;
                        }
                    } else {
                        err_add(E_ERROR, FORBIDDEN_TYPE, "Only boolean value can be used in a condition");
                        return E_ERROR;
                    }
                case RC_BREAK :
                case RC_CRITICAL :
                case RC_ERROR :
                case RC_RETURN :
                default :
                    var_delete(*r, 1); *r = r_save; // On restaure r pour ne pas écrire n'importe où
                    ec_empty(&ec_tmp);
                    return rc;
            }
        }
        uc = uc->next;
    }

    return rc;
}

// Evaluation condition
static return_code op_cond_eval(Variable **r, Exec_context *ec_obj, Exec_context *caller_tmp, struct s_Operation *op, char *go) {
    return_code rc = RC_OK;

    switch((rc = op_eval(op, ec_obj, caller_tmp, r))) {
        case RC_WARNING :
            err_display_last();
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

// Evaluation loop
return_code unit_loop_eval(Variable **r, Exec_context *ec_obj, Exec_context *caller_tmp, Unit_loop *ul) {
    Exec_context ec_tmp;
    return_code rc = RC_OK;
    Variable *r_save = *r;
    char go = 0;

    ec_init_loc(&ec_tmp);
    ec_tmp.caller_context = caller_tmp;

    if(ul) {
        do {
            // Action de début de boucle
            if(ul->start_action) {
                switch((rc = op_eval(ul->start_action, ec_obj, &ec_tmp, r))) {
                    case RC_WARNING :
                        err_display_last();
                    case RC_OK :
                        break;
                    case RC_BREAK :
                    case RC_CRITICAL :
                    case RC_ERROR :
                    case RC_RETURN :
                        var_delete(*r, 1); *r = r_save;
                        ec_empty(&ec_tmp);
                        return rc;
                }
                var_delete(*r, 1); *r = r_save;
            }

            // Existe-il une condition (au moins) ?
            if(ul->start_condition || ul->end_condition) {
                // Condition au lancement de la boucle
                if(ul->start_condition) {
                     switch((rc = op_cond_eval(r, ec_obj, &ec_tmp, ul->start_condition, &go))) {
                        case RC_WARNING :
                        case RC_OK :
                            if(go)
                                break;
                        case RC_BREAK :
                        case RC_CRITICAL :
                        case RC_ERROR :
                        case RC_RETURN :
                        default :
                            var_delete(*r, 1); *r = r_save;
                            ec_empty(&ec_tmp);
                            return rc;
                     }
                     var_delete(*r, 1); *r = r_save;
                }

                // Evaluation
                Linked_list *ll = ul->operations;
                while(ll) {
                    switch((rc = op_eval((Operation*)ll->value, ec_obj, &ec_tmp, r)) ) {
                        case RC_WARNING :
                            err_display_last();
                        case RC_OK :
                            break;
                        case RC_BREAK :
                        case RC_CRITICAL :
                        case RC_ERROR :
                        case RC_RETURN :
                            ec_empty(&ec_tmp);
                            var_delete(*r, 1); *r = r_save;
                            return rc;
                    }
                    var_delete(*r, 1); *r = r_save;
                    ll = ll->next;
                }

                // Opération de fin de boucle
                if(ul->end_action) {
                    switch((rc = op_eval(ul->end_action, ec_obj, &ec_tmp, r))) {
                        case RC_WARNING :
                            err_display_last();
                        case RC_OK :
                            break;
                        case RC_BREAK :
                        case RC_CRITICAL :
                        case RC_ERROR :
                        case RC_RETURN :
                        default :
                            ec_empty(&ec_tmp);
                            var_delete(*r, 1); *r = r_save;
                            return rc;
                    }
                    var_delete(*r, 1); *r = r_save;
                }

                // Condition de fin de boucle
                if(ul->end_condition) {
                     switch((rc = op_cond_eval(r, ec_obj, &ec_tmp, ul->end_condition, &go))) {
                        case RC_WARNING :
                        case RC_OK :
                            if(go)
                                break;
                        case RC_BREAK :
                        case RC_CRITICAL :
                        case RC_ERROR :
                        case RC_RETURN :
                        default :
                            ec_empty(&ec_tmp);
                            var_delete(*r, 1); *r = r_save;
                            return rc;
                     }
                    var_delete(*r, 1); *r = r_save;
                }
            }
        } while(1);
    }
    return RC_OK;
}

