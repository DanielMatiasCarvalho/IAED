/*-------------------------------Projeto 1------------------------------------
Neste projeto, pretende-se a construção de um sistema de gestão de voos,
possuindo a definicao de voos, aeroportos e a consulta ao mesmos. Todas as
funções auxiliares,variáveis e constantes encontram-se definidas neste 
ficheiro.
Autor:Daniel Carvalho
Número: 102556
Ultima atualizacao: 29-03-2022 07:20
-----------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

#define LIM_N_AER 40 /*Limite do numero de aeroportos*/
#define DENTRO 3000 /*Utilizada para ler do stdin a cidade do aeroporto*/
#define FORA 4000 /*Utilizada para ler do stdin a cidade do aeroporto*/
#define ID_AER 4 /*Limite do tamanho da string do ID do aeroporto*/
#define PAIS 31 /*Limite do tamanho da string do pais*/
#define CIDADE 51 /*Limite do tamanho da string da cidade*/
#define TRUE 1
#define FALSE 0
#define CODIGO_VOO 7 /*Limite do vetor do codigo dos voos*/
#define LIM_N_VOO 30000 /*Numero maximo de voos aceites*/
#define MAX_DUR_VOO 12 /*Duração maxima de um voo*/
#define CP_MIN 10 /*Capacidade minima de um voo*/
#define CP_MAX 100 /*Capacidade maxima de um voo*/
#define PAR 1000 /*Constate auxiliar das funções do comando 'p',indicando que 
                se trata dos aeroportos de partida*/
#define CHG 2000 /*Constate auxiliar das funções do comando 'c',indicando que 
                se trata dos aeroportos de chegada*/
#define DIA 24 /*Horas de um dia*/
#define HORA 60 /*Minutos de uma hora*/

 /*-----------------------Estruturas----------------------------*/
typedef struct {
    char id[ID_AER];
    char pais[PAIS];
    char cidade[CIDADE];
} Aeroporto;

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    int horas;
    int minutos;
} Hora;

typedef struct {
    char id[CODIGO_VOO];
    char idpar[ID_AER];
    char idchg[ID_AER];
    Data dataPar;
    Hora horaPar;
    Data dataChg;
    Hora horaChg;
    Hora dur;
    int cp;
} Voo;

/*-------------------------Variaveis Globais-------------------------*/
int numAer=0; /*Numero de aeroportos*/
int numVoo=0; /*Numero de voos*/
Data dataAtual={1,1,2022}; /*Data do dia atual do sistema*/

/*vetor dos dias finais de cada mes do ano*/
int diasDoMes[]={31,28,31,30,31,30,31,31,30,31,30,31};
Aeroporto tabelaAeroporto[LIM_N_AER]; /*Vetor de todos os aeroportos*/
Voo tabelaVoo[LIM_N_VOO]; /*Vetor de todos os voos*/

/*------------------------------Protótipo----------------------------*/
Aeroporto lerAeroporto();
int verificacaoAeroporto(Aeroporto a);
void escreverAeroporto (Aeroporto a);
void obterAerVoos(char c);
void obterTodosAerVoos();
int numeroVoos(char id[ID_AER]);
void ordenarAeroportos();
void escreverAerVoos(int local,int voo);
Voo lerVoo();
int verificacaoVoo(Voo v);
int verificarVoosIguais(Voo v);
int verificarIDVoo(Voo v);
void listaVoos();
int compararAeroportos(char id[ID_AER]);
int verificacaoData(Data dataAlterada);
void escreverVoo(Voo v);
void obter_voos_aer(int n);
Voo chegada(Voo v);
int datasIguais(Data data1,Data data2);
Data diaSeguinte(Data data);
Hora somaHoras(Hora horas1,Hora horas2);
void ordenarVoos(Voo vooAer[MAX_DUR_VOO],int dim,int n);
int verificacaoOrdenarVoos(Voo v1,Voo v2,int n);
int verificarPassado(Data data1,Data data2);
Data lerData();
void escreveData(Data data);

