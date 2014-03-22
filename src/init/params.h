#ifndef _H_PARAMS
#define _H_PARAMS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_Params {

    int argc;
    char** argv;

    char interactive_mod;
    char show_operation;
    char auto_dump;

} Params;

#include "../constant.h"

// Prototypes
void params_init(void);
void params_make(int argc, char **argv);


#endif // _H_PARAMS
