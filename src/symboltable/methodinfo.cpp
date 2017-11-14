#include "methodinfo.h"

MethodInfo::MethodInfo() : args_(), locals_()
{ }

void MethodInfo::add_local_var_info(const VariableInfo& variable_info)
{
    locals_[variable_info.get_var_id()] = variable_info;
}

void MethodInfo::add_arg_info(const VariableInfo& variable_info)
{
    args_[variable_info.get_var_id()] = variable_info;
}

MethodInfo::MethodInfo(const Symbol* return_type_id, const Symbol* method_id)
    : return_type_id_(return_type_id), method_id_(method_id)
{ }
