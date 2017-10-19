#ifndef MINIJAVAC_EXPRESSION_H
#define MINIJAVAC_EXPRESSION_H

#include "visitor.h"
#include "grammar_def.h"

class ExpressionList : public Visitable<ExpressionList>
{
public:
    ExpressionList(const Expression* expression, const ExpressionList* other_expressions)
        : expression_(expression), other_expressions_(other_expressions)
    { }

private:
    const Expression* expression_;
    const ExpressionList* other_expressions_;
};

class Expression
{ };

enum class BinaryOperator {
    ADD, SUB, MUL, DIV, MOD, AND, OR, LESS
};

class BinaryExpression : public Visitable<BinaryExpression>, public Expression
{
public:
    BinaryExpression(const Expression* lhs_expression, BinaryOperator binary_operator,
        const Expression* rhs_expression)
        : lhs_expression_(lhs_expression), binary_operator_(binary_operator), rhs_expression_(rhs_expression)
    { }

private:
    const Expression* lhs_expression_;
    BinaryOperator binary_operator_;
    const Expression* rhs_expression_;
};

class SubscriptExpression : public Visitable<SubscriptExpression>, public Expression
{
public:
    SubscriptExpression(const Expression* expression, const Expression* subscript)
        : expression_(expression), subscript_(subscript)
    { }

private:
    const Expression* expression_;
    const Expression* subscript_;
};

class LengthExpression : public Visitable<LengthExpression>, public Expression
{
public:
    LengthExpression(const Expression* expression) : expression_(expression)
    { }

private:
    const Expression* expression_;
};

class MethodCallExpression : public Visitable<MethodCallExpression>, public Expression
{
public:
    MethodCallExpression(const Expression* expression, const Symbol* method_id,
        const ExpressionList* other_expressions)
        : expression_(expression), method_id_(method_id), other_expressions_(other_expressions)
    { }

private:
    const Expression* expression_;
    const Symbol* method_id_;
    const ExpressionList* other_expressions_;
};

class IntExpression : public Visitable<IntExpression>, public Expression
{
public:
    IntExpression(const Symbol* literal_id) : literal_id_(literal_id)
    { }

private:
    const Symbol* literal_id_;
};

class BoolExpression : public Visitable<BoolExpression>, public Expression
{
public:
    BoolExpression(bool b) : b_(b)
    { }

private:
    bool b_;
};

class IdExpression : public Visitable<IdExpression>, public Expression
{
public:
    IdExpression(const Symbol* id) : id_(id)
    { }

private:
    const Symbol* id_;
};

class ThisExpression : public Visitable<ThisExpression>, public Expression
{ };

class NewArrayExpression : public Visitable<NewArrayExpression>, public Expression
{
public:
    NewArrayExpression(const Type* type, const Expression* subscript_expression)
        : array_element_type_(type), subscript_expression_(subscript_expression)
    { }

private:
    const Type* array_element_type_;
    const Expression* subscript_expression_;
};

class NewObjectExpression : public Visitable<NewObjectExpression>, public Expression
{
public:
    NewObjectExpression(const Type* type) : new_object_type_(type)
    { }

private:
    const Type* new_object_type_;
};

class NegationExpression : public Visitable<NegationExpression>, public Expression
{
public:
    NegationExpression(const Expression* expression) : expression_to_negate_(expression)
    { }

private:
    const Expression* expression_to_negate_;
};

class ParenthesizedExpression: public Visitable<ParenthesizedExpression>, public Expression
{
public:
    ParenthesizedExpression(const Expression* expression) : expression_in_parentheses_(expression)
    { }

private:
    const Expression* expression_in_parentheses_;
};

#endif //MINIJAVAC_EXPRESSION_H
