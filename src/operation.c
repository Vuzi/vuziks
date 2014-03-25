
/* ==       Fichier operation.c       == */

#include "operation.h"

// Prototypes statiques
static return_code unit_op(Variable **r, Operation* op, Variable **var_r, Exec_context *ec_obj, Exec_context *ec_tmp);

// Evaluation d'opération (parcour l'arbre et stocke le résultat dans r)
return_code op_eval(Operation *op, Exec_context *ec_obj, Exec_context *ec_tmp, Variable **r) {

    unsigned int i = 0;
    return_code rc = RC_OK;

    // Buffer de variables
    Variable var[2];
    Variable* var_r[2] = { var, var+1 };

    for(; i < 2; i++)
        var_init_loc(&var[i], NULL, 0, T_NULL);

    if(op) {
        // Evaluation des branches
        for(i = 0; i < 2 && op->operations[i]; i++) {
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
                    err_display_last(); // provisoire, afficher le warning
                    rc = RC_OK;
                case RC_OK :
                    break;
                default :
                    err_add(E_CRITICAL, UNKOWN_TYPE, "Unknown type of return code (%x) from operation", rc);
                    return RC_ERROR;
            }
        }

        // Ligne dans le code
        current_line = op->info.line;

        // Traitement des résultats
        if(op->type & OP_MATH_OR_LOG_TYPE) { // Type d'opération relevant du traitement de variable
            rc = var_op(var_r[0], var_r[1], r, op->type);
        } else if(op->type & OP_OUTPUT) { // Type d'opération relevant d'un affichage
            rc = var_output(var_r[0], op->type);
            *r = var_r[0];
        } else if(op->type & OP_UNIT_TYPE) { // Type d'opération relevant des appels d'unit
            rc = unit_op(r, op, var_r, ec_obj, ec_tmp);
        } else if(op->type == OP_DEC_ATTR) { // Déclaration variable attribut
            rc = ec_add_var(ec_obj, op->info.val, op->info.val_h, r); (*r)->container = ec_obj->variables;
        } else if(op->type == OP_DEC_VAR) { // Déclaration variable temporaire
            rc = ec_add_var(ec_tmp, op->info.val, op->info.val_h, r);
        } else if(op->type == OP_DELETE_VAR) { // Déclaration variable temporaire
            rc = ec_pop_var(ec_tmp, op->info.val, op->info.val_h, r);
        } else if(op->type == OP_DELETE_ATTR) { // Déclaration variable temporaire
            rc = ec_pop_var(ec_obj, op->info.val, op->info.val_h, r);
        }  else if(op->type == OP_VALUE || op->type == OP_UNIT) { // Variable naturelle ou fonction
            *r = op->value;
        } else if(op->type == OP_ATTR_ACCESS) { // Accès valeur attribut
            rc = var_op_attr_access(var_r[0], op->info.val, op->info.val_h, r);
        } else if(op->type & OP_ACCES) { // Accès de variable
            rc = ec_var_access(ec_obj, ec_tmp, op->type, op->info.val, op->info.val_h, r);
        } else if(op->type == OP_RETURN) { // Return
            rc = RC_RETURN; *r = var_copy(var_r[0]); // Copy the value
        } else if(op->type == OP_BREAK) { // Break
            rc = RC_BREAK;
        } else { // Erreur de type d'opération
            err_add(E_ERROR, OP_IMPOSSIBLE, "Unknown type of operation (%x)", op->type); rc = RC_ERROR;
        }

        for(i = 0; i < 2; i++) { // Libération buffer
          /*  if(var_r[i]->deletable)
                var_delete(var_r[i], 1);*/
            var_delete( &var[i], 1);
        }
    }
    return rc;
}

