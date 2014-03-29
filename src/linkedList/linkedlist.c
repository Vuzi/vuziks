#include "linkedList.h"

Linked_list* linked_list_last(Linked_list* ll) {
    while(ll && ll->next) {
        ll = ll->next;
    }
    return ll;
}

void linked_list_append(Linked_list** ll, ptr_type type, void* v) {
    Linked_list *new_ll = (Linked_list*) xmalloc(sizeof(Linked_list));
    new_ll->value = v;

    if(*ll)
        linked_list_last(*ll)->next = new_ll;
    else
        *ll = new_ll;

    new_ll->type = type;
    new_ll->next = NULL;
}

void linked_list_push(Linked_list **ll, ptr_type type, void* v) {
    Linked_list *new_ll = (Linked_list*) xmalloc(sizeof(Linked_list));

    new_ll->value = v;
    new_ll->type = type;
    new_ll->next = *ll;

    *ll = new_ll;
}

void linked_list_del(Linked_list *ll, void (*free_function)(void*)) {
    Linked_list *tmp = NULL;

    while(ll) {
        tmp = ll->next;
        if(free_function) free_function(ll->value);
        xfree(ll);
        ll = tmp;
    }
}
