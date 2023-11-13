#include <stdio.h>

#define VECMAX 100

void grafico (int tabela[],int dim,int maximo);

int main()
{
    int i,n,numeros[VECMAX],alto=0;
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
        if (numeros[i]>alto)
            alto=numeros[i];
    }
    grafico(numeros,n,alto);    
    return 0;
}
void grafico (int tabela[],int dim,int maximo)
{
    int i,j;
    for (i=0;i<maximo;i++){
        for(j=0;j<dim;j++){
            if (tabela[j]>0){
                printf("*");
                tabela[j]--;
            }
            else 
                printf(" ");
        }
        printf("\n");
    }
}