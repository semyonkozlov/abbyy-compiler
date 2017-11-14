#include <cassert>

#include "tableinitializer.h"
#include "../ast/grammar.h"

TableInitializer::TableInitializer()
    : symbol_table_(nullptr), current_class_info_(), current_method_info_(), current_scope_(Scope::GLOBAL)
{ }

bool TableInitializer::init_symbol_table(Table* symbol_table, const Program* ast_root)
{
    if (symbol_table_ == nullptr) {
        return false;
    }
    symbol_table_ = symbol_table;

    if (ast_root) {
        ast_root->accept(this);
    }

    return true;
}

void TableInitializer::visit(const Program* program)
{
    if (program->main_class_) {
        program->main_class_->accept(this);
        symbol_table_->add_class_info(current_class_info_);
    }

    if (program->other_classes_) {
        program->other_classes_->accept(this);
    }
}

void TableInitializer::visit(const MainClassDecl* main_class_decl)
{
    current_class_info_ = ClassInfo(main_class_decl->class_id_);

    current_method_info_ = MethodInfo(Symbol::make_symbol("void"), Symbol::make_symbol("main"));
    current_method_info_.add_arg_info(VariableInfo(Symbol::make_symbol("String[]"), main_class_decl->main_argv_id_));

    current_class_info_.add_method_info(current_method_info_);
}

void TableInitializer::visit(const ClassDeclList* class_decl_list)
{
    if (class_decl_list->new_class_) {
        class_decl_list->new_class_->accept(this);
    }

    if (class_decl_list->other_classes_) {
        class_decl_list->other_classes_->accept(this);
    }
}

void TableInitializer::visit(const ClassDecl* class_decl)
{
    current_class_info_ = ClassInfo(class_decl->class_id_, class_decl->base_class_id_);

    if (class_decl->variables_) {
        current_scope_ = Scope::CLASS;
        class_decl->variables_->accept(this);
    }

    if (class_decl->methods_) {
        class_decl->methods_->accept(this);
    }
}

void TableInitializer::visit(const VarDeclList* var_decl_list)
{
    if (var_decl_list->var_decl_) {
        var_decl_list->var_decl_->accept(this);
    }

    if (var_decl_list->other_var_decls_) {
        var_decl_list->other_var_decls_->accept(this);
    }
}

void TableInitializer::visit(const VarDecl* var_decl)
{
    VariableInfo var_info(var_decl->type_->type_id_, var_decl->var_id_);

    switch (current_scope_) {
        case Scope::CLASS:
            current_class_info_.add_field_info(var_info);
            break;

        case Scope::LOCAL: // TODO do we have scope blocks?
        case Scope::METHOD:
            current_method_info_.add_local_var_info(var_info);
            break;

        default:
            assert(false);
    }
}

void TableInitializer::visit(const MethodDeclList* method_decl_list)
{
    if (method_decl_list->method_decl_) {
        method_decl_list->method_decl_->accept(this);
    }

    if (method_decl_list->other_methods_decls_) {
        method_decl_list->other_methods_decls_->accept(this);
    }
}

void TableInitializer::visit(const MethodDecl* method_decl)
{
    current_method_info_ = MethodInfo(method_decl->return_type_->type_id_, method_decl->method_id_);

    if (method_decl->arg_list_) {
        method_decl->arg_list_->accept(this);
    }

    if (method_decl->var_decls_) {
        current_scope_ = Scope::METHOD;
        method_decl->var_decls_->accept(this);
    }
}

void TableInitializer::visit(const ArgumentList* arg_list)
{
    current_method_info_.add_arg_info(VariableInfo(arg_list->arg_type_->type_id_, arg_list->arg_id_));

    if (arg_list->other_args_) {
        arg_list->other_args_->accept(this);
    }
}
