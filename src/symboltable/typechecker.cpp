#include "typechecker.h"

void TypeChecker::perform_type_checking(const Table* symbol_table, const Program* ast_root)
{
    symbol_table = symbol_table_;

    if (ast_root) {
        ast_root->accept(this);
    }
}