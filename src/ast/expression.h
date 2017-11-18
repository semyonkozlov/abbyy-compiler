#ifndef MINIJAVAC_EXPRESSION_H
#define MINIJAVAC_EXPRESSION_H

#include "visitor.h"
#include "grammardecl.h"

class ExpressionList : public Visitable
{
public:
    ExpressionList(const Expression* expression, const ExpressionList* other_expressions)
        : expression_(expression), other_expressions_(other_expressions)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

/*private:*/
    const Expression* expression_;
    const ExpressionList* other_expressions_;
};

struct Expression : public Visitable
{ };

enum class BinaryOperator 
{
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    AND,
    OR,
    LESS,

    ENUM_SIZE_
};

class BinaryExpression : public Expression
{
public:
    BinaryExpression(const Expression* lhs_expression, BinaryOperator binary_operator,
        const Expression* rhs_expression)
        : lhs_expression_(lhs_expression), binary_operator_(binary_operator), rhs_expression_(rhs_expression)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

/*private:*/
    const Expression* lhs_expression_;
    BinaryOperator binary_operator_;
    const Expression* rhs_expression_;
};

class SubscriptExpression : public Expression
{
public:
    SubscriptExpression(const Expression* expression, const Expression* subscript)
        : expression_(expression), subscript_(subscript)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

/*private:*/
    const Expression* expression_;
    const Expression* subscript_;
};

class LengthExpression : public Expression
{
public:
    LengthExpression(const Expression* expression) : expression_(expression)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

/*private:*/
    const Expression* expression_;
};

class MethodCallExpression : public Expression
{
public:
    MethodCallExpression(const Expression* expression, const Symbol* method_id,
        const ExpressionList* other_expressions)
        : expression_(expression), method_id_(method_id), other_expressions_(other_expressions)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

/*private:*/
    const Expression* expression_;
    const Symbol* method_id_;
    const ExpressionList* other_expressions_;
};

class IntExpression : public Expression
{
public:
    IntExpression(const Symbol* literal_id) : literal_id_(literal_id)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

/*private:*/
    const Symbol* literal_id_;
};

class BoolExpression : public Expression
{
public:
    BoolExpression(bool b) : b_(b)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

/*private:*/
    bool b_;
};

class IdExpression : public Expression
{
public:
    IdExpression(const Symbol* id) : id_(id)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

/*private:*/
    const Symbol* id_;
};

class ThisExpression : public Expression
{
    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }
};

class NewArrayExpression : public Expression
{
public:
    NewArrayExpression(const Type* type, const Expression* subscript_expression)
        : array_element_type_(type), subscript_expression_(subscript_expression)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

/*private:*/
    const Type* array_element_type_;
    const Expression* subscript_expression_;
};

class NewObjectExpression : public Expression
{
public:
    NewObjectExpression(const Type* type) : new_object_type_(type)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

/*private:*/
    const Type* new_object_type_;
};

class NegationExpression : public Expression
{
public:
    NegationExpression(const Expression* expression) : expression_to_negate_(expression)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

/*private:*/
    const Expression* expression_to_negate_;
};

class ParenthesizedExpression : public Expression
{
public:
    ParenthesizedExpression(const Expression* expression) : expression_in_parentheses_(expression)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

/*private:*/
    const Expression* expression_in_parentheses_;
};

class UnaryMinusExpression : public Expression
{
public:
    UnaryMinusExpression(const Expression* expression) : expression_(expression)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

    const Expression* expression_;
};

#endif //MINIJAVAC_EXPRESSION_H
