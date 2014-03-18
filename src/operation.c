#include "operation.h"

static return_code unit_op(Variable **r, Operation* op, Variable **var_r, Exec_context *ec_obj);

return_code op_eval(Operation *op, Exec_context *ec_obj, Exec_context *ec_tmp, Variable **r) {

    unsigned int i = 0;
    return_code rc = RC_OK;

    // Buffer de variables
    Variable var[2];
    Variable* var_r[2] = { var, var+1 };

    for(; i < 2; i++)
        var[i].deletable = 0;

    // Contexte d'execution temporaire vide dans le cas d'un changement de contexte
    Exec_context ec_void;

    // initialisations
    var_init_loc(*r, NULL, 0, T_NULL);
    ec_init_loc(&ec_void);

    if(op) {
        // Evaluation des branches
        for(i = 0; i < 2 && op->operations[i]; i++) {
            // Si modification de contexte
            if( i == 1 && op->type == OP_CNTX_MODIFIER) {
                if(var_r[0]->type == T_OBJECT) {
                    ec_obj = &(var_r[0]->value.v_obj);
                    ec_tmp = &ec_void;
                } else {
                    err_add(E_ERROR, FORBIDDEN_TYPE, "Cannot change operation context using a non-objet variable");
                    return RC_ERROR;
                }
            }
            // Evaluation
            switch((rc = op_eval(op->operations[i], ec_obj, ec_tmp, &var_r[i]))) {
                case RC_ERROR :
                case RC_CRITICAL :
                    return rc;
                case RC_RETURN :
                    err_add(E_CRITICAL, UNKOWN_TYPE, "Return statement inside another operation is prohibited");
                    return RC_ERROR;
                case RC_BREAK :
                    err_add(E_CRITICAL, UNKOWN_TYPE, "Break statement inside another operation is prohibited");
                    return RC_ERROR;
                case RC_WARNING :
                    err_display_last(&e); // provisoire, afficher le warning
                    rc = RC_OK;
                case RC_OK :
                    break;
                default :
                    err_add(E_CRITICAL, UNKOWN_TYPE, "Unknown type of return code from operation");
                    return RC_ERROR;
            }
        }

        // Traitement des résultats
        if(op->type & OP_MATH_OR_LOG_TYPE) { // Type d'opération relevant du traitement de variable
            rc = var_op(var_r[0], var_r[1], r, op->type);
        } else if(op->type & OP_UNIT_TYPE) { // Type d'opération relevant des appels d'unit
            rc = unit_op(r, op, var_r, ec_obj);
        } else if(op->type == OP_DEC_ATTR) { // Déclaration variable attribut
            rc = ec_add_var(ec_obj, op->info.val, op->info.val_h, r);
        } else if(op->type == OP_DEC_VAR) { // Déclaration variable temporaire
            rc = ec_add_var(ec_tmp, op->info.val, op->info.val_h, r);
        } else if(op->type == OP_ACCES) { // Accès de variable
            Variable *tmp = NULL;
            if(!((tmp = var_search(ec_tmp, op->info.val, op->info.val_h)) || (tmp = var_search(ec_obj, op->info.val, op->info.val_h))))
                (*r)->type = T_NONEXISTENT;
            else
                (*r) = tmp;
        } else if(op->type == OP_VALUE) { // Variable naturelle
            *r = op->value;
        } else if(op->type == OP_CNTX_MODIFIER) { // Modification contexte
            ec_empty(&ec_void);
        }  else if(op->type == OP_RETURN) { // Return
            *r = var_copy(var_r[0]); // Copy the value
            rc = RC_RETURN;
        } else if(op->type == OP_BREAK) { // Break
            rc = RC_BREAK;
        } else if(op->type == OP_COMMA) { // Virgule - construction liste chainée
            rc = var_op_comma(var_r[0], var_r[1], op, r);
        } else { // Erreur de type d'opération
            err_add(E_ERROR, OP_IMPOSSIBLE, "Unknown type of operation");
            rc = RC_ERROR; // Ajouter le type
        }

        for(i = 0; i < 2; i++)
            var_delete(&var[i]);
    }
    return rc;

}

static return_code unit_op(Variable **r, Operation* op, Variable **var_r, Exec_context *ec_obj) {
    return_code rc = RC_OK;

    if(op->type == OP_UNIT_CALL) {
        if(var_r[0]->type == T_FUNCTION) {
            if(op->operations[1]->type != OP_COMMA) {
                // Un seul argument
                Linked_list *ll = NULL; // Liste temporaire avec copie
                linked_list_push(&ll, var_copy(var_r[1]));
                rc = unit_function(r, ec_obj, ll, var_r[0]->value.v_func);
                var_empty_llist(ll); // Suppression liste temporaire
            } else
                rc = unit_function(r, ec_obj, var_r[1]->value.v_llist, var_r[0]->value.v_func);
            if(rc == RC_OK || rc == RC_RETURN) // Si on quitte avec un return ou RC_OK tout va bien
                return RC_OK;
            else
                return rc;
        } else {
            err_add(E_ERROR, FORBIDDEN_TYPE, "Using a variable with a forbidden type as a function");
            return RC_ERROR; // Ajouter le type
        }
    } else if(op->type == OP_UNIT_NEW) {
        if(var_r[0]->type == T_FUNCTION) {
            (*r)->type = T_OBJECT;
            ec_init_loc(&((*r)->value.v_obj));
            if(op->operations[1]->type != OP_COMMA) {
                // Un seul argument
                Linked_list *ll = NULL; // Liste temporaire avec copie
                linked_list_push(&ll, var_copy(var_r[1]));
                rc = unit_constructor(&((*r)->value.v_obj), ll, var_r[0]->value.v_func);
                var_empty_llist(ll); // Suppression liste temporaire
            } else
                rc = unit_constructor(&((*r)->value.v_obj), var_r[1]->value.v_llist, var_r[0]->value.v_func);
            if(rc == RC_OK || rc == RC_RETURN) // Si on quitte avec un return ou RC_OK tout va bien
                return RC_OK;
            else
                return rc;
        } else {
            err_add(E_ERROR, FORBIDDEN_TYPE, "Using a variable with a forbidden type as a constructor");
            return RC_ERROR; // Ajouter le type
        }
    } else {
        err_add(E_ERROR, OP_IMPOSSIBLE, "Unknown type of unit operation");
        return RC_ERROR; // Ajouter le type
    }

    return RC_OK;
}


