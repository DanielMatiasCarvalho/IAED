#include <stdio.h>

#define ALUNOS 10
#define DISCIPLINAS 5

long score_disciplina(int disciplina,int valores[][DISCIPLINAS]);
long score_aluno(int aluno,int valores[][DISCIPLINAS]);

int main()
{
    int valores[ALUNOS][DISCIPLINAS];
    int i,j,n,a,d,v;
    int max_discp,max_al,al=0,discp=0;
    int aux;
    scanf("%d",&n);
    for(i=0;i<ALUNOS;i++)
        for(j=0;j<DISCIPLINAS;j++)
            valores[i][j]=0;
    for(i=0;i<n;i++)
    {
        scanf("%d%d%d",&a,&d,&v);
        valores[a][d]=v;
    }
    max_discp=score_disciplina(0,valores);
    for(i=1;i<DISCIPLINAS;i++){
        aux=score_disciplina(i,valores);
        if (max_discp<aux){
            max_discp=aux;
            discp=i;
        }
    }
    max_al=score_aluno(0,valores);
    for(i=1;i<ALUNOS;i++){
        aux=score_aluno(i,valores);
        if (max_al<aux){
            max_al=aux;
            al=i;
        }
    }
    printf("%d\n%d\n",discp,al);
    return 0;
}

long score_disciplina(int disciplina,int valores[][DISCIPLINAS])
{
    int i,soma=0,media;
    for (i=0;i<ALUNOS;i++)
        soma+=valores[i][disciplina];
    media=(soma/ALUNOS);
    return media;
}

long score_aluno(int aluno,int valores[][DISCIPLINAS])
{
    int i,soma=0,media;
    for (i=0;i<DISCIPLINAS;i++)
        soma+=valores[aluno][i];
    media=(soma/DISCIPLINAS);
    return media;
}