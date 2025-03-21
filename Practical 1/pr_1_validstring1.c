#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isValid(char str[]){
    int len = strlen(str)-1;
    if(len<2){
        return false;
    }
    else if(len==2){
        if(str[0]=='b' && str[1]=='b'){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        for(int i=0;i<len-2;i++){
            if(str[i] != 'a'){
                return false;
            }
        }
        for(int i=len-2;i<len;i++){
            if(str[i]!='b'){
                return false;
            }
        }
    }
    return true;
}

int main()
{
   char str[10];
   printf("Enter string : ");
   fgets(str, 10 , stdin);
   bool b=isValid(str);
   if(b){
       printf("String is valid\n");
   }
   else{
       printf("string is invalid");
   }

   return 0;
}