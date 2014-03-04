#include "err.h"

Error e;

// Affichage d'erreur
void err_display_last(Error *e) {
    printf("#error\n  %s\n  level %d and type %d\n", e->msg, e->level, e->type);
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
