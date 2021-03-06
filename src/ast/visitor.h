#ifndef MINIJAVAC_VISITOR_H
#define MINIJAVAC_VISITOR_H

#include "grammardecl.h"
#include "utils/utils.h"

class Visitor
{
public:
    virtual ~Visitor() = default;

    virtual void visit(const Program*) = 0;
    virtual void visit(const Symbol*) = 0;

    virtual void visit(const MainClassDecl*) = 0;
    virtual void visit(const ClassDeclList*) = 0;
    virtual void visit(const ClassDecl*) = 0;
    virtual void visit(const VarDeclList*) = 0;
    virtual void visit(const VarDecl*) = 0;
    virtual void visit(const MethodDeclList*) = 0;
    virtual void visit(const MethodDecl*) = 0;
    virtual void visit(const ArgumentList*) = 0;

    virtual void visit(const UserDefinedType*) = 0;
    virtual void visit(const PrimitiveType*) = 0;
    virtual void visit(const ArrayType*) = 0;

    virtual void visit(const StatementList*) = 0;
    virtual void visit(const AssignSubscriptStatement*) = 0;
    virtual void visit(const PrintStatement*) = 0;
    virtual void visit(const IfStatement*) = 0;
    virtual void visit(const WhileStatement*) = 0;
    virtual void visit(const AssignStatement*) = 0;
    virtual void visit(const ScopedStatement*) = 0;

    virtual void visit(const ExpressionList*) = 0;
    virtual void visit(const LengthExpression*) = 0;
    virtual void visit(const IdExpression*) = 0;
    virtual void visit(const ThisExpression*) = 0;
    virtual void visit(const IntExpression*) = 0;
    virtual void visit(const BoolExpression*) = 0;
    virtual void visit(const MethodCallExpression*) = 0;
    virtual void visit(const SubscriptExpression*) = 0;
    virtual void visit(const ParenthesizedExpression*) = 0;
    virtual void visit(const NewArrayExpression*) = 0;
    virtual void visit(const NewObjectExpression*) = 0;
    virtual void visit(const BinaryExpression*) = 0;
    virtual void visit(const NegationExpression*) = 0;
    virtual void visit(const UnaryMinusExpression*) = 0;
};

class Visitable
{
public:
    Visitable() : location_(yylloc)
    { }

    virtual ~Visitable() = default;

    virtual void accept(Visitor* visitor) const = 0;

/*protected:*/
    Location location_;
};

#endif //MINIJAVAC_VISITOR_H
