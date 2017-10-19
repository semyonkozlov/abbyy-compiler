#ifndef MINIJAVAC_GRAMMAR_H
#define MINIJAVAC_GRAMMAR_H

#include <string>

#include "visitor.h"

class MainClass;
class Symbol;
class ClassDeclList;
class ClassDecl;
class Statement;
class StatementList;
class VarDeclList;
class VarDecl;
class MethodDeclList;
class MethodDecl;
class Type;
class ArgumentList;
class Expression;

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
{
public:
    VarDeclList(const VarDecl* var_decl, const VarDeclList* other_var_decls)
        : var_decl_(var_decl), other_var_decls_(other_var_decls)
    { }

private:
    const VarDecl* var_decl_;
    const VarDeclList* other_var_decls_;
};

class VarDecl : public Visitable<VarDecl>
{
public:
    VarDecl(const Type* type, const Symbol* var_id)
        : type_(type), var_id_(var_id)
    { }

private:
    const Type* type_;
    const Symbol* var_id_;
};

class MethodDeclList : public Visitable<MethodDeclList>
{
public:
    MethodDeclList(const MethodDecl* method_decl, const MethodDeclList* other_methods_decls)
        : method_decl_(method_decl), other_methods_decls_(other_methods_decls)
    { }

private:
    const MethodDecl* method_decl_;
    const MethodDeclList* other_methods_decls_;
};

enum class AccessMod
{
    PUBLIC, PRIVATE
};

class MethodDecl : public Visitable<MethodDecl>
{
public:
    MethodDecl(
        AccessMod access_mod, const Type* return_type, const Symbol* method_id, const ArgumentList* arg_list,
        const VarDeclList* var_decls, const StatementList* statements, const Expression* return_expression)
        : access_mod_(access_mod), return_type_(return_type), method_id_(method_id), arg_list_(arg_list),
          var_decls_(var_decls), statements_(statements), return_expression_(return_expression)
    { }

private:
    AccessMod access_mod_;
    const Type* return_type_;
    const Symbol* method_id_;
    const ArgumentList* arg_list_;
    const VarDeclList* var_decls_;
    const StatementList* statements_;
    const Expression* return_expression_;
};

class ArgumentList : public Visitable<ArgumentList>
{
public:
    ArgumentList(const Type* arg_type, const Symbol* arg_id, const ArgumentList* other_args)
        : arg_type_(arg_type), arg_id_(arg_id), other_args_(other_args)
    { }

private:
    const Type* arg_type_;
    const Symbol* arg_id_;
    const ArgumentList* other_args_;
};

class StatementList : public Visitable<StatementList>
{
public:
    StatementList(const Statement* statement, const StatementList* other_statements)
        : statement_(statement), other_statements_(other_statements)
    { }

private:
    const Statement* statement_;
    const StatementList* other_statements_;
};

class Statement
{ };

class ScopedStatement : public Visitable<ScopedStatement>, public Statement
{
public:
    ScopedStatement(const StatementList* statements_in_scope)
        : statements_in_scope_(statements_in_scope)
    { }

private:
    const StatementList* statements_in_scope_;
};

class IfStatement : public Visitable<IfStatement>, public Statement
{
public:
    IfStatement(const Expression* if_condition, const Statement* statement_if_true,
        const Statement* statement_if_false)
        : if_condition_(if_condition), statement_if_true_(statement_if_true), statement_if_false_(statement_if_false)
    { }

private:
    const Expression* if_condition_;
    const Statement* statement_if_true_;
    const Statement* statement_if_false_;
};

class WhileStatement : public Visitable<WhileStatement>, public Statement
{
public:
    WhileStatement(const Expression* loop_condition, const Statement* inloop_statement)
        : loop_condition_(loop_condition), inloop_statement_(inloop_statement)
    { }

private:
    const Expression* loop_condition_;
    const Statement* inloop_statement_;
};

class PrintStatement : public Visitable<PrintStatement>, public Statement
{
public:
    PrintStatement(const Expression* expression_to_print) : expression_to_print_(expression_to_print)
    { }

private:
    const Expression* expression_to_print_;
};

class AssignStatement : public Visitable<AssignStatement>, public Statement
{
public:
    AssignStatement(const Symbol* lhs_var_id, const Expression* rhs_expression)
        : lhs_var_id_(lhs_var_id), rhs_expression_(rhs_expression)
    { }

private:
    const Symbol* lhs_var_id_;
    const Expression* rhs_expression_;
};

class AssignSubscriptStatement : public Visitable<AssignStatement>, public Statement
{
public:
    AssignSubscriptStatement(const Symbol* lhs_array_id, const Expression* subscript,
        const Expression* rhs_expression)
        : lhs_array_id_(lhs_array_id), subscript_(subscript), rhs_expression_(rhs_expression)
    { }

private:
    const Symbol* lhs_array_id_;
    const Expression* subscript_;
    const Expression* rhs_expression_;
};

class Type
{ };

class PrimitiveType : public Visitable<PrimitiveType>, public Type
{
public:
    enum BuiltinType {
        INT, BOOL, STRING
    };

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

class ExpressionList : public Visitable<ExpressionList>
{ };

class Expression : public Visitable<Expression>
{ };

#endif //MINIJAVAC_GRAMMAR_H
