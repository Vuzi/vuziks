
/* ==       Fichier unit.c       ==  */

#include "unit.h"

// Prototypes statiques
static return_code unit_eval(Exec_context* ec_obj, Exec_context* ec_var, Linked_list* stmts, Variable* eval_value);

// Point d'entrée principal du programme
void unit_main(Unit* start) {
    int goodbye = 0;

    // Retour & contexte
    Exec_context ec_obj, ec_var;
    Variable eval_value;

    p.start_exec = clock(); // début timer

    var_init_loc(&eval_value, NULL, 0, T_NULL);
    ec_init_loc(&ec_obj);
    ec_init_loc(&ec_var);

    switch(unit_eval(&ec_obj, &ec_var, start->statements, &eval_value)) {
        case RC_WARNING :
            err_display_last();
        case RC_BREAK :
        case RC_OK :
            p.end_exec = clock(); // fin timer
            puts("[i] Interpreter stopped (No return value)");
            break;
        case RC_ERROR :
        case RC_CRITICAL:
            p.end_exec = clock(); // fin timer
            err_display_last();
            printf("[x] Error, interpreter stopped with code '%d' \n", e.type);
            goodbye = (int)e.type;
            break;
        case RC_RETURN :
            p.end_exec = clock(); // fin timer
            if(eval_value.type == T_NUM)
                goodbye = (int)(eval_value.value.v_num);
            else if(eval_value.type == T_BOOL)
                goodbye = eval_value.value.v_bool;
            printf("[i] Interpreter stopped (%d) \n", goodbye);
        default:
            break;
    }

    // Libération des valeurs
    var_empty(&eval_value);
    ec_empty(&ec_var);
    ec_empty(&ec_obj);

    // Libération de l'arbre
    unit_empty(start);

    if(p.show_timer)
        printf("[i] Executed in %.4fs\n", ((p.end_exec-p.start_exec)/(double)CLOCKS_PER_SEC));


    // Fin du programme
	exit(goodbye); // ou exit ?
}

// vérifié
static return_code unit_eval(Exec_context* ec_obj, Exec_context* ec_var, Linked_list* stmts, Variable* eval_value) {

    return_code rc = RC_OK;
    Variable *save = eval_value;

    // Buffer temporaire
    Exec_context ec_local; ec_init_loc(&ec_local); ec_local.container = ec_var;

    // Pour chaque statement
    while(stmts) {
        // Evaluation
        switch(stmts->type) {
            case LLT_OPERATION :
                rc = op_eval(ec_obj, &ec_local, (Operation*)stmts->value, &eval_value);
                break;
            case LLT_CONDITION :
                rc = unit_cond_eval(ec_obj, &ec_local, (Unit_conditional*)stmts->value, eval_value);
                break;
            case LLT_LOOP :
                // do loop
                break;
            case LLT_UNIT :
                rc = unit_eval(ec_obj, &ec_local, ((Unit*)stmts->value)->statements, eval_value);
                break;
            default :
                err_add(E_CRITICAL, FORBIDDEN_TYPE, "Statement with an unknown type (%x)", stmts->type);
                rc = RC_CRITICAL;
                goto eval_end;
        }

        // Analyse résultats
        switch(rc) {
            case RC_WARNING :
                err_display_last();
            case RC_OK :
                break;
            case RC_BREAK :
                rc = RC_OK;
            case RC_RETURN :
            case RC_ERROR :
            case RC_CRITICAL :
                goto eval_end;
            default :
                err_add(E_CRITICAL, FORBIDDEN_TYPE, "Unknown evalution return type (%x)", rc);
                rc = RC_CRITICAL;
                goto eval_end;
        }

        // Suivant statement
        NEXT(stmts);

        // Libération valeur temporaire
        if(save->type != T_NULL)
            var_empty(save); // Si on a écrit dans le buffer, c'est forcément une valeur temporaire à vider
        else
            eval_value = save; // Si on a pas écrit dans le buffer, c'est certainement que sont pointeur a été utilisé
                                // pour pointeur une autre valeur, il faut donc le refaire pointer sur le buffer
    }

    // Fin sans return ni erreur
    ec_empty(&ec_local); // Vidage variables locales
    if(save->type != T_NULL) var_empty(save);    // Vidage valeur de return (passage a NULL)
    return rc;

    // Fin avec return/break ou erreur
    eval_end:
        if(rc != RC_RETURN && save->type != T_NULL) // Si on ne retourne rien on vide le buffer et la variable de retour
            var_empty(save);

        ec_empty(&ec_local); // Vidage variables locales
        return rc;
}

