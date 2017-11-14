#include "tableinitializer.h"
#include "../ast/grammar.h"

TableInitializer::TableInitializer() : current_class_info_(), current_method_info_()
{ }

void TableInitializer::init_symbol_table(Table* symbol_table, const Program* ast_root)
{
    symbol_table_ = symbol_table;

    ast_root->accept(this);
}

void TableInitializer::visit(const Program* program)
{
    if (program == nullptr) {
        return;
    }

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
    if (main_class_decl == nullptr) {
        return;
    }

    current_class_info_ = ClassInfo(main_class_decl->class_id_);

    current_method_info_ = MethodInfo(Symbol::make_symbol("void"), Symbol::make_symbol("main"));
    if (main_class_decl->main_body_) {
        main_class_decl->main_body_->accept(this);
    }

    current_class_info_.add_method_info(current_method_info_);
}

void TableInitializer::visit(const ClassDeclList* class_decl_list)
{
    if (class_decl_list == nullptr) {
        return;
    }

    if (class_decl_list->new_class_) {
        class_decl_list->new_class_->accept(this);
    }

    if (class_decl_list->other_classes_) {
        class_decl_list->other_classes_->accept(this);
    }
}

void TableInitializer::visit(const ClassDecl* class_decl)
{
    if (class_decl == nullptr) {
        return;
    }

    current_class_info_ = ClassInfo(class_decl->class_id_, class_decl->base_class_id_);
}


