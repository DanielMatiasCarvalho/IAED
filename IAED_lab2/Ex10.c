#include <stdio.h>

/*Dígitos*/

int main ()
{
    int num,soma,digitos;
    printf("Introduz um número inteiro positivo:\n");
    scanf("%d",&num);
    soma=0;
    for (digitos=0;num!=0;digitos=digitos+1)
    {
        soma=num%10+soma;
        num=num/10;
    }
    printf("Número de dígitos: %d\nSoma dos Dígitos: %d\n",digitos,soma);
    return 0;
}