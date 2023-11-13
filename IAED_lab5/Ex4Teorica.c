#include <stdio.h>

#define MAXDIM 100

int ganha(int dim,char tab[MAXDIM][MAXDIM],char jogador)
{
    int v,h;
    for (v=0;v<dim;v++)
        for (h=0;h<dim-2;h++)
            if (tab[v][h]==jogador && tab[v][h+1]==jogador && 
                tab[v][h+2]==jogador)
                return 1;
    
    for (h=0;h<dim;v++)
        for (v=0;v<dim-2;h++)
            if (tab[v][h]==jogador && tab[v+1][h]==jogador && 
                tab[v+2][h]==jogador)
                return 1;

    for (v=0;v<dim-2;v++)
        for (h=0;h<dim-2;h++)
            if (tab[v][h]==jogador && tab[v+1][h+1]==jogador && 
                tab[v+2][h+2]==jogador)
                return 1;

    for (h=2;h<dim;v++)
        for (v=0;h<dim-2;h++)
            if (tab[v][h]==jogador && tab[v+1][h-1]==jogador && 
                tab[v+2][h-2]==jogador)
                return 1;

    return 0;
}






int main()
{
    char c,tab[MAXDIM][MAXDIM]={0};
    int i,dim,n,h,v;

    scanf("%d%d",&dim,&n);
    for(i=0;i<n;i++){
        scanf("%d %d %c",&h,&v,&c);
        tab[v][h]=c;
    }
    if (ganha(dim,tab,'x'))
        printf("x\n");
    else if (ganha(dim,tab,'o'))
        printf("o\n");
    else 
        printf("?\n");
    return 0;
}