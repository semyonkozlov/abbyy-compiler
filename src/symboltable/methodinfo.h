#ifndef MINIJAVAC_METHODINFO_H
#define MINIJAVAC_METHODINFO_H

#include <map>

#include "symbol.h"
#include "variableinfo.h"
#include "../ast/declaration.h"

class MethodInfo
{
public:
    MethodInfo();
    MethodInfo(AccessMod access_mod, const Symbol* return_type_id, const Symbol* method_id);

    const Symbol* get_method_id() const noexcept
    {
        return method_id_;
    }

    const Symbol* get_return_type_id() const noexcept
    {
        return return_type_id_;
    }

    AccessMod get_access_mod() const noexcept
    {
        return access_mod_;
    }

    const auto& get_args() const noexcept
    {
        return args_;
    }

    const auto& get_locals() const noexcept
    {
        return locals_;
    }

    void add_local_var_info(const VariableInfo& variable_info);
    void add_arg_info(const VariableInfo& variable_info);

private:
    std::map<const Symbol*, VariableInfo> args_;
    std::map<const Symbol*, VariableInfo> locals_;

    AccessMod access_mod_;
    const Symbol* return_type_id_;
    const Symbol* method_id_;
};

#endif //MINIJAVAC_METHODINFO_H
