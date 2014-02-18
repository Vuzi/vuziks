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
	OP_MATH_GT = 20, OP_MATH_GE = 21, OP_MATH_LT = 22, OP_MATH_LE = 23, OP_MATH_EQ = 24, OP_MATH_DIF = 25, OP_MATH_NOT = 26,
	OP_FUNC_BLOC = 30, OP_IT_BLOC = 31, OP_COND_BLOC = 32, OP_BLOC = 33,
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
	s_operation_value_var_nat var_nat; // Variable naturelle
	struct variable *var;              // Lien vers variable enregistrée
	//function func;                   // Lien vers fonction enregistrée
	unit bloc;                         // Bloc de code
	unit_conditional conditional_bloc; // Bloc conditionnel
	unit_iterative iterative_bloc;     // Bloc iteratif
	unit_function function_bloc;       // Bloc déclaration fonction
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


//=====================================================================//
//               variable : variable déclarée et utilisable

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
//               Function : fonction déclarée et utilisable

typedef struct s_function {
	char* name;              // Nom de la fonction (en toute lettre)
	int name_h;              // Hash du nom de la fonction
	s_variale_list *args;
	instruction *content;
} function;

// Liste de fonctions
typedef struct s_function_list {
	struct s_function_list* next;
	variable func;
} function_list;


//=====================================================================//
//                 Blocs : bloc d'instruction spécifique

// Bloc d'instruction vide
typedef struct s_unit {
	variale_list *var_list;     // Liste des variables de l'unité
	function_list *func_list;   // Liste des fonctions de l'unité
	struct s_unit *container;   // Bloc contenant ce bloc d'instruction
	instruction *content;       // Liste des instructions du bloc
} unit;

// Bloc d'unité conditionnel
typedef struct s_unit_conditional {
	operation *condition;      // Condition
	unit *intern;
} unit_conditional;

// Bloc d'unité itératif
typedef struct s_unit_iterative {
	operation *start_action;      // Action de début, 'i = 0' par exemple
	operation *end_action;        // Action de fin (Par d'exemple en C)
	operation *start_condition;   // Condition de début (testé avant de lancer chaque boucle)
	operation *end_condition;     // Condition de fin (cas du do while en C)
	unit *intern;
} unit_iterative;

// Bloc d'unité fonction
typedef struct s_unit_function {
	unit *intern;
} unit_function;