#include <gtest/gtest.h>

#include "ast/parser.y.hpp"
#include "ast/treedeallocator.h"

const Program* program = nullptr;

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    /*yyparse();

    TreeSerializer tree_serializer;
    std::cout << tree_serializer.ast_tree_to_dot(program) << std::endl;

    TreeDeallocator tree_deallocator;

    tree_deallocator.deallocate_tree(program);

    return EXIT_SUCCESS;*/
}