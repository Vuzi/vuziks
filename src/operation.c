#include "operation.h"

return_code op_eval(Operation *op, Variable **r) {

    unsigned int i = 0;
    return_code rc = RC_OK;

    Variable var[2];
    Variable* var_r[2] = { var, var+1 };

    var_init_loc(*r, NULL, T_NULL);

    if(op) {
        // Evaluation des branches
        for(; i < 2; i++) {
            if(op->operations[i]) {
                switch((rc = op_eval(op->operations[i], &var_r[i]))) {
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
        }

        // Traitement des résultats
        if(op->type & OP_MATH_OR_LOG_TYPE) { // Type d'opération relevant du traitement de variable
            return var_op(var_r[0], var_r[1], r, op->type);
        } else if(op->type & OP_UNIT_TYPE) { // Type d'opération relevant des appels d'unit
            return RC_OK; // A gérer / faire
        } else if(op->type == OP_DEC) { // Déclaration de variable
            return RC_OK; // A gérer / faire
        } else if(op->type == OP_VALUE) { // Variable naturelle
            *r = op->value;
            return RC_OK;
        } else if(op->type == OP_RETURN) { // Return
            (*r)->type = var_r[0]->type; (*r)->value = var_r[0]->value;
            return RC_RETURN;
        } else if(op->type == OP_BREAK) { // Break
            return RC_BREAK;
        } else { // Erreur de type d'opération
            err_add(E_CRITICAL, UNKOWN_TYPE, "Unknown type of operation");
            return RC_ERROR; // Ajouter le type
        }

    } else
        return RC_OK;
}
