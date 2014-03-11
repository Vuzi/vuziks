#include <stdio.h>
#include <stdlib.h>

#include "variable.h"
#include "operation.h"

void test_variable(void) {

    Variable a, b, c;
    Variable *_a = &a, *_b = &b, *_c = &c;

    // Initialisation
    var_init(&_a, "a", T_NUM);
    var_init(&_b, "b", T_NUM);
    var_init(&_c, NULL, T_NUM);

    var_dump(_a);
    var_dump(_b);
    var_dump(_c);

    _a->value.v_num = 72.0;
    _b->value.v_num = 10.0;

    var_dump(_a);
    var_dump(_b);

    // == Tests d'opérations ==

    //a - b
    var_op(_a, _b, &_c, OP_MATH_MINUS);
    puts("\na - b = ");
    var_dump(_c);

    //a % b
    var_op(_a, _b, &_c, OP_MATH_MODULO);
    puts("\na % b = ");
    var_dump(_c);

    // == Tests logiques ==

    // a == b
    var_op(_a, _b, &_c, OP_LOG_EQ);
    puts("\na == b = ");
    var_dump(_c);

    // a > b
    var_op(_a, _b, &_c, OP_LOG_GT);
    puts("\na > b = ");
    var_dump(_c);

    // a === b
    var_op(_a, _b, &_c, OP_LOG_TYPE);
    puts("\na === b = ");
    var_dump(_c);

    // Test d'erreur
    var_init(&_a, "a", T_NULL);
    var_init(&_b, "b", T_NUM);

    var_op(_a, _b, &_c, OP_MATH_MINUS);
    puts("\na(null) - b(num) = ");

    err_display_last(&e);

    var_init(&_a, "a", T_BOOL);
    var_init(&_b, "b", T_NUM);

    var_op(_a, _b, &_c, OP_LOG_AND);
    puts("\na(bool) and b(num) = ");

    err_display_last(&e);
}

void test_node(void) {

    Operation root;

    Variable a, b, c, r;
    Variable *result = &r;

    var_init_loc(&a, NULL, T_NUM);
    var_init_loc(&b, NULL, T_NUM);
    var_init_loc(&c, NULL, T_NUM);
    var_init_loc(&r, NULL, T_NULL);

    a.value.v_num = 4.0;
    b.value.v_num = 2.0;
    c.value.v_num = 3.0;

    root.type = OP_MATH_PLUS;
    root.info.val = NULL;
    root.info.val_h = 0;
    root.value = NULL;

    root.operations[0] = malloc(sizeof(Operation));
    root.operations[0]->type = OP_VALUE;
    root.operations[0]->value = &a;
    root.operations[0]->operations[0] = NULL;
    root.operations[0]->operations[1] = NULL;

    root.operations[1] = malloc(sizeof(Operation));
    root.operations[1]->type = OP_MATH_MULT;

    root.operations[1]->operations[0] = malloc(sizeof(Operation));
    root.operations[1]->operations[0]->type = OP_VALUE;
    root.operations[1]->operations[0]->value = &b;
    root.operations[1]->operations[0]->operations[0] = NULL;
    root.operations[1]->operations[0]->operations[1] = NULL;

    root.operations[1]->operations[1] = malloc(sizeof(Operation));
    root.operations[1]->operations[1]->type = OP_VALUE;
    root.operations[1]->operations[1]->value = &c;
    root.operations[1]->operations[1]->operations[0] = NULL;
    root.operations[1]->operations[1]->operations[1] = NULL;

    // Voilà pourquoi c'est chiant à débugger, et encore c'est rien

    puts("Initialisation ok");

    /*
         4 + 2 * 3 = 10 (normalement)
         ----------------------
                +
              /   \
             4     *
                 /   \
                2     3
         ----------------------
    */

    if(op_eval(&root, &result) == RC_OK) // Ici marche, sinon tester type de retour
        var_dump(result);
    else
        err_display_last(&e);
}

int main(void) {

    //test_variable();
    test_node();

    return 0;
}
