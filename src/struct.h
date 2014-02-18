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
	OP_MATH_P_UNARY = 9, OP_MATH_N_UNARY = 10, OP_MATH_PARENTH = 11, OP_MATH_EQUAL = 12, OP_MATH_MINUS_UN = 13, OP_MATH_PLUS_UN = 14,
	OP_MATH_GT = 20, OP_MATH_GE = 21, OP_MATH_LT = 22, OP_MATH_LE = 23, OP_MATH_EQ = 24, OP_MATH_DIF = 25, OP_MATH_NOT = 26, OP_MATH_AND = 27, OP_MATH_OR = 28,
	OP_FUNC_BLOC = 50, OP_IT_BLOC = 51, OP_COND_BLOC = 52, OP_BLOC = 53,
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
//                 Blocs : bloc d'instructions spécifique

// Bloc d'instruction vide
typedef struct s_unit {
	variale_list *var_list;     // Liste des variables de l'unité
	function_list *func_list;   // Liste des fonctions de l'unité
	struct s_unit *container;   // Bloc contenant ce bloc d'instruction
	instruction *content;       // Liste des instructions du bloc
} unit;

// Bloc d'unité conditionnel
typedef struct s_unit_conditional {
	operation *condition;            // Condition
	unit *intern;
	struct s_unit_conditional *next; // Prochaine condition
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


//=====================================================================//
//                 Exemple de construction d'un programme :
/*

	Code : 
	-------------------------------------------------------------------
	
	var a = 12;

	function foo(a,b) {
		return(a+b*2);
	}

	print(foo(a,2));


	Résultat possible en mémoire :
	------------------------------------------------------------------

	(Par défaut, on se trouve dans un "unit" général qui est utilisé comme point de lancement)

	unit {
		var_list {
			var {
				name = a;
				name_h = 84565; (A faire avec une fonction de hashage basique)
				type = L_INT;
				value = 12;
			}
			next = NULL
		}
		var_func {
			func {
				name = a;
				name_h = 84565; (A faire avec une fonction de hashage basique)
				args {
					var {
						name = a;
						name_h = 84565; (A faire avec une fonction de hashage basique)
						type = L_NONE;
						value = 0;
					}
					var {
						name = b;
						name_h = 84565; (A faire avec une fonction de hashage basique)
						type = L_NONE;
						value = 0;
					}
				}
				instructions {
					instruction {
						node {
							appel fonction return {
								a+b*2 décomposé en arbre binaire...
							}
						}
					}
				}
	
			}
			next = NULL;
		}
		instructions {
			instruction {
				node {
					appel fonction print {
						appel fonction foo() {
							a
							12
						}
					}
				}
			}
		}
	}

	Note: suivant la manière dont est gérée le code, il faut voir comment adapter. Si on fait le 
	choix de passer une première fois dans tout le code et de lire toutes les opérations, puis 
	ensuite de l'executer alors par exemple l'ordre de déclaration des fonctions n'aura pas d'importance 
	(Alors que si on lit au fur et à meusure, alors on ne peut appeller une fonction qu'après sa déclaration).

	De même les variables de l'exemple ne sont ajoutée à la liste des variables qu'après avoir été traitées dans le code.

	Règles du langage :
	voir wiki