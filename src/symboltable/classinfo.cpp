#include "classinfo.h"

ClassInfo::ClassInfo() : fields_(), methods_()
{ }

ClassInfo::ClassInfo(const Symbol* class_id, const Symbol* base_class_id)
    : class_id_(class_id), base_class_id_(base_class_id)
{ }

void ClassInfo::add_method_info(const MethodInfo& method_info)
{
    methods_[method_info.get_method_id()] = method_info;
}

void ClassInfo::add_field_info(const VariableInfo& variable_info)
{
    fields_[variable_info.get_var_id()] = variable_info;
}
