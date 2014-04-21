
/* ==       Fichier debug.c       ==*/

#include "debug.h"

// Afficher un certain nombre d'espace(s) - pour la mise en page des dumps
int debug_lvl = 0;

void debug_pr_lvl(void) {
    int i = 0;
    for(; i < debug_lvl; i++)
        fputs("  |  ", stdout);
}

// Type de variable en chaîne
const char* language_type_debug(language_type l) {
    switch(l) {
        case T_TYPE:
            return "type";
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
        case T_FUNCTION_BUILTIN:
            return "function built-in";
        case T_FUNCTION:
            return "function";
        case T_OBJECT:
            return "object";
        case T_ARGS:
            return "arguments";
        case T_NONEXISTENT:
            return "non-existent";
        default :
            return "(Error type)";
    }
}

// Type d'opération en chaîne
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
        case OP_TYPE_IS:
            return "OP_TYPE_IS";
        case OP_TYPE_TYPEOF:
            return "OP_TYPE_TYPEOF";
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
        case OP_ACCES_ATTR:
            return "OP_ACCES_ATTR";
        case OP_ACCES_VAR:
            return "OP_ACCES_VAR";
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
        case OP_UNIT:
            return "OP_UNIT";
        default :
            return "(Error type)";
    }
}

// Affichage debug d'unité
void unit_dump(Unit *u) {

    Linked_list *ll = u->statements;
    debug_pr_lvl(), puts(">unit :");

    debug_pr_lvl(), puts("  statements : ");
    debug_lvl++;

    while(ll) {
        switch(ll->type) {
            case LLT_UNIT :
                unit_dump((Unit*)(ll->value));
                break;
            case LLT_OPERATION :
                op_dump((Operation*)(ll->value));
                break;
            case LLT_VARIABLE :
                var_dump((Variable*)(ll->value));
                break;
            case LLT_CONDITION :
                unit_cond_dump((Unit_conditional*)(ll->value));
                break;
            case LLT_LOOP :
                unit_loop_dump((Unit_loop*)(ll->value));
                break;
            default :
                debug_pr_lvl(), puts(">(error type statement)");
        }
        ll = ll->next;
    }

    debug_lvl--;
}

// Affichage debug d'opération
void op_dump(Operation *o) {

    debug_pr_lvl(), puts(">operation :");

    debug_pr_lvl(), printf("  type : %s (%x)\n", operation_type_debug(o->type), o->type);

    // Valeur
    if(o->identifier.s) {
        debug_pr_lvl(), printf("  info.val : %s\n", o->identifier.s ? o->identifier.s : "(null)");
        debug_pr_lvl(), printf("  info.val_h : %lu\n", (long unsigned)o->identifier.s_h);
    }
    /*if(o->info.line)
        debug_pr_lvl(), printf("  info.line : %u\n", o->info.line);*/

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
        op_dump((Operation*)o->operations[0]);
        debug_lvl--;

    }
    if(o->operations[1]) {
        debug_pr_lvl(), printf("  right operation : \n");
        debug_lvl++;
        op_dump((Operation*)o->operations[1]);
        debug_lvl--;
    }
}

// Affichage debug variable
void var_dump(Variable *v) {
    debug_pr_lvl(), fputs(">variable", stdout);
    if(v) {
        if(v->container) fputs(" <attr>", stdout); else fputs(" <var>", stdout);
        if(v->name) printf(" '%s' :\n", v->name);
        else puts(" <anonymous> :");
        debug_pr_lvl(), printf("  name_h : %ld\n", (long unsigned)v->name_h);
        debug_pr_lvl(), printf("  type : %s\n", language_type_debug(v->type));
        debug_pr_lvl(),  fputs("  value : ", stdout);

        switch(v->type) {
            case T_TYPE:
                printf("%s\n", language_type_debug(v->value.v_type));
                break;
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
                // todo
                break;
            case T_FUNCTION_BUILTIN:
                puts("(compiled code)");
                break;
            case T_FUNCTION:
                puts("function : ");
                debug_lvl++;
                unit_dump(v->value.v_func);
                debug_lvl--;
                break;
            case T_OBJECT:
                puts("object : ");
                debug_lvl++;
                var_obj_dump(v->value.v_obj);
                debug_lvl--;
                break;
            case T_ARGS:
                puts("arguments : ");
                debug_lvl++;
                debug_pr_lvl(), puts("(todo)");
                //var_obj_dump(v->value.v_obj);
                debug_lvl--;
                break;
            default :
                puts("(Error type)");
        }
    } else
        debug_pr_lvl(), puts(" <null> : \n\t(null)");
}
/*
void var_obj_type_dump(Object *o) {
    var_search(o->ec->variables, name)
}*/

