#include "symbol.h"

std::shared_ptr<Symbol> make_symbol(const std::string& str)
{
    static std::unordered_map<std::string, std::shared_ptr<Symbol>> intern_map;

    if (auto intern = intern_map.find(str); intern != std::end(intern_map)) {
        return intern->second;
    }

    auto new_intern = std::make_shared<Symbol>(str);
    intern_map.insert({ str, new_intern });
    return new_intern;
}
