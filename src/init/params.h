#ifndef _H_PARAMS
#define _H_PARAMS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../err/err.h"

// Paramètres d'execution
typedef struct s_Params {

    int argc;
    char** argv;

    char interactive_mod;
    char show_operation;
    char auto_dump;
    char mem_info;
    char show_timer;
    char verbose;

    time_t start_parsing;
    time_t end_parsing;
    time_t start_exec;
    time_t end_exec;

    FILE* file;

} Params;

#include "../constant.h"

// Prototypes
void params_init(void);
void params_free(void);
void params_make(int argc, char **argv);


#endif // _H_PARAMS
