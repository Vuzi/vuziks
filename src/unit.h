#ifndef _H_UNIT
#define _H_UNIT

#include "linkedList/linkedList.h"

typedef struct s_Unit {
    Linked_list *operations;
} Unit;

typedef struct s_Unit_conditional {
    Linked_list *operations;
    struct s_Operation *condition;    // Condition
	Linked_list *next;       // Prochaine condition
} Unit_conditional;

typedef struct s_Unit_loop {
    Linked_list *operations;
    struct s_Operation *start_action;      // Action de début, 'i = 0' par exemple
    struct s_Operation *end_action;        // Action de fin (Par d'exemple en C)
    struct s_Operation *start_condition;   // Condition de début (testé avant de lancer chaque boucle)
    struct s_Operation *end_condition;     // Condition de fin (cas du do while en C)
} Unit_loop;

typedef struct s_Exec_context {
    Linked_list* variables;                 // Liste des variables du contexte
    struct s_Exec_context* caller_context;  // Contexte de la variable l'ayant appelé
    struct s_Variable* caller;              // Variable l'ayant appelé
} Exec_context;

#endif // _H_UNIT
