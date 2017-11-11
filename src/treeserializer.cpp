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
    syntax_label_[ID_EXPRESSION] = "IdExpression";
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
    syntax_label_[UNARY_MINUS_EXPRESSION] = "UnaryMinusExpression";
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
    dot_stream_ << "\t";
    add_vertex_(from);
    dot_stream_ << "->";
    ++syntax_counter_[to];
    add_vertex_(to);
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

    if (program->other_classes_) {
        parent_ = PROGRAM;
        program->other_classes_->accept(this);
    }
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

    parent_ = CLASS_DECL_LIST;
    class_decl_list->new_class_->accept(this);

    if (class_decl_list->other_classes_) {
        parent_ = CLASS_DECL_LIST;
        class_decl_list->other_classes_->accept(this);
    }
}

void TreeSerializer::visit(const ClassDecl* class_decl)
{
    if (class_decl == nullptr) {
        return;
    }

    add_edge_(parent_, CLASS_DECL);

    parent_ = CLASS_DECL;
    class_decl->class_id_->accept(this);

    if (class_decl->methods_) {
        parent_ = CLASS_DECL;
        class_decl->methods_->accept(this);
    }

    if (class_decl->variables_) {
        parent_ = CLASS_DECL;
        class_decl->variables_->accept(this);
    }

    if (class_decl->base_class_id_) {
        parent_ = CLASS_DECL;
        class_decl->base_class_id_->accept(this);
    }
}

void TreeSerializer::visit(const VarDeclList* var_decl_list)
{
    if (var_decl_list == nullptr) {
        return;
    }

    add_edge_(parent_, VAR_DECL_LIST);

    parent_ = VAR_DECL_LIST;
    var_decl_list->var_decl_->accept(this);

    if (var_decl_list->other_var_decls_) {
        parent_ = VAR_DECL_LIST;
        var_decl_list->other_var_decls_->accept(this);
    }
}

void TreeSerializer::visit(const VarDecl* var_decl)
{
    if (var_decl == nullptr) {
        return;
    }

    add_edge_(parent_, VAR_DECL);

    parent_ = VAR_DECL;
    var_decl->type_->accept(this);

    parent_ = VAR_DECL;
    var_decl->var_id_->accept(this);
}

void TreeSerializer::visit(const MethodDeclList* method_decl_list)
{
    if (method_decl_list == nullptr) {
        return;
    }

    add_edge_(parent_, METHOD_DECL_LIST);

    parent_ = METHOD_DECL_LIST;
    method_decl_list->method_decl_->accept(this);

    if (method_decl_list->other_methods_decls_) {
        parent_ = METHOD_DECL_LIST;
        method_decl_list->other_methods_decls_->accept(this);
    }
}

void TreeSerializer::visit(const MethodDecl* method_decl)
{
    if (method_decl == nullptr) {
        return;
    }

    add_edge_(parent_, METHOD_DECL);

    if (method_decl->arg_list_) {
        parent_ = METHOD_DECL;
        method_decl->arg_list_->accept(this);
    }

    parent_ = METHOD_DECL;
    method_decl->method_id_->accept(this);

    parent_ = METHOD_DECL;
    method_decl->return_expression_->accept(this);

    parent_ = METHOD_DECL;
    method_decl->return_type_->accept(this);

    if (method_decl->statements_) {
        parent_ = METHOD_DECL;
        method_decl->statements_->accept(this);
    }

    if (method_decl->var_decls_) {
        parent_ = METHOD_DECL;
        method_decl->var_decls_->accept(this);
    }
}

void TreeSerializer::visit(const ArgumentList* argument_list)
{
    if (argument_list == nullptr) {
        return;
    }

    add_edge_(parent_, ARGUMENT_LIST);

    parent_ = ARGUMENT_LIST;
    argument_list->arg_id_->accept(this);

    parent_ = ARGUMENT_LIST;
    argument_list->arg_type_->accept(this);

    if (argument_list->other_args_) {
        parent_ = ARGUMENT_LIST;
        argument_list->other_args_->accept(this);
    }
}

