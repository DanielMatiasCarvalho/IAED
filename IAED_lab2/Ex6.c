#include <stdio.h>

/*Maior e Menor*/

int main()
{
    int n,ciclo;
    float min,max,num;
    printf("Introduza o número de valores inteiros que irá introduzir:\n");
    scanf("%d",&n);
    printf("Introduza um número inteiro:\n");
    scanf("%f",&num);
    min=max=num;
    for (ciclo= 2;ciclo <= n; ciclo=ciclo + 1)
    {
        printf("Introduza um número inteiro:\n");
        scanf("%f",&num);
        if (num<min)
            min=num;
        if (num>max)
            max=num;
    }
    printf("min: %f, max: %f\n",min,max);
    return 0;
}
