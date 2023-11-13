#include <stdio.h>

typedef struct{
    int horas;
    int minutos;
} Horas;

#define DIM 100

Horas conversaoHoras(char horas[]);
Horas somaHoras(Horas horas1,Horas horas2);


int main(){
    char horas1[DIM],horas2[DIM];
    Horas h1,h2,soma;
    scanf("%s",horas1);
    scanf("%s",horas2);
    h1=conversaoHoras(horas1);
    h2=conversaoHoras(horas2);
    soma=somaHoras(h1,h2);
    printf("%.2d:%.2d\n",soma.horas,soma.minutos);
    return 0;
}
Horas conversaoHoras(char horas[])
{
    Horas h={0,0};
    int i,j;
    for(i=0;horas[i]!=':';i++)
        h.horas=h.horas*10+(horas[i]-'0');
    for(j=i+1;horas[j]!='\0';j++)
        h.minutos=h.minutos*10+(horas[j]-'0');
    return h;
}
Horas somaHoras(Horas horas1,Horas horas2)
{
    Horas soma;
    soma.horas=horas2.horas+horas1.horas;
    soma.minutos=horas2.minutos+horas1.minutos;
    if (soma.minutos>=60){
        soma.horas+=(soma.minutos/60);
        soma.minutos=soma.minutos%60;
    }
    return soma;
}