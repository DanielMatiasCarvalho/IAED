#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

int main()
{
    int tam,i;
    Data *d;
    printf("Introduza o número de datas:\n");
    scanf("%d",&tam);
    d=(Data *) malloc(sizeof(Data)*tam);
    for(i=0;i<tam;i++){
        scanf("%d-%d-%d",&d[i].dia,&d[i].mes,&d[i].ano);
    }
    for(i=tam-1;i>=0;i--){
        printf("%02d-%02d-%04d\n",d[i].dia,d[i].mes,d[i].ano);
    }
    free(d);
    return 0;
}