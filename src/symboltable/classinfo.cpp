#include "classinfo.h"

ClassInfo::ClassInfo() : fields_(), methods_()
{ }

ClassInfo::ClassInfo(const Symbol* class_id, const Symbol* base_class_id)
    : class_id_(class_id), base_class_id_(base_class_id)
{ }

void ClassInfo::add_method(const MethodInfo& method_info)
{
    methods_[method_info.get_method_id()] = method_info;
}

void ClassInfo::add_field(const VariableInfo& variable_info)
{
    fields_[variable_info.get_var_id()] = variable_info;
}

bool ClassInfo::has_method(const Symbol* method_id) const
{
    return methods_.count(method_id) == 1;
}

bool ClassInfo::has_field(const Symbol* var_id) const
{
    return fields_.count(var_id) == 1;
}

const VariableInfo& ClassInfo::get_field(const Symbol* var_id) const
{
    return fields_.at(var_id);
}
