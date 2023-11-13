#include <stdio.h>

#define DIM 1000
typedef struct {
    char nome[10];
    float valor;
    float rendimento;
} Stock;

float calculoRendimento(float a,float b);

int main()
{
    int n,i,titulo=0;
    float maior_rendimento=0,rendimento;
    Stock portfolio[DIM];
    scanf("%d",&n);
    for (i=0;i<n;i++){
        scanf("%s%f%f",portfolio[i].nome,&portfolio[i].valor,
                &portfolio[i].rendimento);
        rendimento=calculoRendimento(portfolio[i].valor,
                                    portfolio[i].rendimento);
        if (rendimento>maior_rendimento){
            maior_rendimento=rendimento;
            titulo=i;
        }  
    }
    printf("%s %.2f %.2f\n",portfolio[titulo].nome,
            portfolio[titulo].valor,portfolio[titulo].rendimento);
    return 0;
}

float calculoRendimento(float a,float b)
{
    float c;
    c=(a*(b/100));
    return c;
}