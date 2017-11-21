#include <cassert>
#include <iostream>

#include <fmt/format.h>

#include "tableinitializer.h"
#include "ast/grammar.h"

TableInitializer::TableInitializer()
    : symbol_table_(nullptr), current_class_(), current_method_(), current_scope_(Scope::GLOBAL)
{ }

void TableInitializer::init_symbol_table(Table* symbol_table, const Program* ast_root)
{
    assert(symbol_table != nullptr);
    symbol_table_ = symbol_table;

    if (ast_root) {
        ast_root->accept(this);
    }
}

void TableInitializer::visit(const Program* program)
{
    if (program->main_class_) {
        program->main_class_->accept(this);
    }

    if (program->other_classes_) {
        program->other_classes_->accept(this);
    }
}

void TableInitializer::visit(const MainClassDecl* main_class_decl)
{
    if (symbol_table_->has_class(main_class_decl->class_id_)) {
        ::register_error(ErrorType::REDEFINITION, class_decl_to_string_(main_class_decl->class_id_),
            main_class_decl->location_);
        return;
    }

    current_class_ = ClassInfo(main_class_decl->class_id_);

    current_method_ = MethodInfo(AccessMod::PUBLIC, Symbol::make_symbol("void"), Symbol::make_symbol("main"));
    current_method_.add_arg({ Symbol::make_symbol("String[]"), main_class_decl->main_argv_id_ });

    current_class_.add_method(current_method_);

    symbol_table_->add_class(current_class_);
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
    if (symbol_table_->has_class(class_decl->class_id_)) {
        ::register_error(ErrorType::REDEFINITION,
            "class" + class_decl->class_id_->to_string(), class_decl->location_);
        return;
    }

    current_class_ = ClassInfo(class_decl->class_id_, class_decl->base_class_id_);

    if (class_decl->variables_) {
        current_scope_ = Scope::CLASS;
        class_decl->variables_->accept(this);
    }

    if (class_decl->methods_) {
        class_decl->methods_->accept(this);
    }

    symbol_table_->add_class(current_class_);
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
            if (current_class_.has_field(var_decl->var_id_)) { // TODO conflicting declaration
                ::register_error(ErrorType::REDECLARATION,
                    var_decl_to_string_(var_decl->type_->type_id_, var_decl->var_id_),
                    var_decl->location_);
                return;
            }

            current_class_.add_field(var_info);
            break;

        case Scope::METHOD:
            if (current_method_.has_arg(var_decl->var_id_) || current_method_.has_local_var(var_decl->var_id_)) {
                ::register_error(ErrorType::REDECLARATION,
                    var_decl_to_string_(var_decl->type_->type_id_, var_decl->var_id_),
                    var_decl->location_);
                return;
            }

            current_method_.add_local_var(var_info);
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
    if (current_class_.has_method(method_decl->method_id_)) {
        ::register_error(ErrorType::REDEFINITION,
            method_decl_to_string_(method_decl->return_type_->type_id_, method_decl->method_id_),
            method_decl->location_);
        return;
    }

    current_method_ = MethodInfo(method_decl->access_mod_, method_decl->return_type_->type_id_,
        method_decl->method_id_);

    if (method_decl->arg_list_) {
        method_decl->arg_list_->accept(this);
    }

    if (method_decl->var_decls_) {
        current_scope_ = Scope::METHOD;
        method_decl->var_decls_->accept(this);
    }

    current_class_.add_method(current_method_);
}


void TableInitializer::visit(const ArgumentList* arg_list)
{
    if (current_method_.has_arg(arg_list->arg_id_)) {
        register_error(ErrorType::REDECLARATION,
            var_decl_to_string_(arg_list->arg_type_->type_id_, arg_list->arg_id_),
            arg_list->location_);
        return;
    }

    current_method_.add_arg({ arg_list->arg_type_->type_id_, arg_list->arg_id_ });

    if (arg_list->other_args_) {
        arg_list->other_args_->accept(this);
    }
}

std::string TableInitializer::var_decl_to_string_(const Symbol* type_id, const Symbol* var_id) const
{
    switch (current_scope_) {
        case Scope::CLASS:
            return fmt::format("{} {}.{}", type_id->to_string(), current_class_.get_class_id()->to_string(),
                var_id->to_string());

        case Scope::METHOD:
        default:
            return fmt::format("{} {}", type_id->to_string(), var_id->to_string());

    }
}

std::string TableInitializer::class_decl_to_string_(const Symbol* class_id) const
{
    return fmt::format("class {}", class_id->to_string());
}

std::string TableInitializer::method_decl_to_string_(const Symbol* return_type_id, const Symbol* method_id) const
{
    return fmt::format("{} {}.{}()", return_type_id->to_string(), current_class_.get_class_id()->to_string(),
        method_id->to_string());
}

