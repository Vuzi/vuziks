#ifndef _H_OPERATION
#define _H_OPERATION

/* ==       Fichier operation.h       ==
   Contient les structure, �num�rations
   et fonctions li�es � la cr�ation et �
   la manipulation des op�rations du
   langage                                */

// Includes
#include "hash/hash.h"
#include "err/err.h"
#include "str/str.h"
#include "math/math.h"

// Les diff�rents types de types
#define OP_UNIT_TYPE 0x100
#define OP_MATH 0x200
#define OP_MATH_UNARY 0x400
#define OP_LOG 0x800
#define OP_MATH_OR_LOG_TYPE 0x1E00
#define OP_VAR 0x2000
#define OP_OUTPUT 0x8000

// Repr�sente les diff�rents types possibles d'une operation
typedef enum e_operation_type {
    // Ne sert � rien
	OP_NOTHING = 0,

    // Appel d'unit�, soit en fonction soit en constructeur
	OP_UNIT_CALL = 0x101, OP_UNIT_NEW = 0x102,

    // Op�ration math�matiques
	OP_MATH_PLUS = 0x201, OP_MATH_MINUS = 0x202, OP_MATH_MULT = 0x203, OP_MATH_POW = 0x204, OP_MATH_DIV = 0x205,
	OP_MATH_MODULO = 0x206, OP_MATH_INTDIV = 0x207, OP_MATH_P_UNARY = 0x401, OP_MATH_M_UNARY = 0x402,

    // Op�ration logique
	OP_LOG_GT = 0x801, OP_LOG_GE = 0x802, OP_LOG_LT = 0x803, OP_LOG_LE = 0x804, OP_LOG_EQ = 0x805, OP_LOG_DIF = 0x806,
	OP_LOG_TYPE = 0x807, OP_LOG_NOT = 0x808, OP_LOG_AND = 0x809, OP_LOG_OR = 0x810, OP_LOG_EXIST = 0x811,

    // Assignation
    OP_ASSIGN = 0x1004,

    // Variable naturelle et d�claration
    OP_VALUE = 0x2000, OP_DEC_VAR = 0x2001, OP_DEC_ATTR = 0x2002,

    // D�claration de variable/de fonction et suppression de variable
    OP_ACCES = 0x2020, OP_ACCES_VAR = 0x2021, OP_ACCES_ATTR = 0x2022, OP_ATTR_ACCESS = 0x2003, OP_DELETE_VAR = 0x2004,
    OP_DELETE_ATTR = 0x2005, OP_UNIT = 0x2006,

    // Op�rateur sp�ciaux
	OP_COMMA = 0x4000, OP_RETURN = 0x4001, OP_BREAK = 0x4002,

    // Op�rateur d'affichage
	OP_OUTPUT_VAR_DUMP = 0x8000

} operation_type;

#include "variableOp.h"

typedef struct s_Variale Variable;

// Information de l'op�ration (d�clarations & num�ro de ligne)
typedef struct s_Operation_info {
    char* val;
    hash_t val_h;
    unsigned int line;
} Operation_info;

// Op�ration (noed de l'arbre)
typedef struct s_Operation {
	struct s_Operation *operations[2];
	operation_type type;
    Operation_info info;
	Variable* value;
} Operation;

// Prototypes
return_code op_delete(Operation *op);
return_code op_init_loc(Operation *op, operation_type type, Operation *left, Operation *right, Variable *value);
return_code op_init(Operation **op, operation_type type, Operation *left, Operation *right, Variable *value);
Operation* op_new(operation_type type, Operation *left, Operation *right, Variable *value);
return_code op_eval(Operation *op, Exec_context *ec_obj, Exec_context *ec_tmp, Variable **r) ;
return_code op_unit(Variable **r, Operation* op, Variable **var_r, Exec_context *ec_obj);

#endif // _H_OPERATION
