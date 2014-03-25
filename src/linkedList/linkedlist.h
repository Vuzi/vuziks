#ifndef _H_LINKEDLIST
#define _H_LINKEDLIST

#include <stdlib.h>
#include "../err/err.h"

typedef struct s_Linked_list {
    struct s_Linked_list* next;
    void* value;
} Linked_list;

Linked_list* linked_list_last(Linked_list* ll);
void linked_list_append(Linked_list** ll, void* v);
void linked_list_push(Linked_list **ll, void* v);
void linked_list_del(Linked_list *ll, void (*free_function)(void*));

#endif // _H_LINKEDLIST
