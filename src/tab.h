#ifndef TAB_H_INCLUDED
#define TAB_H_INCLUDED

/* ==       Fichier tab.h       ==
   Contient les opérations sur les
   tableaux                               */

// Includes
#include <math.h>

#include "hash/hash.h"
#include "err/err.h"
#include "str/str.h"
#include "math/math.h"
#include "variable.h"
#include "unit.h"
#include "operation.h"

typedef struct t_Array {
    unsigned int nb_cases
    unsigned int nb_cases_total
    int* tab[2];
} Array;

//Prototypes

Array* array_init()
int array_get(Array* a, int key)
int array_remove(Array* a, int key)
void array_push(Array* a, int val)
void array_add(Array* a, int key, int value)
void array_pop(Array* a, int val)
void array_sort(Array* a)
bool array_eq(Array* a, Array *b)
void array_del(Array** a)


#endif // TAB_H_INCLUDED
