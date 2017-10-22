#include "grammar.h"

#include "treeserializer.h"

TreeSerializer::TreeSerializer() : dot_stream_(), parent_(PROGRAM), syntax_counter_(), syntax_label_()
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
    syntax_label_[PRINT_STATEMENT] = "PrintStatement";
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
    dot_stream_.str({});

    dot_stream_ << "digraph ast {\n";
    program->accept(this);
    dot_stream_ << "}";
    return dot_stream_.str();
}

void TreeSerializer::add_edge_(TreeSerializer::SyntaxType from, TreeSerializer::SyntaxType to)
{
    dot_stream_<< "\t";
    add_vertex_(from);
    dot_stream_ << "->";
    add_vertex_(to);
    ++syntax_counter_[to];
    dot_stream_ << ";\n";
}

void TreeSerializer::add_vertex_(TreeSerializer::SyntaxType syntax_type)
{
    dot_stream_ << "{" << syntax_label_[syntax_type] << syntax_counter_[syntax_type];
    dot_stream_ << "[label=\"" << syntax_label_[syntax_type] << "\"]}";
}

void TreeSerializer::visit(const Program* program)
{
    if (program == nullptr) {
        return;
    }

    parent_ = PROGRAM;
    program->main_class_->accept(this);

    parent_ = PROGRAM;
    program->other_classes_->accept(this);
}


void TreeSerializer::visit(const Symbol* symbol)
{
    if (symbol == nullptr) {
        return;
    }

    add_edge_(parent_, SYMBOL);
}

void TreeSerializer::visit(const MainClass* main_class)
{
    if (main_class == nullptr) {
        return;
    }

    add_edge_(parent_, MAIN_CLASS);

    parent_ = MAIN_CLASS;
    main_class->class_id_->accept(this);

    parent_ = MAIN_CLASS;
    main_class->main_argv_id_->accept(this);

    parent_ = MAIN_CLASS;
    main_class->main_body_->accept(this);
}

void TreeSerializer::visit(const ClassDeclList* class_decl_list)
{
    if (class_decl_list == nullptr) {
        return;
    }

    add_edge_(parent_, CLASS_DECL_LIST);

    parent_= CLASS_DECL_LIST;
    class_decl_list->new_class_->accept(this);

    parent_ = CLASS_DECL_LIST;
    class_decl_list->other_classes_->accept(this);
}

void TreeSerializer::visit(const ClassDecl* class_decl)
{
	if( class_decl == nullptr ) {
		return;
	}

	add_edge_( parent_, CLASS_DECL );

	parent_ = CLASS_DECL;
	class_decl->class_id_->accept( this );

	parent_ = CLASS_DECL;
	class_decl->methods_->accept( this );

	parent_ = CLASS_DECL;
	class_decl->variables_->accept( this );

	parent_ = CLASS_DECL;
	class_decl->base_class_id_->accept( this );
}

void TreeSerializer::visit(const VarDeclList* var_decl_list)
{
	if( var_decl_list == nullptr ) {
		return;
	}

	add_edge_( parent_, VAR_DECL_LIST );

	parent_ = VAR_DECL_LIST;
	var_decl_list->other_var_decls_->accept( this );

	parent_ = VAR_DECL_LIST;
	var_decl_list->var_decl_->accept( this );
}

void TreeSerializer::visit(const VarDecl* var_decl)
{
	if( var_decl == nullptr ) {
		return;
	}

	add_edge_( parent_, VAR_DECL );
	
	parent_ = VAR_DECL;
	var_decl->type_->accept( this );

	parent_ = VAR_DECL;
	var_decl->var_id_->accept( this );
}

void TreeSerializer::visit(const MethodDeclList* method_decl_list)
{
	if( method_decl_list == nullptr ) {
		return;
	}

	add_edge_( parent_, METHOD_DECL_LIST );

	parent_ = METHOD_DECL_LIST;
	method_decl_list->method_decl_->accept( this );

	parent_ = METHOD_DECL_LIST;
	method_decl_list->other_methods_decls_->accept( this );
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

void TreeSerializer::visit(const ThisExpression* this_expression)
{
    if (this_expression == nullptr) {
        return;
    }

    add_edge_(parent_, THIS_EXPRESSION);
}

void TreeSerializer::visit(const IntExpression* int_expression)
{
    if (int_expression == nullptr) {
        return;
    }

    add_edge_(parent_, INT_EXPRESSION);

    parent_ = INT_EXPRESSION;
    int_expression->literal_id_->accept(this);
}

void TreeSerializer::visit(const BoolExpression* bool_expression)
{
    if (bool_expression == nullptr) {
        return;
    }

    add_edge_(parent_, BOOL_EXPRESSION);
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
