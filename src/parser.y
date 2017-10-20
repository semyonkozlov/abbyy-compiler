%code requires {
#include "grammar.h"
}

%{
#include <FlexLexer.h>

int yylex(void)
{
    static yyFlexLexer scanner;
    return scanner.yylex();
}

void yyerror(const char* str)
{
    std::cerr << str << std::endl;
}

extern const class Program* program;
%}

%union {
    const Symbol* symbol; // TODO

    const Program* program;
    const MainClass* main_class;
    const ClassDeclList* class_decl_list;
    const ClassDecl* class_decl;
    const VarDeclList* var_decl_list;
    const VarDecl* var_decl;
    const MethodDeclList* method_decl_list;
    const MethodDecl* method_decl;
    const ArgumentList* arg_list;
    const Type* type;
    const StatementList* statement_list;
    const Statement* statement;
    const ExpressionList* expression_list;
    const Expression* expression;
}

%error-verbose

%token                      T_AND       "&&"
%token                      T_OR        "||"
%token                      T_ENTRY
%token                      T_INTTYPE   "int"
%token                      T_BOOLTYPE  "bool"
%token                      T_STRTYPE   "String"
%token                      T_NEW       "new"
%token                      T_RETURN    "return"
%token                      T_PRINT
%token                      T_CLASS     "class"
%token                      T_PUBLIC    "public"
%token                      T_PRIVATE   "private"
%token                      T_EXTENDS   "extends"
%token                      T_THIS      "this"
%token                      T_IF        "if"
%token                      T_ELSE      "else"
%token                      T_WHILE     "while"
%token                      T_TRUE      "true"
%token                      T_FALSE     "false"
%token                      T_LENGTH    "length"

%token  <symbol>            T_IDENTIFIER
%token  <symbol>            T_INTLITERAL

%type   <program>           PROGRAM
%type   <main_class>        MAIN_CLASS
%type   <class_decl_list>   CLASS_DECL_LIST
%type   <class_decl>        CLASS_DECL
%type   <var_decl_list>     VAR_DECL_LIST
%type   <var_decl>          VAR_DECL
%type   <method_decl_list>  METHOD_DECL_LIST
%type   <method_decl>       METHOD_DECL
%type   <arg_list>          ARGUMENT_LIST
%type   <arg_list>          ARGUMENT_REST
%type   <type>              TYPE
%type   <statement_list>    STATEMENT_LIST
%type   <statement>         STATEMENT
%type   <expression_list>   EXPRESSION_LIST
%type   <expression_list>   EXPRESSION_REST
%type   <expression>        EXPRESSION

%left '+' '-'
%left '*' '/' '%'
%right '!'
%left '.' '['
%nonassoc '<'

%nonassoc T_AND
%nonassoc T_OR
%nonassoc T_UNMINUS

%start PROGRAM
%%

PROGRAM: 
    MAIN_CLASS CLASS_DECL_LIST 
    { program = $$ = new Program($1, $2); }
    ;

MAIN_CLASS: 
    "class" T_IDENTIFIER '{'
        "public" T_ENTRY '(' "String" '[' ']' T_IDENTIFIER ')' 
        '{' STATEMENT '}' 
    '}'
    { $$ = new MainClass($2, $10, $13); }
    ;

CLASS_DECL_LIST: 
    CLASS_DECL '{' error '}' 
    { std::cerr << "Error in class decl list rule." << std::endl; }
    |
    CLASS_DECL CLASS_DECL_LIST
    { $$ = new ClassDeclList($1, $2); }
    |
    /* empty */
    { $$ = nullptr; }
    ;

CLASS_DECL: 
    "class" T_IDENTIFIER '{'
        VAR_DECL_LIST
        METHOD_DECL_LIST
    '}'
    { $$ = new ClassDecl($2, nullptr, $4, $5); }
    |
    "class" T_IDENTIFIER "extends" T_IDENTIFIER '{'
        VAR_DECL_LIST
        METHOD_DECL_LIST
    '}'
    { $$ = new ClassDecl($2, $4, $6, $7); }
    ;

VAR_DECL_LIST:
    VAR_DECL_LIST VAR_DECL
    { $$ = new VarDeclList($2, $1); }
    |
    /* empty */
    { $$ = nullptr; }
    ;

VAR_DECL: 
    TYPE T_IDENTIFIER ';'
    { $$ = new VarDecl($1, $2); }
    ;

METHOD_DECL_LIST: 
    METHOD_DECL METHOD_DECL_LIST
    { $$ = new MethodDeclList($1, $2); }
    |
    /* empty */
    { $$ = nullptr; }  
    ;

METHOD_DECL:
    "public" TYPE T_IDENTIFIER '(' ARGUMENT_LIST ')' '{'
        VAR_DECL_LIST
        STATEMENT_LIST
        "return" EXPRESSION ';'
    '}'
    { $$ = new MethodDecl(AccessMod::PUBLIC, $2, $3, $5, $8, $9, $11); }
    |
    "private" TYPE T_IDENTIFIER '(' ARGUMENT_LIST ')' '{'
        VAR_DECL_LIST
        STATEMENT_LIST
        "return" EXPRESSION ';'
    '}'
    { $$ = new MethodDecl(AccessMod::PRIVATE, $2, $3, $5, $8, $9, $11); }
    ;

