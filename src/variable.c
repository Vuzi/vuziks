#include "variable.h"

// Pour la mise en page des dumps et aux affichages de debug
int debug_lvl = 0;

void debug_pr_lvl(void) {
    int i = 0;
    for(; i < debug_lvl; i++)
        fputs("|  ", stdout);
}

// Type de variable
const char* language_type_debug(language_type l) {
    switch(l) {
        case T_NUM:
            return "digital";
        case T_NULL:
            return "null";
        case T_BOOL:
            return "boolean";
        case T_ARRAY:
            return "array";
        case T_REF:
            return "reference";
        case T_OBJECT:
            return "object";
        default :
            return "(Error type)";
    }
}

// Initialisation
return_code var_init(Variable **a, const char* name, language_type type) {

    if(!(*a)) {
        (*a) = (Variable*)malloc(sizeof(Variable));
    }

    (*a)->name = (name ? str_copy(name) : NULL);
    (*a)->name_h = (name ? str_hash(name) : 0);
    (*a)->type = type;

    switch(type) {
        case T_NULL :
            return RC_OK;
        case T_BOOL :
            (*a)->value.v_bool = 0;
            return RC_OK;
        case T_NUM :
            (*a)->value.v_num = 0.0;
            return RC_OK;
        case T_ARRAY :
            return RC_OK;
        case T_REF :
            return RC_OK;
        case T_OBJECT :
            return RC_OK;
        default :
            err_add(E_CRITICAL, UNKOWN_TYPE, "Creation with an unknown type : the variable type cannot be resolved as a known type");
            return RC_ERROR;
    }
}


// Opérations
return_code var_op_add(Variable *a, Variable *b, Variable *r) {
    r->value.v_num = a->value.v_num + b->value.v_num;
    return RC_OK;
}

return_code var_op_min(Variable *a, Variable *b, Variable *r) {
    r->value.v_num = a->value.v_num - b->value.v_num;
    return RC_OK;
}

return_code var_op_mult(Variable *a, Variable *b, Variable *r) {
    r->value.v_num = a->value.v_num * b->value.v_num;
    return RC_OK;
}

return_code var_op_pow(Variable *a, Variable *b, Variable *r) {
    r->value.v_num = pow(a->value.v_num, b->value.v_num);
    return RC_OK;
}

return_code var_op_div(Variable *a, Variable *b, Variable *r) {
    if(a->value.v_num != 0) {
        r->value.v_num = a->value.v_num / b->value.v_num;
        return RC_OK;
    } else {
        err_add(E_CRITICAL, OP_IMPOSSIBLE, "Division by zero : it's not a clever thing to do in programming");
        return RC_ERROR;
    }
}

return_code var_op_intdiv(Variable *a, Variable *b, Variable *r) {
    if(a->value.v_num != 0) {
        r->value.v_num = integer_division(a->value.v_num, b->value.v_num);
        return RC_OK;
    } else {
        err_add(E_CRITICAL, OP_IMPOSSIBLE, "Division by zero : it's not a clever thing to do in programming");
        return RC_ERROR;
    }
}

return_code var_op_modulo(Variable *a, Variable *b, Variable *r) {
    r->value.v_num = modulo(a->value.v_num, b->value.v_num);
    return RC_OK;
}

// Operation mathématique
return_code var_op_math(Variable *a, Variable *b, Variable *r, operation_type type) {

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
                err_add(E_CRITICAL, UNKOWN_TYPE, "Operation with an unknown type : the operation type cannot be resolved as a known type");
                return RC_ERROR;
        }
    } else {
        err_add(E_CRITICAL, FORBIDDEN_TYPE, "Operation with a forbidden type : only digital type can use mathematical operator");
        return RC_ERROR;
        // todo : ajouter les types posant problème à l'erreur
    }
}

return_code var_op_un_p(Variable *a, Variable *r) {
    r->value.v_num = a->value.v_num;
    return RC_OK;
}

return_code var_op_un_m(Variable *a, Variable *r) {
    r->value.v_num = - (a->value.v_num);
    return RC_OK;
}

// Operation mathématique unaire
return_code var_op_math_unary(Variable *a,Variable *r, operation_type type) {

    if(a->type == T_NUM) {

        r->type = T_NUM;

        switch(type) {
            case OP_MATH_P_UNARY :
                return var_op_un_p(a, r);
            case OP_MATH_M_UNARY :
                return var_op_un_m(a, r);
            default :
                err_add(E_CRITICAL, UNKOWN_TYPE, "Unary operation with an unknown type : the operation type cannot be resolved as a known type");
                return RC_ERROR;
        }
    } else {
        err_add( E_CRITICAL, FORBIDDEN_TYPE, "Unary operation with a forbidden type : only digital type can use unary mathematical operator");
        return RC_ERROR;
        // todo : ajouter les types posant problème à l'erreur
    }
}

