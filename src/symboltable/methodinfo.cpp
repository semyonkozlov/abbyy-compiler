#include "methodinfo.h"

MethodInfo::MethodInfo() : args_(), locals_()
{ }

MethodInfo::MethodInfo(AccessMod access_mod, const Symbol* return_type_id, const Symbol* method_id)
    : access_mod_(access_mod), return_type_id_(return_type_id), method_id_(method_id)
{ }


void MethodInfo::add_local_var_info(const VariableInfo& variable_info)
{
    locals_[variable_info.get_var_id()] = variable_info;
}

void MethodInfo::add_arg_info(const VariableInfo& variable_info)
{
    args_[variable_info.get_var_id()] = variable_info;
}