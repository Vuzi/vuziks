
/* ==       Fichier variableOp.c       == */

#include "variableOp.h"

// Prototypes statiques
static return_code var_op_add(Variable *a, Variable *b, Variable *r);
static return_code var_op_min(Variable *a, Variable *b, Variable *r);
static return_code var_op_mult(Variable *a, Variable *b, Variable *r);
static return_code var_op_pow(Variable *a, Variable *b, Variable *r);
static return_code var_op_div(Variable *a, Variable *b, Variable *r);
static return_code var_op_intdiv(Variable *a, Variable *b, Variable *r);
static return_code var_op_modulo(Variable *a, Variable *b, Variable *r);
static return_code var_op_math(Variable *a, Variable *b, Variable *r, operation_type type);
static return_code var_op_un_p(Variable *a, Variable *r);
static return_code var_op_un_m(Variable *a, Variable *r);
static return_code var_op_math_unary(Variable *a,Variable *r, operation_type type);
static return_code var_op_comp(Variable *a, Variable *b, Variable *r, operation_type type);
static return_code var_op_equal(Variable *a, Variable *b, Variable *r, operation_type type);
static return_code var_op_comp_type(Variable *a, Variable *b, Variable *r);
static return_code var_op_or_and(Variable *a, Variable *b, Variable *r, operation_type type);
static return_code var_op_not(Variable *a, Variable *r);
static return_code var_op_exist(Variable *a, Variable *r);
static return_code var_op_log(Variable *a, Variable *b, Variable *r, operation_type type);
static return_code var_op_type(Variable *a, Variable *b, Variable *v, operation_type type);
static return_code var_op_typeof(Variable *a, Variable *v);
static return_code var_op_typeis(Variable *a, Variable *b, Variable *v);
// Opération
static return_code var_op_add(Variable *a, Variable *b, Variable *r) {
    r->value.v_num = a->value.v_num + b->value.v_num;
    return RC_OK;
}

static return_code var_op_min(Variable *a, Variable *b, Variable *r) {
    r->value.v_num = a->value.v_num - b->value.v_num;
    return RC_OK;
}

static return_code var_op_mult(Variable *a, Variable *b, Variable *r) {
    r->value.v_num = a->value.v_num * b->value.v_num;
    return RC_OK;
}

static return_code var_op_pow(Variable *a, Variable *b, Variable *r) {
    r->value.v_num = pow(a->value.v_num, b->value.v_num);
    return RC_OK;
}

static return_code var_op_div(Variable *a, Variable *b, Variable *r) {
    if(b->value.v_num != .0) {
        r->value.v_num = a->value.v_num / b->value.v_num;
        return RC_OK;
    } else {
        err_add(E_CRITICAL, OP_IMPOSSIBLE, "Division by zero : it's not a clever thing to do in programming");
        return RC_ERROR;
    }
}

static return_code var_op_intdiv(Variable *a, Variable *b, Variable *r) {
    if(b->value.v_num != .0) {
        r->value.v_num = integer_division(a->value.v_num, b->value.v_num);
        return RC_OK;
    } else {
        err_add(E_CRITICAL, OP_IMPOSSIBLE, "Division by zero : it's not a clever thing to do in programming");
        return RC_ERROR;
    }
}

static return_code var_op_modulo(Variable *a, Variable *b, Variable *r) {
    r->value.v_num = modulo(a->value.v_num, b->value.v_num);
    return RC_OK;
}

// vérifié
// Operation mathématique
static return_code var_op_math(Variable *a, Variable *b, Variable *v, operation_type type) {

    if(a->type == T_NUM && a->type == b->type) {

        v->type = T_NUM;

        switch(type) {
            case OP_MATH_PLUS :
                return var_op_add(a, b, v);
            case OP_MATH_MINUS :
                return var_op_min(a, b, v);
            case OP_MATH_MULT :
                return var_op_mult(a, b, v);
            case OP_MATH_POW :
                return var_op_pow(a, b, v);
            case OP_MATH_DIV :
                return var_op_div(a, b, v);
            case OP_MATH_INTDIV :
                return var_op_intdiv(a, b, v);
            case OP_MATH_MODULO :
                return var_op_modulo(a, b, v);
            default :
                err_add(E_CRITICAL, UNKOWN_TYPE, "Unknown type of operation (%x) : the operation type cannot be resolved as a known type", type);
                return RC_ERROR;
        }
    } else {
        err_add(E_CRITICAL, FORBIDDEN_TYPE, "Operation with a forbidden type (%s and %s) : only digital type can use mathematical operator",
                language_type_debug(a->type), language_type_debug(b->type));
        return RC_ERROR;
    }
}

