#ifndef _H_LINKEDLIST
#define _H_LINKEDLIST

#include <stdlib.h>

typedef struct s_Linked_list {
    struct s_Linked_list* next;
    void* value;
} Linked_list;

void linked_list_append(Linked_list** ll, void* v);
void linked_list_del(Linked_list *ll, void (*free_function)(void*));

#endif // _H_LINKEDLIST
