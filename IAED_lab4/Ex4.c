#include <stdio.h>
#include <string.h>

#define MAX 80

int main()
{
    int len,i;
    char s[MAX];
    printf("Introduza uma palavra:\n");
    scanf("%s",s);
    len=strlen(s)-1;
    for (i=0;i<=(len/2);i++){
        if (s[i]!=s[len-i]){
            printf("no");
            return 0;
        }
    }
    printf("yes");
    return 0;
}