#include "table.h"

Table::Table() : classes_()
{ }

void Table::add_class(const ClassInfo& class_info)
{
    classes_[class_info.get_class_id()] = class_info;
}

bool Table::has_class(const Symbol* class_id) const
{
    return classes_.count(class_id) == 1;
}

const ClassInfo& Table::get_class(const Symbol* class_id) const
{
    return classes_.at(class_id);
}
