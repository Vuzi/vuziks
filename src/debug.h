#ifndef _H_DEBUG
#define _H_DEBUG


#include "variableOp.h"
#include "operation.h"
#include "unit.h"
#include "linkedList/linkedList.h"

#include "hash/hash.h"

extern int debug_lvl;

// Prototypes
void debug_pr_lvl(void);
const char* language_type_debug(language_type l);
const char* operation_type_debug(operation_type o) ;

void unit_dump(Unit *u);
void op_dump(struct s_Operation *o);
void var_dump(Variable *v);

#endif // _H_DEBUG
