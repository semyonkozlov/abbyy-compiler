#include "methodinfo.h"

MethodInfo::MethodInfo() : args_(), locals_()
{ }

MethodInfo::MethodInfo(AccessMod access_mod, const Symbol* return_type_id, const Symbol* method_id)
    : access_mod_(access_mod), return_type_id_(return_type_id), method_id_(method_id)
{ }

void MethodInfo::add_arg(const VariableInfo& variable_info)
{
    args_[variable_info.get_var_id()] = variable_info;
}

void MethodInfo::add_local_var(const VariableInfo& variable_info)
{
    locals_[variable_info.get_var_id()] = variable_info;
}

bool MethodInfo::has_arg(const Symbol* var_id) const
{
    return args_.count(var_id) == 1;
}

bool MethodInfo::has_local_var(const Symbol* var_id) const
{
    return locals_.count(var_id) == 1;
}

const VariableInfo& MethodInfo::get_variable(const Symbol* var_id) const
{
    if (has_arg(var_id)) {
        return args_.at(var_id);
    }

    return locals_.at(var_id);
}
