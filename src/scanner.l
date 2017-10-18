%{
#include <stdio.h>

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
"int"                   update_location(); return TOK_INTTYPE;
"boolean"               update_location(); return TOK_BOOLTYPE;
"String"                update_location(); return TOK_STRTYPE;

"new"                   update_location(); return TOK_NEW;
"return"                update_location(); return TOK_RETURN;

"System.out.println"    update_location(); return TOK_PRINT;
"static void main"      update_location(); return TOK_ENTRY;

"public"                update_location(); return TOK_PUBLIC;
"private"               update_location(); return TOK_PRIVATE;
"while"                 update_location(); return TOK_WHILE;
"if"                    update_location(); return TOK_IF;
"else"                  update_location(); return TOK_ELSE;
"class"                 update_location(); return TOK_CLASS;
"this"                  update_location(); return TOK_THIS;
"extends"               update_location(); return TOK_EXTENDS;
"true"                  update_location(); return TOK_TRUE;
"false"                 update_location(); return TOK_FALSE;

"&&"                    update_location(); return TOK_AND;
"||"                    update_location(); return TOK_OR;

{ID}                    update_location(); return TOK_ID;
{INTLITERAL}            update_location(); return TOK_INTLITERAL;

"//".*$                 update_location();
"/*".*"*/"              update_location();

[[:space:]]+            update_location();

.                       printf("Lexical error at (%d, %d)", line_counter, char_counter); abort();
%%

void update_location()
{
    //printf("(%d, %d)", x, y);
    for (int i = 0; i < yyleng; ++i) {
        if (yytext[i] == '\n') {
            ++line_counter;
            char_counter = 1;
        } else {
            ++char_counter;
        }
    }
    //printf("(%d, %d)", x, y);
}
