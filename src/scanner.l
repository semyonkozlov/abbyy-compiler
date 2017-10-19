%{
#include <iostream>

#include "parser.y.hpp"

int line_counter = 1;
int char_counter = 1;
void update_location();
%}

%option noyywrap

DIGIT                   [0-9]
LETER                   [a-zA-Z_]
ID                      {LETER}({DIGIT}|{LETER})*
INTLITERAL              [1-9]{DIGIT}*|0
BOOLLITERAL             (false|true)

%%
"int"                   update_location(); return T_INTTYPE;
"boolean"               update_location(); return T_BOOLTYPE;
"String"                update_location(); return T_STRTYPE;

"new"                   update_location(); return T_NEW;
"return"                update_location(); return T_RETURN;

"System.out.println"    update_location(); return T_PRINT;
"static void main"      update_location(); return T_ENTRY;

"public"                update_location(); return T_PUBLIC;
"private"               update_location(); return T_PRIVATE;
"while"                 update_location(); return T_WHILE;
"if"                    update_location(); return T_IF;
"else"                  update_location(); return T_ELSE;
"class"                 update_location(); return T_CLASS;
"this"                  update_location(); return T_THIS;
"extends"               update_location(); return T_EXTENDS;
"true"                  update_location(); return T_TRUE;
"false"                 update_location(); return T_FALSE;
"length"                update_location(); return T_LENGTH;

"&&"                    update_location(); return T_AND;
"||"                    update_location(); return T_OR;

{ID}                    { 
                            update_location();
                            yylval.symbol = new Symbol(yytext);
                            return T_IDENTIFIER;
                        }   
                    
{INTLITERAL}            {
                            update_location();
                            yylval.symbol = new Symbol(yytext);
                            return T_INTLITERAL;        
                        }

"//".*$                 update_location();
"/*".*"*/"              update_location();

[[:space:]]+            update_location();
.                       return yytext[0];
%%

void update_location()
{
    //printf("(%d, %d)", x, y);
    /*for (int i = 0; i < yyleng; ++i) {
        if (yytext[i] == '\n') {
            ++line_counter;
            char_counter = 1;
        } else {
            ++char_counter;
        }
    }*/
    //printf("(%d, %d)", x, y);
}