int main()
{
    char c;
    Aeroporto aeroporto;
    Data dataAlterada;
    Voo voo;
    int verificacao=0;
    while ((c=getchar())!='q'){
        switch(c)
        {
            case 'a': /*adiciona um novo aeroporto ao sistema */
                    aeroporto=lerAeroporto();
                    verificacao=verificacaoAeroporto(aeroporto);
                    if (!verificacao)
                        break;
                    escreverAeroporto(aeroporto);
                    break;
            case 'l':
                /*escreve um aeroporto e o número de voos que têm origem nele*/
                    if((c=getchar())==' ' || c=='\t')
                    /*escreve para os aeroportos no stdin*/
                            obterAerVoos(c);
                    else
                    /*todos os aeroportos*/
                        obterTodosAerVoos();
                    break;
            case 'v':
                /*adiciona um voo ou lista todos os voos*/
                    if((c=getchar())==' ' || c=='\t'){
                        /*adicona o voo*/
                        voo=lerVoo();
                        verificacao=verificacaoVoo(voo);
                        if (!verificacao)
                            break;
                    }  
                    else {
                        /*lista os voos*/
                        listaVoos();
                    }
                    break;
            case 'p':
                /*lista os voos com partida de um aeroporto*/
                    obter_voos_aer(PAR);
                    break;
            case 'c':
                /*lista os voos com chegada a um aeroporto*/
                    obter_voos_aer(CHG);
                    break;
            case 't':
                /*avança a data do sistema*/
                    dataAlterada=lerData();
                    verificacao=verificacaoData(dataAlterada);
                    if (!verificacao){
                        printf("invalid date\n");
                        break;
                    }
                    dataAtual=dataAlterada;
                    escreveData(dataAtual);
                    break;
        }
    }
    return 0;
}
/*------------------------------lerAeroporto-----------------------------------
Esta funcao recebe atraves do stdin um ID, uma cidade e um pais, correspondente
a esse aeroporto, devolvendo estas variaveis colocadas numa estrutura
Aeroporto
-----------------------------------------------------------------------------*/
Aeroporto lerAeroporto()
{
    Aeroporto a;
    int estado=FORA,i=0;
    char c;
    scanf("%s%s",a.id,a.pais);
    while ((c=getchar())!='\n'){ /*para ler a cidade*/
        if (estado==FORA && ((c>='A' && c<='Z')|| (c>='a' && c<='z'))){
            estado=DENTRO;
            a.cidade[i]=c;
            i++;
        }
        else if (estado==DENTRO){
            a.cidade[i]=c;
            i++;
        }
    }
    a.cidade[i]='\0'; /*finalizar a string da cidade*/
    return a;
}

/*---------------------------verificacaoAeroporto------------------------------
Esta funcao recebe um aeroporto, verifica eventuais erros dos inputs,
devolvendo FALSE e terminando se tal. Se passar pelos erros todos, 
esse aeroporto é adicionado ao vetor de todos os aeroportos, acrecentando
1 ao numero de aeroportos e devolvendo TRUE
-----------------------------------------------------------------------------*/

int verificacaoAeroporto(Aeroporto a)
{
    int i;
    if (numAer<LIM_N_AER){
        for (i=0;i<ID_AER-1;i++)
            if(a.id[i]<'A' || a.id[i]>'Z'){
                printf("invalid airport ID\n");
                return FALSE;
            }
        for(i=0;i<numAer;i++){
            if(!strcmp(a.id,tabelaAeroporto[i].id)){
                printf("duplicate airport\n");
                return FALSE;
            }
        }
    }
    else {
        printf("too many airports\n");
        return FALSE;
    }
    tabelaAeroporto[numAer]=a;
    numAer++;
    return TRUE;
}

/*----------------------------escreverAeroporto--------------------------------
Escreve para o standard output o ID do aeroporto.
-----------------------------------------------------------------------------*/

void escreverAeroporto (Aeroporto a)
{
    printf("airport %s\n",a.id);
}

/*------------------------------obterAerVoos-------------------------------------
Esta funcao le um ID de um aeroporto, e apos as verificacoes, escreve o ID 
do aeroporto com a cidade, pais e numero de voos com origem nele.
-----------------------------------------------------------------------------*/

void obterAerVoos(char c)
{
    int res,voo,i;
    char id[ID_AER];
    while (c!='\n'){
        scanf("%s",id);
        c=getchar();
        res=compararAeroportos(id);
        if (res){
            voo=numeroVoos(id);
            for (i=0;i<numAer;i++){
                if (!strcmp(id,tabelaAeroporto[i].id)){
                    escreverAerVoos(i,voo);
                    break;
                }
            }
        }
        else if (!res){
            printf("%s: no such airport ID\n",id);
        }
    }
}

