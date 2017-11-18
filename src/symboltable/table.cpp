#include "table.h"

Table::Table() : classes_()
{ }

void Table::add_class_info(const ClassInfo& class_info)
{
    classes_[class_info.get_class_id()] = class_info;
}
