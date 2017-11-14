#include <iostream>
#include <fstream>
#include <cassert>

#include "ast/parser.y.hpp"

const Program* program = nullptr;

int main(int argc, char** argv)
{
    yyparse();

    //TreeSerializer tree_serializer;
    //std::cout << tree_serializer.ast_tree_to_dot(program) << std::endl;

    Table table;
    TableInitializer table_initializer;
    auto is_ok = table_initializer.init_symbol_table(&table, program);
    assert(is_ok);
    // TODO add deleter visitor

    return EXIT_SUCCESS;
}