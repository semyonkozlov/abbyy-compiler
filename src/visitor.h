#ifndef MINIJAVAC_VISITOR_H
#define MINIJAVAC_VISITOR_H

struct Visitor
{
    virtual void visit(const void*) = 0;
};

template<typename T>
struct Visitable
{
    virtual ~Visitable() = 0;

    virtual void accept(Visitor* visitor) const
    {
        visitor->visit(static_cast<const T*>(this));
    }
};

template<typename T>
Visitable<T>::~Visitable()
{ }

#endif //MINIJAVAC_VISITOR_H
