#ifndef _H_OPERATION
#define _H_OPERATION

/* ==       Fichier operation.h       ==
   Contient les structure, énumérations
   et fonctions liées à la création et à
   la manipulation des opérations du
   langage                                */

// Includes
#include "hash/hash.h"
#include "variable.h"

// Les différents types de types
#define OP_UNIT_TYPE 0x100
#define OP_MATH 0x200
#define OP_MATH_UNARY 0x400
#define OP_LOG 0x800
#define OP_TYPE 0x1000
#define OP_MATH_OR_LOG_TYPE 0x1E00
#define OP_VAR 0x2000
#define OP_OUTPUT 0x8000

// Représente les différents types possibles d'une operation
typedef enum e_operation_type {
    // Ne sert à rien
	OP_NOTHING = 0,

    // Appel d'unité, soit en fonction soit en constructeur
	OP_UNIT_CALL = 0x101, OP_UNIT_NEW = 0x102,

    // Opération mathématiques
	OP_MATH_PLUS = 0x201, OP_MATH_MINUS = 0x202, OP_MATH_MULT = 0x203, OP_MATH_POW = 0x204, OP_MATH_DIV = 0x205,
	OP_MATH_MODULO = 0x206, OP_MATH_INTDIV = 0x207, OP_MATH_P_UNARY = 0x401, OP_MATH_M_UNARY = 0x402,

    // Opération logique
	OP_LOG_GT = 0x801, OP_LOG_GE = 0x802, OP_LOG_LT = 0x803, OP_LOG_LE = 0x804, OP_LOG_EQ = 0x805, OP_LOG_DIF = 0x806,
	OP_LOG_TYPE = 0x807, OP_LOG_NOT = 0x808, OP_LOG_AND = 0x809, OP_LOG_OR = 0x810, OP_LOG_EXIST = 0x811,

	// Opération sur les types
	OP_TYPE_IS = 0x1001, OP_TYPE_TYPEOF = 0x1002,

    // Assignation
    OP_ASSIGN = 0x2001,

    // Variable naturelle et déclaration
    OP_VALUE = 0x2002, OP_DEC_VAR = 0x2003, OP_DEC_ATTR = 0x2004,

    // Déclaration de variable/de fonction et suppression de variable
    OP_ACCES = 0x2020, OP_ACCES_VAR = 0x2021, OP_ACCES_ATTR = 0x2022, OP_TAB_ACCESS = 0x2023,
    OP_ATTR_ACCESS = 0x2005, OP_DELETE_VAR = 0x2006, OP_DELETE_ATTR = 0x2007, OP_UNIT = 0x2008,

    // Opérateur spéciaux
	OP_COMMA = 0x4000, OP_RETURN = 0x4001, OP_BREAK = 0x4002,

    // Opérateur d'affichage
	OP_OUTPUT_VAR_DUMP = 0x8000

} operation_type;

// Information de l'opération (déclarations & numéro de ligne)
typedef struct s_Operation_identifier {
    char* s;
    hash_t s_h;
} Operation_identifier;

typedef struct s_Variable Variable;

// Opération (noed de l'arbre)
typedef struct s_Operation {
	struct s_Operation *operations[2];
	ptr_type operations_types[2];
	operation_type type;
    Operation_identifier identifier;
    Variable* value;
} Operation;

#include "unit.h"
#include "variableOp.h"

// Prototypes
return_code op_eval(Exec_context* ec_obj, Exec_context* ec_var, Operation* op, Variable** eval_value);

return_code op_init_loc(Operation *op, operation_type type, Operation *left, Operation *right, Variable *value);
Operation* op_new(operation_type type, Operation *left, Operation *right, Variable *value);
void op_delete(Operation *op);

#endif // _H_OPERATION
