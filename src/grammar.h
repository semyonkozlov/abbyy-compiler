#ifndef MINIJAVAC_GRAMMAR_H
#define MINIJAVAC_GRAMMAR_H

#include <string>

#include "visitor.h"

class MainClass;
class ClassDeclList;
class Symbol;
class Statement;
class ClassDecl;
class VarDeclList;
class MethodDeclList;

class Program : public Visitable<Program>
{
public:
    Program(const MainClass* main_class, const ClassDeclList* other_classes) :
        main_class_(main_class), other_classes_(other_classes)
    { }

private:
    const MainClass* main_class_;
    const ClassDeclList* other_classes_;
};

class MainClass : public Visitable<MainClass>
{
public:
    MainClass(const Symbol* class_id, const Symbol* main_argv_id, const Statement* main_body)
        : class_id_(class_id), main_argv_id_(main_argv_id), main_body_(main_body)
    { }

private:
    const Symbol* class_id_;
    const Symbol* main_argv_id_;
    const Statement* main_body_;
};

class Symbol : public Visitable<MainClass>
{
public:
    Symbol(std::string str) : str_(std::move(str))
    { }

    Symbol(const Symbol&) = delete;
    Symbol& operator=(const Symbol& symbol) = delete;

    const std::string& to_string() const
    {
        return str_;
    }

private:
    std::string str_;
};

class ClassDeclList : public Visitable<ClassDeclList>
{
public:
    ClassDeclList(const ClassDecl* new_class, const ClassDeclList* other_classes)
        : new_class_(new_class), other_classes_(other_classes)
    { }

private:
    const ClassDecl* new_class_;
    const ClassDeclList* other_classes_;
};

class ClassDecl : public Visitable<ClassDecl>
{
public:
    ClassDecl(const Symbol* class_id, const Symbol* base_class_id,
        const VarDeclList* variables, const MethodDeclList* methods)
        : class_id_(class_id), base_class_id_(base_class_id), variables_(variables), methods_(methods)
    { }

private:
    const Symbol* class_id_;
    const Symbol* base_class_id_;
    const VarDeclList* variables_;
    const MethodDeclList* methods_;

};

class VarDeclList : public Visitable<VarDeclList>
{ };

class VarDecl : public Visitable<VarDecl>
{ };

class MethodDeclList : public Visitable<MethodDeclList>
{ };

class MethodDecl : public Visitable<MethodDecl>
{ };

class ArgumentList : public Visitable<ArgumentList>
{ };

class StatementList : public Visitable<StatementList>
{ };

class Statement : public  Visitable<Statement>
{ };

class Type : public Visitable<Type>
{ };

class ExpressionList : public Visitable<ExpressionList>
{ };

class Expression : public Visitable<Expression>
{ };

#endif //MINIJAVAC_GRAMMAR_H