void TreeSerializer::visit(const UserDefinedType* user_defined_type)
{
    if (user_defined_type == nullptr) {
        return;
    }

    add_edge_(parent_, USER_DEFINED_TYPE);

    parent_ = USER_DEFINED_TYPE;
    user_defined_type->type_id_->accept(this);
}

void TreeSerializer::visit(const PrimitiveType* primitive_type)
{
    if (primitive_type == nullptr) {
        return;
    }

    add_edge_(parent_, PRIMITIVE_TYPE);
}

void TreeSerializer::visit(const ArrayType* array_type)
{
    if (array_type == nullptr) {
        return;
    }

    add_edge_(parent_, ARRAY_TYPE);
}

void TreeSerializer::visit(const StatementList* statement_list)
{
    if (statement_list == nullptr) {
        return;
    }

    add_edge_(parent_, STATEMENT_LIST);

    parent_ = STATEMENT_LIST;
    statement_list->statement_->accept(this);

    if (statement_list->other_statements_) {
        parent_ = STATEMENT_LIST;
        statement_list->other_statements_->accept(this);
    }
}

void TreeSerializer::visit(const AssignSubscriptStatement* assign_subscript_statement)
{
    if (assign_subscript_statement == nullptr) {
        return;
    }

    add_edge_(parent_, ASSIGN_SUBSCRIPT_STATEMENT);

    parent_ = ASSIGN_SUBSCRIPT_STATEMENT;
    assign_subscript_statement->lhs_array_id_->accept(this);

    parent_ = ASSIGN_SUBSCRIPT_STATEMENT;
    assign_subscript_statement->rhs_expression_->accept(this);

    parent_ = ASSIGN_SUBSCRIPT_STATEMENT;
    assign_subscript_statement->subscript_->accept(this);
}

void TreeSerializer::visit(const PrintStatement* print_statement)
{
    if (print_statement == nullptr) {
        return;
    }

    add_edge_(parent_, PRINT_STATEMENT);

    parent_ = PRINT_STATEMENT;
    print_statement->expression_to_print_->accept(this);
}

void TreeSerializer::visit(const IfStatement* if_statement)
{
    if (if_statement == nullptr) {
        return;
    }

    add_edge_(parent_, IF_STATEMENT);

    parent_ = IF_STATEMENT;
    if_statement->if_condition_->accept(this);

    parent_ = IF_STATEMENT;
    if_statement->statement_if_false_->accept(this);

    parent_ = IF_STATEMENT;
    if_statement->statement_if_true_->accept(this);
}

void TreeSerializer::visit(const WhileStatement* while_statement)
{
    if (while_statement == nullptr) {
        return;
    }

    add_edge_(parent_, WHILE_STATEMENT);

    parent_ = WHILE_STATEMENT;
    while_statement->inloop_statement_->accept(this);

    parent_ = WHILE_STATEMENT;
    while_statement->loop_condition_->accept(this);
}

void TreeSerializer::visit(const AssignStatement* assign_statement)
{
    if (assign_statement == nullptr) {
        return;
    }

    add_edge_(parent_, ASSIGN_STATEMENT);

    parent_ = ASSIGN_STATEMENT;
    assign_statement->lhs_var_id_->accept(this);

    parent_ = ASSIGN_STATEMENT;
    assign_statement->rhs_expression_->accept(this);
}

void TreeSerializer::visit(const ScopedStatement* scoped_statement)
{
    if (scoped_statement == nullptr) {
        return;
    }

    add_edge_(parent_, SCOPED_STATEMENT);

    if (scoped_statement->statements_in_scope_) {
        parent_ = SCOPED_STATEMENT;
        scoped_statement->statements_in_scope_->accept(this);
    }
}

void TreeSerializer::visit(const ExpressionList* expression_list)
{
    if (expression_list == nullptr) {
        return;
    }

    add_edge_(parent_, EXPRESSION_LIST);

    parent_ = EXPRESSION_LIST;
    expression_list->expression_->accept(this);

    if (expression_list->other_expressions_) {
        parent_ = EXPRESSION_LIST;
        expression_list->other_expressions_->accept(this);
    }
}

