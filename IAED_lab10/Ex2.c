#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

void bubbleSort(int tamanho,Data *d);
int verificarData(Data d1,Data d2);

int main()
{
    int tam,i;
    Data *d;
    printf("Introduza o número de datas:\n");
    scanf("%d",&tam);
    d=(Data *) malloc(sizeof(Data)*tam);
    for(i=0;i<tam;i++){
        scanf("%d-%d-%d",&d[i].dia,&d[i].mes,&d[i].ano);
        if (i>0){
            bubbleSort(i+1,d);
        }
    }
    /*bubbleSort(tam,d);*/
    for(i=0;i<tam;i++){
        printf("%02d-%02d-%04d\n",d[i].dia,d[i].mes,d[i].ano);
    }
    free(d);
    return 0;
}

void bubbleSort(int tamanho,Data *d)
{
    int j;
    Data aux;
    for(j=tamanho-1;j>0;j--){
        if (verificarData(d[j-1],d[j])){
            aux=d[j-1];
            d[j-1]=d[j];
            d[j]=aux;
        }
    }
}

int verificarData(Data data1,Data data2)
{
    int d1,d2;
    d1=data1.ano*10000+data1.mes*100+data1.dia;
    d2=data2.ano*10000+data2.mes*100+data2.dia;
    if (d1>d2)
        return TRUE;
    return FALSE;
}