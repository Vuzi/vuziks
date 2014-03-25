
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
static return_code var_op_type(Variable *a, Variable *b, Variable *r);
static return_code var_op_or_and(Variable *a, Variable *b, Variable *r, operation_type type);
static return_code var_op_not(Variable *a, Variable *r);
static return_code var_op_exist(Variable *a, Variable *r);
static return_code var_op_log(Variable *a, Variable *b, Variable *r, operation_type type);
static return_code var_op_assign(Variable *a, Variable *b, Variable **r);

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

// Operation mathématique
static return_code var_op_math(Variable *a, Variable *b, Variable *r, operation_type type) {

    if(a->type == T_NUM && a->type == b->type) {

        r->type = T_NUM;

        switch(type) {
            case OP_MATH_PLUS :
                return var_op_add(a, b, r);
            case OP_MATH_MINUS :
                return var_op_min(a, b, r);
            case OP_MATH_MULT :
                return var_op_mult(a, b, r);
            case OP_MATH_POW :
                return var_op_pow(a, b, r);
            case OP_MATH_DIV :
                return var_op_div(a, b, r);
            case OP_MATH_INTDIV :
                return var_op_intdiv(a, b, r);
            case OP_MATH_MODULO :
                return var_op_modulo(a, b, r);
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

// Operation mathématique unaire
static return_code var_op_math_unary(Variable *a,Variable *r, operation_type type) {

    if(a->type == T_NUM) {

        r->type = T_NUM;

        switch(type) {
            case OP_MATH_P_UNARY :
                return var_op_un_p(a, r);
            case OP_MATH_M_UNARY :
                return var_op_un_m(a, r);
            default :
                err_add(E_CRITICAL, UNKOWN_TYPE, "Unknown type of operation (%x) : the operation type cannot be resolved as a known type", type);
                return RC_ERROR;
        }
    } else {
        err_add(E_CRITICAL, FORBIDDEN_TYPE, "Operation with a forbidden type (%s) : only digital type can use mathematical operator", language_type_debug(a->type));
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
            case T_FUNCTION :
                r->value.v_bool = (a->value.v_func == b->value.v_func ? 1 : 0);
                break;
            case T_OBJECT :
                r->value.v_bool = (&(a->value.v_obj) == &(b->value.v_obj) ? 1 : 0);
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

static return_code var_op_type(Variable *a, Variable *b, Variable *r) {

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
static return_code var_op_log(Variable *a, Variable *b, Variable *r, operation_type type) {

    switch(type) {
        case OP_LOG_GT :
        case OP_LOG_GE :
        case OP_LOG_LT :
        case OP_LOG_LE :
            return var_op_comp(a, b, r, type);
        case OP_LOG_EQ :
        case OP_LOG_DIF :
            return var_op_equal(a, b, r, type);
        case OP_LOG_TYPE :
            return var_op_type(a, b, r);
        case OP_LOG_AND :
        case OP_LOG_OR :
            return var_op_or_and(a, b, r, type);
        case OP_LOG_NOT :
            return var_op_not(a, r);
        case OP_LOG_EXIST :
            return var_op_exist(a, r);
        default :
            err_add(E_CRITICAL, UNKOWN_TYPE, "Unknown type of logical operation : the operation type cannot be resolved as a known type");
            return RC_ERROR;
    }
}

// Accès à un attribut
return_code var_op_attr_access(Variable *a, const char* name, hash_t name_h, Variable **r) {
    if(a->type == T_NONEXISTENT) {
        err_add(E_ERROR, FORBIDDEN_TYPE, "Cannot access member variable of a non-existent variable : '%s'", a->name);
        return RC_ERROR;
    } else {
        if(a->type == T_OBJECT) {
            Variable *v = (a->value.v_obj ? var_search(a->value.v_obj->ec.variables, name, name_h) : NULL);
            if(v) {
                *r = v;
                return RC_OK;
            } else {
                // A mieux faire
                err_add(E_ERROR, CANT_ACCESS, "Cannot access member variable '%s' (hash : %lu)", name, (long unsigned)name_h);
                return RC_ERROR;
            }
        } else {
            err_add(E_ERROR, FORBIDDEN_TYPE, "Cannot access member variable using a non-objet variable");
            return RC_ERROR;
        }
    }
}

// Assigne b dans a, sans modifier l'adresse de a (correspond au a = b )
return_code var_op_assign(Variable *a, Variable *b, Variable **r) {

    // On vérifie si a est déclaré
    if(a->name_h != 0) {
        // On vérifie si le type est affectable
        if(b->type != T_NONEXISTENT) {
            *r = a;
            switch(b->type) {
                // Cas par recopie simple
                case T_NULL :
                case T_NUM :
                case T_BOOL :
                case T_FUNCTION :
                    a->value = b->value;
                    a->type= b->type;
                    return RC_OK;
                // Cas par recopie de référence
                case T_OBJECT :
                    a->value.v_obj = b->value.v_obj;
                    a->value.v_obj->n_links++;
                    a->type= b->type;
                    return RC_OK;
                case T_LINKEDLIST :
                    // A refaire
                    //var_op_assign_llist(a, b);
                    a->type= b->type;
                    return RC_OK;
                case T_ARRAY :
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
        // On vérifie si le type est affectable
        if(b->type != T_NONEXISTENT) {
            err_add(E_ERROR, FORBIDDEN_TYPE, "Cannot assign value of type nonexistent (%s)", var_name(b));
            return RC_ERROR;
        } else {
            err_add(E_ERROR, FORBIDDEN_TYPE, "Cannot assign value to temporary variable");
            return RC_ERROR;
        }
    }

}

// Effectuer une opération mathématique
return_code var_op(Variable *a, Variable *b, Variable **r, operation_type type) {

    // Hub de traitement des variable. Que ce soit opération, accès, affectation, toute
    // opération de ce type passe par là, d'où la présence de et binaire pour éviter de
    // perdre du temps et limiter les traitement

    if(OP_MATH & type) // Opération mathématique
        return var_op_math(a, b, *r, type);
    else if(OP_MATH_UNARY & type) // Opération mathématique unaire
        return var_op_math_unary(a, *r, type);
    else if(OP_LOG & type) // Opération logique
        return var_op_log(a, b, *r, type);
    else if(OP_ASSIGN == type) // Assignation
        return var_op_assign(a, b, r);
    else { // Erreur opération inconnue !
        err_add(E_CRITICAL, UNKOWN_TYPE, "Unknown type of operation (%x) between two variables", type);
        return RC_ERROR;
    }
}
