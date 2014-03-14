#include "unit.h"

return_code unit_function(Variable **r, Exec_context *ec_obj, Exec_context *ec_tmp, Unit *u); // Retourne la valeur de l'évaluation
return_code unit_constructor(Exec_context **ec_obj, Exec_context *ec_tmp, Unit *u); // Retourne le contexte du nouvel objet
return_code unit_cond_eval(Exec_context *ec_obj, Exec_context *ec_tmp, Unit_conditional *uc); // Evalue la condition
return_code unit_loop_eval(Exec_context *ec_obj, Exec_context *ec_tmp, Unit_loop *ul); // Evalue la boucle
