#ifndef _H_ERR
#define _H_ERR

#include <stdarg.h>
#include <stdio.h>

//=====================================================================//
//                     Buffer d'erreur - provisoir

typedef enum e_return_code {
    RC_OK, RC_WARNING, RC_ERROR, RC_CRITICAL, RC_BREAK, RC_RETURN
} return_code;

typedef enum e_error_type {
    FORBIDDEN_TYPE, NULL_VALUE, UNKOWN_TYPE, OP_IMPOSSIBLE, CANT_ACCESS
} error_type;

typedef enum e_error_level {
    E_INFO=0, E_DEBUG=1, E_WARNING=2, E_ERROR=3, E_CRITICAL=4
} error_level;

typedef struct s_Error {
    char msg[512];
    error_type type;
    error_level level;
} Error;

extern Error e;

void err_display_last(Error *e);
void err_add(error_level lvl, error_type type, const char* msg, ...);

#endif // _H_HASH