// Opération
static return_code var_op_un_p(Variable *a, Variable *r) {
    r->value.v_num = a->value.v_num;
    return RC_OK;
}

static return_code var_op_un_m(Variable *a, Variable *r) {
    r->value.v_num = - (a->value.v_num);
    return RC_OK;
}

// Vérifié
// Operation mathématique unaire
static return_code var_op_math_unary(Variable *a,Variable *v, operation_type type) {

    if(a->type == T_NUM) {

        v->type = T_NUM;

        switch(type) {
            case OP_MATH_P_UNARY :
                return var_op_un_p(a, v);
            case OP_MATH_M_UNARY :
                return var_op_un_m(a, v);
            default :
                err_add(E_CRITICAL, UNKOWN_TYPE, "Unknown type of unary operation (%x) : the operation type cannot be resolved as a known type", type);
                return RC_ERROR;
        }
    } else {
        err_add(E_CRITICAL, FORBIDDEN_TYPE, "Operation with a forbidden type (%s) : only digital type can use unary mathematical operator", language_type_debug(a->type));
        return RC_ERROR;
    }
}

// Opération
static return_code var_op_comp(Variable *a, Variable *b, Variable *r, operation_type type) {

    if(a->type == T_NUM && a->type == b->type) {
        r->type = T_BOOL;
        switch(type) {
            case OP_LOG_GT :
                r->value.v_bool = ( a->value.v_num > b->value.v_num ? 1 : 0 );
                break;
            case OP_LOG_GE :
                r->value.v_bool = ( a->value.v_num >= b->value.v_num ? 1 : 0 );
                break;
            case OP_LOG_LT :
                r->value.v_bool = ( a->value.v_num <  b->value.v_num ? 1 : 0 );
                break;
            case OP_LOG_LE :
                r->value.v_bool = ( a->value.v_num <= b->value.v_num ? 1 : 0 );
                break;
            default :
                err_add(E_CRITICAL, UNKOWN_TYPE, "Unknown type of operation (%x) : the operation type cannot be resolved as a known type", type);
                return RC_ERROR;
        }
   } else {
        err_add(E_CRITICAL, FORBIDDEN_TYPE, "Operation with a forbidden type (%s and %s) : only digital type can use mathematical operator",
                language_type_debug(a->type), language_type_debug(b->type));
        return RC_ERROR;
    }

    return RC_OK;
}

static return_code var_op_equal(Variable *a, Variable *b, Variable *r, operation_type type) {

    r->type = T_BOOL;

    if(a->type == b->type) {
        switch(a->type) {
            case T_NONEXISTENT:
                r->value.v_bool = 0; // Toujours faux
                break;
            case T_TYPE:
                r->value.v_bool = (a->value.v_type == b->value.v_type ? 1 : 0);
                break;
            case T_NULL:
                r->value.v_bool = (a == b ? 1 : 0);
                break;
            case T_NUM:
                r->value.v_bool = (a->value.v_num == b->value.v_num ? 1 : 0);
                break;
            case T_BOOL:
                r->value.v_bool = (a->value.v_bool == b->value.v_bool ? 1 : 0);
                break;
            case T_ARRAY :
                r->value.v_bool = (a/*->value.v_array*/ == b/*->value.v_array*/ ? 1 : 0);
                break;
            case T_FUNCTION_BUILTIN :
                r->value.v_bool = (a->value.v_func_builtin == b->value.v_func_builtin ? 1 : 0);
                break;
            case T_FUNCTION :
                r->value.v_bool = (a->value.v_func == b->value.v_func ? 1 : 0);
                break;
            case T_OBJECT :
                r->value.v_bool = (a->value.v_obj == b->value.v_obj ? 1 : 0);
                break;
            default :
                err_add(E_CRITICAL, UNKOWN_TYPE, "Equality comparison with an unknown variable type (%x) : the type compared cannot be resolved as a known variable type", type);
                return RC_ERROR;
        }
    } else {
        r->value.v_bool = 0;
    }

    if(type == OP_LOG_DIF)
        r->value.v_bool = r->value.v_bool ? 1 : 0;

    return RC_OK;
}

static return_code var_op_comp_type(Variable *a, Variable *b, Variable *r) {

    r->type = T_BOOL;
    r->value.v_bool = (a->type == b->type ? 1 : 0);

    return RC_OK;
}

