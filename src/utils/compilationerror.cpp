#include "compilationerror.h"

CompilationError::CompilationError()
{

}

const char* CompilationError::what() const noexcept
{
    return "Compilation error";
}
