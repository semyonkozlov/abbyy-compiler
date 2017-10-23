#include <iostream>
#include <fstream>

#include "parser.y.hpp"
#include "treeserializer.h"

const Program* program = nullptr;

int main(int argc, char** argv)
{
    yyparse();

    TreeSerializer tree_serializer;
    std::cout << tree_serializer.ast_tree_to_dot(program) << std::endl;

    //std::cout << program << std::endl;
    //std::cout << program->other_classes_ << std::endl;
    //std::cout << program->main_class_ << std::endl;
    return EXIT_SUCCESS;
}