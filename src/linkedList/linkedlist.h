#ifndef _H_LINKEDLIST
#define _H_LINKEDLIST

#include <stdlib.h>
#include "../err/err.h"

// define
#define NEXT(linked_list) \
         linked_list = linked_list->next

#define LAST(linked_list) \
           if(linked_list) \
                while(linked_list->next) linked_list = linked_list->next; \
           else \
                linked_list


// Type de la valeur de la liste chainée (Nous sert à cast le pointeur)
typedef enum e_ptr_type {
    LLT_UNIT,
    LLT_CONDITION,
    LLT_LOOP,
    LLT_OPERATION,
    LLT_VARIABLE
} ptr_type;

typedef struct s_Linked_list {
    struct s_Linked_list* next;
    ptr_type type;
    void* value;
} Linked_list;

Linked_list* linked_list_last(Linked_list* ll);
void linked_list_append(Linked_list** ll, ptr_type type, void* v);
void linked_list_push(Linked_list **ll, ptr_type type, void* v);
void linked_list_del(Linked_list *ll, void (*free_function)(void*));

#endif // _H_LINKEDLIST
