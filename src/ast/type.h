#ifndef MINIJAVAC_TYPE_H
#define MINIJAVAC_TYPE_H

#include "visitor.h"
#include "grammardecl.h"
#include "symboltable/tableinitializer.h"
#include "treeserializer.h"

class Type : public Visitable
{
    friend TableInitializer; // TODO make friends in all classes
    friend TreeSerializer;

public:
    Type() = default;

    explicit Type(const Symbol* type_id) : type_id_(type_id)
    { }

protected:
    const Symbol* type_id_;
};

enum class BuiltinType 
{
    INT, BOOL, STRING
};

class PrimitiveType : public Type
{
    friend TableInitializer;
    friend TreeSerializer;

public:
    explicit PrimitiveType(BuiltinType type) : Type(), type_(type)
    {
        switch (type) {
            case BuiltinType::INT:
                Type::type_id_ = Symbol::make_symbol("int");
                break;

            case BuiltinType::BOOL:
                Type::type_id_ = Symbol::make_symbol("bool");
                break;

            case BuiltinType::STRING:
                Type::type_id_ = Symbol::make_symbol("String");
                break;
        }
    }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }

private:
    BuiltinType type_;
};

class UserDefinedType : public Type
{
    friend TableInitializer;
    friend TreeSerializer;

public:
    explicit UserDefinedType(const Symbol* type_id) : Type(type_id)
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }
};

class ArrayType : public Type
{
    friend TableInitializer;
    friend TreeSerializer;

public:
    ArrayType() : Type(Symbol::make_symbol("int[]"))
    { }

    virtual void accept(Visitor* visitor) const override
    {
        visitor->visit(this);
    }
};

#endif //MINIJAVAC_TYPE_H
