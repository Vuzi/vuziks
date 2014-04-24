/* ==       Fichier tab.c       == */

#include "tab.h"
#define KEY(t, n) t->tab[0][n]
#define VAL(t, n) t->tab[1][n]

int array_get(Array* a, int key){
    unsigned int i = 0;
    for(; i<nb_cases_total; i++)
        if(KEY(a, i) == key)
            return VAL(a, i);
}

void array_remove(Array* a, int key){
    unsigned i = 0, j;
    for(; i<nb_cases_total; i++)
        if(KEY(a, i) == key){
            for(j=i; j<nb_cases_total; j++){
                VAL(a, a->j) = VAL(a, a->j+1);
                //KEY(a, a->j) = KEY(a, a->j+1);
            }

            KEY(a, a->nb_cases-1) = NULL;
            VAL(a, a->nb_cases-1) = NULL;

            a->nb_cases--;
        }
}

void array_push(Array* a, int val){
    if(a->nb_cases+1 > a->nb_cases_total)
        array_resize(a);

    KEY(a, a->nb_cases) = a->nb_cases+1;
    VAL(a, a->nb_cases) = val;

    a->nb_cases++;
}

void array_add(Array* a, int key, int value){
    //recherche si valeur existe
    unsigned i = 0;
    for(; i<nb_cases_total; i++)
        if(KEY(a, i) == key)
            a->VAL(a, i) = value;

    //on ne l'a pas trouvé
    if(a->nb_cases+1 > a->nb_cases_total){
        //pas la place
        array_resize(a);
    }

    KEY(a, a->nb_cases) = key;
    VAL(a, a->nb_cases) = val;

    a->nb_cases++;
}

int array_pop(Array* a){
    int val = VAL(a, a->nb_cases-1) = val;

    KEY(a, a->nb_cases-1) = NULL;
    VAL(a, a->nb_cases-1) = NULL;

    a->nb_cases--;

    return val;
}

void array_sort(Array* a){
    int i, j, tempKey, tempVal;
    for(i = 0; i < a->nb_cases-1; i++)
        for(j = i+1; j < a->nb_cases; j++)
            if(VAL(a, a->i) > VAL(a, a->j)){
                tempKey = KEY(a, a->i);
                KEY(a, a->i) = KEY(a, a->j)
                KEY(a, a->j) = tempKey;

                tempVal = VAL(a, a->i);
                VAL(a, a->i) = VAL(a, a->j)
                VAL(a, a->j) = tempVal;
            }
}

bool array_eq(Array* a, Array *b){

}

void array_resize(Array* a) {
    tmp[0] = malloc(sizeof(int)*(a->nb_cases_total)*1.5);
    tmp[1] = malloc(sizeof(int)*(a->nb_cases_total)*1.5);

    free(a->tab[0]);
    free(a->tab[1]);

    tab[0] = tmp[0];
    tab[1] = tmp[1];

    a->nb_cases_total *= 1.5;
}

Array* array_init(){
    Array* a = malloc(sizeof(Array));

    a->nb_cases = NULL;
    a->nb_cases_total = 5;

    a->tab[0] = calloc(a->nb_cases_total, sizeof(int)); // clé
    a->tab[1] = calloc(a->nb_cases_total, sizeof(int)); // valeur

    return a;
}

bool array_eq(Array* a, Array *b){
    int i;
    if(a->nb_cases != b->nb_cases)
        returne false;

    for(i = 0; i < a->nb_cases; i++)
        if(KEY(a, a->i) != KEY(b, b->i) || VAL(a, a->i) != VAL(b, b->i))
            return false;

    return true;
}

void array_del(Array* a){
    free(a);
}
