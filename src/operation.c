#include "operation.h"

return_code op_eval(Operation *op, Exec_context *ec_obj, Exec_context *ec_tmp, Variable **r) {

    unsigned int i = 0;
    return_code rc = RC_OK;

    // Buffer de variables
    Variable var[2];
    Variable* var_r[2] = { var, var+1 };

    // Contexte d'execution vide dans le cas d'un changement de contexte
    Exec_context ec_void;
    ec_void.variables = NULL;
    ec_void.caller_context = NULL;
    ec_void.caller = NULL;

    // Valeur de retour initialisée à NULL
    var_init_loc(*r, NULL, 0, T_NULL);

    if(op) {
        // Evaluation des branchesreturn r; }
        for(; i < 2 && op->operations[i]; i++) {
            // Si modification de contexte
            if( i == 1 && op->type == OP_CNTX_MODIFIER) {
                if(var_r[0]->type == T_OBJECT) {
                    ec_obj = &(var_r[0]->value.v_obj); ec_tmp = &ec_void;
                } else {
                    err_add(E_ERROR, FORBIDDEN_TYPE, "Cannot change operation context using a non-objet variable");
                    return RC_ERROR;
                }
            }
            // Evaluation
            switch((rc = op_eval(op->operations[i], ec_obj, ec_tmp, &var_r[i]))) {
                case RC_BREAK :
                case RC_ERROR :
                case RC_CRITICAL :
                    return rc;
                case RC_RETURN :
                    **r = *var_r[i];
                    return rc;
                case RC_WARNING :
                    err_display_last(&e); // provisoire, afficher le warning
                case RC_OK :
                    break;
                default :
                    err_add(E_CRITICAL, UNKOWN_TYPE, "Unknown type of return code from operation");
                    return RC_ERROR;
            }
        }

        // Traitement des résultats
        if(op->type & OP_MATH_OR_LOG_TYPE) { // Type d'opération relevant du traitement de variable
            return var_op(var_r[0], var_r[1], r, op->type);
        } else if(op->type & OP_UNIT_TYPE) { // Type d'opération relevant des appels d'unit
            return op_unit(r, op, var_r, ec_obj);
        } else if(op->type == OP_DEC_ATTR) { // Déclaration d'attribut
            Variable *new_v = NULL;
            if((rc = var_init(&new_v, op->info.val, op->info.val_h, T_NULL)) == RC_OK)
                linked_list_push(&(ec_obj->variables), (void*)new_v);
            *r = new_v;
            return rc;
        } else if(op->type == OP_DEC_VAR) { // Déclaration de variable
            Variable *new_v = NULL;
            if((rc = var_init(&new_v, op->info.val, op->info.val_h, T_NULL)) == RC_OK)
                linked_list_push(&(ec_tmp->variables), (void*)new_v);
            *r = new_v;
            return rc;
        } else if(op->type == OP_COMMA) { // Virgule - construction liste chainée
            if(op->operations[1]->type == OP_COMMA) {
                // On push notre valeur au dessus
                linked_list_push(&(var_r[1]->value.v_llist), (void*)(&(var_r[0]))); // A faire en copiant la valeur !!
                **r = var[1];
            } else {
                // On crée la liste et on push dedans les deux valeurs
                (*r)->type = T_LINKEDLIST;
                (*r)->value.v_llist = NULL;
                linked_list_push(&((*r)->value.v_llist), (void*)(&(var_r[0]))); // A faire en copiant la valeur !!
                linked_list_push(&((*r)->value.v_llist), (void*)(&(var_r[1]))); // A faire en copiant la valeur !!
            }
            return RC_OK;
        } else if(op->type == OP_ACCES) { // Accès de variable
            if(((var_r[0] = var_search(ec_tmp, op->info.val, op->info.val_h))) ||
               ((var_r[0] = var_search(ec_obj, op->info.val, op->info.val_h))))
                *r = var_r[0];
            else
                (*r)->type = T_NONEXISTENT;
            return RC_OK;
        } else if(op->type == OP_VALUE) { // Variable naturelle
            *r = op->value;
            return RC_OK;
        } else if(op->type == OP_ASSIGN) { // Assignation valeur
            if(var_r[0]->name) {
                if(var_r[1]->type != T_NONEXISTENT) {
                    var_r[0]->type = var_r[1]->type;
                    var_r[0]->value = var_r[1]->value;
                    return RC_OK;
                } else{
                    err_add(E_CRITICAL, FORBIDDEN_TYPE, "Cannot assign value of type nonexistent");
                    return RC_ERROR;
                }
            } else {
                err_add(E_CRITICAL, FORBIDDEN_TYPE, "Cannot assign value to temporary variable");
                return RC_ERROR;
            }
        } else if(op->type == OP_CNTX_MODIFIER) { // Modification contexte
            return RC_OK; // Rien à faire
        } else if(op->type == OP_RETURN) { // Return
            (*r)->type = var_r[0]->type; (*r)->value = var_r[0]->value;
            return RC_RETURN;
        } else if(op->type == OP_BREAK) { // Break
            return RC_BREAK;
        } else { // Erreur de type d'opération
            err_add(E_ERROR, OP_IMPOSSIBLE, "Unknown type of operation");
            return RC_ERROR; // Ajouter le type
        }
    } else
        return RC_OK;
}


return_code op_unit(Variable **r, Operation* op, Variable **var_r, Exec_context *ec_obj) {
    return_code rc = RC_OK;

    if(op->type == OP_UNIT_CALL) {
        if(var_r[0]->type == T_REF) {
            if(op->operations[1]->type != OP_COMMA) {
                // Un seul argument
                Linked_list *ll = NULL;
                linked_list_push(&ll, (void*)var_r[1]);
                rc = unit_function(r, ec_obj, ll, &(var_r[0]->value.v_ref));
            } else
                rc = unit_function(r, ec_obj, var_r[1]->value.v_llist, &(var_r[0]->value.v_ref));
            if(rc == RC_OK || rc == RC_RETURN) // Si on quitte avec un return ou RC_OK tout va bien
                return RC_OK;
            else
                return rc;
        } else {
            err_add(E_ERROR, FORBIDDEN_TYPE, "Using a variable with a forbidden type as a function");
            return RC_ERROR; // Ajouter le type
        }
    } else if(op->type == OP_UNIT_NEW) {
        if(var_r[0]->type == T_REF) {
            (*r)->type = T_OBJECT;
            ec_init_loc(&((*r)->value.v_obj));
            rc = unit_constructor(&((*r)->value.v_obj), NULL, &(var_r[0]->value.v_ref));
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
