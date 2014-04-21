/* ==       Fichier tab.c       == */

#include "tab.h"
#define KEY(t, n) t->tab[0][n]
#define VAL(t, n) t->tab[1][n]

int array_get(Array* a, int key){

}

int array_remove(Array* a, int key){

}

void array_push(Array* a, int val){



    KEY(a, a->nb_cases) = a->nb_cases;
    VAL(a, a->nb_cases) = val;
}

void array_add(Array* a, int key, int value){
    //recherche si valeur existe
    unsigned i = 0;
    for(; i<nb_cases_total; i++){
        if(KEY(a, i) == key){
            a->VAL(a, i) = value;
        }
    }
    //on ne l'a pas trouvé
    if(a->nb_cases+1 > a->nb_cases_total){
        //pas la place
        array_resize(a, a->nb_cases_total*1.5);
    }

    KEY(a, a->nb_cases) = key;
    VAL(a, a->nb_cases) = val;

    a->nb_cases++;
}

void array_pop(Array* a, int val){

}

void array_sort(Array* a){

}

bool array_eq(Array* a, Array *b){

}

Array* array_init(){
    Array* a = malloc(sizeof(Array)):

    a->nb_cases = NULL;
    a->nb_cases_total = 5;

    a->tab[0] = calloc(nb_cases_total, sizeof(int)); // clé
    a->tab[1] = calloc(nb_cases_total, sizeof(int)); // valeur

    return a;
    KEY(a, 2)
    //3è clé de tab a
}

void array_del(Array** a){

}
