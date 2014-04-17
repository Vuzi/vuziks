#ifndef _H_VARIABLEOP
#define _H_VARIABLEOP

/* ==       Fichier variableOp.h       ==
   Contient les opérations sur les
   variables                               */

// Includes
#include <math.h>
#include "math/math.h"
#include "variable.h"
#include "operation.h"

// Prototypes
return_code var_op(Variable* a, Variable* b, Variable* eval_value, operation_type type);
return_code var_op_assign(Variable* a, Variable* b, Variable** eval_value);
return_code var_op_attr_access(Variable* a, Operation_identifier* id, Variable** eval_value);
return_code var_op_return(Variable *a, Variable* eval_value);

#endif // _H_VARIABLEOP
