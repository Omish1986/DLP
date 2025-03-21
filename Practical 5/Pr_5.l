%{
#include <stdio.h>
#include <stdlib.h>

FILE *yyin;
%}

%%
[ \t\n]+                      {/* Ignore spaces, tabs, and newlines */}
"int"|"char"|"return"|"void"|"struct"|"long"  { printf("Keyword: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]*        { printf("Identifier: %s\n", yytext); }
[0-9]+\.[0-9]+               { printf("Constant: %s\n", yytext); }  // Float constants
[0-9]+                        { printf("Constant: %s\n", yytext); }  // Integer constants
\"([^\"\\]|\\.)*\"            { printf("String: %s\n", yytext); }  // String literals
[{}()\[\],;]                  { printf("Punctuation: %s\n", yytext); }
[+\-*/=]                      { printf("Operator: %s\n", yytext); }
"&"                           { printf("Operator: %s\n", yytext); }  // Address-of operator
"/*"([^*]|\*+[^*/])*\*+"/"    { printf("Comment: Multi-line comment\n"); }
"//".*                        { printf("Comment: Single-line comment\n"); }
\.                            { printf("Punctuation: %s\n", yytext); }  // Dot in floating numbers
.                             { printf("Lexical Error: %s\n", yytext); } // Any other error

%%

int yywrap() {
    return 1;
}

int main() {
    char filename[100];

    printf("Enter the name of the C file: ");
    scanf("%s", filename);

    yyin = fopen(filename, "r");
    if (!yyin) {
        printf("Error opening file: %s\n", filename);
        return 1;
    }

    yylex();
    fclose(yyin);
    
    return 0;
}
