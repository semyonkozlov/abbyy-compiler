#ifndef MINIJAVAC_TABLEINITIALIZER_H
#define MINIJAVAC_TABLEINITIALIZER_H

#include "ast/visitor.h"
#include "table.h"

enum class Scope
{
    GLOBAL,
    CLASS,
    METHOD,

    ENUM_SIZE_
};

class TableInitializer final : public Visitor
{
public:
    TableInitializer();

    void init_symbol_table(Table* symbol_table, const Program* ast_root);

    void visit(const Program*) override;
    void visit(const Symbol*) override { }

    void visit(const MainClassDecl*) override;
    void visit(const ClassDeclList*) override;
    void visit(const ClassDecl*) override;
    void visit(const VarDeclList*) override;
    void visit(const VarDecl*) override;
    void visit(const MethodDeclList*) override;
    void visit(const MethodDecl*) override;
    void visit(const ArgumentList*) override;

    void visit(const UserDefinedType*) override { }
    void visit(const PrimitiveType*) override { }
    void visit(const ArrayType*) override { }

    void visit(const StatementList*) override { }
    void visit(const AssignSubscriptStatement*) override { }
    void visit(const PrintStatement*) override { }
    void visit(const IfStatement*) override { }
    void visit(const WhileStatement*) override { }
    void visit(const AssignStatement*) override { }
    void visit(const ScopedStatement*) override { }

    void visit(const ExpressionList*) override { }
    void visit(const LengthExpression*) override { }
    void visit(const IdExpression*) override { }
    void visit(const ThisExpression*) override { }
    void visit(const IntExpression*) override { }
    void visit(const BoolExpression*) override { }
    void visit(const MethodCallExpression*) override { }
    void visit(const SubscriptExpression*) override { }
    void visit(const ParenthesizedExpression*) override { }
    void visit(const NewArrayExpression*) override { }
    void visit(const NewObjectExpression*) override { }
    void visit(const BinaryExpression*) override { }
    void visit(const NegationExpression*) override { }
    void visit(const UnaryMinusExpression*) override { }

private:
    std::string var_decl_to_string_(const Symbol* type_id, const Symbol* var_id) const;
    std::string class_decl_to_string_(const Symbol* class_id) const;
    std::string method_decl_to_string_(const Symbol* return_type_id, const Symbol* method_id) const;

    Table* symbol_table_;

    ClassInfo current_class_;
    MethodInfo current_method_;
    Scope current_scope_;
};

#endif //MINIJAVAC_TABLEINITIALIZER_H
