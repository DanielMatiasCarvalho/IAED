#include <stdio.h>

#define DIM 100
#define DIA31 31
#define DIA30 30
enum meses {JAN=1,FEV,MAR,ABR,MAIO,JUN,JUL,AGO,SET,OUT,NOV,DEZ};

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

void escreveData(Data data);
Data proximoDia(Data data);
Data conversaoData(char data[]);

int main()
{
    char data1[DIM];
    Data d1,dSeguinte;
    scanf("%s",data1);
    d1=conversaoData(data1);
    dSeguinte=proximoDia(d1);
    escreveData(dSeguinte);
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

Data proximoDia(Data data)
{
    if (data.dia==31 && data.mes==DEZ){
        data.dia=1;
        data.mes=JAN;
        data.ano+=1;
    }
    else if(data.mes==DEZ)
        data.dia+=1;
    else if ((data.mes==FEV) && ((data.ano%4==0 && data.ano%100!=0) || 
            (data.ano%400==0)))
        {
            if (data.dia==28)
                data.dia+=1;
            else if (data.dia==29){
                data.dia=1;
                data.mes=MAR;
            }
        }
    else if (data.dia==28 && data.mes==FEV){
        data.dia=1;
        data.mes=MAR;
    }
    else if(data.mes==FEV)
        data.dia+=1;
    else if (data.mes==JAN || data.mes==MAR || data.mes==MAIO ||
            data.mes==JUL || data.mes==AGO || data.mes==OUT){
            if (data.dia==31){
                data.dia=1;
                data.mes+=1;
            }
            else 
                data.dia+=1;
    }
    else if (data.mes==MAR || data.mes==ABR || data.mes==JUN || 
            data.mes==SET || data.mes==NOV){
                if (data.dia==30){
                    data.dia=1;
                    data.mes+=1;
                }
                else
                    data.dia+=1;
    }
    return data;
}

void escreveData(Data data)
{
    printf("%.2d-%.2d-%.4d\n",data.dia,data.mes,data.ano);
}