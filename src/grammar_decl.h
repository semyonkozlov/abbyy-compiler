#ifndef MINIJAVAC_GRAMMAR_DEF_H
#define MINIJAVAC_GRAMMAR_DEF_H

class Program;
class Symbol;

class MainClass;
class ClassDeclList;
class ClassDecl;
class VarDeclList;
class VarDecl;
class MethodDeclList;
class MethodDecl;
class ArgumentList;

class Type;
class UserDefinedType;
class PrimitiveType;
class ArrayType;
class PrimitiveType;

class Statement;
class StatementList;
class AssignSubscriptStatement;
class PrintStatement;
class IfStatement;
class WhileStatement;
class AssignStatement;
class ScopedStatement;

class Expression;
class ExpressionList;
class LengthExpression;
class IdExpression;
class ThisExpression;
class IntExpression;
class BoolExpression;
class MethodCallExpression;
class SubscriptExpression;
class ParenthesizedExpression;
class NewArrayExpression;
class NewObjectExpression;
class BinaryExpression;
class NegationExpression;

#endif //MINIJAVAC_GRAMMAR_DEF_H