void TreeSerializer::visit(const LengthExpression* length_expression)
{
    if (length_expression == nullptr) {
        return;
    }

    add_edge_(parent_, LENGTH_EXPRESSION);

    parent_ = LENGTH_EXPRESSION;
    length_expression->expression_->accept(this);
}

void TreeSerializer::visit(const IdExpression* id_expression)
{
    if (id_expression == nullptr) {
        return;
    }

    add_edge_(parent_, ID_EXPRESSION);

    parent_ = ID_EXPRESSION;
    id_expression->id_->accept(this);
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

void TreeSerializer::visit(const MethodCallExpression* method_call_expression)
{
    if (method_call_expression == nullptr) {
        return;
    }

    add_edge_(parent_, METHOD_CALL_EXPRESSION);

    parent_ = METHOD_CALL_EXPRESSION;
    method_call_expression->expression_->accept(this);

    parent_ = METHOD_CALL_EXPRESSION;
    method_call_expression->method_id_->accept(this);

    if (method_call_expression->other_expressions_) {
        parent_ = METHOD_CALL_EXPRESSION;
        method_call_expression->other_expressions_->accept(this);
    }
}

void TreeSerializer::visit(const SubscriptExpression* subscript_expression)
{
    if (subscript_expression == nullptr) {
        return;
    }

    add_edge_(parent_, SUBSCRIPT_EXPRESSION);

    parent_ = SUBSCRIPT_EXPRESSION;
    subscript_expression->expression_->accept(this);

    parent_ = SUBSCRIPT_EXPRESSION;
    subscript_expression->subscript_->accept(this);
}

void TreeSerializer::visit(const ParenthesizedExpression* parenthesized_expression)
{
    if (parenthesized_expression == nullptr) {
        return;
    }

    add_edge_(parent_, PARENTHESIZED_EXPRESSION);

    parent_ = PARENTHESIZED_EXPRESSION;
    parenthesized_expression->expression_in_parentheses_->accept(this);
}

void TreeSerializer::visit(const NewArrayExpression* new_array_expression)
{
    if (new_array_expression == nullptr) {
        return;
    }

    add_edge_(parent_, NEW_ARRAY_EXPRESSION);

    parent_ = NEW_ARRAY_EXPRESSION;
    new_array_expression->array_element_type_->accept(this);

    parent_ = NEW_ARRAY_EXPRESSION;
    new_array_expression->subscript_expression_->accept(this);
}

void TreeSerializer::visit(const NewObjectExpression* new_object_expression)
{
    if (new_object_expression == nullptr) {
        return;
    }

    add_edge_(parent_, NEW_OBJECT_EXPRESSION);

    parent_ = NEW_OBJECT_EXPRESSION;
    new_object_expression->new_object_type_->accept(this);
}

void TreeSerializer::visit(const BinaryExpression* binary_expression)
{
    if (binary_expression == nullptr) {
        return;
    }

    add_edge_(parent_, BINARY_EXPRESSION);

    parent_ = BINARY_EXPRESSION;
    binary_expression->lhs_expression_->accept(this);

    parent_ = BINARY_EXPRESSION;
    binary_expression->rhs_expression_->accept(this);
}

void TreeSerializer::visit(const NegationExpression* negation_expression)
{
    if (negation_expression == nullptr) {
        return;
    }

    add_edge_(parent_, NEGATION_EXPRESSION);

    parent_ = NEGATION_EXPRESSION;
    negation_expression->expression_to_negate_->accept(this);
}

void TreeSerializer::visit(const UnaryMinusExpression* unary_minus_expression)
{
    if (unary_minus_expression == nullptr) {
        return;
    }

    add_edge_(parent_, UNARY_MINUS_EXPRESSION);

    parent_ = UNARY_MINUS_EXPRESSION;
    unary_minus_expression->expression_->accept(this);
}
