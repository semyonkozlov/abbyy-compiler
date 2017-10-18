%{
extern "C" {
    int yylex(void);
}

void yyerror(const char* str)
{
    std::cerr << str << std::endl;
}
%}

%union {
    char* id;
    int number;

    const IProgram* program;
    const IMainClass* main_class;
    const IClassDeclList* class_decl_list;
    const IClassDecl* class_decl;
    const IVarDeclList* var_decl_list;
    const IVarDecl* var_decl;
    const IMethodDeclList* method_decl_list;
    const IMethodDecl* method_decl;
    const IFormalList* formal_list;
    const IType* type;
    const IStatementList* statement_list;
    const IStatement* statement;
    const IExpList* expression_list;
    const IExpression* expression;
}

%error-verbose

%token TOK_INTTYPE TOK_BOOLTYPE TOK_STRTYPE
%token TOK_NEW TOK_RETURN TOK_PRINT TOK_ENTRY
%token TOK_CLASS TOK_PUBLIC TOK_PRIVATE TOK_EXTENDS TOK_THIS
%token TOK_IF TOK_ELSE TOK_WHILE
%token TOK_OR TOK_AND TOK_TRUE TOK_FALSE

%token <id> TOK_ID
%token <number> TOK_INTLITERAL

%nonassoc TOK_AND
%nonassoc TOK_OR
%nonassoc '<'
%left '+' '-'
%left '*' '/'
%right '!'
%left '.' '['

%type <program> PROGRAM
/*%type <main_class> MAIN_CLASS
%type <class_decl_list> CLASS_DECL_LIST
%type <class_decl> CLASS_DECL
%type <var_decl_list> VAR_DECL_LIST
%type <var_decl> VAR_DECL*/

%%
PROGRAM: TOK_ENTRY { }
;
%%