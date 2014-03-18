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

void unit_dump(Unit *u);
void op_dump(Operation *o);
void var_dump(Variable *v);

#endif // _H_DEBUG
