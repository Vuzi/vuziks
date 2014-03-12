#include "linkedList.h"

void linked_list_append(Linked_list** ll, void* v) {
    Linked_list *new_ll = (Linked_list*) malloc(sizeof(Linked_list));
    new_ll->value = v;

    if(*ll) {
        new_ll->next = (*ll)->next;
        (*ll)->next = new_ll;
    } else
        new_ll->next = new_ll;

    *ll = new_ll;
}

void linked_list_del(Linked_list *ll, void (*free_function)(void*)) {
    Linked_list *last_ll = ll;
    Linked_list *tmp = NULL;

    ll = ll->next;

    if(ll) {
        do {
            if(free_function) free_function(ll->value);
            tmp = ll->next;
            free(ll);
            ll = tmp;
        }while(ll != last_ll);
    }
}
