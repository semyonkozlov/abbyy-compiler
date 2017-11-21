#include "typechecker.h"

void TypeChecker::perform_type_checking(const Table* symbol_table, const Program* ast_root)
{
    if (symbol_table == nullptr) {
        throw std::invalid_argument("symbol table must be initialized");
    }
    symbol_table_ = symbol_table;

    if (ast_root) {
        ast_root->accept(this);
    }
}