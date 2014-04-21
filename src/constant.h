#ifndef _H_CONSTANT
#define _H_CONSTANT

/* ==       Fichier constant.h       ==
   Contient les constantes du programme */

#include "variable.h"
#include "init/params.h"

// Var globales
extern struct s_Params p;
// Liste des générateur d'objets pour les fonctions built-in de base du langage
extern struct s_Object*(*func_builtin_tab[128])(Exec_context*);
extern unsigned int func_builtin_tab_n;

// Defines
#define VERSION_NUM "0.03b"

#endif
