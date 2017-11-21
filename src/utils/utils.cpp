#include <sstream>

#include <fmt/format.h>

#include "utils.h"

CompilationError::CompilationError(ErrorType error_type, std::string additional_description, Location error_location)
    : error_type_(error_type),
      additional_description_(std::move(additional_description)),
      error_location_(error_location)
{ }

std::string CompilationError::to_string() const
{
    switch (error_type_) {
        case ErrorType::REDECLARATION:
            return fmt::format("{}:{}: error: redeclaration of \'{}\'",
                error_location_.first_line, error_location_.first_column, additional_description_);

        case ErrorType::REDEFINITION:
            return fmt::format("{}:{}: error: redefinition of \'{}\'",
                error_location_.first_line, error_location_.first_column, additional_description_);

        case ErrorType::CONFLICTING_DECLARATION:
            return fmt::format("{}:{}: error: conflicting declaration \'{}\'",
                error_location_.first_line, error_location_.first_column, additional_description_);

        default:
            return "compilation error";
    }
}

void register_error(ErrorType error_type, std::string additional_description, Location error_location)
{
    ::compilation_errors.emplace_back(error_type, additional_description, error_location);
}

std::vector<CompilationError> compilation_errors;