#ifndef MINIJAVAC_TABLE_H
#define MINIJAVAC_TABLE_H

#include "symbol.h"
#include "classinfo.h"

class Table
{
public:
    Table();

    void add_class(const ClassInfo& class_info);
    bool has_class(const Symbol* class_id) const;

    const auto& get_classes() const noexcept
    {
        return classes_;
    }

    const ClassInfo& get_class(const Symbol* class_id) const;

private:
    std::map<const Symbol*, ClassInfo> classes_;
};

#endif //MINIJAVAC_TABLE_H
