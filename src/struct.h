/*
[bloc conditionnel]
                    [instruction] [nodes]
[bloc iteratif]
[bloc fonction]
                    [bloc instruction]
                                       [instruction] [nodes]
*/

//=====================================================================//
//                         Langage en lui-même

// Type de donnée possibles
enum e_language_type {
	L_INT, L_FLOAT, L_DOUBLE, L_CHAR, L_BOOL, L_NULL, L_VOID // A voir
} language_type;

// Représente une valeur possible
typedef union u_language_value {
	int v_int;
	float v_float;
	double v_double;
	char v_char;
	char v_bool;
} language_value;


//=====================================================================//
//                   Node de l'arbre binaire (Opération)

// Représente les différents types possibles d'une operation
typedef enum e_operation_type {
	OP_NOTHING = 1, 
	OP_FUNC_CALL = 2, 
	OP_MATH_PLUS = 3, OP_MATH_MINUS = 4, OP_MATH_MULT = 5, OP_MATH_POW = 6, OP_MATH_DIV = 7, OP_MATH_MODULO = 8,
	OP_MATH_P_UNARY = 9, OP_MATH_N_UNARY = 10, OP_MATH_PARENTH = 11,
	OP_MATH_GT = 20, OP_MATH_GE = 21, OP_MATH_LT = 22, OP_MATH_LE = 23, OP_MATH_EQ = 24, OP_MATH_DIF = 25, OP_MATH_NOT = 26
	OP_VALUE = 99
} operation_type;

// Type possible de valeurs d'une operation
typedef enum e_operation_value_type {
	OP_NAT_VAL, OP_VAR, OP_FUNC, OP_NONE
} operation_value_type;

typedef struct s_operation_value {
	operation_value_type type;
	operation_value_union v;
} operation_value;

typedef union u_operation_value_union {
	s_operation_value_var_nat var_nat;
	//variable var;
	//function func;
} operation_value_union;

// Représente une valeur possible utilisable (Avec type)
typedef struct s_operation_value_var_nat {
	language_type type;
	language_value value;
} operation_value_var;

// Une operation représente une opération simple
typedef struct s_operation {
	operation_type type;            // Type d'opération, obligatoire
	langage_type r_type;            // Type valeur renvoyée, obligatoire
	operation_value value;          // Valeur de l'arbre, facultatif dans le cas d'opération
	struct operation **operations;  // Branches de l'arbre binaire, facultatif si l'arbre s'arrête
	unsigned int n_operations;      // Nombre de branches (2 branches normalements, plus suivant les fonctions)
} operation;

// Accès à une variable naturelle int :
// operation -> value -> v -> var_nat -> value -> v_int
// Accès à une variable enregistrée int :
// operation -> value -> v -> var -> value -> v_int

//=====================================================================//
//                   Instructions : Liste d'instructions
//                        d'un bloc d'instruction


typedef struct s_instruction {
	struct s_instruction *next;  // Suivante instruction
	operation *operations;       // Arbre des opérations contenue dans l'instruction
} instruction;