#include <stdio.h>

/*Média*/

int main()
{
    float num,soma,media;
    int n,ciclo;
    printf ("Introduza o número de valores que irá utilizar na sua média:\n");
    scanf("%d",&n);
    soma=0;
    for (ciclo=1;ciclo <= n;ciclo=ciclo+1)
    {
        printf("Introduza um número real:\n");
        scanf("%f",&num);
        soma=soma+num;
    }
    media=soma/n;
    printf("%.2f\n",media);
    return 0;
}