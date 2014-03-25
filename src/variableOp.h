#ifndef _H_VARIABLEOP
#define _H_VARIABLEOP

/* ==       Fichier variableOp.h       ==
   Contient les opérations sur les
   variables                               */

// Includes
#include <math.h>

#include "hash/hash.h"
#include "err/err.h"
#include "str/str.h"
#include "math/math.h"
#include "variable.h"
#include "unit.h"
#include "operation.h"

typedef struct s_Operation Operation;

// Prototypes
return_code var_op(Variable *a, Variable *b, Variable **r, operation_type type);
return_code var_op_comma(Variable *a, Variable *b, Operation *op, Variable **r);
return_code var_op_attr_access(Variable *a, const char* name, hash_t name_h, Variable **r);

#endif // _H_VARIABLEOP
