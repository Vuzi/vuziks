#include <stdio.h>
#include <stdlib.h>

#include "variable.h"
#include "operation.h"
#include "unit.h"

#include "hash/hash.h"

void test_variable(void);
void test_node(void);

void test_variable(void) {

    Variable a, b, c;
    Variable *_a = &a, *_b = &b, *_c = &c;

    // Initialisation
    var_init(&_a, "a", str_hash("a"), T_NUM);
    var_init(&_b, "b", str_hash("b"), T_NUM);
    var_init(&_c, NULL, 0, T_NUM);

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
    var_init(&_a, "a", str_hash("a"), T_NULL);
    var_init(&_b, "b", str_hash("b"), T_NUM);

    var_op(_a, _b, &_c, OP_MATH_MINUS);
    puts("\na(null) - b(num) = ");

    err_display_last(&e);

    var_init(&_a, "a", str_hash("a"), T_BOOL);
    var_init(&_b, "b", str_hash("b"), T_NUM);

    var_op(_a, _b, &_c, OP_LOG_AND);
    puts("\na(bool) and b(num) = ");

    err_display_last(&e);
}

void test_node(void) {

    Exec_context ec_obj;
    Exec_context ec_tmp;

    Operation root;

    Variable a, b, c, r;
    Variable *result = &r;

    ec_obj.variables = NULL;
    ec_tmp.variables = NULL;

    var_init_loc(&a, "a", str_hash("a"), T_NUM);
    var_init_loc(&b, NULL, 0, T_NUM);
    var_init_loc(&c, NULL, 0, T_NUM);
    var_init_loc(&r, NULL, 0, T_NULL);

    a.value.v_num = 4.0;
    b.value.v_num = 2.0;
    c.value.v_num = 3.0;

    linked_list_append(&(ec_obj.variables), (void*)(&a));

    root.type = OP_MATH_PLUS;
    root.info.val = NULL;
    root.info.val_h = 0;
    root.value = NULL;

    root.operations[0] = malloc(sizeof(Operation));
    root.operations[0]->type = OP_ACCES;
    root.operations[0]->info.val = "a";
    root.operations[0]->info.val_h = str_hash("a");
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

    if(op_eval(&root, &ec_obj, &ec_tmp, &result) == RC_OK) // Ici marche, sinon tester type de retour
        var_dump(result);
    else
        err_display_last(&e);
}

int main(void) {

    //test_variable();
    test_node();

    return 0;
}
