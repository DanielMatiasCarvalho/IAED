#include <stdio.h>

int main()
{
    int numa,numb,numc,max;
    printf("Introduza três valores inteiros:\n");
    scanf("%d%d%d",&numa,&numb,&numc);
    max=numa;
    if (numb>max)
        max=numb;
    if (numc>max)
        max=numc;
    printf("O maior número introduzido é %d\n",max);
    return 0;
}