// Vérifié
return_code unit_function(Exec_context *ec_obj, Exec_context *ec_var_caller, Linked_list* args, Unit* function, Variable* eval_value) {

    return_code rc = RC_OK;
    Exec_context ec_var;

    ec_init_loc(&ec_var); ec_var.container = ec_var_caller;

    // Récupération des valeurs envoyées
    Linked_list* expected = function->args;

    // Tant qu'on attend des arguments
    while(expected) {
        Variable* arg = (Variable*)expected->value;
        // Tant qu'on a envoyé des arguments
        if(args) {
            // Une évaluation peut soit écrire dans notre buffer, soit utiliser le pointeur pour pointer sur un autre élément
            Variable var, *var_r = &var;
            var_init_loc(var_r, NULL, 0, T_NULL);

            // Evaluation
            switch((rc = op_eval(ec_obj, ec_var_caller, (Operation*)args->value, &var_r))) {
                case RC_WARNING :
                    err_display_last();
                case RC_OK :
                    break;
                case RC_BREAK :
                case RC_RETURN :
                    goto eval_quit;
                case RC_ERROR :
                case RC_CRITICAL :
                    if(var.type != T_NULL) var_empty(&var); // Libération
                    goto eval_quit;
                default :
                    if(var.type != T_NULL) var_empty(&var); // Libération
                    err_add(E_CRITICAL, UNKOWN_TYPE, "Unknown evalution return type (%x)", rc);
                    rc = RC_CRITICAL;
                    goto eval_quit;
            }

            // Ajout à la liste temporaire par copie
            ec_push_var(&ec_var, var_copy_data(var_r, var_new(arg->name, arg->name_h, T_NULL)));

            // Libération de notre buffer
            if(var.type != T_NULL)
                var_empty(&var);

            NEXT(args);
        } else {
            // Ajout à la liste temporaire par copie
            ec_push_var(&ec_var, var_new(arg->name, arg->name_h, T_NULL));
        }

        NEXT(expected);
    }

    // Evaluation
    switch((rc = unit_eval(ec_obj, &ec_var, function->statements, eval_value))) {
        case RC_WARNING :
            err_display_last();
        case RC_BREAK :
        case RC_RETURN :
            rc = RC_OK;
        case RC_OK :
            break;
        case RC_ERROR :
        case RC_CRITICAL :
            break;
        default :
            err_add(E_CRITICAL, UNKOWN_TYPE, "Unknown evalution return type (%x)", rc);
            rc = RC_CRITICAL;
    }

    eval_quit:
        ec_empty(&ec_var);
        return rc;
}

