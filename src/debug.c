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
        default :
            return "(Error type)";
    }
}


void unit_dump(Unit *u) {

    Linked_list *ll = u->operations;
    debug_pr_lvl(), puts(">unit :");

    debug_lvl++;
    while(ll) {
        debug_pr_lvl(), puts("   operations : ");
        op_dump((Operation*)(ll->value));
        ll = ll->next;
    }
    debug_lvl--;
}

void op_dump(Operation *o) {

    debug_pr_lvl(), puts(">operation :");

    debug_pr_lvl(), printf("  type : %x\n", o->type);

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
    debug_pr_lvl(), puts(">variable :");
    if(v) {
        debug_pr_lvl(), printf("  name : %s\n", v->name);
        debug_pr_lvl(), printf("  name_h : %lu\n", (long unsigned)v->name_h);
        debug_pr_lvl(), printf("  type : %s\n", language_type_debug(v->type));
        debug_pr_lvl(), printf("  n_links : %d\n", v->n_links);
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
        debug_pr_lvl(), puts("\t(null)");
}
