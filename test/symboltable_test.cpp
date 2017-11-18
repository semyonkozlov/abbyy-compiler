#include <fstream>
#include <unordered_set>

#include <FlexLexer.h>

#include "gtest/gtest.h"

#include "../src/ast/parser.y.hpp"

extern yyFlexLexer scanner;
extern Program* program;

class SymbolTableTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        test_input_.open(TEST_DATA_FILE_NAME_);
        ASSERT_TRUE(test_input_.is_open());

        scanner.switch_streams(&test_input_);

        yyparse();

        bool is_ok = initializer_.init_symbol_table(&table_, program);
        ASSERT_TRUE(is_ok);
    }

    void TearDown() override
    {
        scanner.switch_streams(&std::cin);
        test_input_.close();

        // TODO!!! delete program ast tree
    }

    static constexpr const char* TEST_DATA_FILE_NAME_ = "../test/data/LinkedList.java";

    Table table_;
    TableInitializer initializer_;

    std::ifstream test_input_;
};

TEST_F(SymbolTableTest, correct_classes)
{
    auto classes = table_.get_classes();
    EXPECT_EQ(classes.size(), 4u);

    std::unordered_set<std::string> class_names;

    for (const auto& [symbol, _] : classes) {
        class_names.insert(symbol->to_string());
    }

    std::unordered_set<std::string> expected_class_names{"LinkedList", "Element", "List", "LL"};
    EXPECT_EQ(class_names, expected_class_names);
}

TEST_F(SymbolTableTest, correct_methods)
{
    auto classes = table_.get_classes();
    auto element_class = classes[Symbol::make_symbol("Element")];

    EXPECT_EQ(element_class.get_fields().size(), 3u);
    EXPECT_TRUE(element_class.get_fields().count(Symbol::make_symbol("Age")));

    EXPECT_EQ(element_class.get_methods().size(), 6u);
    EXPECT_TRUE(element_class.get_methods().count(Symbol::make_symbol("Compare")));
}

TEST_F(SymbolTableTest, correct_args_and_vars)
{
    auto classes = table_.get_classes();
    auto list_class = classes[Symbol::make_symbol("List")];
    auto list_methods = list_class.get_methods();

    auto init_new_method = list_methods[Symbol::make_symbol("InitNew")];
    auto init_new_args = init_new_method.get_args();
    EXPECT_EQ(init_new_args.size(), 3u);

    auto v_elem_var_id = Symbol::make_symbol("v_elem");
    ASSERT_TRUE(init_new_args.count(v_elem_var_id));
    EXPECT_EQ(init_new_args[v_elem_var_id].get_type_id(), Symbol::make_symbol("Element"));

    auto search_method = list_methods[Symbol::make_symbol("Search")];
    auto search_locals = search_method.get_locals();
    EXPECT_EQ(search_locals.size(), 5u);

    auto aux01_var_id = Symbol::make_symbol("aux01");
    ASSERT_TRUE(search_locals.count(aux01_var_id));
    EXPECT_EQ(search_locals[aux01_var_id].get_type_id(), Symbol::make_symbol("List"));

    EXPECT_EQ(search_method.get_return_type_id(), Symbol::make_symbol("int"));
    EXPECT_EQ(search_method.get_access_mod(), AccessMod::PUBLIC);
}