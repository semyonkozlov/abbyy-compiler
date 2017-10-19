#ifndef MINIJAVAC_EXPRESSION_H
#define MINIJAVAC_EXPRESSION_H

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
    AND, LESS, MUL, DIV, MOD, OR
};

class BinaryExpression : public Visitable<BinaryExpression>, public Expression
{ };

#endif //MINIJAVAC_EXPRESSION_H
