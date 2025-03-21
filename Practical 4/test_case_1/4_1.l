%option noyywrap
%{
#include <stdio.h>

int v=0, c=0;
%}
%%
[aeiouAEIOU] { v++; }
[a-zA-Z] { c++; } 
[ \t\n] ;  
. ;  
%%
int main() {
    printf("Enter string: ");
    yylex();
    printf("Vowels: %d, Consonants: %d\n", v, c);
    return 0;
}
