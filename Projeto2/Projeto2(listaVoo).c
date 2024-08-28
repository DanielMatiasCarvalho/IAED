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
#include <stdlib.h>

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
#define LIM_INSTRUCAO 65536

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

typedef struct{
    char codVoo[CODIGO_VOO];
    Data dataVoo;
    char *codRes;
    int numPas;
} Reserva;

typedef struct stru_noV {
    Voo v;
    struct stru_noV *proximo;
}noV;

typedef struct stru_noR {
    Reserva res;
    struct stru_noR *proximo;
}noR;

/*-------------------------Variaveis Globais-------------------------*/
int numAer=0; /*Numero de aeroportos*/
int numVoo=0; /*Numero de voos*/
Data dataAtual={1,1,2022}; /*Data do dia atual do sistema*/

/*vetor dos dias finais de cada mes do ano*/
int diasDoMes[]={31,28,31,30,31,30,31,31,30,31,30,31};
Aeroporto tabelaAeroporto[LIM_N_AER]; /*Vetor de todos os aeroportos*/
noV *cabecaVoo=NULL; /*Cabeca da lista de todos os voos*/
noR *cabecaReserva=NULL; /*Cabeca da lista de todas as reservas*/

/*------------------------------Protótipo----------------------------*/
Aeroporto lerAeroporto();
int verificacaoAeroporto();
void escreverAeroporto (char *id);
void obterAerVoos(char c);
void obterTodosAerVoos();
int numeroVoos(char *id);
void ordenarAeroportos();
void escreverAerVoos(int local,int voo);
Voo lerVoo();
int verificacaoVoo();
int verificarVoosIguais(Voo *v);
int verificarIDVoo(char *id);
void listaVoos();
int compararAeroportos(char *id);
int verificacaoData(Data dataAlterada);
void escreverVoo(noV *v);
void obter_voos_aer(int n);
Voo chegada(Voo *v);
int datasIguais(Data data1,Data data2);
Data diaSeguinte(Data data);
Hora somaHoras(Hora horas1,Hora horas2);
void ordenarVoos(Voo *vooAer,int dim,int n);
int verificacaoOrdenarVoos(Voo v1,Voo v2,int n);
int verificarPassado(Data data1,Data data2);
Data lerData();
void escreveData(Data data);
int calcularData(Data d);
int aeroportoInvalido(char *id);
int calculaHora(Hora h);
int aeroportoDuplicado(char *id);
void listaVoosPartida(char *id);
void listaVoosChegada(char *id);
void alteraData();
void listaAeroportos();
void adicionaListaVoos();
noV * novoNoV(Voo v);
noV * apagarListaV(noV * cabeca);
noV * inserirV(noV *cabeca,Voo v);
noV * apagaCodigoVoo(char *codigo);
noR * novoNoR(char* codigoVoo,char *codigoRes,Data d,int num);
noR * apagarListaR(noR * cabeca);
noR * apagaCodigoReserva(noR *cabeca,char *codigo);
noR * apagaCodigoVooReserva(noR *cabeca,char *codigo);
void apagaCodigo();
int apagaVoo(char *codigo);
void apagaReserva(char *codigo);
noR * adicionaReserva(noR *atual);
void adicionaListaReservas();
int validaReserva(noR *ptr);
noV * encontraVoo(char *codigo, Data d);
noR * encontraReserva(char *codigo);
int validaEntradaVoo(char *codigo,Data d);
void listaReservas(char *codigo, Data d);