return_code var_op_comp(Variable *a, Variable *b, Variable *r, operation_type type) {


    if(a->type == T_NUM && a->type == b->type) {

        r->type = T_BOOL;
        puts("hello");
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
                err_add(E_CRITICAL, UNKOWN_TYPE, "Comparison with an unknown type : the comparison type cannot be resolved as a known type");
                return RC_ERROR;
        }
   } else {
        err_add(E_CRITICAL, FORBIDDEN_TYPE, "Comparison with a forbidden type : only digital type can use compararison operator");
        return RC_ERROR;
        // todo : ajouter les types posant problème à l'erreur
    }

    return RC_OK;
}

return_code var_op_equal(Variable *a, Variable *b, Variable *r, operation_type type) {

    r->type = T_BOOL;

    if(a->type == b->type) {
        switch(a->type) {
            case T_NULL:
                r->value.v_bool = (a == b ? 1 : 0);
                break;
            case T_BOOL:
                r->value.v_bool = (a->value.v_bool == b->value.v_bool ? 1 : 0);
                break;
            case T_ARRAY :
                r->value.v_bool = (a/*->value.v_array*/ == b/*->value.v_array*/ ? 1 : 0);
                break;
            case T_REF :
                r->value.v_bool = (a/*->value.v_ref*/ == b/*->value.v_ref*/ ? 1 : 0);
                break;
            case T_OBJECT :
                r->value.v_bool = (a/*->value.v_object*/ == b/*->value.v_object*/ ? 1 : 0);
                break;
            default :
                err_add(E_CRITICAL, UNKOWN_TYPE, "Equality comparison with an unknown variable type : the type compared cannot be resolved as a known variable type");
                return RC_ERROR;
        }
    } else {
        r->value.v_bool = 0;
    }

    if(type == OP_LOG_DIF)
        r->value.v_bool = r->value.v_bool ? 1 : 0;

    return RC_OK;
}

return_code var_op_type(Variable *a, Variable *b, Variable *r, operation_type type) {

    r->type = T_BOOL;
    r->value.v_bool = (a->type == b->type ? 1 : 0);

    return RC_OK;
}

return_code var_op_or_and(Variable *a, Variable *b, Variable *r, operation_type type) {

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
                err_add(E_CRITICAL, UNKOWN_TYPE, "Logical operation with an unknown type : the logical operation type cannot be resolved as a known type");
                return RC_ERROR;
        }
    } else {
        err_add(E_CRITICAL, FORBIDDEN_TYPE, "Logical operation with a forbidden type : only booleab type can use logical operator");
        return RC_ERROR;
        // todo : ajouter les types posant problème à l'erreur
    }

    return RC_OK;
}

return_code var_op_not(Variable *a, Variable *b, Variable *r) {

    if(a->type == T_BOOL) {

        r->type = T_BOOL;
        r->value.v_bool = (a->value.v_bool ? 0 : 1);

    } else {
        err_add(E_CRITICAL, FORBIDDEN_TYPE, "Logical operation with a forbidden type : only booleab type can use logical operator");
        return RC_ERROR;
        // todo : ajouter les types posant problème à l'erreur
    }

    return RC_OK;
}

return_code var_op_log(Variable *a, Variable *b, Variable *r, operation_type type) {

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
            return var_op_type(a, b, r, type);
        case OP_LOG_AND :
        case OP_LOG_OR :
            return var_op_or_and(a, b, r, type);
        case OP_LOG_NOT :
            return var_op_not(a, b, r);
        default :
            err_add(E_CRITICAL, UNKOWN_TYPE, "Logical comparison or operation with an unknown type : the operation type cannot be resolved as a known type");
            return RC_ERROR;
    }
}

// Effectuer une opération mathématique
return_code var_op(Variable *a, Variable *b, Variable *r, operation_type type) {
    if(OP_MATH & type)
        return var_op_math(a, b, r, type);
    else if(OP_MATH_UNARY & type)
        return var_op_math_unary(a, r, type);
    else if(OP_LOG & type)
        return var_op_log(a, b, r, type);
    /*else if(OP_UNIT & type)
        return var_op_unit(a, b, type);*/
    else if(OP_PARENTH == type) {
        r->type = a->type; r->value = a->value;
        return RC_OK;
    } else {
        err_add(E_CRITICAL, UNKOWN_TYPE, "Unknown type of operation between two variable");
        return RC_ERROR;
        // todo : écrire l'erreur
    }
}

// Affichage debug
void var_dump(Variable *v) {
    debug_pr_lvl(), puts(">variable :");
    if(v) {
        debug_pr_lvl(), printf("  name : %s\n", v->name);
        debug_pr_lvl(), printf("  name_h : %lu\n", (long unsigned)v->name_h);
        debug_pr_lvl(), printf("  type : %s\n", language_type_debug(v->type));
        debug_pr_lvl(), fputs("  value : ", stdout);

        switch(v->type) {
            case T_NUM:
                printf("%lf\n", v->value.v_num);
                break;
            case T_BOOL:
                v->value.v_bool ? puts("True") : puts("False");
                break;
            case T_NULL:
                puts("null");
                break;
            /* Autres case à faire */
            default :
                puts("(Error type)");
        }
    } else
        debug_pr_lvl(), puts("\t(null)");
}
