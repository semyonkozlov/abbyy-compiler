#include "variableinfo.h"

VariableInfo::VariableInfo() : type_id_()
{ }

VariableInfo::VariableInfo(const Symbol* type_id, const Symbol* var_id) : type_id_(type_id), var_id_(var_id)
{ }
