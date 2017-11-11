#ifndef MINIJAVAC_SYMBOL_H
#define MINIJAVAC_SYMBOL_H

#include <string>
#include <unordered_map>
#include <memory>

#include "visitor.h"

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

private:
    std::string str_;
};

std::shared_ptr<Symbol> make_symbol(const std::string& str);

#endif //MINIJAVAC_SYMBOL_H
