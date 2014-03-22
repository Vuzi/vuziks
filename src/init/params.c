#include "params.h"

static int param_make(char* option, char* argument);
static void show_version(void);
static void show_help(void);

Params *p = NULL;

void params_init(void) {
	p = (Params*)malloc(sizeof(Params));

	p->interactive_mod = 1;
	p->show_operation = 0;
	p->auto_dump = 0;

	p->argc = 0;
	p->argv = NULL;
}

void params_make(int argc, char **argv) {

    int i = 1, j = 0, arg_length;
    short int no_more_op = 0;

    char short_tmp[2] = {0};
    char *arg_tmp = NULL;

    // For each param
    for (i = 1; i < argc; i++) {

        arg_length = strlen(argv[i]);

        // Start with a dash
        if(!no_more_op && arg_length > 0 && argv[i][0] == '-') {
            // Second dash : long argument
            if(arg_length > 1 && argv[i][1] == '-') {
                // If just double dash, no more args
                if(arg_length == 2) {
                    no_more_op = 1;
                }
                // Long argument
                else {

                    if(argv[i][2] == '=')
                        printf("[x] Option '%s' is ambigous", argv[i]);

                    arg_tmp = strchr(argv[i]+2, (int)'=');

                    if(arg_tmp) {
                        *arg_tmp = '\0';
                        arg_tmp++;
                        param_make(argv[i]+2, arg_tmp);
                    } else {
                        if(argc < i+1)
                            i += param_make(argv[i]+2, argv[i+1]);
                        else
                            param_make(argv[i]+2, NULL);
                    }
                }
            }
            // Only one dash, stdin
            else if(arg_length == 1) {
                // stdin comme fichier
            }
            // Short args
            else {
                // More than one (or values)
                if(arg_length > 2) {
                    for(j = 1; j < arg_length; j++) {
                        short_tmp[0] = argv[i][j];

                        if(j+1 < arg_length) {
                            if(param_make(short_tmp, argv[i]+j+1)) // argument + line ending
                                j = arg_length-1;
                        } else if(i+1 < argc)
                            i += param_make(short_tmp, argv[i+1]); // argument + next
                        else
                            param_make(short_tmp, NULL);
                    }
                }
                // One arg
                else {
                    if(i+1 < argc)
                        i += param_make(argv[i]+1, argv[i+1]);
                    else
                        param_make(argv[i]+1, NULL);
                }
            }
        }
        // Node dash, filename
        else {
            // Pas encore géré !
        }

    }
}

static int param_make(char* option, char* argument) {

    argument++; // en attendant

    if(p) {
        if (!strcmp(option, "i") || !strcmp(option, "interactive")) {
            p->interactive_mod = 1;
            return 0;
        } else if (!strcmp(option, "show-op")) {
            p->show_operation = 1;
            return 0;
        }else if (!strcmp(option, "auto-dump")) {
            p->auto_dump = 1;
            return 0;
        } else if (!strcmp(option, "h") || !strcmp(option, "help")) {
            show_help();
            exit(0);
        } else if (!strcmp(option, "v") || !strcmp(option, "version")) {
            show_version();
            exit(0);
        } else {
            printf("[x] Unknown option : '%s'", option);
            return 0;
        }
    }
    return 0;
}

static void show_version(void) {
    printf("[i] Vuziks - version %s\n    By G. Villerez & G. Delapres \n\n    Compiled at %s on %s\n",VERSION_NUM, __TIME__,__DATE__);
    #ifdef DEBUG
        puts("[i](Compiled in debug version)");
    #endif
}

static void show_help(void) {
   puts("[i] Usage: vuziks [OPTION]... [FILE]\n\n"
         "     -i --interactive             Interactive mode (default with no files).\n"
         "       --auto-dump                    Automaticaly dump the last value of a statement.\n"
         "       --show-op                      Show the detail of each operation.\n");
}
