#include "grammar.h"

#include "treeserializer.h"

TreeSerializer::TreeSerializer() : parent_name_(), dotstream_(), syntax_counter_(), syntax_label_()
{
    syntax_label_[PROGRAM] = "Program";
    syntax_label_[SYMBOL] = "Symbol";
    syntax_label_[MAIN_CLASS] = "MainClass";
    syntax_label_[CLASS_DECL_LIST] = "ClassDeclList";
    syntax_label_[CLASS_DECL] = "ClassDecl";
    syntax_label_[VAR_DECL_LIST] = "VarDeclList";
    syntax_label_[VAR_DECL] = "VarDecl";
    syntax_label_[METHOD_DECL_LIST] = "MethodDeclList";
    syntax_label_[METHOD_DECL] = "MethodDecl";
    syntax_label_[ARGUMENT_LIST] = "ArgumentList";
    syntax_label_[USER_DEFINED_TYPE] = "UserDefinedType";
    syntax_label_[PRIMITIVE_TYPE] = "PrimitiveType";
    syntax_label_[ARRAY_TYPE] = "ArrayType";
    syntax_label_[STATEMENT_LIST] = "StatementList";
    syntax_label_[ASSIGN_SUBSCRIPT_STATEMENT] = "AssignSubscriptStatement";
    syntax_label_[PRINT_STATEMENT] = "PrintStatent";
    syntax_label_[IF_STATEMENT] = "IfStatement";
    syntax_label_[WHILE_STATEMENT] = "WhileStatement";
    syntax_label_[ASSIGN_STATEMENT] = "AssignStatement";
    syntax_label_[SCOPED_STATEMENT] = "ScopedStatement";
    syntax_label_[EXPRESSION_LIST] = "ExpressionList";
    syntax_label_[LENGTH_EXPRESSION] = "LengthExpression";
    syntax_label_[ID_EXPRESSION] = "IdExpression;";
    syntax_label_[THIS_EXPRESSION] = "ThisExpression";
    syntax_label_[INT_EXPRESSION] = "IntExpression";
    syntax_label_[BOOL_EXPRESSION] = "BoolExpression";
    syntax_label_[METHOD_CALL_EXPRESSION] = "MethodCallExpression";
    syntax_label_[SUBSCRIPT_EXPRESSION] = "SubscriptExpression";
    syntax_label_[PARENTHESIZED_EXPRESSION] = "ParenthesizedExpression";
    syntax_label_[NEW_ARRAY_EXPRESSION] = "NewArrayExpression";
    syntax_label_[NEW_OBJECT_EXPRESSION] = "NewObjectExpression";
    syntax_label_[BINARY_EXPRESSION] = "BinaryExpression";
    syntax_label_[NEGATION_EXPRESSION] = "NegationExpression";
}

std::string TreeSerializer::ast_tree_to_dot(const Program* program)
{
    dotstream_.str({});

    dotstream_ << "digraph ast {\n";
    program->accept(this);
    dotstream_ << "};";
    return dotstream_.str();
}

void TreeSerializer::add_edge_(TreeSerializer::SyntaxNode from, TreeSerializer::SyntaxNode to)
{
    add_vertex_(from);
    dotstream_ << "->";
    add_vertex_(to);
}

void TreeSerializer::add_vertex_(TreeSerializer::SyntaxNode node)
{
    dotstream_ << '{' << syntax_label_[node] << syntax_counter_[node];
    dotstream_ << "[label=\"" << syntax_label_[node] << "\"]}";
}

void TreeSerializer::visit(const Program* program)
{

    program->main_class_->accept(this);
    program->other_classes_->accept(this);
}


void TreeSerializer::visit(const Symbol*)
{

}

void TreeSerializer::visit(const MainClass*)
{

}

void TreeSerializer::visit(const ClassDeclList*)
{

}

void TreeSerializer::visit(const ClassDecl*)
{

}

void TreeSerializer::visit(const VarDeclList*)
{

}

void TreeSerializer::visit(const VarDecl*)
{

}

void TreeSerializer::visit(const MethodDeclList*)
{

}

void TreeSerializer::visit(const MethodDecl*)
{

}

void TreeSerializer::visit(const ArgumentList*)
{

}

void TreeSerializer::visit(const UserDefinedType*)
{

}

void TreeSerializer::visit(const PrimitiveType*)
{

}

void TreeSerializer::visit(const ArrayType*)
{

}

void TreeSerializer::visit(const StatementList*)
{

}

void TreeSerializer::visit(const AssignSubscriptStatement*)
{

}

void TreeSerializer::visit(const PrintStatement*)
{

}

void TreeSerializer::visit(const IfStatement*)
{

}

void TreeSerializer::visit(const WhileStatement*)
{

}

void TreeSerializer::visit(const AssignStatement*)
{

}

void TreeSerializer::visit(const ScopedStatement*)
{

}

void TreeSerializer::visit(const ExpressionList*)
{

}

void TreeSerializer::visit(const LengthExpression*)
{

}

void TreeSerializer::visit(const IdExpression*)
{

}

void TreeSerializer::visit(const ThisExpression*)
{

}

void TreeSerializer::visit(const IntExpression*)
{

}

void TreeSerializer::visit(const BoolExpression*)
{

}

void TreeSerializer::visit(const MethodCallExpression*)
{

}

void TreeSerializer::visit(const SubscriptExpression*)
{

}

void TreeSerializer::visit(const ParenthesizedExpression*)
{

}

void TreeSerializer::visit(const NewArrayExpression*)
{

}

void TreeSerializer::visit(const NewObjectExpression*)
{

}

void TreeSerializer::visit(const BinaryExpression*)
{

}

void TreeSerializer::visit(const NegationExpression*)
{

}
