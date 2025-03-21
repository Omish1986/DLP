%option noyywrap
%{
#include <stdio.h>

int v=0, c=0;
%}
%%
charusat { printf("University"); }  
. { printf(yytext);}
%%
int main() {
    printf("Enter line: ");
    yylex();
    
    return 0;
}
