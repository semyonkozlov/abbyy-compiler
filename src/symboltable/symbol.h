#ifndef MINIJAVAC_SYMBOL_H
#define MINIJAVAC_SYMBOL_H

#include <string>
#include <unordered_map>
#include <memory>

#include "../ast/visitor.h"

class Symbol : public Visitable
{
public:
    Symbol(const Symbol&) = delete;
    Symbol& operator=(const Symbol& symbol) = delete;

    static const Symbol* make_symbol(const std::string& str);

    const std::string& to_string() const
    {
        return str_;
    }

    void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

private:
    Symbol(std::string str) : str_(std::move(str))
    { }

    static std::unordered_map<std::string, const Symbol*> intern_map_;

    std::string str_;
};

#endif //MINIJAVAC_SYMBOL_H