// Opération sur des unité - appel de fonction/constructeur
static return_code unit_op(Variable **r, Operation* op, Variable **var_r, Exec_context *ec_obj, Exec_context *ec_tmp) {
    return_code rc = RC_OK;
    Exec_context ec_obj_tmp;

    // Changement du context objet pour les appels d'attributs
    if(var_r[0]->container) {
        ec_obj_tmp.variables = var_r[0]->container;
        ec_obj_tmp.caller_context = ec_obj;
    } else
        ec_obj_tmp = *ec_obj;

    // Appel de fonction
    if(op->type == OP_UNIT_CALL) {
        if(var_r[0]->type == T_FUNCTION) {

            if(op->value) // Appel
                rc = unit_function(r, &ec_obj_tmp, ec_tmp, op->value->value.v_llist, var_r[0]->value.v_func);
            else
                rc = unit_function(r, &ec_obj_tmp, ec_tmp, NULL, var_r[0]->value.v_func);

            if(rc == RC_OK || rc == RC_RETURN) // Si on quitte avec un return ou RC_OK tout va bien
                return RC_OK;
            else
                return rc;
        } else {
            err_add(E_ERROR, FORBIDDEN_TYPE, "Using a variable (%s) with a forbidden type (%s) as a function",
                    var_name(var_r[0]), language_type_debug(var_r[0]->type));
            return RC_ERROR; // Ajouter le type
        }
    }
    // Appel de constructeur
    else if(op->type == OP_UNIT_NEW) {
        if(var_r[0]->type == T_FUNCTION) {

            // Variable
            (*r)->type = T_OBJECT;
            (*r)->value.v_obj = var_new_object(NULL);

            // Contexte
            Exec_context *tmp_ec_obj = &((*r)->value.v_obj->ec);

            if(op->value) // Appel
                rc = unit_constructor(tmp_ec_obj, &ec_obj_tmp, ec_tmp, op->value->value.v_llist, var_r[0]->value.v_func);
            else
                rc = unit_constructor(tmp_ec_obj, &ec_obj_tmp, ec_tmp, NULL, var_r[0]->value.v_func);

            // Si on quitte avec un return ou RC_OK tout va bien
            if(rc == RC_OK || rc == RC_RETURN) {
                return RC_OK;
            } else {
                var_empty((*r)); // Erreur, on supprime l'objet
                return rc;
            }
        } else {
            err_add(E_ERROR, FORBIDDEN_TYPE, "Using a variable (%s) with a forbidden type (%s) as a constructor",
                    var_name(var_r[0]), language_type_debug(var_r[0]->type));
            return RC_ERROR; // Ajouter le type
        }
    } else {
        err_add(E_ERROR, OP_IMPOSSIBLE, "Unknown type of unit operation (%x)", op->type);
        return RC_ERROR; // Ajouter le type
    }

    return RC_OK;
}

// Initialisation d'unit
return_code op_init_loc(Operation *op, operation_type type, Operation *left, Operation *right, Variable *value) {
    if(op) {
        op->info.val = NULL;
        op->info.val_h = 0;
        op->info.line = 0;
        op->operations[0] = left;
        op->operations[1] = right;
        op->type = type;
        op->value = value;
    }
    return RC_OK;
}

// Initialisation avec allocation (si pas alloué)
/*return_code op_init(Operation **op, operation_type type, Operation *left, Operation *right, Variable *value) {

    if(!(*op))
        (*op) = (Operation*)xmalloc(sizeof(Operation));

    return op_init_loc(*op, type, left, right, value);
}*/

// Initialisation et allocation avec retour de pointeur
Operation* op_new(operation_type type, Operation *left, Operation *right, Variable *value) {
    Operation *op = (Operation*)xmalloc(sizeof(Operation));
    op_init_loc(op, type, left, right, value);
    return op;
}

// Destruction d'opération
return_code op_delete(Operation *op) {
    int i = 0;
    if(op) {
        for(; i < 2; i++) {
            if(op->operations[i])
                op_delete(op->operations[i]);
        }

        if(op->value) { // Valeur
            // Cas spécial des fonctions
            if(op->value->type == T_FUNCTION) {
                unit_empty(op->value->value.v_func);
                xfree(op->value->value.v_func);
                op->value->value.v_func = NULL;
            }
            var_delete(op->value, 0);
        }
        if(op->info.val) // Nom
            xfree(op->info.val);
        xfree(op);
    }
    return RC_OK;
}
