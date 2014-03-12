#ifndef _H_OPERATION
#define _H_OPERATION

#include "hash/hash.h"
#include "err/err.h"
#include "str/str.h"
#include "math/math.h"

//=====================================================================//
//                   Node de l'arbre binaire (Opération)

// Les différents types de types
#define OP_UNIT_TYPE 0x100
#define OP_MATH 0x200
#define OP_MATH_UNARY 0x400
#define OP_LOG 0x800
#define OP_MATH_OR_LOG_TYPE 0x1F00
#define OP_VAR 0x2000

// Représente les différents types possibles d'une operation
typedef enum e_operation_type {
	OP_NOTHING = 0,

	OP_UNIT_CALL = 0x101, OP_UNIT_NEW = 0x102,

	OP_MATH_PLUS = 0x201, OP_MATH_MINUS = 0x202, OP_MATH_MULT = 0x203, OP_MATH_POW = 0x204, OP_MATH_DIV = 0x205, OP_MATH_MODULO = 0x206, OP_MATH_INTDIV = 0x207,

	OP_MATH_P_UNARY = 0x401, OP_MATH_M_UNARY = 0x402,

	OP_LOG_GT = 0x801, OP_LOG_GE = 0x802, OP_LOG_LT = 0x803, OP_LOG_LE = 0x804, OP_LOG_EQ = 0x805, OP_LOG_DIF = 0x806, OP_LOG_TYPE = 0x807,
	OP_LOG_NOT = 0x808, OP_LOG_AND = 0x809, OP_LOG_OR = 0x810,

    OP_PARENTH = 0x1002,

	OP_ASSIGN = 0x2000, OP_VALUE = 0x2001, OP_DEC = 0x2002, OP_ACCES = 0x2003, OP_CNTX_MODIFIER = 0x2004,

	OP_RETURN = 0x4001, OP_BREAK = 0x4002

} operation_type;


#include "variable.h"


typedef struct s_Operation_info {
    char* val;
    hash_t val_h;
} Operation_info;


// Noeud de l'arbre
typedef struct s_Operation {
	struct s_Operation *operations[2];
	operation_type type;
    Operation_info info;
	Variable* value;
} Operation;

// Prototypes

return_code op_eval(Operation *op, Exec_context *ec_obj, Exec_context *ec_tmp, Variable **r) ;

#endif // _H_OPERATION
