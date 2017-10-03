%{
#include <stdio.h>
#include <string.h>

int x = 1;
int y = 1;

void update_location();
%}

%option noyywrap

DIGIT           [0-9]
LETER           [a-zA-Z_]
ID              {LETER}({DIGIT}|{LETER})*
INTLITERAL      [1-9]{DIGIT}*|0
BOOLLITERAL 	(false|true)

%%
"("     printf("LBRACE "); update_location();
")"     printf("RBRACE "); update_location();

"{"     printf("BEGIN "); update_location();
"}"     printf("END ");

"["     printf("LBRACKET "); update_location();
"]"     printf("RBRACKER "); update_location();

";"     printf("ENDSTM "); update_location();

"int"     printf("TYPEINT "); update_location();
"boolean" printf("TYPEBOOL "); update_location();
"String"  printf("TYPESTR "); update_location();

"new"       printf("OPNEW "); update_location();
"return"    printf("OPRETURN "); update_location();
"+"         printf("OPPLUS "); update_location();
"-"         printf("OPMINUS "); update_location();
"*"         printf("OPTIMES "); update_location();
"%"         printf("OPMOD "); update_location();
"<"         printf("OPLESS "); update_location();
"="         printf("OPASSIGN "); update_location();
"&&"        printf("OPAND "); update_location();
"||"        printf("OPOR "); update_location();
"!"         printf("OPNOT "); update_location();
"."         printf("OPDOT "); update_location();
","         printf("OPCOMMA "); update_location();

"System.out.println" 	printf("OPPRINT "); update_location();
"static void main" 		printf("ENTRYPOINT "); update_location();

"public"    printf("KWPUBLIC "); update_location();
"private"   printf("KWPRIVATE "); update_location();
"while"     printf("KWWHILE "); update_location();
"if"        printf("KWIF "); update_location();
"else"      printf("KWELSE "); update_location();
"class"     printf("KWCLASS "); update_location();
"this"      printf("KWTHIS "); update_location();
"extends"   printf("KWEXTENDS "); update_location();

"//".*$     printf("COMMENT "); update_location();
"/*".*"*/"  printf("COMMENT "); update_location(); 

{BOOLLITERAL}	printf("BOOLLITERAL(%s)", yytext); update_location();
{ID}            printf("ID(%s) ", yytext); update_location();
{INTLITERAL}    printf("INTLITERAL(%s) ", yytext); update_location();

" "				printf(""); update_location();
"\n"			printf("\n"); update_location();
[[:space:]]+ 	printf("%s", yytext); update_location();

.   			printf("Lexical error at (%d, %d)", x, y); abort();
%%

void update_location()
{
	//printf("(%d, %d)", x, y);
	if(strcmp(yytext, "\n") == 0) {
		++y;
		x = 1;
	}
	x += yyleng;
	//printf("(%d, %d)", x, y);
}