int main()
{
    char c;
    while ((c=getchar())!='q'){
        switch(c){
            case 'a': verificacaoAeroporto();
                    break;
            case 'l': listaAeroportos();
                    break;
            case 'v': adicionaListaVoos();
                    break;
            case 'p': obter_voos_aer(PAR);
                    break;
            case 'c': obter_voos_aer(CHG);
                    break;
            case 't': alteraData();
                    break;
            case 'r': adicionaListaReservas();
                    break;
            case 'e': apagaCodigo();
                    break;
            }
    }
    apagarListaR(cabecaReserva);
    apagarListaV(cabecaVoo);
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

int verificacaoAeroporto()
{
    Aeroporto a;
    a=lerAeroporto();
    if (numAer<LIM_N_AER){
        if(aeroportoInvalido(a.id)){
            printf("invalid airport ID\n");
            return FALSE;
        }
        if(aeroportoDuplicado(a.id)){
            printf("duplicate airport\n");
            return FALSE;
        }
    }
    else {
        printf("too many airports\n");
        return FALSE;
    }
    tabelaAeroporto[numAer]=a;
    numAer++;
    escreverAeroporto(a.id);
    return TRUE;
}

int aeroportoInvalido(char *id)
{
    int i;
    for (i=0;i<ID_AER-1;i++)
        if(id[i]<'A' || id[i]>'Z'){
            return TRUE;
        }
    return FALSE;
}

int aeroportoDuplicado(char *id)
{
    int i;
    for(i=0;i<numAer;i++){
        if(!strcmp(id,tabelaAeroporto[i].id)){
            return TRUE;
        }
    }
    return FALSE;
}

/*----------------------------escreverAeroporto--------------------------------
Escreve para o standard output o ID do aeroporto.
-----------------------------------------------------------------------------*/

void escreverAeroporto (char *id)
{
    printf("airport %s\n",id);
}

void listaAeroportos()
{
    char c;
    if((c=getchar())==' ' || c=='\t')
        /*escreve para os aeroportos no stdin*/
        obterAerVoos(c);
    else
        /*todos os aeroportos*/
        obterTodosAerVoos();
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

int numeroVoos(char *id)
{
    int res=0;
    noV * aux;
    for(aux=cabecaVoo;aux!=NULL;aux=aux->proximo){
        if (!strcmp(id,aux->v.idpar))
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


void adicionaListaVoos()
{
    char c;
    if((c=getchar())==' ' || c=='\t'){
        /*adicona o voo*/
        verificacaoVoo();
    }  
    else {
        /*lista os voos*/
        listaVoos();
        }
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

int verificacaoVoo()
{
    Voo v;
    Voo *ptr;
    v=lerVoo();
    ptr=&v;
    if (numVoo<LIM_N_VOO){
        if (!verificarIDVoo(ptr->id)){
            printf("invalid flight code\n");
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
        if (!verificarVoosIguais(ptr)){
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
    cabecaVoo=inserirV(cabecaVoo,v);
    numVoo++;
    return TRUE;
}

/*---------------------------verificarVoosIguais-------------------------------
Faz a verificação se o codigo do voo já existe na mesma data de partida
-----------------------------------------------------------------------------*/

int verificarVoosIguais(Voo *voo)
{
    noV * aux;
    for(aux=cabecaVoo;aux!=NULL;aux=aux->proximo){
        if(strcmp(voo->id,aux->v.id)==0 && 
            datasIguais(voo->dataPar,aux->v.dataPar)==TRUE){
            printf("flight already exists\n");
            return FALSE;
        }
    }
    return TRUE;
}

/*---------------------------verificarIDVoo-------------------------------
Faz a verificação se o codigo do voo e valido
-----------------------------------------------------------------------------*/

int verificarIDVoo(char *id)
{
    int i,len;
    len=strlen(id);
    for(i=0;i<len;i++){
        if (i<2){ /*Primeiras duas letras*/
            if (id[i]<'A' || id[i]>'Z'){
                return FALSE;
            }
        }
        else if(id[2]<'1' || id[2]>'9'){
                /*o primeiro digito nao pode ser 0*/
                return FALSE;
            }
        else if(id[i]<'0' || id[i]>'9'){
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
    noV *aux;
    for (aux=cabecaVoo;aux!=NULL;aux=aux->proximo){
        escreverVoo(aux);
    }
}

/*--------------------------compararAeroportos---------------------------------
Esta funcao recebe um ID de um aeroporto e verifica se este existe no vetor
de todos os aeroportos do programa, devolvendo TRUE caso existe e FALSE caso
contrario
-----------------------------------------------------------------------------*/

int compararAeroportos(char *id)
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
    int num=calcularData(dataAlterada);
    Data proximoAno=dataAtual;
    proximoAno.ano++;
    return !(num< calcularData(dataAtual)
                || num>calcularData(proximoAno));
}

/*------------------------------escreverVoo------------------------------------
Esta funcao recebe uma variavel de uma estrutura de voo, escrevendo no standard
output as suas componentes
-----------------------------------------------------------------------------*/

void escreverVoo(noV *ptr)
{
    printf("%s %s %s %02d-%02d-%02d %02d:%02d\n",ptr->v.id,ptr->v.idpar,
                                                ptr->v.idchg,
                                                ptr->v.dataPar.dia,
                                                ptr->v.dataPar.mes,
                                                ptr->v.dataPar.ano,
                                                ptr->v.horaPar.horas,
                                                ptr->v.horaPar.minutos);
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
    int res;
    char id[ID_AER];

    scanf("%s",id);
    res=compararAeroportos(id);
    if (res && n==PAR){ /*comando 'p'*/
        listaVoosPartida(id);
    }
    else if(res && n==CHG){ /*comando 'c'*/
        listaVoosChegada(id);    
    }
    else if (!res)
        printf("%s: no such airport ID\n",id);
}

void listaVoosPartida(char *id)
{
    int i,len=0;
    noV * aux;
    Voo vooAer[LIM_N_VOO];
    for (aux=cabecaVoo;aux!=NULL;aux=aux->proximo) /*criacao do vetor auxiliar*/
        if (!strcmp(id,aux->v.idpar)){
            vooAer[len]=aux->v;
            len++;
    }
    ordenarVoos(vooAer,len,PAR);
    for (i=0;i<len;i++){
        printf("%s %s %02d-%02d-%04d %02d:%02d\n",vooAer[i].id,
                                            vooAer[i].idchg,
                                            vooAer[i].dataPar.dia,
                                            vooAer[i].dataPar.mes,
                                            vooAer[i].dataPar.ano,
                                            vooAer[i].horaPar.horas,
                                            vooAer[i].horaPar.minutos);
    }
}

void listaVoosChegada(char *id)
{
    int i,len=0;
    noV * aux;
    Voo vooAer[LIM_N_VOO];
    Voo *ptr=NULL;
    for (aux=cabecaVoo;aux!=NULL;aux=aux->proximo){
        if (!strcmp(id,aux->v.idchg)){
            vooAer[len]=aux->v;
            ptr=&vooAer[len];
            vooAer[len]=chegada(ptr);
            len++;
        }
    }
    ordenarVoos(vooAer,len,CHG);
    for (i=0;i<len;i++){
        printf("%s %s %02d-%02d-%04d %02d:%02d\n",vooAer[i].id,
                                                vooAer[i].idpar,
                                                vooAer[i].dataChg.dia,
                                                vooAer[i].dataChg.mes,
                                                vooAer[i].dataChg.ano,
                                                vooAer[i].horaChg.horas,
                                                vooAer[i].horaChg.minutos);
    }
}

/*------------------------------chegada------------------------------------
Esta funcao recebe um Voo, calculando de seguida a data e a hora de chegada,
desse mesmo voo
-----------------------------------------------------------------------------*/

Voo chegada(Voo *v)
{
    Data d={0,0,0};
    Hora h={0,0};
    h=somaHoras(v->horaPar,v->dur);
    d=v->dataPar;
    /*alteracao das horas, adicionando as horas de partida 
    a duracao do voo*/
    if (h.horas>=DIA){
        /*se alterar o dia*/
        h.horas-=DIA;
        d=diaSeguinte(v->dataPar);
    }
    v->horaChg.horas=h.horas;
    v->horaChg.minutos=h.minutos;
    v->dataChg.dia=d.dia;
    v->dataChg.mes=d.mes;
    v->dataChg.ano=d.ano;
    return *v;
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

void ordenarVoos(Voo *vooAer,int dim,int n)
{
    int i,j,done;
    Voo aux;
    for(i=0;i<dim;i++){
        done=1;
        for(j=0;j<dim-1-i;j++){
            if (verificacaoOrdenarVoos(vooAer[j],vooAer[j+1],n)){
                aux=vooAer[j];
                vooAer[j]=vooAer[j+1];
                vooAer[j+1]=aux;
                done=0;
            }
        }
        if (done) break;
    }
}

/*------------------------verificacaoOrdenarVoos-------------------------------
Esta funcao recebe dois voos e um inteiro que indica se se trata do comando
'p' ou 'c', sendo uma funcao auxiliar para ordenar os voos da data e hora mais
antiga para a mais recente
-----------------------------------------------------------------------------*/

int verificacaoOrdenarVoos(Voo v1,Voo v2,int n)
{
    int v1Hora,v2Hora;
    /*devolve TRUE apenas se o v1 é mais recente que o v2*/
    if (n==PAR){ /*comando 'p'*/
        v1Hora=calculaHora(v1.horaPar);
        v2Hora=calculaHora(v2.horaPar);
        if (verificarPassado(v1.dataPar,v2.dataPar))
            return TRUE;
        else if (datasIguais(v1.dataPar,v2.dataPar) && 
                v2Hora<v1Hora)
            return TRUE;
    }
    /*devolve TRUE apenas se o v1 é mais recente que o v2*/
    else if(n==CHG){ /*comando 'c*/
        v1Hora=calculaHora(v1.horaChg);
        v2Hora=calculaHora(v2.horaChg);
        if (verificarPassado(v1.dataChg,v2.dataChg))
            return TRUE;
        else if (datasIguais(v1.dataChg,v2.dataChg) && 
                v2Hora<v1Hora)
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
    d1=calcularData(data1);
    d2=calcularData(data2);
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

int calcularData(Data d)
{
    int num;
    num=d.ano*10000+d.mes*100+d.dia;
    return num;
}

int calculaHora(Hora h)
 {
     return ((h.horas*HORA)+h.minutos);
 }

 void alteraData()
 {
    Data d;
    int verificacao;
    d=lerData();
    verificacao=verificacaoData(d);
    if (!verificacao){
        printf("invalid date\n");
        }
    else {
        dataAtual=d;
        escreveData(dataAtual);
    }
 }

noV * novoNoV(Voo v){
    noV *ptr;
    ptr=(noV *)malloc(sizeof(noV));
    ptr->v=v;
    ptr->proximo=NULL;
    return ptr;
}

noV * apagarListaV(noV * cabeca){
    noV * aux;
    while (cabeca){
        aux=cabeca->proximo;
        free(cabeca);
        cabeca=aux;
    }
    return NULL;
}

noV * inserirV(noV *cabeca,Voo v)
{
    noV * aux;
    if (cabeca==NULL)
        return novoNoV(v);
    for(aux=cabeca;aux->proximo!=NULL;aux=aux->proximo)
        ;
    aux->proximo=novoNoV(v);
    return cabeca;
}

noV * apagaCodigoVoo(char *codigo)
{
    noV *t,*ant,*aux;
    while (cabecaVoo!=NULL){
        if(strcmp(cabecaVoo->v.id,codigo)==0){
            aux=cabecaVoo;
            cabecaVoo=cabecaVoo->proximo;
            free(aux);
        }
    }
    if (cabecaVoo!=NULL){
        for(t=cabecaVoo->proximo,ant=cabecaVoo;t!=NULL;ant=t,t=t->proximo){
            if (strcmp(t->v.id,codigo)==0){
                ant->proximo=t->proximo;
                free(t);
                t=ant;
            }
        }
    }
    return cabecaVoo;
}

noR * novoNoR(char* codigoVoo,char *codigoRes,Data d,int num){
    noR *ptr;
    ptr=(noR *)malloc(sizeof(noR));
    ptr->res.codRes=(char *)malloc(sizeof(char)*(strlen(codigoRes)+1));
    strcpy(ptr->res.codVoo,codigoVoo);
    strcpy(ptr->res.codRes,codigoRes);
    ptr->res.dataVoo.dia=d.dia;
    ptr->res.dataVoo.mes=d.mes;
    ptr->res.dataVoo.ano=d.ano;
    ptr->res.numPas=num;
    ptr->proximo=NULL;
    return ptr;
}

noR * apagarListaR(noR * cabeca){
    noR * aux;
    while (cabeca){
        aux=cabeca->proximo;
        free(cabeca->res.codRes);
        free(cabeca);
        cabeca=aux;
    }
    return NULL;
}

noR * apagaCodigoReserva(noR *cabeca,char *codigo)
{
    noR *t,*ant;
    noV *voo;
    for(t=cabeca,ant=NULL;t!=NULL;ant=t, t=t->proximo)
    {
        if (strcmp(t->res.codRes,codigo)==0){
            if(t==cabeca)
                cabeca=t->proximo;
            else 
                ant->proximo=t->proximo;
            voo=encontraVoo(t->res.codVoo,t->res.dataVoo);
            voo->v.cp=voo->v.cp + t->res.numPas;
            free(t->res.codRes);
            free(t);
            break;
        }
    }
    return cabeca;
}

noR * apagaCodigoVooReserva(noR *cabeca,char *codigo)
{
    noR *t,*ant,*aux;
    while (cabeca!=NULL){
        if(strcmp(cabeca->res.codVoo,codigo)==0){
            aux=cabeca;
            cabeca=cabeca->proximo;
            free(aux->res.codRes);
            free(aux);
        }
    }
    if (cabeca!=NULL){
        for(t=cabeca->proximo,ant=cabeca;t!=NULL;ant=t,t=t->proximo){
            if (strcmp(t->res.codRes,codigo)==0){
                ant->proximo=t->proximo;
                free(t->res.codRes);
                free(t);
                t=ant;
            }
        }
    }
    return cabeca;
}

noR * adicionaReserva(noR * atual)
{
    noR *t,*ant;
    if(cabecaReserva==NULL)
    {
        return atual;
    }
    for(t=cabecaReserva,ant=NULL;t!=NULL;ant=t, t=t->proximo)
    {
        if (strcmp(atual->res.codRes,t->res.codRes)<0){
            if(t==cabecaReserva){
                atual->proximo=t;
                cabecaReserva=atual;
            }
            else{
                atual->proximo=t;
                ant->proximo=atual;
            }
            return cabecaReserva;
        }
    }
    ant->proximo=atual;
    return cabecaReserva;
}

void apagaCodigo()
{
    char codigo[LIM_INSTRUCAO];
    int len=0;
    
    scanf("%s",codigo);
    len=strlen(codigo);
    if (len<10){
        apagaVoo(codigo);
    }
    else{
        apagaReserva(codigo);
    }
}

int apagaVoo(char *codigo)
{
    noV * aux;
    int existe=FALSE;
    if(!verificarIDVoo(codigo)){
        printf("not found\n");
        return FALSE;
    }
    for(aux=cabecaVoo;aux!=NULL;aux=aux->proximo){
        if (!strcmp(codigo,aux->v.id)){
            existe=TRUE;
            break;
            }
        }
    if(existe){
        cabecaVoo=apagaCodigoVoo(codigo);
        cabecaReserva=apagaCodigoVooReserva(cabecaReserva,codigo);
        return TRUE;
    }
    else    
        printf("not found\n");
    return FALSE;
}

void apagaReserva(char *codigo)
{
    noR * aux;
    aux=encontraReserva(codigo);
    if(aux!=NULL){
        cabecaReserva=apagaCodigoReserva(cabecaReserva,codigo);
    }
    else
        printf("not found\n");
}

void adicionaListaReservas()
{
    char c;
    Data d;
    char codV[CODIGO_VOO],codR[LIM_INSTRUCAO];
    int num;
    noV *ptr2;
    noR *aux;
    scanf("%s %d-%d-%d",codV,&d.dia,&d.mes,&d.ano);
    if ((c=getchar())==' ' || c=='\t'){
        scanf("%s %d",codR,&num);
        aux=novoNoR(codV,codR,d,num);
        if (validaReserva(aux)){
            cabecaReserva=adicionaReserva(aux);
            ptr2=encontraVoo(codV,d);
            ptr2->v.cp=ptr2->v.cp-num;
        }
        else{
            free(aux->res.codRes);
            free(aux);
        }
    }
    else{
        if(validaEntradaVoo(codV,d)){
           listaReservas(codV,d); 
        }
    }
}

int validaReserva(noR *ptr)
{
    int i;
    noV * auxV;
    noR * auxR;
    for(i=0;ptr->res.codRes[i]!='\0';i++){
        if((ptr->res.codRes[i]<'0' || ptr->res.codRes[i]>'9') &&
            (ptr->res.codRes[i]<'A' || ptr->res.codRes[i]>'Z')){
                printf("invalid reservation code\n");
                return FALSE;
            }
    }
    if(i<10){
        printf("invalid reservation code\n");
        return FALSE;
    }
    auxV=encontraVoo(ptr->res.codVoo,ptr->res.dataVoo);
    if(auxV==NULL){
        printf("%s: flight does not exist\n",ptr->res.codVoo);
        return FALSE;
    }
    auxR=encontraReserva(ptr->res.codRes);
    if(auxR!=NULL){
        printf("%s: flight reservation already used\n",ptr->res.codRes);
        return FALSE;
    }
    if(auxV->v.cp < ptr->res.numPas){
        printf("too many reservations\n");
        return FALSE;
    }
    if (!verificacaoData(ptr->res.dataVoo)){
        printf("invalid date\n");
        return FALSE;
    }
    if(ptr->res.numPas<=0){
        printf("invalid passenger number\n");
        return FALSE;
    }
    return TRUE;
}

int validaEntradaVoo(char *codigo,Data d)
{
    noV *ptr=NULL;
    ptr=encontraVoo(codigo,d);
    if(ptr==NULL){
        printf("%s: flight does not exist\n",ptr->v.id);
        return FALSE;
    }
    if (!verificacaoData(ptr->v.dataPar)){
        printf("invalid date\n");
        return FALSE;
    }
    return TRUE;
}

noV * encontraVoo(char *codigo, Data d)
{
    noV *aux,*res=NULL;
    for(aux=cabecaVoo;aux!=NULL;aux=aux->proximo){
        if (strcmp(codigo,aux->v.id)==0 && 
            datasIguais(aux->v.dataPar,d)){
            res=aux;
            break;
            }
    }
    return res;
}

noR * encontraReserva(char *codigo)
{
    noR *aux,*res=NULL;
    for(aux=cabecaReserva;aux!=NULL;aux=aux->proximo){
        if (strcmp(codigo,aux->res.codRes)==0){
            res=aux;
            break;
            }
    }
    return res;
}

void listaReservas(char *codigo, Data d)
{
    noR *aux;
    for(aux=cabecaReserva;aux!=NULL;aux=aux->proximo)
    {
        if(strcmp(aux->res.codVoo,codigo)==0 && 
            datasIguais(d,aux->res.dataVoo))
        printf("%s %d\n",aux->res.codRes,aux->res.numPas);
    }
}
