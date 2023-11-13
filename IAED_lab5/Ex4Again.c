#include <stdio.h>

/*nao entendo o que se passa*/

#define MAXDIM 100

int ganha(int dim, char tab[][MAXDIM],char jogador);

int main()
{
    char tab[MAXDIM][MAXDIM];
    char jogador,p1='x',p2='o';
    int horizontal,vertical;
    int resultado1,resultado2;
    int d,n;
    int i,j;
    scanf("%d%d\n",&d,&n);
    for(i=0;i<d+2 && i<MAXDIM;i++)
        for(j=0;j<d+4 && j<MAXDIM;j++)
            tab[i][j]='1';
    for (i=0;i<n;i++){
        scanf("%d%d %c\n",&horizontal,&vertical,&jogador);
        tab[horizontal][vertical+2]=jogador;
    }
    resultado1=ganha(d,tab,p1);
    resultado2=ganha(d,tab,p2);
    if (resultado1)
        putchar(p1);
    else if (resultado2)
        putchar(p2);
    else
        putchar('?');
    return 0;
}

int ganha(int dim, char tab[][MAXDIM],char jogador)
{
    int i,j;
    for (i=0;i<dim;i++){
        for (j=2;j<dim+2;i++){
            if (tab[i][j]==jogador){
                if (tab[i][j+1]==jogador && tab[i][j+2]==jogador)
                    return 1;
                else if (tab[i+1][j]==jogador && tab[i+2][j]==jogador)
                    return 1;
                else if (tab[i+1][j+1]==jogador && tab[i+2][j+2]==jogador)
                    return 1;
            }   
        }
    }
    return 0;
}