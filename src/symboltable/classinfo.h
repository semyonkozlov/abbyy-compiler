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

    const Symbol* get_base_class_id() const noexcept
    {
        return base_class_id_;
    }

    const auto& get_fields() const noexcept
    {
        return fields_;
    }

    const auto& get_methods() const noexcept
    {
        return methods_;
    }

    void add_method(const MethodInfo& method_info);
    void add_field(const VariableInfo& variable_info);

    bool has_method(const Symbol* method_id) const;
    bool has_field(const Symbol* var_id) const;

    const VariableInfo& get_field(const Symbol* var_id) const;

private:
    std::map<const Symbol*, VariableInfo> fields_;
    std::map<const Symbol*, MethodInfo> methods_;

    const Symbol* class_id_;
    const Symbol* base_class_id_;
};

#endif //MINIJAVAC_CLASS_INFO_H
