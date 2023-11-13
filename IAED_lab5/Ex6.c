#include <stdio.h>

#define DIM 100
typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

void escreveData(Data data1,Data data2);
Data dataMaisAntiga(Data data1,Data data2);
Data conversaoData(char data[]);

int main()
{
    char data1[DIM],data2[DIM];
    Data d1,d2,dAntiga;
    scanf("%s%s",data1,data2);
    d1=conversaoData(data1);
    d2=conversaoData(data2);
    dAntiga=dataMaisAntiga(d1,d2);
    if (dAntiga.dia==d1.dia && dAntiga.mes==d1.mes && dAntiga.ano==d1.ano)
        escreveData(d1,d2);
    else
        escreveData(d2,d1);
    return 0;
}

Data conversaoData(char data[])
{
    int i,j,k;
    Data d={0,0,0};
    for (i=0;data[i]!='-';i++)
        d.dia=d.dia*10+(data[i]-'0');
    for (j=i+1;data[j]!='-';j++)
        d.mes=d.mes*10+(data[j]-'0');
    for (k=j+1;data[k]!='\0';k++)
        d.ano=d.ano*10+(data[k]-'0');
    return d;
}

Data dataMaisAntiga(Data data1,Data data2)
{
    if (data1.ano<data2.ano)
        return data1;
    else if (data2.ano<data1.ano)
        return data2;
    else if (data1.mes<data2.mes)
        return data1;
    else if (data1.mes<data2.mes)
        return data2;
    else if (data1.dia<data2.dia)
        return data1;
    return data2;
}
void escreveData(Data data1,Data data2)
{
    printf("%.2d-%.2d-%.4d %.2d-%.2d-%.4d\n",data1.dia,data1.mes,data1.ano,
                                data2.dia,data2.mes,data2.ano);
}