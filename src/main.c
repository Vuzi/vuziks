#include <stdio.h>
#include <stdlib.h>

#include "variableOp.h"
#include "operation.h"
#include "unit.h"
#include "debug.h"

#include "hash/hash.h"

/*
    A faire, urgent :

     - Ajouter un champ numéro aux variables (nombre de liens)
     - Faire des fonctions "intelligentes" de suppression de variables
     - Faire des fonctions "intelligentes" de suppression de contexte (Ou de vidage)
     - Faire des fonctions intelligentes de copies de variables
     - Faire des fonctions de copie de variable
     - Nouveau type : référence (Pas le même que function)
     - Opérateur '@' pour récupérer une référence (Uniquement sur variable nommée)
     - Opérateur '*' d'accès (Uniquement sur variable nommée de type référence)
     - Refaire en étant plus attentif à la mémoire ( !!! )
*/

void test_variable(void);
void test_node(void);
void test_function(void);

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
    ec_obj.caller = NULL;
    ec_obj.caller_context = NULL;
    ec_tmp.variables = NULL;
    ec_tmp.caller = NULL;
    ec_tmp.caller_context = NULL;

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

void test_function(void) {

    // a = unit(a) { var r = a * 2;
    //               return r; }
    //
    // var c = a(14);

    // -- Debut fonction -- //

    Unit func;
    Variable arg;

    var_init_loc(&arg, "a", str_hash("a"), T_NULL);

    func.args = NULL;
    linked_list_append(&func.args, (void*)&arg);

    func.operations = NULL;

    /*
         var r = a * 2
         ----------------------
                =
              /   \
           var r   *
                 /   \
                a     2
         ----------------------
    */

    Variable deux;
    var_init_loc(&deux, NULL, 0, T_NUM);
    deux.value.v_num = 2.0;

    Operation func_op1;
    Operation func_op1_1;
    Operation func_op1_2;
    Operation func_op1_2_1;
    Operation func_op1_2_2;

    func_op1.info.val = NULL;
    func_op1.info.val_h = 0;
    func_op1.value = NULL;

    func_op1.type = OP_ASSIGN;
    func_op1.operations[0] = &func_op1_1;
    func_op1.operations[1] = &func_op1_2;

    func_op1_1.type = OP_DEC_VAR;

    func_op1_1.info.val = "r";
    func_op1_1.info.val_h = str_hash("r");
    func_op1_1.value = NULL;

    func_op1_1.operations[0] = NULL;
    func_op1_1.operations[1] = NULL;

    func_op1_2.type = OP_MATH_MULT;

    func_op1_2.info.val = NULL;
    func_op1_2.info.val_h = 0;
    func_op1_2.value = NULL;

    func_op1_2.operations[0] = &func_op1_2_1;
    func_op1_2.operations[1] = &func_op1_2_2;

    func_op1_2_1.type = OP_ACCES;

    func_op1_2_1.info.val = "a";
    func_op1_2_1.info.val_h = str_hash("a");
    func_op1_2_1.value = NULL;

    func_op1_2_1.operations[0] = NULL;
    func_op1_2_1.operations[1] = NULL;

    func_op1_2_2.type = OP_VALUE;
    func_op1_2_2.value = &deux;

    func_op1_2_2.info.val = NULL;
    func_op1_2_2.info.val_h = 0;

    func_op1_2_2.operations[0] = NULL;
    func_op1_2_2.operations[1] = NULL;

    linked_list_append(&func.operations, (void*)&func_op1);

    /*
         return r
         ----------------------
                return
                   \
                   r
         ----------------------
    */

    Operation func_op2;
    Operation func_op2_1;

    func_op2.info.val = NULL;
    func_op2.info.val_h = 0;
    func_op2.value = NULL;

    func_op2.type = OP_RETURN;
    func_op2.operations[0] = &func_op2_1;
    func_op2.operations[1] = NULL;

    func_op2_1.type = OP_ACCES;
    func_op2_1.info.val = "r";
    func_op2_1.info.val_h = str_hash("r");
    func_op2_1.value = NULL;

    func_op2_1.operations[0] = NULL;
    func_op2_1.operations[1] = NULL;

    linked_list_append(&func.operations, (void*)&func_op2);

    // -- Ligne de code suivante -- //

    /*   var c = a(14);
         ----------------------
                  =
                /  \
            var c  appel
                   / \
                  a   2
         ----------------------
    */

    Operation op1;
    Operation op1_1;
    Operation op1_2;
    Operation op1_2_1;
    Operation op1_2_2;

    op1.type = OP_ASSIGN;

    op1.operations[0] = &op1_1;
    op1.operations[1] = &op1_2;

    op1.info.val = NULL;
    op1.info.val_h = 0;
    op1.value = NULL;

    op1_1.type = OP_DEC_VAR;
    op1_1.info.val = "c";
    op1_1.info.val_h = str_hash("c");
    op1_1.value = NULL;

    op1_1.operations[0] = NULL;
    op1_1.operations[1] = NULL;

    op1_2.type = OP_UNIT_CALL;
    op1_2.info.val = NULL;
    op1_2.info.val_h = 0;
    op1_2.value = NULL;

    op1_2.operations[0] = &op1_2_1;
    op1_2.operations[1] = &op1_2_2;

    op1_2_1.info.val = "a";
    op1_2_1.info.val_h = str_hash("a");
    op1_2_1.value = NULL;

    op1_2_1.operations[0] = NULL;
    op1_2_1.operations[1] = NULL;

    op1_2_1.type = OP_ACCES;

    op1_2_2.info.val = NULL;
    op1_2_2.info.val_h = 0;
    op1_2_2.value = NULL;

    op1_2_2.type = OP_VALUE;
    op1_2_2.value = &deux;

    op1_2_2.operations[0] = NULL;
    op1_2_2.operations[1] = NULL;

    // Contexte d'appel
    Exec_context ec_objet;
    Exec_context ec_tmp;

    ec_init_loc(&ec_objet);
    ec_init_loc(&ec_tmp);

    Variable func_a;

    var_init_loc(&func_a, "a", str_hash("a"), T_FUNCTION);
    func_a.value.v_func = &func;

    linked_list_append(&(ec_tmp.variables), (void*)&func_a);

    Variable r;
    Variable *r_ = &r;

    // Appel
    puts("Initialization ok");

    puts("\nmain :");

    op_dump(&op1);

    puts("\nfunction a :");

    unit_dump(&func);

    puts("\nValeur execution :");

    if(op_eval(&op1, &ec_objet, &ec_tmp, &r_) != RC_OK)
        err_display_last(&e);

    var_dump((Variable*)(ec_tmp.variables->value));

    puts("Eval ok");

}

int main(void) {

    //test_variable();
    //test_node();
    test_function();

    return 0;
}
