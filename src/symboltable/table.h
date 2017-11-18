#ifndef MINIJAVAC_TABLE_H
#define MINIJAVAC_TABLE_H

#include "symbol.h"
#include "classinfo.h"

class Table
{
public:
    Table();

    void add_class_info(const ClassInfo& class_info);

    const auto& get_classes() const noexcept
    {
        return classes_;
    }

private:
    std::map<const Symbol*, ClassInfo> classes_;
};

#endif //MINIJAVAC_TABLE_H