// Affichage debug objet
void var_obj_dump(Object *o) {
    debug_pr_lvl(), fputs(">object\n", stdout);
    if(o) {
        debug_pr_lvl(), printf("  n_links : %d\n", o->n_links);
        debug_pr_lvl(), printf("  variables :\n");

        debug_lvl++;
        Linked_list *ll = o->ec.variables;
        while(ll)
            var_dump((Variable*)ll->value), ll = ll->next;
        debug_lvl--;

    } else
        debug_pr_lvl(), fputs("  (null)\n", stdout);
}

void unit_cond_dump(Unit_conditional* uc) {

    Linked_list* ll = uc->statements;

    debug_pr_lvl(), puts(">conditional unit");
    debug_pr_lvl(), puts("  condition :");
        if(uc->condition) {
            debug_lvl++;
            op_dump(uc->condition);
            debug_lvl--;
        } else
            debug_pr_lvl(), puts("  (none)");



    debug_pr_lvl(), puts("  statements : ");
    debug_lvl++;

    while(ll) {
        switch(ll->type) {
            case LLT_UNIT :
                unit_dump((Unit*)(ll->value));
                break;
            case LLT_OPERATION :
                op_dump((Operation*)(ll->value));
                break;
            case LLT_VARIABLE :
                var_dump((Variable*)(ll->value));
                break;
            case LLT_CONDITION :
                unit_cond_dump((Unit_conditional*)(ll->value));
                break;
            case LLT_LOOP :
                // a faire
                break;
            default :
                debug_pr_lvl(), puts(">(error type statement)");
        }
        ll = ll->next;
    }

    debug_lvl--;

    if(uc->next)
        unit_cond_dump(uc->next);

}

void unit_loop_dump(Unit_loop *ul) {

    Linked_list* ll = ul->statements;

    debug_pr_lvl(), puts(">loop unit");
    debug_pr_lvl(), puts("  start statement :");
        if(ul->start_action) {
            debug_lvl++;
            op_dump(ul->start_action);
            debug_lvl--;
        } else
            debug_pr_lvl(), puts("  (none)");

    debug_pr_lvl(), puts("  start condition :");
        if(ul->start_condition) {
            debug_lvl++;
            op_dump(ul->start_condition);
            debug_lvl--;
        } else
            debug_pr_lvl(), puts("  (none)");

    debug_pr_lvl(), puts("  end condition :");
        if(ul->end_condition) {
            debug_lvl++;
            op_dump(ul->end_condition);
            debug_lvl--;
        } else
            debug_pr_lvl(), puts("  (none)");

    debug_pr_lvl(), puts("  statements : ");
    debug_lvl++;

    while(ll) {
        switch(ll->type) {
            case LLT_UNIT :
                unit_dump((Unit*)(ll->value));
                break;
            case LLT_OPERATION :
                op_dump((Operation*)(ll->value));
                break;
            case LLT_VARIABLE :
                var_dump((Variable*)(ll->value));
                break;
            case LLT_CONDITION :
                unit_cond_dump((Unit_conditional*)(ll->value));
                break;
            case LLT_LOOP :
                // a faire
                break;
            default :
                debug_pr_lvl(), puts(">(error type statement)");
        }
        ll = ll->next;
    }

    debug_lvl--;
}
