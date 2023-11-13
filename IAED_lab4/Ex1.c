#include <stdio.h>

#define VECMAX 100

int main()
{
    int n,numeros[VECMAX],i,j;
    printf("Introduza o número de valores inteiros \
positivos que irá escrever:\n");
    scanf("%d\n",&n);
    while (n<=0 || n>=VECMAX){
        printf("Introduza o número de valores inteiros \
positivos que irá escrever:\n");
        scanf("%d\n",&n);
    }
    for(i=0;i<n;i++){
        scanf("%d",&numeros[i]);
    }
    for (i=0;i<n;i++){
        for(j=0;j<numeros[i];j++)
            printf("*");
        printf("\n");
    }
    return 0;
}
