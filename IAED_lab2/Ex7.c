#include <stdio.h>

/*Divisores*/

#define UNIDADE 1 
#define ZERO 0

int main()
{
    int num,ciclo,divisores;
    printf("Introduza um número inteiro positivo:\n");
    scanf("%d",&num);
    divisores=0;
    for (ciclo=1;ciclo <= num;ciclo=ciclo+1)
    {
        if (num%ciclo==0)
            divisores=divisores+1;
    }
    printf("%d\n",divisores);
    return 0;
}