// Vérifié
return_code unit_constructor(Exec_context *ec_obj_caller, Exec_context *ec_var_caller, Linked_list* args, Unit* function, Variable* eval_value) {

   return_code rc = RC_OK;

    // Futur obj
    Object *o = var_new_object(NULL);

    ec_init_loc(&o->ec);
    o->ec.container = ec_obj_caller;

    switch((rc = unit_function(&o->ec, ec_var_caller, args, function, eval_value))) {
        case RC_WARNING :
            err_display_last();
        case RC_BREAK :
        case RC_RETURN :
            rc = RC_OK;
        case RC_OK :
            if(eval_value->type != T_NULL) var_empty(eval_value);
            // Création de l'objet
            o->ec.container = NULL;
            eval_value->type = T_OBJECT;
            eval_value->value.v_obj = o;
            eval_value->container = ec_obj_caller;
            return rc; // On sort ici
        case RC_ERROR :
        case RC_CRITICAL :
            break;
        default :
            err_add(E_CRITICAL, FORBIDDEN_TYPE, "Unknown evalution return type (%x)", rc);
            rc = RC_CRITICAL;
    }

    // Erreur lors de l'appel au constructeur, libération
    if(eval_value->type != T_NULL) var_empty(eval_value);
    ec_empty(&o->ec);
    xfree(o);

    return rc;
}

// vérifié
// Alloue et initialise une nouvelle unité
Unit* unit_new(Linked_list *statements, Linked_list *args) {
    Unit* u = (Unit*)xmalloc(sizeof(Unit));

    u->args = args;
    u->statements = statements;

    return u;
}

// vérifié
// Vide une unité
void unit_empty(Unit *u) {

    Linked_list* tmp = NULL;

    while(u->statements) {
        switch(u->statements->type) {
            case LLT_UNIT :
                unit_empty((Unit*)u->statements->value);
                xfree((Unit*)u->statements->value);
                break;
            case LLT_CONDITION :
                unit_cond_delete((Unit_conditional*)u->statements->value);
                break;
            case LLT_LOOP :
                // todo
                break;
            case LLT_OPERATION :
                op_delete((Operation*)u->statements->value);
                break;
            default :
                break;
        }
        tmp = u->statements;
        NEXT(u->statements);
        xfree(tmp);
    }

    while(u->args) {
        tmp = u->args;
        if(((Variable*)(tmp->value))->name) xfree(((Variable*)(tmp->value))->name);
        var_delete(((Variable*)(tmp->value)));
        NEXT(u->args);
        xfree(tmp);
    }

}

// vérifié
// Initialise un ec
void ec_init_loc(Exec_context *ec) {
    ec->container = NULL;
    ec->variables = NULL;
}

// Vérifié
// Vide un ec
void ec_empty(Exec_context *ec) {
    var_empty_llist(ec->variables);
}

// Vérifié
// Ajoute une variable dans un ec -- on stocke et retourne un pointeur
return_code ec_add_var(Exec_context* ec, Operation_identifier* id, Variable** eval_value) {

    // Création valeur (T_NULL par défaut)
    *eval_value = var_new(id->s, id->s_h, T_NULL);

    // Ajout au contexte
    linked_list_push(&(ec->variables), LLT_VARIABLE, (void*)(*eval_value));

    return RC_OK;
}

// Vérifié
void ec_push_var(Exec_context* ec, Variable* v) {
    linked_list_push(&(ec->variables), LLT_VARIABLE, (void*)v);
}

// vérifié
// Retourne une variable contenue dans un des deux ec courants
return_code ec_var_access(Exec_context* ec_obj, Exec_context* ec_tmp, operation_type type, Operation_identifier* id, Variable** eval_value) {
    Variable *tmp = NULL;

    if(type == OP_ACCES || type == OP_ACCES_ATTR)
        tmp = var_search_ec(ec_obj, id->s, id->s_h);

    if((!tmp) && (type == OP_ACCES || type == OP_ACCES_VAR))
        tmp = var_search_ec(ec_tmp, id->s, id->s_h);

    if(!tmp) (*eval_value)->type = T_NONEXISTENT, (*eval_value)->name = id->s;
    else     (*eval_value) = tmp; // Si on trouve on fait pointer dessus

    return RC_OK;
}

