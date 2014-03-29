#ifndef _H_ERR
#define _H_ERR

/* ==       Fichier err.h       ==
   Gestion des erreurs              */

// Includes
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

// Type de retour
typedef enum e_return_code {
    RC_OK, RC_WARNING, RC_ERROR, RC_CRITICAL, RC_BREAK, RC_RETURN
} return_code;

// Type d'erreur
typedef enum e_error_type {
    FORBIDDEN_TYPE=1, NULL_VALUE=2, UNKOWN_TYPE=3, OP_IMPOSSIBLE=4, CANT_ACCESS=5, USELESS_ACTION=6
} error_type;

// Niveau d'erreur
typedef enum e_error_level {
    E_INFO=0, E_DEBUG=1, E_WARNING=2, E_ERROR=3, E_CRITICAL=4
} error_level;

// Erreur
typedef struct s_Error {
    char msg[512];
    error_type type;
    error_level level;
} Error;

extern Error e;
extern unsigned int current_line;
extern int nb_alloc;
extern size_t size_alloc;

// Prototypes
void* xmalloc(size_t s);
void xfree(void* p);

void print_memory_info(void);

void err_display_last(void);
void err_add(error_level lvl, error_type type, const char* msg, ...);

#endif // _H_HASH
