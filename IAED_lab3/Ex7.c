#include <stdio.h>

#define FORA 0
#define DENTRO 1
#define PRIMEIRO 2
#define SEGUNDO 3

int main()
{
    int op,n1=0,n2=0,estado=FORA,numero=PRIMEIRO;
    char c;
    while((c=getchar())!='\n'){
        if(numero==PRIMEIRO && c>='0' && c<='9'){
            estado=DENTRO;
            n1=n1*10+(c-'0');
        }
        if(estado==DENTRO && c==' '){
            estado=FORA;
            numero=SEGUNDO;
        }
        if (c=='+' || c=='-')
            op=c;
        if(numero==SEGUNDO && c>='0' && c<='9'){
            estado=DENTRO;
            n2=n2*10+(c-'0');
        }
        if(numero==SEGUNDO && estado==FORA && (c==' '||c=='\n')){
            if (op=='+'){
                n1=n1+n2;
                n2=0;
            }
            if (op=='-'){
                n1=n1-n2;
                n2=0;
            }
        }
    }
    if (op=='+')
        n1+=n2;
    else
        n1-=n2;
    printf("%d\n",n1);
    return 0;
}