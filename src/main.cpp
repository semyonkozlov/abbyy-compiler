#include <iostream>
#include <fstream>

#include "ast/parser.y.hpp"
#include "ast/treeserializer.h"
#include "symboltable/table.h"
#include "symboltable/tableinitializer.h"

const Program* program = nullptr;

int main(int argc, char** argv)
{
    yyparse();

    TreeSerializer tree_serializer;
    std::cout << tree_serializer.ast_tree_to_dot(program) << std::endl;

    Table table;
    TableInitializer table_initializer;
    table_initializer.init_symbol_table(&table, program);

    // TODO add deleter visitor

    return EXIT_SUCCESS;
}