#ifndef MINIJAVAC_TABLE_H
#define MINIJAVAC_TABLE_H

#include "symbol.h"

class Table
{
public:
    Table();

    void begin_scope();
    void end_scope();

    void add_binding(Symbol key, int i); // TODO
};

#endif //MINIJAVAC_TABLE_H
