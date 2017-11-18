#ifndef MINIJAVAC_CLASSINFO_H
#define MINIJAVAC_CLASSINFO_H

#include "symbol.h"
#include "methodinfo.h"

class ClassInfo
{
public:
    ClassInfo();
    explicit ClassInfo(const Symbol* class_id, const Symbol* base_class_id = nullptr);

    const Symbol* get_class_id() const noexcept
    {
        return class_id_;
    }

    const auto& get_fields() const noexcept
    {
        return fields_;
    }

    const auto& get_methods() const noexcept
    {
        return methods_;
    }

    void add_method_info(const MethodInfo& method_info); // TODO throw error if double decl
    void add_field_info(const VariableInfo& variable_info);

private:
    std::map<const Symbol*, VariableInfo> fields_;
    std::map<const Symbol*, MethodInfo> methods_;

    const Symbol* class_id_;
    const Symbol* base_class_id_;
};

#endif //MINIJAVAC_CLASS_INFO_H