static return_code var_op_or_and(Variable *a, Variable *b, Variable *r, operation_type type) {

    if(a->type == T_BOOL && a->type == b->type) {

        r->type = T_BOOL;
        switch(type) {
            case OP_LOG_AND :
                r->value.v_bool = ( a->value.v_bool &&  b->value.v_bool ? 1 : 0 );
                break;
            case OP_LOG_OR :
                r->value.v_bool = ( a->value.v_bool ||  b->value.v_bool ? 1 : 0 );
                break;
            default :
                err_add(E_CRITICAL, UNKOWN_TYPE, "Unknown type of logical operation (%x) : the logical operation type cannot be resolved as a known type", type);
                return RC_ERROR;
        }
    } else {
        err_add(E_CRITICAL, FORBIDDEN_TYPE, "Logical operation with a forbidden type (%s and %s) : only boolean type can use logical operator",
                language_type_debug(a->type), language_type_debug(b->type));
        return RC_ERROR;
    }

    return RC_OK;
}

static return_code var_op_not(Variable *a, Variable *r) {

    if(a->type == T_BOOL) {

        r->type = T_BOOL;
        r->value.v_bool = (a->value.v_bool ? 0 : 1);

    } else {
        err_add(E_CRITICAL, FORBIDDEN_TYPE, "Logical operation with a forbidden type (%s) : only boolean type can use mathematical operator",
                language_type_debug(a->type));
        return RC_ERROR;
    }

    return RC_OK;
}

static return_code var_op_exist(Variable *a, Variable *r) {

    r->type = T_BOOL;
    r->value.v_bool = (a->type == T_NONEXISTENT ? 0 : 1);

    return RC_OK;
}

// Opération logique
static return_code var_op_log(Variable *a, Variable *b, Variable *v, operation_type type) {

    switch(type) {
        case OP_LOG_GT :
        case OP_LOG_GE :
        case OP_LOG_LT :
        case OP_LOG_LE :
            return var_op_comp(a, b, v, type);
        case OP_LOG_EQ :
        case OP_LOG_DIF :
            return var_op_equal(a, b, v, type);
        case OP_LOG_TYPE :
            return var_op_comp_type(a, b, v);
        case OP_LOG_AND :
        case OP_LOG_OR :
            return var_op_or_and(a, b, v, type);
        case OP_LOG_NOT :
            return var_op_not(a, v);
        case OP_LOG_EXIST :
            return var_op_exist(a, v);
        default :
            err_add(E_CRITICAL, UNKOWN_TYPE, "Unknown type of logical operation : the operation type cannot be resolved as a known type");
            return RC_ERROR;
    }
}

// Opération logique
static return_code var_op_type(Variable *a, Variable *b, Variable *v, operation_type type) {

    switch(type) {
        case OP_TYPE_TYPEOF :
            return var_op_typeof(a, v);
        case OP_TYPE_IS :
            return var_op_typeis(a, b, v);
        default :
            err_add(E_CRITICAL, UNKOWN_TYPE, "Unknown type of type operation : the operation type cannot be resolved as a known type");
            return RC_ERROR;
    }
}

static return_code var_op_typeof(Variable *a, Variable *v) {

    v->type = T_TYPE;
    v->value.v_type = a->type;

    return RC_OK;
}

static return_code var_op_typeis(Variable *a, Variable *b, Variable *v) {

    v->type = T_BOOL;

    if(b->type != T_TYPE) {
        v->value.v_bool = 0;
        err_add(E_WARNING, FORBIDDEN_TYPE, "Using the 'is' operation with another type (%s) than 'type'", language_type_debug(b->type));
        return RC_WARNING;
    }

    v->value.v_bool = a->type == b->value.v_type ? 1 : 0;
    return RC_OK;

}

// Accès à un attribut
return_code var_op_attr_access(Variable *a, Operation_identifier *id, Variable **eval_value) {
    if(a->type == T_NONEXISTENT) {
        err_add(E_ERROR, FORBIDDEN_TYPE, "Cannot access member variable of a non-existent variable : '%s'", var_name(a));
        return RC_ERROR;
    } else {
        if(a->type == T_OBJECT) {
            // Sécurité provisoire
            if(a->name_h) {
                Variable *v = (a->value.v_obj ? var_search(a->value.v_obj->ec.variables, id->s, id->s_h) : NULL);
                if(v) {
                    *eval_value = v;
                    return RC_OK;
                } else {
                    (*eval_value)->type = T_NONEXISTENT; (*eval_value)->name = id->s;
                    err_add(E_WARNING, CANT_ACCESS, "Cannot access member variable '%s' in object '%s'", id->s, var_name(a));
                    return RC_WARNING;
                }
            } else {
                err_add(E_ERROR, FORBIDDEN_TYPE, "Cannot access member variable (%s) of temporary variable", id->s);
                return RC_ERROR;
            }
        } else {
            err_add(E_ERROR, FORBIDDEN_TYPE, "Cannot access member variable (%s) using a non-objet variable (%s - %s)",
                    id->s, var_name(a), language_type_debug(a->type));
            return RC_ERROR;
        }
    }
}