/*----------------------------obterTodosAerVoos--------------------------------
Esta funcao ordena o vetor dos aeroportos, escrevendo no standard output
o ID do aeroporto, a cidade, o pais e o numero de voos com origem nesse
aeroporto
-----------------------------------------------------------------------------*/

void obterTodosAerVoos()
{
    int i,voo;
    ordenarAeroportos();
    for(i=0;i<numAer;i++){
        voo=numeroVoos(tabelaAeroporto[i].id);
        escreverAerVoos(i,voo);
    }
}

/*------------------------------numeroVoos-------------------------------------
Esta funcao recebe um ID de aeroporto, devolvendo o numero de voos com origem
nele
-----------------------------------------------------------------------------*/

int numeroVoos(char id[ID_AER])
{
    int i,res=0;
    for(i=0;i<numVoo;i++){
        if (!strcmp(id,tabelaVoo[i].idpar))
            res++;
    }
    return res;
}

/*---------------------------ordenarAeroportos---------------------------------
Esta funcao ordena os vetores de aeroportos que recebe por ordem alfabetica dos 
ID's dos aeroportos usando o algoritmo de ordenacao Insertion Sort
-----------------------------------------------------------------------------*/

void ordenarAeroportos()
{
    int i,j;
    for (i=1;i<numAer;i++){
        Aeroporto aux=tabelaAeroporto[i];
        j=i-1;
        while (j>=0 && strcmp(tabelaAeroporto[j].id,aux.id)>0){
                tabelaAeroporto[j+1]=tabelaAeroporto[j];
                j--;
        }
        tabelaAeroporto[j+1]=aux;
    }
}

/*--------------------------escreverAerVoos------------------------------
Esta funcao recebe uma posicao do vetor dos aeroportos, escrevendo esse 
aeroporto associado ao numero de voos com origem nele
-----------------------------------------------------------------------------*/

void escreverAerVoos(int local,int voo)
 {
    printf("%s %s %s %d\n",tabelaAeroporto[local].id,
                                tabelaAeroporto[local].cidade,
                                tabelaAeroporto[local].pais,
                                voo);
 }

/*--------------------------------lerVoo---------------------------------------
Esta funcao le as componentes necessarias de um voo,(ID,ID do aeroportos 
de partida e chegada, data de partida, hora de partida, duracao e capacidade)
devolvendo esses valores associados a uma estrutura Voo
-----------------------------------------------------------------------------*/

Voo lerVoo()
{
    Voo v;
    scanf("%s%s%s",v.id,v.idpar,v.idchg);
    scanf("%d-%d-%d",&v.dataPar.dia,&v.dataPar.mes,&v.dataPar.ano);
    scanf("%d:%d",&v.horaPar.horas,&v.horaPar.minutos);
    scanf("%d:%d",&v.dur.horas,&v.dur.minutos);
    scanf("%d",&v.cp);
    return v;
}

/*------------------------------verificacaoVoo---------------------------------
Esta funcao recebe uma variavel da estrutura Voo, verificando se as componentes
dessa variavel sao validas. Se causar erros, esta funcao devolve o erro e 
FALSE, por outro lado, se nao infrigir nenhum erro, essa variavel e adicionada
ao vetor dos voos, aumentando o numero de voos, e devolvendo TRUE
-----------------------------------------------------------------------------*/

int verificacaoVoo(Voo v)
{
    if (numVoo<LIM_N_VOO){
        if (!verificarIDVoo(v)){
            return FALSE;
        }
        if(!compararAeroportos(v.idpar)){
            printf("%s: no such airport ID\n",v.idpar);
            return FALSE;
        }
        if(!compararAeroportos(v.idchg)){
            printf("%s: no such airport ID\n",v.idchg);
            return FALSE;
        }
        if (!verificacaoData(v.dataPar)){
            printf("invalid date\n");
            return FALSE;
        }
        if (!verificarVoosIguais(v)){
            return FALSE;
        }
        if ((v.dur.horas==MAX_DUR_VOO && v.dur.minutos>0) || 
            v.dur.horas>MAX_DUR_VOO){
            printf("invalid duration\n");
            return FALSE;
        }
        if (v.cp<CP_MIN || v.cp>CP_MAX){
            printf("invalid capacity\n");
            return FALSE;
        }
    }
    else {
         printf("too many flights\n");
         return FALSE;
    }
    tabelaVoo[numVoo]=v;
    numVoo++;
    return TRUE;
}

