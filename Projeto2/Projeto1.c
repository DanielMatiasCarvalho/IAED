#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/*-------------------------Variaveis Globais-------------------------*/
int numAer=0; /*Numero de aeroportos*/
int numVoo=0; /*Numero de voos*/
Data dataAtual={1,1,2022}; /*Data do dia atual do sistema*/

/*vetor dos dias finais de cada mes do ano*/
int diasDoMes[]={31,28,31,30,31,30,31,31,30,31,30,31};
Aeroporto tabelaAeroporto[LIM_N_AER]; /*Vetor de todos os aeroportos*/
Voo tabelaVoo[LIM_N_VOO]; /*Vetor de todos os voos*/
/*-------------------------------------------------------------------*/

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
esse aeroporto é adicionado ao vetor de todos os aeroportos, acrescentando
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

/*-----------------------------aeroportoInvalido-------------------------------
Verifica se o ID introduzido no stdin e passado para a funcao
e valido em todos os seus parametros, devolvendo TRUE ou FALSE
-----------------------------------------------------------------------------*/

int aeroportoInvalido(char *id)
{
    int i;
    for (i=0;i<ID_AER-1;i++)
        if(id[i]<'A' || id[i]>'Z'){
            return TRUE;
        }
    return FALSE;
}

/*-----------------------------aeroportoDuplicado------------------------------
Verifica se o ID introduzido no stdin e passado para a funcao
ja existe no vetor de todos os aeroportos, devolvendo TRUE ou FALSE
-----------------------------------------------------------------------------*/

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

/*-----------------------------listaAeroportos---------------------------------
Funcao utilizada no comando l para determinar se sera escrito no standard
output os aeroportos e o seu numero de voos introduzidos ou todos
-----------------------------------------------------------------------------*/

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
        res=compararAeroportos(id); /*verifica se ID de aeroporto existe*/
        if (res){
            voo=numeroVoos(id); /*numero de voos do aeroporto lido*/
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

/*----------------------------escreverAerVoos----------------------------------
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

/*--------------------------adicionaListaVoos----------------------------------
Funcao associada ao comando v tal que decide se lista todos os voos ou se
verifica o voo introduzido no std output, validado-se a sua possibilidade
de introduzi-lo no vetor dos voos
-----------------------------------------------------------------------------*/

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
Esta funcao le do satndard input um variavel voo e verifica se as componentes
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
        if (v.cp<CP_MIN){
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
Faz a verificacao se o codigo do voo ja existe na mesma data de partida
-----------------------------------------------------------------------------*/

int verificarVoosIguais(Voo *voo)
{
    int i;
    for(i=0;i<numVoo;i++){
        if(strcmp(voo->id,tabelaVoo[i].id)==0 && 
            datasIguais(voo->dataPar,tabelaVoo[i].dataPar)==TRUE){
            printf("flight already exists\n");
            return FALSE;
        }
    }
    return TRUE;
}

/*---------------------------verificarIDVoo-------------------------------
Faz a verificacao se o codigo do voo introduzido e valido
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
    int i;
    Voo* ptr;
    for (i=0;i<numVoo;i++){
        ptr=&tabelaVoo[i];
        escreverVoo(ptr);
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
Esta funcao recebe a data introduzida pelo standard input,
verificando se esta nao e passado da data atual nem que a ultrapassa em mais
de um ano, devolvendo FALSE se tal e TRUE caso seja valida
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
Esta funcao recebe um ponteiro de uma estrutura de voo, escrevendo no standard
output as suas componentes
-----------------------------------------------------------------------------*/

void escreverVoo(Voo *ptr)
{
    printf("%s %s %s %02d-%02d-%02d %02d:%02d\n",ptr->id,ptr->idpar,
                                                ptr->idchg,
                                                ptr->dataPar.dia,
                                                ptr->dataPar.mes,
                                                ptr->dataPar.ano,
                                                ptr->horaPar.horas,
                                                ptr->horaPar.minutos);
}

/*----------------------------obter_voos_aer-----------------------------------
Esta funcao recebe um inteiro, que representa se se trata de um ID de um 
aeroporto de partida (comando 'p') ou de chegada (comando 'c'). Apos verificar
se o ID e de um aeroporto, e passado o id para novas funcoes, uma para as 
partidas (comando 'p') e outra para as chegas (comando 'c') ou, caso 
contrario, indica um erro e termina a funcao
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

/*----------------------------listaVoosPartida---------------------------------
Esta funcao recebe um id de um aeroporto de partida, e devolve de forma 
ordenada por data e hora os voos com partida nesse aeroporto,
escrevendo para o standard output tal
-----------------------------------------------------------------------------*/

void listaVoosPartida(char *id)
{
    int i,len=0;
    Voo vooAer[LIM_N_VOO];
    for (i=0;i<numVoo;i++) /*criacao do vetor auxiliar*/
        if (!strcmp(id,tabelaVoo[i].idpar)){
            vooAer[len]=tabelaVoo[i];
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

/*----------------------------listaVoosPartida---------------------------------
Esta funcao recebe um id de um aeroporto de chegada, e devolve de forma 
ordenada por data e hora os voos com chegada nesse aeroporto,
escrevendo para o standard output tal
-----------------------------------------------------------------------------*/

void listaVoosChegada(char *id)
{
    int i,len=0;
    Voo vooAer[LIM_N_VOO]; /*criacao do vetor auxiliar*/
    Voo *ptr=NULL;
    for (i=0;i<numVoo;i++){
        if (!strcmp(id,tabelaVoo[i].idchg)){
            vooAer[len]=tabelaVoo[i];
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
Esta funcao recebe um ponteiro de um Voo, 
calculando de seguida a data e a hora de chegada, desse mesmo voo
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
a data1 e superior ah data2, ou seja, que e mais recente
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

/*--------------------------------calcularData---------------------------------
Esta funcao recebe uma data, tranformando-a num inteiro
-----------------------------------------------------------------------------*/

int calcularData(Data d)
{
    int num;
    num=d.ano*10000+d.mes*100+d.dia;
    return num;
}

/*--------------------------------calcularHora---------------------------------
Esta funcao recebe uma hora, tranformando-a num inteiro
-----------------------------------------------------------------------------*/

int calculaHora(Hora h)
 {
     return ((h.horas*HORA)+h.minutos);
 }

/*--------------------------------alteraData---------------------------------
Esta funcao le uma data, valida-a e se for valida troca a atual por ela
----------------------------------------------------------------------------*/

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
