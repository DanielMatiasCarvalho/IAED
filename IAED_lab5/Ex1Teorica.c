#include <stdio.h>

#define ALUNOS 10
#define DISCIPLINAS 5

long score_disciplina(int disciplina,int valores[ALUNOS][DISCIPLINAS])
{
    int i;
    long score=0;
    for(i=0;i<ALUNOS;i++)
        score+=valores[i][disciplina];
    return score;
}

long score_aluno(int aluno,int valores[ALUNOS][DISCIPLINAS])
{
    int i;
    long score=0;
    for(i=0;i<DISCIPLINAS;i++)
        score+=valores[aluno][i];
    return score;
}

int main()
{
    int i,a,d,v,n;
    long score,max_score;
    int valores[ALUNOS][DISCIPLINAS]={0};

    scanf("%d",&n);

    for(i=0;i<n;i++){
        scanf("%d%d%d",&a,&d,&v);
        valores[a][d]=v;
    }
    d=0;
    max_score=score_disciplina(0,valores);
    for (i=1;i<DISCIPLINAS;i++){
        score=score_disciplina(i,valores);
        if(score>max_score) {
            max_score=score;
            d=i;
        }
    }
    a=0;
    max_score=score_aluno(0,valores);
    for(i=1;i<ALUNOS;i++){
        score=score_aluno(i,valores);
        if(score>max_score){
            max_score=score;
            a=i;
        }
    }
    printf("%d\n%d\n",d,a);
    return 0;
}