#ifndef MINIJAVAC_DECLARATIONERROR_H
#define MINIJAVAC_DECLARATIONERROR_H

#include "compilationerror.h"
#include "../symboltable/variableinfo.h"

class DeclarationError : public CompilationError
{
public:
    DeclarationError();

    const char* what() const override;
};

#endif //MINIJAVAC_DECLARATIONERROR_H
