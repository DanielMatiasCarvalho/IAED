#include <stdio.h>
enum meses {JAN=1,FEV,MAR,ABR,MAIO,JUN,JUL,AGO,SET,OUT,NOV,DEZ};
#define DIAMIN 1440
#define HORMIN 60
typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct{
    int horas;
    int minutos;
} Horas;

Data proximoDia(Data data);

int main()
{
    Data d,datainicial={1,1,2022};
    Horas h={0,0};
    int minutostotais=0;
    scanf("%d-%d-%d",&d.dia,&d.mes,&d.ano);
    while(d.dia!=datainicial.dia || d.mes != datainicial.mes ||
        d.ano != datainicial.ano){
            datainicial=proximoDia(datainicial);
            minutostotais+=DIAMIN;
        }
    scanf("%d:%d",&h.horas,&h.minutos);
    minutostotais+=h.minutos+(h.horas*HORMIN);
    printf("%d\n",minutostotais);
    return 0;
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
