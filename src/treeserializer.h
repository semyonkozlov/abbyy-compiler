#ifndef MINIJAVAC_TREESERIALIZER_H
#define MINIJAVAC_TREESERIALIZER_H

#include <string>
#include <array>
#include <sstream>
#include <queue>

#include "visitor.h"
#include "grammar_decl.h"

class TreeSerializer : public Visitor
{
public:
    TreeSerializer() noexcept;

    std::string ast_tree_to_dot(const Program* program);

    void visit(const Program* program) override;

private:
    enum SyntaxNode
    {

    };

    std::queue<std::string> parent_name_;
    std::stringstream dotstream_;
    std::array<std::size_t, -1> syntax_counter_;
    std::array<std::string, -1> syntax_label_;

    void add_edge_(SyntaxNode from, SyntaxNode to);

};

#endif //MINIJAVAC_TREESERIALIZER_H
