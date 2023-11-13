#include <stdio.h>

/*Conversão*/

int main()
{
    int pertempo,horas,minutos,segundos;
    printf("Introduza um período de tempo em segundos:\n");
    scanf("%d",&pertempo);
    horas=pertempo/3600;
    minutos=(pertempo%3600)/60;
    segundos=(pertempo%3600)%60;

    printf("'%02d:%02d:%02d\n'",horas,minutos,segundos);
    return 0;
}