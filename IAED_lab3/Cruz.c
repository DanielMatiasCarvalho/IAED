#include<stdio.h>

void cruz(int n)
{
    int colunas,linhas;
    for(linhas=1;linhas<=n;linhas++){
        for(colunas=0;colunas<n;colunas++){
            if (colunas==linhas-1 || colunas==n-linhas)
                if (colunas==n-1)
                    printf("*");
                else
                    printf("* ");
            else
                if (colunas==n-1)
                    printf("-");
                else 
                    printf("- ");
        }
        printf("\n");
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
    cruz(n);
    return 0;
}
