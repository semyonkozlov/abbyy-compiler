#ifndef MINIJAVAC_TYPE_H
#define MINIJAVAC_TYPE_H

#include "grammar_def.h"

class Type
{ };

enum class BuiltinType {
    INT, BOOL, STRING
};

class PrimitiveType : public Visitable<PrimitiveType>, public Type
{
public:
    explicit PrimitiveType(BuiltinType type) : type_(type)
    { }

private:
    BuiltinType type_;
};

class UserDefinedType : public Visitable<UserDefinedType>, public Type
{
public:
    UserDefinedType(const Symbol* type_id) : type_id_(type_id)
    { }

private:
    const Symbol* type_id_;
};

class ArrayType : public Visitable<ArrayType>, public Type
{
public:
    //explicit ArrayType(const Type* element_type) : element_type_(element_type)
    //{ }

private:
    // const Type* element_type_;
};

#endif //MINIJAVAC_TYPE_H
