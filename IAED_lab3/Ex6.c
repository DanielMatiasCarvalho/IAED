#include <stdio.h>

int main()
{
    int c,soma=0;
    c=getchar();
    while(c!=EOF){
        if (c>'0' && c<='9')
            soma=soma + (c-'0');
        c=getchar();
    }
    if ((soma%9)==0)
        printf("yes\n");
    else    
        printf("no\n");
    return 0;
}