#include <iostream>

#include "parser.y.hpp"

const Program* program = nullptr;

int main(int argc, char** argv)
{
    yyparse();
    std::cout << program << std::endl;
    return EXIT_SUCCESS;
}