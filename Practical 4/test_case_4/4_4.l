%{
#include <stdio.h>

int d=0,lc=0,uc=0,ss=0,ec=0,l=0;
%}
%%
[0-9] { d++; l++; }
[a-z] { lc++;l++; }
[A-Z] { uc++;l++; }
[*@#,;$] { ss++;l++; }
\n { if(d>0 && lc>0 && uc>0 && ss>0 && l>=9 && l<=15 && ec==0)
{
    printf("valid \n");d=0,lc=0,uc=0,ss=0,ec=0,l=0;
}
   
else{ 
    printf("Invalid \n");
    d=0,lc=0,uc=0,ss=0,ec=0,l=0;
}
}
. {ec++ ;}
%%
int main() {
    printf("Enter password: ");
    yylex();
    
    return 0;
}
int yywrap() {}
