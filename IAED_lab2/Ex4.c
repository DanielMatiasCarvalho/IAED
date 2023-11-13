#include <stdio.h>

/*Ordena 3*/

int main()
{
    int numa,numb,numc;
    printf("Introduza três números inteiros:\n");
    scanf("%d%d%d",&numa,&numb,&numc);
    if (numa<=numb)
    {
        if (numa<=numc)
        {
            if (numb<=numc)
                printf("%d %d %d\n",numa,numb,numc);
            else
                printf("%d %d %d\n",numa,numc,numb);
        }
        else
            printf("%d %d %d\n",numc,numa,numb);
    }
    else
    {
        if (numb<=numc)
        {
            if (numa<=numc)
                printf("%d %d %d\n",numb,numa,numc);
            else
                printf("%d %d %d\n",numb,numc,numa);
        }
        else
            printf("%d %d %d\n",numc,numb,numa);
    }
    return 0;         
}