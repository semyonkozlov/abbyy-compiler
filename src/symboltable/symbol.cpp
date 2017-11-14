#include "symbol.h"

std::unordered_map<std::string, const Symbol*> Symbol::intern_map_{};

const Symbol* Symbol::make_symbol(const std::string& str)
{
    if (auto intern = intern_map_.find(str); intern != std::end(intern_map_)) {
        return intern->second;
    }

    auto new_intern = new Symbol(str);
    intern_map_[str] = new_intern;
    return new_intern;
}
