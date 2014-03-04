#ifndef _H_VARIABLE
#define _H_VARIABLE

#include <math.h>

#include "hash/hash.h"
#include "err/err.h"
#include "str/str.h"
#include "math/math.h"

//=====================================================================//
//                         Langage en lui-même

// Type de donnée possibles
typedef enum e_language_type {
	T_NULL = 0, T_BOOL = 1, T_NUM = 2, T_ARRAY = 3, T_REF = 4, T_OBJECT = 5
} language_type;

// Représente une valeur possible (null n'ayant pas de représentation)
typedef union u_Language_value {
	char v_bool;
	double v_num;
	// Array
	// Reférence
	// Objet
} Language_value;


//=====================================================================//
//               variable : variable utilisable

// Variable en mémoire
typedef struct s_Variale {
	char* name;            // Nom de la variable (en toute lettre)
	hash_t name_h;         // Hashage du nom de la variable, pour la trouver plus vite
	language_type type;    // Type de la variable
	Language_value value;  // Valeur de la variable
} Variable;


//=====================================================================//
//                   Node de l'arbre binaire (Opération)

// Les différents types de types
#define OP_UNIT 0x1
#define OP_MATH 0x10
#define OP_MATH_UNARY 0x20
#define OP_LOG 0x40

// Représente les différents types possibles d'une operation
typedef enum e_operation_type {
	OP_NOTHING = 0,

	OP_UNIT_CALL = 0x1, OP_UNIT_REF = 0x3, OP_UNIT_NEW = 0x5,

	OP_MATH_PLUS = 0x10, OP_MATH_MINUS = 0x11, OP_MATH_MULT = 0x12, OP_MATH_POW = 0x13, OP_MATH_DIV = 0x14, OP_MATH_MODULO = 0x15, OP_MATH_INTDIV = 0x16,

	OP_MATH_P_UNARY = 0x20, OP_MATH_M_UNARY = 0x21,

	OP_MATH_ASSIGN = 0x30,

	OP_LOG_GT = 0x40, OP_LOG_GE = 0x41, OP_LOG_LT = 0x42, OP_LOG_LE = 0x43, OP_LOG_EQ = 0x44, OP_LOG_DIF = 0x45, OP_LOG_TYPE = 0x46, OP_LOG_NOT = 0x47, OP_LOG_AND = 0x48, OP_LOG_OR = 0x49,

    OP_PARENTH = 0x50,

	OP_VALUE = 0x60

} operation_type;

#endif // _H_VARIABLE
