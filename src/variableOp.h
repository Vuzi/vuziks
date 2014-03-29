#ifndef _H_VARIABLEOP
#define _H_VARIABLEOP

/* ==       Fichier variableOp.h       ==
   Contient les op�rations sur les
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
return_code var_op(Variable* a, Variable* b, Variable* eval_value, operation_type type);
return_code var_op_assign(Variable* a, Variable* b, Variable** eval_value);
return_code var_op_attr_access(Variable* a, Operation_identifier* id, Variable** eval_value);
return_code var_op_return(Variable *a, Variable* eval_value);

#endif // _H_VARIABLEOP
