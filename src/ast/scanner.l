%{
#include <iostream>

#include "parser.y.hpp"

#define YY_USER_ACTION update_location();

static int line_counter = 1;
static int column_counter = 1;

yyFlexLexer scanner;

void update_location()
{
    yylloc.first_line = line_counter;
    yylloc.first_column = column_counter;

    for (int i = 0; i < scanner.YYLeng(); ++i) {
        if (scanner.YYText()[i] == '\n') {
            ++line_counter;
            column_counter = 1;
        } else {
            ++column_counter;
        }
    }

    yylloc.last_line = line_counter;
    yylloc.last_column = column_counter;
}
%}

%option yylineno
%option noyywrap

DIGIT                   [0-9]
LETER                   [a-zA-Z_]
ID                      {LETER}({DIGIT}|{LETER})*
INTLITERAL              [1-9]{DIGIT}*|0
BOOLLITERAL             (false|true)

%%
"int"                   return T_INTTYPE;
"boolean"               return T_BOOLTYPE;
"String"                return T_STRTYPE;

"new"                   return T_NEW;
"return"                return T_RETURN;

"System.out.println"    return T_PRINT;
"static void main"      return T_ENTRY;

"public"                return T_PUBLIC;
"private"               return T_PRIVATE;
"while"                 return T_WHILE;
"if"                    return T_IF;
"else"                  return T_ELSE;
"class"                 return T_CLASS;
"this"                  return T_THIS;
"extends"               return T_EXTENDS;
"true"                  return T_TRUE;
"false"                 return T_FALSE;
"length"                return T_LENGTH;

"&&"                    return T_AND;
"||"                    return T_OR;

{ID}                    {
                            yylval.symbol = Symbol::make_symbol(yytext);
                            return T_IDENTIFIER;
                        }   
                    
{INTLITERAL}            {
                            yylval.symbol = Symbol::make_symbol(yytext);
                            return T_INTLITERAL;        
                        }

"//".*$
"/*".*"*/"

[[:space:]]+

.                       return yytext[0]; // TODO
