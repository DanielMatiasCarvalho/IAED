#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int i=0, len;
    char s[1000];
    char *ptr;
    ptr=s;
    scanf("%s",s);
    len=strlen(s);
    while (i!=len){
        printf("%s",*(ptr+i));
        i++;
    }

    return 0;
}