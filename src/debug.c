#include "debug.h"



// Pour la mise en page des dumps et aux affichages de debug
int debug_lvl = 0;

void debug_pr_lvl(void) {
    int i = 0;
    for(; i < debug_lvl; i++)
        fputs("  |  ", stdout);
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
        case T_LINKEDLIST:
            return "linked list";
        case T_REF:
            return "reference";
        case T_FUNCTION:
            return "function";
        case T_OBJECT:
            return "object";
        case T_NONEXISTENT:
            return "non-existent";
        default :
            return "(Error type)";
    }
}

// Type d'opération
const char* operation_type_debug(operation_type o) {
    switch(o) {
        case OP_NOTHING:
            return "OP_NOTHING";
        case OP_UNIT_CALL:
            return "OP_UNIT_CALL";
        case OP_UNIT_NEW:
            return "OP_UNIT_NEW";
        case OP_MATH_PLUS:
            return "OP_MATH_PLUS";
        case OP_MATH_MINUS:
            return "OP_MATH_MINUS";
        case OP_MATH_MULT:
            return "OP_MATH_MULT";
        case OP_MATH_POW:
            return "OP_MATH_POW";
        case OP_MATH_DIV:
            return "OP_MATH_DIV";
        case OP_MATH_MODULO:
            return "OP_MATH_MODULO";
        case OP_MATH_INTDIV:
            return "OP_MATH_INTDIV";
        case OP_MATH_P_UNARY:
            return "OP_MATH_P_UNARY";
        case OP_MATH_M_UNARY:
            return "OP_MATH_M_UNARY";
        case OP_LOG_GT:
            return "OP_LOG_GT";
        case OP_LOG_GE:
            return "OP_LOG_GE";
        case OP_LOG_LT:
            return "OP_LOG_LT";
        case OP_LOG_LE:
            return "OP_LOG_LE";
        case OP_LOG_EQ:
            return "OP_LOG_EQ";
        case OP_LOG_DIF:
            return "OP_LOG_DIF";
        case OP_LOG_TYPE:
            return "OP_LOG_TYPE";
        case OP_LOG_NOT:
            return "OP_LOG_NOT";
        case OP_LOG_EXIST:
            return "OP_LOG_EXIST";
        case OP_LOG_AND:
            return "OP_LOG_AND";
        case OP_LOG_OR:
            return "OP_LOG_OR";
        case OP_REF_GET:
            return "OP_REF_GET";
        case OP_REF_ACCESS:
            return "OP_REF_ACCESS";
        case OP_ASSIGN:
            return "OP_ASSIGN";
        case OP_VALUE:
            return "OP_VALUE";
        case OP_DEC_VAR:
            return "OP_DEC_VAR";
        case OP_DEC_ATTR:
            return "OP_DEC_ATTR";
        case OP_DELETE_VAR:
            return "OP_DELETE_VAR";
        case OP_DELETE_ATTR:
            return "OP_DELETE_ATTR";
        case OP_ACCES:
            return "OP_ACCES";
        case OP_ATTR_ACCESS:
            return "OP_ATTR_ACCESS";
        case OP_COMMA:
            return "OP_COMMA";
        case OP_RETURN:
            return "OP_RETURN";
        case OP_BREAK:
            return "OP_BREAK";
        case OP_OUTPUT_VAR_DUMP:
            return "OP_OUTPUT_VAR_DUMP";
        default :
            return "(Error type)";
    }
}


void unit_dump(Unit *u) {

    Linked_list *ll = u->operations;
    debug_pr_lvl(), puts(">unit :");

    while(ll) {
        debug_pr_lvl(), puts("  operations : ");
        debug_lvl++;
        op_dump((Operation*)(ll->value));
        ll = ll->next;
        debug_lvl--;
    }
}

void op_dump(Operation *o) {

    debug_pr_lvl(), puts(">operation :");

    debug_pr_lvl(), printf("  type : %s (%x)\n", operation_type_debug(o->type), o->type);

    // Valeur
    if(o->info.val) {
        debug_pr_lvl(), printf("  info.val : %s\n", o->info.val);
        debug_pr_lvl(), printf("  info.val_h : %lu\n", (long unsigned)o->info.val_h);
    }

    // Variable
    if(o->value) {
        debug_pr_lvl(), printf("  info.value : \n");
        debug_lvl++;
        var_dump(o->value);
        debug_lvl--;
    }

    // Branches
    if(o->operations[0]) {
        debug_pr_lvl(), printf("  left operation : \n");
        debug_lvl++;
        op_dump(o->operations[0]);
        debug_lvl--;
    }

    if(o->operations[1]) {
        debug_pr_lvl(), printf("  right operation : \n");
        debug_lvl++;
        op_dump(o->operations[1]);
        debug_lvl--;
    }
}


// Affichage debug
void var_dump(Variable *v) {
    debug_pr_lvl(), fputs(">variable", stdout);
    if(v) {
        if(v->name) printf(" '%s' :\n", v->name);
        else puts(" <anonymous> :");
        debug_pr_lvl(), printf("  name_h : %lu\n", (long unsigned)v->name_h);
        debug_pr_lvl(), printf("  type : %s\n", language_type_debug(v->type));
        debug_pr_lvl(), printf("  n_links : %d\n", v->n_links);
        debug_pr_lvl(), printf("  deletable : %d\n", v->deletable);
        debug_pr_lvl(),  fputs("  value : ", stdout);

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
            case T_NONEXISTENT:
                puts("non-existent");
                break;
            case T_LINKEDLIST:
                puts("linked list");
                break;
            /* Autres case à faire */
            case T_REF:
                puts("reference : ");
                debug_lvl++;
                var_dump(v->value.v_ref);
                debug_lvl--;
                break;
            case T_FUNCTION:
                puts("function : ");
                debug_lvl++;
                unit_dump(v->value.v_func);
                debug_lvl--;
                break;
            case T_OBJECT:
                puts("object");
                break;
            default :
                puts("(Error type)");
        }
    } else
        debug_pr_lvl(), puts(" <null> : \n\t(null)");
}
