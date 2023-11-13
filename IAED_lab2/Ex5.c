#include <stdio.h>

/*Ciclo*/

int main()
{
    int numero,sequencia=1;
    printf("Introduza um númeo inteiro positivo:\n");
    scanf("%d",&numero);
    while(sequencia <= numero)
    {
        printf("%d\n",sequencia);
        sequencia = sequencia + 1;
    }
    return 0;
}