// Vérifié
// Supprime une variable d'un ec, et la met dans le buffer eval_value
return_code ec_pop_var(Exec_context* ec, Operation_identifier* id, Variable* eval_value) {

    Variable* tmp = NULL;

    // Recherche
    Linked_list* ll = ec->variables, *last = NULL;

    while(ec) {
        while(ll) {
            if( ((Variable*)ll->value)->name_h == id->s_h && !strcmp(((Variable*)ll->value)->name, id->s) ) {
                // Valeur cherchée
                tmp = ((Variable*)ll->value);

                // Décrochage de la valeur
                if(last)
                    last->next = ll->next;
                else
                    ec->variables = ll->next;

                goto search_result;
            }
            last = ll;
            NEXT(ll);
        }
        ec = ec->container;
    }

    // Pas trouvé
    eval_value->type = T_NONEXISTENT;
    err_add(E_WARNING, CANT_ACCESS, "Couldn't find var '%s' for deletion", id->s);
    return RC_WARNING;

    // Trouvé
    search_result:
        // Recopie des valeirs
        eval_value->type = tmp->type;
        eval_value->value = tmp->value;

        // Libération variable, on peut car le contenu de la variable à été récupéré (et sera libéré correctement plus tard si non stocké)
        xfree(tmp);

        return RC_OK;
}

Unit_conditional* unit_cond_new(Operation* cond, Unit_conditional* before, Linked_list* statements) {
    Unit_conditional* uc = xmalloc(sizeof(Unit_conditional));

    uc->condition = cond;
    uc->next = NULL;
    uc->statements = statements;

    if(before) before->next = uc;

    return uc;
}

void unit_cond_delete(Unit_conditional* uc) {
    op_delete(uc->condition);

    var_empty_args(uc->statements);

    if(uc->next) unit_cond_delete(uc->next);

    xfree(uc);
}

return_code unit_cond_eval(Exec_context *ec_obj, Exec_context *ec_var, Unit_conditional *uc, Variable* eval_value) {

    return_code rc = RC_OK;
    Variable* save = eval_value;

    do {
        // Opération pour récupérer la condition
        if(uc->condition) {
            switch((rc = op_eval(ec_obj, ec_var, uc->condition, &eval_value))) {
                case RC_WARNING :
                    err_display_last();
                    rc = RC_OK;
                case RC_OK :
                    break;
                case RC_BREAK :
                case RC_CRITICAL :
                case RC_ERROR :
                case RC_RETURN :
                    goto cond_end;
                default :
                    err_add(E_CRITICAL, FORBIDDEN_TYPE, "Unknown evalution return type (%x)", rc);
                    rc = RC_CRITICAL;
                    goto cond_end;
            }

            // Test de la condition
            switch(eval_value->type) {
                case T_BOOL :
                    if(eval_value->value.v_bool)
                        goto cond_true;
                    break;
                case T_NUM :
                    if(eval_value->value.v_bool != 0.0)
                        goto cond_true;
                    break;
                case T_NONEXISTENT :
                case T_NULL :
                    break;
                default :
                    // Cas de variables complexes, forcément vrai
                    goto cond_true;
            }

            if(eval_value->type != T_NULL) var_empty(eval_value); // Libération
            else eval_value = save;

        } else // else
            goto cond_true;

        NEXT(uc);
    } while(uc);

    // Aucune condition validée, on quitte
    return rc;

    // Condition validée
    cond_true:
        switch((rc = unit_eval(ec_obj, ec_var, uc->statements, eval_value))) {
             case RC_WARNING :
                    err_display_last();
            case RC_BREAK :
                    rc = RC_OK;
            case RC_OK :
                break;
            case RC_RETURN :
                return rc;
            case RC_CRITICAL :
            case RC_ERROR :
                goto cond_end;
            default :
                err_add(E_CRITICAL, FORBIDDEN_TYPE, "Unknown evalution return type (%x)", rc);
                rc = RC_CRITICAL;
                goto cond_end;
        }

    cond_end:
        if(eval_value->type != T_NULL) var_empty(eval_value); // Libération
        else eval_value = save;

        return rc;
}

/*
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

*/
