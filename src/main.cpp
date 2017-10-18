#include <iostream>

#include "parser.y.hpp"

int main(int argc, char** argv)
{
    return yyparse();
}