/*---------------------------verificarVoosIguais-------------------------------
Faz a verificação se o codigo do voo já existe na mesma data de partida
-----------------------------------------------------------------------------*/

int verificarVoosIguais(Voo v)
{
    int i;
    for(i=0;i<numVoo;i++){
        if(strcmp(v.id,tabelaVoo[i].id)==0 && 
            datasIguais(v.dataPar,tabelaVoo[i].dataPar)==TRUE){
            printf("flight already exists\n");
            return FALSE;
        }
    }
    return TRUE;
}

/*---------------------------verificarIDVoo-------------------------------
Faz a verificação se o codigo do voo e valido
-----------------------------------------------------------------------------*/

int verificarIDVoo(Voo v)
{
    int i,len;
    len=strlen(v.id);
    for(i=0;i<len;i++){
        if (i<2){ /*Primeiras duas letras*/
            if (v.id[i]<'A' || v.id[i]>'Z'){
                printf("invalid flight code\n");
                return FALSE;
            }
        }
        else if(v.id[2]<'1' || v.id[2]>'9'){
                /*o primeiro digito nao pode ser 0*/
                printf("invalid flight code\n");
                return FALSE;
            }
        else if(v.id[i]<'0' || v.id[i]>'9'){
                printf("invalid flight code\n");
                return FALSE;
        }
    }
    return TRUE;
}

/*-------------------------------listaVoos-------------------------------------
Escreve para o standard output todos voos do pela ordem de criacao
-----------------------------------------------------------------------------*/

void listaVoos()
{
    int i;
    for (i=0;i<numVoo;i++)
        escreverVoo(tabelaVoo[i]);
}

/*--------------------------compararAeroportos---------------------------------
Esta funcao recebe um ID de um aeroporto e verifica se este existe no vetor
de todos os aeroportos do programa, devolvendo TRUE caso existe e FALSE caso
contrario
-----------------------------------------------------------------------------*/

int compararAeroportos(char id[ID_AER])
{
    int i;
    for (i=0;i<numAer;i++)
        if (!strcmp(id,tabelaAeroporto[i].id))
            return TRUE;
    return FALSE;
}

/*---------------------------verificacaoData-----------------------------------
Esta recebe a data atual do sistema e a recebida pelo standard input,
verificando esta não é passado da data atual nem que ultrapassa o dia 
01-01-2023, devolvendo FALSE se tal e TRUE caso seja valida a data recebida
-----------------------------------------------------------------------------*/

int verificacaoData(Data dataAlterada)
{

    if (dataAlterada.ano<dataAtual.ano){ /*ano anterior*/
        return FALSE;
    }
    else if (dataAlterada.ano==dataAtual.ano && /*mes anterior*/
            dataAlterada.mes<dataAtual.mes){
                return FALSE;
            }
    else if (dataAlterada.ano==dataAtual.ano && /*dia anterior*/
            dataAlterada.mes==dataAtual.mes && 
            dataAlterada.dia<dataAtual.dia){
                return FALSE;
            }
    else if (dataAlterada.ano>dataAtual.ano+1){ /*mais que 1 ano futuro*/
                return FALSE;
    }
    else if (dataAlterada.ano==dataAtual.ano+1 && 
            dataAlterada.mes>dataAtual.mes){
                /*mes para alem do atual no proximo ano*/
                return FALSE;
            }
    else if (dataAlterada.ano==dataAtual.ano+1 &&
            dataAlterada.mes==dataAtual.mes &&
            dataAlterada.dia>dataAtual.dia){
                /*dia para alem do atual no ano futuro, no mesmo mes*/
                return FALSE;
            }
    return TRUE;
}

/*------------------------------escreverVoo------------------------------------
Esta funcao recebe uma variavel de uma estrutura de voo, escrevendo no standard
output as suas componentes
-----------------------------------------------------------------------------*/

void escreverVoo(Voo v)
{
    printf("%s %s %s %02d-%02d-%02d %02d:%02d\n",v.id,v.idpar,v.idchg,
                                                v.dataPar.dia,
                                                v.dataPar.mes,v.dataPar.ano,
                                                v.horaPar.horas,
                                                v.horaPar.minutos);
}

