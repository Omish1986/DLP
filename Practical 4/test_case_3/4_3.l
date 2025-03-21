%option noyywrap
%{
#include <stdio.h>
#include <stdlib.h>

int char_count = 0, word_count = 0, line_count = 1;
FILE *fp;
%}

%%

\n            { line_count++; char_count++; }
[ \t]+       { char_count += yyleng; }
[A-Za-z0-9]+ { word_count++; char_count += yyleng; }
.            { char_count++; }

%%

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s file1\n", argv[0]);
        return 1;
    }
    
    fp = fopen(argv[1], "r");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }
    
    yyin = fp;
    yylex();
    fclose(fp);
    
    printf("Characters : %d\n", char_count);
    printf("Words : %d\n", word_count);
    printf("Lines : %d\n", line_count);
    
    return 0;
}
