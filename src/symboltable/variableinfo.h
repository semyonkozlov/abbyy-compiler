#ifndef MINIJAVAC_VARIABLEINFO_H
#define MINIJAVAC_VARIABLEINFO_H

#include "symbol.h"

class VariableInfo
{
public:
    VariableInfo();
    VariableInfo(const Symbol* type_id, const Symbol* var_id_);

    const Symbol* get_var_id() const noexcept
    {
        return var_id_;
    }

private:
    const Symbol* type_id_;
    const Symbol* var_id_;
};

#endif //MINIJAVAC_VARIABLEINFO_H
