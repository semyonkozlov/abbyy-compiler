#ifndef MINIJAVAC_GRAMMAR_H
#define MINIJAVAC_GRAMMAR_H

#include <string>

#include "visitor.h"
#include "declaration.h"
#include "statement.h"
#include "type.h"
#include "expression.h"

class Program : public Visitable<Program>
{
public:
    Program(const MainClass* main_class, const ClassDeclList* other_classes) :
        main_class_(main_class), other_classes_(other_classes)
    { }

private:
    const MainClass* main_class_;
    const ClassDeclList* other_classes_;
};

class Symbol : public Visitable<MainClass>
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

private:
    std::string str_;
};

#endif //MINIJAVAC_GRAMMAR_H
