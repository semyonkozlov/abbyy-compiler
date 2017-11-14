#ifndef MINIJAVAC_COMPILATIONERROR_H
#define MINIJAVAC_COMPILATIONERROR_H

#include <exception>

class CompilationError : public std::exception
{
public:
    CompilationError();

    const char* what() const noexcept override;
};

#endif //MINIJAVAC_COMPILATIONERROR_H
