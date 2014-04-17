
/* ==       Fichier operation.c       == */

#include "operation.h"

// Prototypes statiques
static return_code unit_op(operation_type type, Exec_context* ec_obj, Exec_context* ec_var, Variable* args, Variable* function, Variable* eval_value);

// vérifié
return_code op_eval(Exec_context* ec_obj, Exec_context* ec_var, Operation* op, Variable** eval_value) {

    // Variables utilitaires
    unsigned int i = 0;
    return_code rc = RC_OK;

    // Buffer de variables & de pointeurs
    Variable var[2];
    Variable* var_r[2] = { var, var+1 };

    // Initialisation buffer à T_NULL
    for(; i < 2; i++)
        var_init_loc(var + i, NULL, 0, T_NULL);

    // Evaluation des branches
    for(i = 0; i < 2 && op->operations[i]; i++) {
        switch((rc = op_eval(ec_obj, ec_var, op->operations[i], var_r + i))) {
            case RC_WARNING :
                err_display_last();
            case RC_OK :
                break;
            case RC_RETURN :
                var_op_return(var_r[i], *eval_value);
            case RC_BREAK :
            case RC_ERROR :
            case RC_CRITICAL :
                goto eval_end;
            default :
                err_add(E_CRITICAL, FORBIDDEN_TYPE, "Unknown evalution return type (%x)", rc);
                rc = RC_CRITICAL;
                goto eval_end;
        }
    }

    // Traitement des résultats
    if(op->type & OP_MATH_OR_LOG_TYPE) { // Type d'opération relevant du traitement de variable
        rc = var_op(var_r[0], var_r[1], *eval_value, op->type); // On écrit directement dans le buffer ici
    } else if(op->type == OP_ASSIGN) { // Assignation, le pointeur du buffer pointera sur la valeur enregistrée
        rc = var_op_assign(var_r[0], var_r[1], eval_value);
    } else if(op->type & OP_OUTPUT) { // Type d'opération relevant d'un affichage (ne retourne rien)
        rc = var_output(var_r[0], op->type); // Ne modifie pas le buffer
    } else if(op->type & OP_UNIT_TYPE) { // Type d'opération relevant des appels de fonction/constructeur
        rc = unit_op(op->type, ec_obj, ec_var, op->value, var_r[0], *eval_value);
    } else if(op->type == OP_DEC_ATTR) { // Déclaration variable attribut, la nouvelle valeur sera pointée par le pointeur du buffer
        rc = ec_add_var(ec_obj, &op->identifier, eval_value); (*eval_value)->container = ec_obj; // On rattache l'élément membre à son objet
    } else if(op->type == OP_DEC_VAR) { // Déclaration variable temporaire, la nouvelle valeur sera pointée par le pointeur du buffer
        rc = ec_add_var(ec_var, &op->identifier, eval_value);
    } else if(op->type == OP_VALUE || op->type == OP_UNIT) { // Valeur naturelle ou fonction, on utilise le pointeur du buffer
        rc = RC_OK; (*eval_value) = op->value;
    } else if(op->type == OP_DELETE_VAR) { // Suppression variable, sa valeur sera recopiée dans le buffer et la variable deviendra anonyme
        rc = ec_pop_var(ec_var, &op->identifier, *eval_value);
    } else if(op->type == OP_DELETE_ATTR) { // Suppression attribut, sa valeur sera recopiée dans le buffer et la variable deviendra anonyme
        rc = ec_pop_var(ec_obj, &op->identifier, *eval_value);
    } else if(op->type == OP_ATTR_ACCESS) { // Accès valeur attribut, on utilise le pointeur du buffer
        rc = var_op_attr_access(var_r[0], &op->identifier, eval_value);
    } else if(op->type & OP_ACCES) { // Accès de variable
        rc = ec_var_access(ec_obj, ec_var, op->type, &op->identifier, eval_value); // Utilise le pointeur du buffer
    } else if(op->type == OP_RETURN) { // Return
        rc = RC_RETURN; var_op_return(var_r[0], *eval_value); // Recopier la valeur dans le buffer eval_value
    } else if(op->type == OP_BREAK) { // Break, aucune valeur retournée
        rc = RC_BREAK;
    } else { // Erreur de type d'opération
        err_add(E_ERROR, FORBIDDEN_TYPE, "Unknown type of operation (%x)", op->type); rc = RC_ERROR;
    }

    eval_end :
        // Libération buffer
        for(i = 0; i < 2; i++)
            if(var[i].type != T_NULL) var_empty(var + i); // Si la variable est à NULL, alors le buffer n'a pas été utilisé

        return rc;
}

static return_code unit_op(operation_type type, Exec_context* ec_obj, Exec_context* ec_var, Variable* args, Variable* function, Variable* eval_value) {

    // Fonction classique
    if(function->type == T_FUNCTION) {
        if(type == OP_UNIT_NEW) // constructor
            return unit_constructor((function->container ? function->container : ec_obj), ec_var, (args ? args->value.v_llist : NULL), function->value.v_func, eval_value);
        else // fonction
            return unit_function((function->container ? function->container : ec_obj), ec_var, (args ? args->value.v_llist : NULL), function->value.v_func, eval_value);
    }
    // Fonction built-in
    else if(function->type == T_FUNCTION_BUILTIN) {
        return unit_function_builtin((function->container ? function->container : ec_obj), ec_var, function, (args ? args->value.v_llist : NULL), eval_value, type == OP_UNIT_NEW ? 1 : 0);
    }
    // Erreur
    else {
        err_add(E_ERROR, FORBIDDEN_TYPE, "Trying to use a '%s' as a function", language_type_debug(function->type));
        return RC_ERROR;
    }

}

// Vérifié
// Initialisation d'unit
return_code op_init_loc(Operation *op, operation_type type, Operation *left, Operation *right, Variable *value) {
    if(op) {
        op->identifier.s = NULL;
        op->identifier.s_h = 0;
        op->operations[0] = left;
        op->operations[1] = right;
        op->type = type;
        op->value = value;
    }
    return RC_OK;
}

// Vérifié
// Initialisation et allocation avec retour de pointeur
Operation* op_new(operation_type type, Operation *left, Operation *right, Variable *value) {
    Operation *op = (Operation*)xmalloc(sizeof(Operation));
    op_init_loc(op, type, left, right, value);
    return op;
}

// Vérifié
// Destruction d'opération
void op_delete(Operation *op) {
    int i = 0;
    if(op) {
        for(; i < 2; i++) {
            if(op->operations[i])
                op_delete(op->operations[i]);
        }

        if(op->identifier.s)
            xfree(op->identifier.s);

        if(op->value) { // Valeur
            // Cas spécial des fonctions
            if(op->value->type == T_FUNCTION) {
                unit_empty(op->value->value.v_func);
                xfree(op->value->value.v_func);
                op->value->value.v_func = NULL;
            }
            var_delete(op->value);
        }

        xfree(op);
    }
}
