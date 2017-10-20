#ifndef MINIJAVAC_GRAMMAR_H
#define MINIJAVAC_GRAMMAR_H

#include <string>

#include "visitor.h"
#include "declaration.h"
#include "statement.h"
#include "type.h"
#include "expression.h"

class Program : public Visitable
{
public:
    Program(const MainClass* main_class, const ClassDeclList* other_classes) :
        main_class_(main_class), other_classes_(other_classes)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

/*private:*/
    const MainClass* main_class_;
    const ClassDeclList* other_classes_;
};

class Symbol : public Visitable
{
public:
    Symbol(std::string str) : str_(std::move(str))
    { }

    Symbol(const Symbol&) = delete;
    Symbol& operator=(const Symbol& symbol) = delete;

    const std::string& to_string() const
    {
        return str_;
    }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

/*private:*/
    std::string str_;
};

#endif //MINIJAVAC_GRAMMAR_H