ARGUMENT_LIST:
    TYPE T_IDENTIFIER ARGUMENT_REST
    { $$ = new ArgumentList($1, $2, $3); }
    |
    /* empty */
    { $$ = nullptr; }
    ;

ARGUMENT_REST:
    ',' TYPE T_IDENTIFIER ARGUMENT_REST
    { $$ = new ArgumentList($2, $3, $4); }
    |
    /* empty */
    { $$ = nullptr; }
    ;

TYPE:
    "int" '[' ']' // TODO shift/reduce conflict here
    { $$ = new ArrayType(); }
    |
    "bool"
    { $$ = new PrimitiveType(BuiltinType::BOOL); }
    |
    "int"
    { $$ = new PrimitiveType(BuiltinType::INT); }
    |
    "String"
    { $$ = new PrimitiveType(BuiltinType::STRING); }
    |
    T_IDENTIFIER
    { $$ = new UserDefinedType($1); }
    ;

STATEMENT_LIST:
    STATEMENT STATEMENT_LIST
    { $$ = new StatementList($1, $2); }
    |
    /* empty */
    { $$ = nullptr; }
    ;

STATEMENT:
    '{' STATEMENT_LIST '}'
    { $$ = new ScopedStatement($2); }
    |
    "if" '(' EXPRESSION ')' STATEMENT "else" STATEMENT
    { $$ = new IfStatement($3, $5, $7); }
    |
    "while" '(' EXPRESSION ')' STATEMENT
    { $$ = new WhileStatement($3, $5); }
    |
    T_PRINT '(' EXPRESSION ')' ';'
    { $$ = new PrintStatement($3); }
    |
    T_IDENTIFIER '=' EXPRESSION ';'
    { $$ = new AssignStatement($1, $3); }
    |
    T_IDENTIFIER '[' EXPRESSION ']' '=' EXPRESSION ';'
    { $$ = new AssignSubscriptStatement($1, $3, $6); }
    /*|
    EXPRESSION ';'
    { $$ = nullptr; std::cerr << "Statement has no effect" << std::endl; }*/
    ;

EXPRESSION_LIST:
    EXPRESSION EXPRESSION_REST
    { $$ = new ExpressionList($1, $2); }
    |
    /* empty */
    { $$ = nullptr; }

EXPRESSION_REST:
    ',' EXPRESSION EXPRESSION_REST
    { $$ = new ExpressionList($2, $3); }
    |
    /* empty */
    { $$ = nullptr; }

EXPRESSION:
    EXPRESSION "&&" EXPRESSION
    { $$ = new BinaryExpression($1, BinaryOperator::AND, $3); }
    |
    EXPRESSION '<' EXPRESSION
    { $$ = new BinaryExpression($1, BinaryOperator::LESS, $3); }
    |
    EXPRESSION '+' EXPRESSION
    { $$ = new BinaryExpression($1, BinaryOperator::ADD, $3); }
    |
    EXPRESSION '-' EXPRESSION
    { $$ = new BinaryExpression($1, BinaryOperator::SUB, $3); }
    |
    EXPRESSION '*' EXPRESSION
    { $$ = new BinaryExpression($1, BinaryOperator::MUL, $3); }
    |
    EXPRESSION '/' EXPRESSION
    { $$ = new BinaryExpression($1, BinaryOperator::DIV, $3); }
    |
    EXPRESSION '%' EXPRESSION
    { $$ = new BinaryExpression($1, BinaryOperator::MOD, $3); }
    |
    EXPRESSION "||" EXPRESSION
    { $$ = new BinaryExpression($1, BinaryOperator::OR, $3); }
    |
    /*EXPRESSION ',' EXPRESSION
    { $$ = new BinaryExpression($1, BinaryOperator::COMMA, $3); }
    |*/
    '-' EXPRESSION %prec T_UNMINUS // TODO create class
    { $$ = nullptr; }
    |
    EXPRESSION '[' EXPRESSION ']'
    { $$ = new SubscriptExpression($1, $3); }
    |
    EXPRESSION '.' "length" 
    { $$ = new LengthExpression($1); }
    |
    EXPRESSION '.' T_IDENTIFIER '(' EXPRESSION_LIST ')'
    { $$ = new MethodCallExpression($1, $3, $5); }
    |
    T_INTLITERAL 
    { $$ = new IntExpression($1); }
    |
    "true"
    { $$ = new BoolExpression(true); }
    |
    "false"
    { $$ = new BoolExpression(false); }
    |
    T_IDENTIFIER
    { $$ = new IdExpression($1); }
    |
    "this"
    { $$ = new ThisExpression(); }
    |
    "new" TYPE '[' EXPRESSION ']'
    { $$ = new NewArrayExpression($2, $4); }
    |
    "new" TYPE '(' ')'
    { $$ = new NewObjectExpression($2); }
    |
    '!' EXPRESSION
    { $$ = new NegationExpression($2); }
    |
    '(' EXPRESSION ')'
    { $$ = new ParenthesizedExpression($2); }
    ;
%%