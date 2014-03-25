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
    Linked_list *operations;   // Liste des opérations de l'unité
    Linked_list *args;         // Arguments attendus
} Unit;

// Unité - condition
typedef struct s_Unit_conditional {
    Linked_list *operations;
    struct s_Operation *condition;     // Condition
	struct s_Unit_conditional *next;   // Prochaine condition (cas des else)
} Unit_conditional;

// Unité - boucle
typedef struct s_Unit_loop {
    Linked_list *operations;
    struct s_Operation *start_action;      // Action de début, 'i = 0' par exemple
    struct s_Operation *end_action;        // Action de fin (Par d'exemple en C)
    struct s_Operation *start_condition;   // Condition de début (testé avant de lancer chaque boucle)
    struct s_Operation *end_condition;     // Condition de fin (cas du do while en C)
} Unit_loop;

// Contexte d'execution
typedef struct s_Exec_context {
    Linked_list* variables;                 // Liste des variables du contexte
    struct s_Exec_context* caller_context;  // Contexte de la variable l'ayant appelé
    struct s_Variable* caller;              // Variable l'ayant appelé
} Exec_context;

#include "variableOp.h"
#include "operation.h"


typedef struct s_Variale Variable;

// Prototypes
void eval_main(Unit* start);

return_code ec_init_loc(Exec_context *ec);
return_code ec_init(Exec_context **ec);
return_code ec_add_var(Exec_context* ec, char* name, hash_t name_h, Variable **r);
return_code ec_var_access(Exec_context* ec_obj, Exec_context* ec_tmp, operation_type type, char* name, hash_t name_h, Variable **r);
return_code ec_pop_var(Exec_context *ec, char* name, hash_t name_h, Variable **r);
return_code ec_empty(Exec_context *ec);

Unit* unit_new(Linked_list *operations, Linked_list *args);
return_code unit_empty(Unit *u);

return_code unit_function(Variable **r, Exec_context *ec_obj, Exec_context *caller_tmp, Linked_list *args, Unit *u); // Retourne la valeur de l'évaluation
return_code unit_constructor(Exec_context *ec_obj, Exec_context *caller_obj, Exec_context *caller_tmp, Linked_list *args,  Unit *u); // Retourne le contexte du nouvel objet
return_code unit_cond_eval(Variable **r, Exec_context *ec_obj, Exec_context *ec_tmp_source, Unit_conditional *uc); // Evalue la condition
return_code unit_loop_eval(Variable **r, Exec_context *ec_obj, Exec_context *ec_tmp_source, Unit_loop *ul); // Evalue la boucle

#endif // _H_UNIT
