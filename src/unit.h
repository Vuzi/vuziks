#ifndef _H_UNIT
#define _H_UNIT

/* ==       Fichier unit.h       ==
   Contient les structure, énumérations
   et fonctions liées à la création et à
   la manipulation des unités
   d'opérations du langage                */

// Includes
#include "constant.h"
#include "linkedList/linkedList.h"
#include "err/err.h"

// Unité - fonction
typedef struct s_Unit {
    Linked_list *statements;   // Liste des opérations de l'unité
    Linked_list *args;         // Arguments attendus
} Unit;

// Unité - condition
typedef struct s_Unit_conditional {
    Linked_list *statements;
    struct s_Operation *condition;     // Condition
	struct s_Unit_conditional *next;   // Prochaine condition (cas des else)
} Unit_conditional;

// Unité - boucle
typedef struct s_Unit_loop {
    Linked_list *statements;
    struct s_Operation *start_action;      // Action de début, 'i = 0' par exemple
    struct s_Operation *start_condition;   // Condition de début (testé avant de lancer chaque boucle)
    struct s_Operation *end_condition;     // Condition de fin (cas du do while en C)
} Unit_loop;

// Contexte d'execution
typedef struct s_Exec_context {
    Linked_list* variables;                 // Liste des variables du contexte
    struct s_Exec_context* container;       // Contexte où contenu
    struct s_Object* object;
} Exec_context;

#include "variableOp.h"
#include "operation.h"


typedef struct s_Variale Variable;
typedef struct s_Operation Operation;

// Prototypes
void unit_main(Unit* start);

return_code unit_function(Exec_context *ec_obj, Exec_context *ec_var_caller, Linked_list* args, Unit* function, Variable* eval_value);
return_code unit_constructor(Exec_context *ec_obj_caller, Exec_context *ec_var_caller, Linked_list* args, Unit* function, Variable* eval_value);

Unit* unit_new(Linked_list *statements, Linked_list *args);
void unit_empty(Unit *u);

void ec_init_loc(Exec_context *ec);
void ec_empty(Exec_context *ec);

void ec_push_var(Exec_context* ec, Variable* v);
return_code ec_add_var(Exec_context* ec, Operation_identifier* id, Variable** eval_value);
return_code ec_var_access(Exec_context* ec_obj, Exec_context* ec_tmp, operation_type type, Operation_identifier* id, Variable** eval_value);
return_code ec_pop_var(Exec_context* ec, Operation_identifier* id, Variable* eval_value);

Unit_conditional* unit_cond_new(Operation* cond, Unit_conditional* before, Linked_list* statements);
void unit_cond_delete(Unit_conditional* uc);

return_code unit_cond_eval(Exec_context *ec_obj, Exec_context *ec_var, Unit_conditional *uc, Variable* eval_value);

Unit_loop* unit_loop_new(Operation* start_cond, Operation* end_cond, Operation* start_action, Linked_list* statements);
void unit_loop_delete(Unit_loop* ul);
return_code unit_loop_eval(Exec_context *ec_obj, Exec_context *ec_var, Unit_loop *ul, Variable* eval_value);


#endif // _H_UNIT
