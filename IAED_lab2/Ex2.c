#include <stdio.h>

/*Ordena 2*/

int main()
{
    int n,m;
    printf("Introduza dois números inteiros:\n");
    scanf("%d%d",&n,&m);
    if (n>m)
        printf("%d\n%d\n",m,n);
    else
        printf("%d\n%d\n",n,m);
    return 0;
}