#include <stdio.h>

#define FORA 0
#define DENTRO 1

int main()
{
    int estado=FORA,escape=FORA;
    char c;
    while((c=getchar())!=EOF){
        if(c=='"' && estado==FORA){
            estado=DENTRO;
            if((c=getchar())=='"'){
                printf("\n");
                estado=FORA;
            }
        }
        else if(c=='\\' && estado==DENTRO && escape==FORA)
            escape=DENTRO;
        else if (c=='"' && estado==DENTRO){
            printf("\n");
            estado=FORA;
        }
        
        if(estado==DENTRO){
            if(escape==DENTRO){
                c=getchar();
                escape=FORA;
            }
            putchar(c);
        }
    }
    return 0;
}