/*----------------------------obter_voos_aer-----------------------------------
Esta funcao recebe um inteiro, que representa se se trata de um ID de um 
aeroporto de partida (comando 'p') ou de chegada (comando 'c'). Apos verificar
se o ID e de um aeroporto, sao colocados os voos com esse aeroporto num vetor
auxiliar, que e ordenado por data e hora (de partida para o comando 'p' e de
chegada para o comando 'c'), imprimindo no final esses voos e as suas 
componentes de forma ordenada
-----------------------------------------------------------------------------*/

void obter_voos_aer(int n)
{
    int lenPar=0,lenChg=0,i,res;
    char id[ID_AER];
    Voo vooAer[LIM_N_VOO];

    scanf("%s",id);
    res=compararAeroportos(id);
    if (res && n==PAR){ /*comando 'p'*/
        for (i=0;i<numVoo;i++) /*criacao do vetor auxiliar*/
            if (!strcmp(id,tabelaVoo[i].idpar)){
                vooAer[lenPar]=tabelaVoo[i];
                lenPar++;
            }
        ordenarVoos(vooAer,lenPar,PAR);
        for (i=0;i<lenPar;i++){
            printf("%s %s %02d-%02d-%04d %02d:%02d\n",vooAer[i].id,
                                            vooAer[i].idchg,
                                            vooAer[i].dataPar.dia,
                                            vooAer[i].dataPar.mes,
                                            vooAer[i].dataPar.ano,
                                            vooAer[i].horaPar.horas,
                                            vooAer[i].horaPar.minutos);
        }
    }
    else if(res && n==CHG){ /*comando 'c'*/
        for (i=0;i<numVoo;i++){
            if (!strcmp(id,tabelaVoo[i].idchg)){
                vooAer[lenChg]=tabelaVoo[i];
                vooAer[lenChg]=chegada(vooAer[lenChg]);
                lenChg++;
            }
        }
        ordenarVoos(vooAer,lenChg,CHG);
        for (i=0;i<lenChg;i++){
            printf("%s %s %02d-%02d-%04d %02d:%02d\n",vooAer[i].id,
                                                vooAer[i].idpar,
                                                vooAer[i].dataChg.dia,
                                                vooAer[i].dataChg.mes,
                                                vooAer[i].dataChg.ano,
                                                vooAer[i].horaChg.horas,
                                                vooAer[i].horaChg.minutos);
        }
    }
    else if (!res)
        printf("%s: no such airport ID\n",id);
}

/*------------------------------chegada------------------------------------
Esta funcao recebe um Voo, calculando de seguida a data e a hora de chegada,
desse mesmo voo
-----------------------------------------------------------------------------*/

Voo chegada(Voo v)
{
    Data d={0,0,0};
    Hora h={0,0};
    h=somaHoras(v.horaPar,v.dur);
    d=v.dataPar;
    /*alteracao das horas, adicionando as horas de partida 
    a duracao do voo*/
    if (h.horas>=DIA){
        /*se alterar o dia*/
        h.horas-=DIA;
        d=diaSeguinte(v.dataPar);
    }
    v.horaChg.horas=h.horas;
    v.horaChg.minutos=h.minutos;
    v.dataChg.dia=d.dia;
    v.dataChg.mes=d.mes;
    v.dataChg.ano=d.ano;
    return v;
}

/*------------------------------datasIguais------------------------------------
Esta funcao recebe duas datas e verifica se sao iguais, devolvendo TRUE se tal
e FALSE caso contrario
-----------------------------------------------------------------------------*/

int datasIguais(Data data1,Data data2)
{
    if (data1.dia==data2.dia && data1.mes==data2.mes && data1.ano==data2.ano)
        return TRUE;
return FALSE;
}

/*-----------------------------diaSeguinte-------------------------------------
Esta funcao recebe uma data e altera-a para o proximo dia
-----------------------------------------------------------------------------*/

Data diaSeguinte(Data data)
{
    if (data.dia==diasDoMes[data.mes-1]){
        data.dia=1;
        data.mes++;
        if (data.mes>12){
            data.mes=1;
            data.ano++;
        }
    }
    else    
        data.dia++;
    return data;

}

