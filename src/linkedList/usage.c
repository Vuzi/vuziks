#include <stdio.h>
#include <stdlib.h>

#include "linkedList.h"

int main(void){

    // Avec des variables naturelles
    Linked_list *ll = NULL;
    int a = 1, b = 2, c = 99;

    linked_list_append(&ll, (void*)&a);
    linked_list_append(&ll, (void*)&b);
    linked_list_append(&ll, (void*)&c);

    linked_list_del(ll, NULL); ll = NULL;

    // Avec des pointeurs
    Linked_list *ll = NULL;
    int *a = malloc(sizeof(int));
    int *b = malloc(sizeof(int));
    int *c = malloc(sizeof(int));

    *a = 1;
    *b = 2;
    *c = 99;

    linked_list_append(&ll, (void*)a);
    linked_list_append(&ll, (void*)b);
    linked_list_append(&ll, (void*)c);

    linked_list_del(ll, free);

    return 0;
}
