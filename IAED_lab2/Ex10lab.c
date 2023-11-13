#include <stdio.h>

int main()
{
    int c,n,soma;
    scanf("%d",&n);
    soma=0;
    c=0;
    do{
        soma=soma + (n%10);
        n=n/10;
        c++;
    }while(n>0);
    printf("%d\n%d\n",c,soma);
    return 0;
}