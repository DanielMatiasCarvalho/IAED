#include <stdio.h>

/*e possivel fazer so com que os floats e que metam duas casas? nao sao todos porque voi assim a estrutura definida?*/

typedef struct{
    float real;

    float imag;
} Complexo;

Complexo leComplexo();
Complexo somaComplexos(Complexo a, Complexo b);
void escreveComplexo(Complexo a);

int main()
{
    Complexo a, b,c;
    a=leComplexo();
    b=leComplexo();

    c=somaComplexos(a,b);
    escreveComplexo(c);
    return 0;
}

Complexo leComplexo()
{
    Complexo a;
    char sinal,i;
    scanf("%f%c%f%c",&a.real,&sinal,&a.imag,&i);
    if (sinal == '-')
        a.imag*=-1;
    return a;
}

Complexo somaComplexos(Complexo a, Complexo b)
{
    a.real+=b.real;
    a.imag+=b.imag;
    return a;
}

void escreveComplexo(Complexo a)
{
    if (a.imag<0)
        printf("%.2f%.2fi",a.real,a.imag);
    else
        printf("%.2f+%.2fi",a.real,a.imag);
}   