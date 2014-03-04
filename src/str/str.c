#include "str.h"

// copy de chaine
char* str_copy(const char* s) {
	char* copy = (char*) malloc(sizeof(char)*(strlen(s)+1));
	return strcpy(copy, s);
}
