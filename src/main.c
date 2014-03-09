#include <stdio.h>
#include <stdlib.h>

#include "variable.h"

int main(void) {

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
    var_op(_a, _b, _c, OP_MATH_MINUS);
    puts("a - b = ");
    var_dump(_c);

    //a % b
    var_op(_a, _b, _c, OP_MATH_MODULO);
    puts("a % b = ");
    var_dump(_c);

    // == Tests logiques ==

    // a == b
    var_op(_a, _b, _c, OP_LOG_EQ);
    puts("a == b = ");
    var_dump(_c);

    // a > b
    var_op(_a, _b, _c, OP_LOG_GT);
    puts("a > b = ");
    var_dump(_c);

    // a === b
    var_op(_a, _b, _c, OP_LOG_TYPE);
    puts("a === b = ");
    var_dump(_c);

    // Test d'erreur
    var_init(&_a, "a", T_NULL);
    var_init(&_b, "b", T_NUM);

    var_op(_a, _b, _c, OP_MATH_MINUS);
    puts("a(null) - b(num) = ");

    err_display_last(&e);

    var_init(&_a, "a", T_BOOL);
    var_init(&_b, "b", T_NUM);

    var_op(_a, _b, _c, OP_LOG_AND);
    puts("a(bool) and b(num) = ");

    err_display_last(&e);


    return 0;
}