// vérifié
// Copie une variable dans v en vue de la retourner
return_code var_op_return(Variable *a, Variable* eval_value) {
    // On vérifie si le type est retournable
    if(a->type != T_NONEXISTENT) {
        switch(a->type) {
            // Cas par recopie simple
            case T_NULL :
            case T_TYPE :
            case T_NUM :
            case T_BOOL :
            case T_FUNCTION :
            case T_FUNCTION_BUILTIN :
                eval_value->value = a->value;
                eval_value->type= a->type;
                return RC_OK;
            // Cas par recopie de référence
            case T_OBJECT :
                eval_value->value.v_obj = a->value.v_obj;
                eval_value->value.v_obj->n_links++;
                eval_value->type= a->type;
                return RC_OK;
            case T_LINKEDLIST :
                // A refaire
                //var_op_assign_llist(a, b);
                eval_value->type= a->type;
                return RC_OK;
            case T_ARRAY :
                // A refaire
                // var_op_assign_array(a, b);
                eval_value->type= a->type;
                return RC_OK;
            default :
                err_add(E_CRITICAL, UNKOWN_TYPE, "Unknown type (%x) of returned variable", a->type);
                return RC_ERROR;
        }

    } else {
        err_add(E_WARNING, FORBIDDEN_TYPE, "Cannot return non-existent value (null value will be returned)");
        return RC_WARNING;
    }
}

// Vérifié
// Assigne b dans a, sans modifier l'adresse de a (correspond au a = b )
return_code var_op_assign(Variable* a, Variable* b, Variable** eval_value) {

    // On vérifie si a est déclaré
    if(a->name_h != 0) {
        // On vérifie si le type est affectable
        if(b->type != T_NONEXISTENT) {
            *eval_value = a;
            switch(b->type) {
                // Cas par recopie simple
                case T_NULL :
                case T_TYPE :
                case T_NUM :
                case T_BOOL :
                case T_FUNCTION :
                case T_FUNCTION_BUILTIN :
                    a->value = b->value;
                    a->type= b->type;
                    return RC_OK;
                // Cas par recopie de référence
                case T_OBJECT :
                    if(a->value.v_obj != b->value.v_obj) {
                        a->value.v_obj = b->value.v_obj;
                        a->value.v_obj->n_links++;
                        a->type= b->type;
                    }
                    return RC_OK;
                case T_LINKEDLIST :
                    // A refaire
                    //var_op_assign_llist(a, b);
                    a->type= b->type;
                    return RC_OK;
                case T_ARRAY :
                    // A refaire
                    // var_op_assign_array(a, b);
                    a->type= b->type;
                    return RC_OK;
                default :
                    err_add(E_CRITICAL, UNKOWN_TYPE, "Unknown type (%x) of assignated variable", b->type);
                    return RC_ERROR;
            }

        } else {
            err_add(E_ERROR, FORBIDDEN_TYPE, "Cannot assign value of type nonexistent (%s)", var_name(b));
            return RC_ERROR;
        }
    } else {
        // On vérifie si le type était affectable
        if(a->type == T_NONEXISTENT) {
            err_add(E_ERROR, FORBIDDEN_TYPE, "Cannot assign value to nonexistent variable (%s)", var_name(a));
            return RC_ERROR;
        } else {
            err_add(E_ERROR, FORBIDDEN_TYPE, "Cannot assign value to temporary variable");
            return RC_ERROR;
        }
    }

}

// vérifié
// Effectuer une opération mathématique
return_code var_op(Variable* a, Variable* b, Variable* eval_value, operation_type type) {

    // Hub de traitement des opérations maths, logique, et d'assignation
    // Tous ces traitements écrivent leurs résultats directement dans la variable
    // Pointée par eval_value

    if(OP_MATH & type) // Opération mathématique
        return var_op_math(a, b, eval_value, type);
    else if(OP_MATH_UNARY & type) // Opération mathématique unaire
        return var_op_math_unary(a, eval_value, type);
    else if(OP_LOG & type) // Opération logique
        return var_op_log(a, b, eval_value, type);
    else if(OP_TYPE & type) // Opération sur les types
        return var_op_type(a, b, eval_value, type);
    else { // Erreur opération inconnue !
        err_add(E_CRITICAL, UNKOWN_TYPE, "Unknown type of operation (%x) between two variables", type);
        return RC_ERROR;
    }
}
