#include <stdio.h>

enum constantes {MAXDIM = 100, WIN = 1, LOSS = 0};

void recebe_tab(char tab[][MAXDIM], int n);
void inicializa_tab(char tab[][MAXDIM], int dim);
int ganha(int dim, char tab[][MAXDIM], char player);

int main(){
    char tab[MAXDIM][MAXDIM], p1 = 'x', p2 = 'o';
    int dim, n;

    printf("Introduza os dados do tabuleiro: ");
    scanf("%d%d", &dim, &n);
    inicializa_tab(tab, dim);
    recebe_tab(tab, n);

    if (ganha(dim, tab, p1) == WIN)
        printf("Ganhou o jogador %c!\n", p1);
    else if (ganha(dim, tab, p2) == WIN)
        printf("Ganhou o jogador %c!\n", p2);
    else
        printf("Empataram!");
    return 0;
}

void inicializa_tab(char tab[][MAXDIM], int dim){
    int i, j;
    /* chegar o tab 2 colunas para a direita para evitar index erros
    e preencher as 2 primeiras colunas, as 2 após o tab e as 2 linhas 
    por baixo também, pela mesma razão*/
    for (i = 0; i < dim + 2 && i < MAXDIM; i++)
        for (j = 0; j < dim + 4 && j < MAXDIM; j++)
            tab[i][j] = '-';
}

void recebe_tab(char tab[][MAXDIM], int n){
    int i, j, k;
    char c;

    for (k = 0; k < n; k++){
        scanf("%d%d %c", &i, &j, &c);
        tab[i][j+2] = c; /* j+2 pq o tab está desviado em 2 col para a dir */
    }
}

int ganha(int dim, char tab[][MAXDIM], char player){
    int i, j;

    for(i = 0; i < dim; i++){
        for (j = 2; j < dim + 2; j++){
            if (tab[i][j] == player){
                if (tab[i][j+1] == player && tab[i][j+2] == player )
                    return WIN;
                if (tab[i+1][j] == player && tab[i+2][j] == player)
                    return WIN;
                if (tab[i+1][j+1] == player && tab[i+2][j+2] == player)
                    return WIN;
                if (tab[i+1][j-1] == player && tab[i+2][j-2] == player)
                    return WIN;
            }
        }
    }
    return LOSS;
}