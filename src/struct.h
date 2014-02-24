
//=====================================================================//
//                         Langage en lui-même

// Type de donnée possibles
enum e_language_type {
	T_INT, T_LINT, T_FLOAT, T_DOUBLE, T_CHAR, T_BOOL, T_VOID
} language_type;

// Représente une valeur possible
typedef union u_language_value {
	int v_int;
	long int v_lint;
	float v_float;
	double v_double;
	char v_char;
	char v_bool;
} language_value;


//=====================================================================//
//               variable : variable utilisable

// Variable en mémoire
typedef struct s_variale {
	char* name;            // Nom de la variable (en toute lettre)
	int name_h;            // Hashage du nom de la variable, pour la trouver plus vite
	language_type type;    // Type de la variable
	language_value value;  // Valeur de la variable
} variable;

// Liste de variables
typedef struct s_variale_list {
	struct s_variale_list* next;
	variable var;
} variable_list;


//=====================================================================//
//                   Node de l'arbre binaire (Opération)

// Représente les différents types possibles d'une operation
typedef enum e_operation_type {
	OP_NOTHING = 0, 
	OP_FUNC_CALL = 10, 
	OP_MATH_PLUS = 20, OP_MATH_MINUS = 21, OP_MATH_MULT = 22, OP_MATH_POW = 23, OP_MATH_DIV = 24, OP_MATH_MODULO = 25,
	OP_MATH_P_UNARY = 26, OP_MATH_N_UNARY = 27, OP_MATH_PARENTH = 28, OP_MATH_AFF = 29,
	OP_MATH_GT = 30, OP_MATH_GE = 31, OP_MATH_LT = 32, OP_MATH_LE = 33, OP_MATH_EQ = 34, OP_MATH_DIF = 35, OP_MATH_NOT = 36, OP_MATH_AND = 37, OP_MATH_OR = 38,
	OP_VALUE = 40
} operation_type;

// Valeurs possibles
typedef union u_operation_value {
	char* var;
	variable var;
} operation_value;

// Noeud de l'arbre
typedef struct s_operation {
	struct s_operation **operations;
	unsigned int n;
	operation_type type;
	operation_value value;
} operation;


//=====================================================================//
//                   Instructions : Liste d'instructions
//                        d'un bloc d'instruction

typedef union s_value_instruction {
	unit_loop *loop;
	unit_conditional *cond;
	unit *base;
	unit_function *func;
	operation *op;
} value_instruction;

typedef enum e_type_instruction {
	I_OP, I_FOR, I_IF, I_UNIT, I_FUNC
} type_instruction;

typedef struct s_instruction {
	value_instruction value;
	type_instruction type;
} instruction;

typedef struct s_instruction_list {
	struct s_instruction_list *next;
	instruction *ins;
} instruction_list;


//=====================================================================//
//                 Blocs : bloc d'instructions spécifique

// Bloc d'instruction vide
typedef struct s_unit {
	value_instruction parent;    // Contexte, à modifier pour les fonctions
	type_instruction parent_type;
                                 // Liste des éléments
	variable_list *variables;
	function_list *functions;
	instruction_list *instructions;
} unit;

// Bloc de boucle itératives
typedef struct s_unit_loop {
	unit intern;
	operation *start_action;      // Action de début, 'i = 0' par exemple
	operation *end_action;        // Action de fin (Par d'exemple en C)
	operation *start_condition;   // Condition de début (testé avant de lancer chaque boucle)
	operation *end_condition;     // Condition de fin (cas du do while en C)
} unit_loop;

// Bloc d'unité conditionnel
typedef struct s_unit_conditional {
	unit intern;
	operation *condition;            // Condition
	struct s_unit_conditional *next; // Prochaine condition
} unit_conditional;

// Bloc d'unité fonction
typedef struct s_unit_function {
	unit intern;
	char *name;
	char **args;  // A voir
	int n_args;
} unit_function;


//=====================================================================//
//                 Blocs : bloc de fonction

// Fonction
typedef struct s_function {
	char* name;            // Nom de la fonction (en toute lettre)
	int name_h;            // Hashage du nom de la fonction, pour la trouver
	unit *intern;
	variable_list *args;   // Arguments
} function;

// Liste de fonctions
typedef struct s_function_list {
	struct s_function_list *next;
	function func;
} function_list;



//=====================================================================//
//                          Prog

typedef struct s_program {
	unit *intern;           // Point de lancement du programme
}

