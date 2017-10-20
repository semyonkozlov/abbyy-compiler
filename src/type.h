#ifndef MINIJAVAC_TYPE_H
#define MINIJAVAC_TYPE_H

#include "visitor.h"
#include "grammar_decl.h"

class Type : public Visitable
{ };

enum class BuiltinType 
{
    INT, BOOL, STRING
};

class PrimitiveType : public Type
{
public:
    explicit PrimitiveType(BuiltinType type) : type_(type)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

/*private:*/
    BuiltinType type_;
};

class UserDefinedType : public Type
{
public:
    UserDefinedType(const Symbol* type_id) : type_id_(type_id)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

/*private:*/
    const Symbol* type_id_;
};

class ArrayType : public Type
{
public:
    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

    //explicit ArrayType(const Type* element_type) : element_type_(element_type)
    //{ }

/*private:*/
    // const Type* element_type_;
};

#endif //MINIJAVAC_TYPE_H
