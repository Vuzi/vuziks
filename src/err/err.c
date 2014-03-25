
/* ==       Fichier err.h       ==*/

#include "err.h"
#include "../linkedList/linkedList.h"

Error e;
unsigned int current_line = 0;
int nb_alloc = 0;
size_t size_alloc = 0;

void print_memory_info(void) {
    printf("[i] %d memory block(s) not free'd \n", nb_alloc);
    printf("[i] %d octets malloc'd \n", size_alloc/8);
}

void* xmalloc(size_t s) {
    void* p = malloc(s);
    nb_alloc++;
    size_alloc += s;
    if(!p) {
        perror("[x] Error mallo() :");
        exit(EXIT_FAILURE);
    }
    return p;
}

void xfree(void* p) {
    nb_alloc--;
    free(p);
}

// Affichage d'erreur
void err_display_last(void) {
    if(e.level > E_WARNING)
        printf("[x] %d | Error : %s\n    level %d and type %d\n", current_line, e.msg, e.level, e.type);
    else if(e.level > E_INFO)
        printf("[x] %d | Warn. : %s\n    level %d and type %d\n", current_line, e.msg, e.level, e.type);
    else
        printf("[x] %d | Info. : %s\n    level %d and type %d\n", current_line, e.msg, e.level, e.type);
}

// Ajout d'erreur
void err_add(error_level lvl, error_type type, const char* msg, ...) {

    va_list va;
    va_start(va, msg);

    vsprintf(e.msg, msg, va);

    e.level = lvl;
    e.type = type;

    va_end(va);
}
