#include <stdio.h>

void piramide(int n)
{
    int linhas,colunas,aux,espaco=2*n-1;
    for(linhas=1;linhas<=n;linhas++){
        for(aux=1;aux<espaco;aux++)
            printf(" ");
        for(colunas=1;colunas<=linhas;colunas++)
            printf("%d ",colunas);
        for(colunas=linhas-1;colunas>=1;colunas--)
            if (colunas==1)
                printf("%d",colunas);
            else
                printf("%d ",colunas);
        printf("\n");
        espaco=espaco-2;
    }
}
int main()
{
    int n;
    scanf("%d",&n);
    if (n<2){
        while (n<2){
            printf("Introduza um número maior ou igual a 2:\n");
            scanf("%d",&n);
        }
    }
    piramide(n);
    return 0;
}
