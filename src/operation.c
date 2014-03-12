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

    // Valeur de retour initialis�e � NULL
    var_init_loc(*r, NULL, T_NULL);

    if(op) {
        // Evaluation des branches
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

        // Traitement des r�sultats
        if(op->type & OP_MATH_OR_LOG_TYPE) { // Type d'op�ration relevant du traitement de variable
            return var_op(var_r[0], var_r[1], r, op->type);
        } else if(op->type & OP_UNIT_TYPE) { // Type d'op�ration relevant des appels d'unit
            return RC_OK; // A g�rer / faire
        } else if(op->type == OP_DEC) { // D�claration de variable
            return RC_OK; // A g�rer / faire
        } else if(op->type == OP_ACCES) { // Acc�s de variable
            if(((var_r[0] = var_search(ec_tmp->variables, op->info.val, op->info.val_h))) ||
               ((var_r[0] = var_search(ec_obj->variables, op->info.val, op->info.val_h))))
                *r = var_r[0];
            else
                (*r)->type = T_NONEXISTENT;
            return RC_OK;
        } else if(op->type == OP_VALUE) { // Variable naturelle
            *r = op->value;
            return RC_OK;
        } else if(op->type == OP_CNTX_MODIFIER) { // Modification contexte
            return RC_OK; // Rien � faire
        } else if(op->type == OP_RETURN) { // Return
            (*r)->type = var_r[0]->type; (*r)->value = var_r[0]->value;
            return RC_RETURN;
        } else if(op->type == OP_BREAK) { // Break
            return RC_BREAK;
        } else { // Erreur de type d'op�ration
            err_add(E_CRITICAL, UNKOWN_TYPE, "Unknown type of operation");
            return RC_ERROR; // Ajouter le type
        }

    } else
        return RC_OK;
}
