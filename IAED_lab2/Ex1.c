#include <stdio.h>

/*Maior de três*/

int main()
{
    int numa,numb,numc;
    printf("Introduza três valores inteiros:\n");
    scanf("%d%d%d",&numa,&numb,&numc);
    if (numa>numb)
    {
        if (numa>numc)
            printf("O maior número introduzido é %d\n",numa);
        else
            printf("O maior número introduzido é %d\n",numc);
    }
    else 
    { 
        if (numb>numc)
            printf("O maior número introduzido é %d\n",numb);
        else
            printf("O maior número introduzido é %d\n",numc);
    }
    return 0;
}