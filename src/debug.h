#ifndef _H_DEBUG
#define _H_DEBUG

/* ==       Fichier debug.h       ==
   Contient les fonctions et valeurs
   liées au debug (affichage des
   différents types de données)       */

// Includes
#include <stdio.h>
#include "variable.h"

// Var globales
extern int debug_lvl;

// Prototypes
void debug_pr_lvl(void);
const char* language_type_debug(language_type l);
const char* operation_type_debug(operation_type o) ;

void unit_dump(Unit *u);
void unit_cond_dump(Unit_conditional* uc);
void unit_loop_dump(Unit_loop *ul);
void op_dump(Operation *o);
void var_dump(Variable *v);
void var_obj_dump(Object *o);

#endif // _H_DEBUG
