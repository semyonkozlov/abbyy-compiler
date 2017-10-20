#include <iostream>

#include "parser.y.hpp"
#include "treeserializer.h"

const Program* program = nullptr;

int main(int argc, char** argv)
{
    //std::cout << std::is_abstract_v<TreeSerializer> << std::endl;
    yyparse();
    std::cout << program << std::endl;
    return EXIT_SUCCESS;
}