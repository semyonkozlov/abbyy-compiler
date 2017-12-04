#ifndef MINIJAVAC_UTILS_H
#define MINIJAVAC_UTILS_H

#include <string>
#include <vector>

#include "ast/parser.y.hpp"

using Location = YYLTYPE;

enum class ErrorType
{
    LEXICAL_ERROR,
    SYNTAX_ERROR,
    REDECLARATION,
    REDEFINITION,
    CONFLICTING_DECLARATION,

    ENUM_SIZE_
};

class CompilationError
{
public:
    explicit CompilationError(ErrorType error_type, std::string additional_description = {}, 
        Location error_location = {});

    std::string to_string() const;

private:
    ErrorType error_type_;
    std::string additional_description_;
    Location error_location_;
};

void register_error(ErrorType error_type, std::string additional_description = {}, Location error_location = {});

extern std::vector<CompilationError> compilation_errors;

#endif //MINIJAVAC_UTILS_H