/*------------------------------somaHoras-------------------------------------
Esta funcao recebe duas horas, e soma as suas componentes de horas e 
de minutos, sendo que no caso de os minutos da soma serem maiores que 60,
e acrescentado uma hora
-----------------------------------------------------------------------------*/

Hora somaHoras(Hora horas1,Hora horas2)
{
    Hora soma;
    soma.horas=horas2.horas+horas1.horas;
    soma.minutos=horas2.minutos+horas1.minutos;
    if (soma.minutos>=HORA){
        soma.horas++;
        soma.minutos=soma.minutos%HORA;
    }
    return soma;
}

/*------------------------------ordenarVoos------------------------------------
Esta funcao recebe um vetor de voos e a sua dimensao, ordenando os voos, 
pela sua data e hora,da mais antiga para mais recente, atraves do algoritmo
de ordenacao Bubble Sort, colocando-se sempre o "maior" elemento em cada 
iteracao na posicao correta
-----------------------------------------------------------------------------*/

void ordenarVoos(Voo vooAer[LIM_N_VOO],int dim,int n)
{
    int i,j;
    Voo aux;
    for(i=0;i<dim;i++){
        for(j=0;j<dim-1-i;j++){
            if (verificacaoOrdenarVoos(vooAer[j],vooAer[j+1],n)){
                aux=vooAer[j];
                vooAer[j]=vooAer[j+1];
                vooAer[j+1]=aux;
            }
        }
    }
}

/*------------------------verificacaoOrdenarVoos-------------------------------
Esta funcao recebe dois voos e um inteiro que indica se se trata do comando
'p' ou 'c', sendo uma funcao auxiliar para ordenar os voos da data e hora mais
antiga para a mais recente
-----------------------------------------------------------------------------*/

int verificacaoOrdenarVoos(Voo v1,Voo v2,int n)
{
    /*devolve TRUE apenas se o v1 é mais recente que o v2*/
    if (n==PAR){ /*comando 'p'*/
        if (verificarPassado(v1.dataPar,v2.dataPar))
            return TRUE;
        else if (datasIguais(v1.dataPar,v2.dataPar) && 
                v2.horaPar.horas<v1.horaPar.horas)
            return TRUE;
        else if (datasIguais(v1.dataPar,v2.dataPar) &&
                v2.horaPar.horas==v1.horaPar.horas &&
                v2.horaPar.minutos<v1.horaPar.minutos)
            return TRUE;
    }
    /*devolve TRUE apenas se o v1 é mais recente que o v2*/
    else if(n==CHG){ /*comando 'c*/
        if (verificarPassado(v1.dataChg,v2.dataChg))
            return TRUE;
        else if (datasIguais(v1.dataChg,v2.dataChg) && 
                v2.horaChg.horas<v1.horaChg.horas)
            return TRUE;
        else if (datasIguais(v1.dataChg,v2.dataChg) &&
                v2.horaChg.horas==v1.horaChg.horas &&
                v2.horaChg.minutos<v1.horaChg.minutos)
            return TRUE;
    }
    /*devolve FALSE apenas se o v1 tem data e hora igual a v2 ou v2 é mais
    recente que v1*/
    return FALSE;
}

/*----------------------------verificarPassado---------------------------------
Esta funcao recebe duas datas, converte-as na forma AAAAMMDD, e indica se 
a data1 é superior à data 2, ou seja, que é mais recente
-----------------------------------------------------------------------------*/

int verificarPassado(Data data1,Data data2)
{
    int d1,d2;
    /* data: int AAAAMMDD */
    d1=data1.ano*10000+data1.mes*100+data1.dia;
    d2=data2.ano*10000+data2.mes*100+data2.dia;
    if (d1>d2)
        return TRUE;
    return FALSE;
}



/*--------------------------------lerData--------------------------------------
Esta funcao le uma data no standard input, colocando-a nos parametros
corretos da estrutura Data
-----------------------------------------------------------------------------*/

Data lerData()
{
    Data d;
    scanf("%d-%d-%d",&d.dia,&d.mes,&d.ano);
    return d;
}

/*--------------------------------lerData--------------------------------------
Esta funcao recebe uma data, escrevendo-la no standard output de forma 
correta
-----------------------------------------------------------------------------*/

void escreveData(Data data)
{
    printf("%02d-%02d-%04d\n",data.dia,data.mes,data.ano);
}