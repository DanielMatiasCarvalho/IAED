#include <stdio.h>

void quadrado(int n)
{
    int linhas=1,colunas,numero;
    while (linhas<=n) {
        colunas=0;
        numero=linhas;
        while (++colunas<=n){
            if (colunas<n)
                printf("%d\t",numero);
            else
                printf("%d\n",numero);
            numero++;
        }
        linhas++;
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
    quadrado(n);
    return 0;
}

