#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/*-------------------------Variaveis Globais-------------------------*/
extern int numAer; /*Numero de aeroportos*/
extern int numVoo; /*Numero de voos*/
extern Data dataAtual; /*Data do dia atual do sistema*/

/*Vetor dos dias finais de cada mes do ano*/
extern int diasDoMes[];
extern Aeroporto tabelaAeroporto[LIM_N_AER]; /*Vetor de todos os aeroportos*/
extern Voo tabelaVoo[LIM_N_VOO]; /*Vetor de todos os voos*/
/*-------------------------------------------------------------------*/

/*--------------------------------novoNoR------------------------------------
Cria um novo no para a lista das reservas
----------------------------------------------------------------------------*/


noR * novoNoR(char* codigoVoo,char *codigoRes,Data d,int num,noR *cabeca){
    noR *ptr;
    ptr=(noR *)malloc(sizeof(noR));
    if(ptr==NULL)
    {
        printf("No memory\n");
        apagarListaR(cabeca);
        exit(0);
    }
    ptr->res.codRes=(char *)malloc(sizeof(char)*(strlen(codigoRes)+1));
    if(ptr->res.codRes==NULL)
    {
        printf("No memory\n");
        apagarListaR(cabeca);
        exit(0);
    }
    strcpy(ptr->res.codVoo,codigoVoo);
    strcpy(ptr->res.codRes,codigoRes);
    ptr->res.dataVoo.dia=d.dia;
    ptr->res.dataVoo.mes=d.mes;
    ptr->res.dataVoo.ano=d.ano;
    ptr->res.numPas=num;
    ptr->proximo=NULL;
    return ptr;
}

/*--------------------------------apagarListaR-------------------------------
Esta funcao apaga toda a lista da reservas
----------------------------------------------------------------------------*/

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

/*---------------------------apagaCodigoReserva------------------------------
Esta funcao apaga da lista da reservas, uma reserva com o codigo fornecido
----------------------------------------------------------------------------*/

noR * apagaCodigoReserva(noR *cabeca,char *codigo)
{
    noR *t,*ant;
    int i;
    for(t=cabeca,ant=NULL;t!=NULL;ant=t, t=t->proximo)
    {
        if (strcmp(t->res.codRes,codigo)==0){
            if(t==cabeca) /*se for a cabeca*/
                cabeca=t->proximo;
            else /*se for outro caso*/
                ant->proximo=t->proximo;
            i=encontraVoo(t->res.codVoo,t->res.dataVoo);
            /*alteracao da capacidade*/
            tabelaVoo[i].cp=tabelaVoo[i].cp + t->res.numPas; 
            free(t->res.codRes);
            free(t);
            break;
        }
    }
    return cabeca;
}

/*---------------------------apagaCodigoVooReserva---------------------------
Esta funcao apaga da lista da reservas, uma reserva com o codigo de Voo
fornecido
----------------------------------------------------------------------------*/

noR * apagaCodigoVooReserva(noR *cabeca,char *codigo,Data data)
{
    noR *t,*ant,*aux;
    int done;
    while (cabeca!=NULL){ /*se as reservas forem a cabeca da lista*/
        done =FALSE;
        if(strcmp(cabeca->res.codVoo,codigo)==0 &&
            datasIguais(cabeca->res.dataVoo,data)){
            aux=cabeca;
            cabeca=cabeca->proximo;
            free(aux->res.codRes);
            free(aux);
            done=TRUE;
        }
        if (!done){
            break;
        }
    }/* corre o whilhe ate nao ser mais a cabeca*/
    if (cabeca!=NULL){ /*apaga qualquer outra reserva para alem da cabeca*/
        for(t=cabeca->proximo,ant=cabeca;t!=NULL;ant=t,t=t->proximo){
            if (strcmp(t->res.codRes,codigo)==0 &&
                datasIguais(cabeca->res.dataVoo,data)){
                ant->proximo=t->proximo;
                free(t->res.codRes);
                free(t);
                t=ant;
            }
        }
    }
    return cabeca;
}

/*------------------------------adicionaReserva-------------------------------
Esta funcao adiciona um no de reserva ah sua lista de forma ordenada
lexicográfica.
----------------------------------------------------------------------------*/

noR * adicionaReserva(noR * atual,noR *cabeca)
{
    noR *t,*ant;
    if(cabeca==NULL)
    {
        return atual;
    }
    else{
        for(t=cabeca,ant=NULL;t!=NULL;ant=t, t=t->proximo)
        {
            if (strcmp(atual->res.codRes,t->res.codRes)<0){
                /*ate ao momento que o proximo e "maior" que o atual*/
                if(t==cabeca){
                    atual->proximo=t;
                    cabeca=atual;
                }
                else{
                    atual->proximo=t;
                    ant->proximo=atual;
                }
                return cabeca;
            }
        }
    }
    ant->proximo=atual; /*se ficar na ultima posicao*/
    return cabeca;
}

/*--------------------------------apagaCodigo---------------------------------
Funcao utilizada para o comando e para eliminar um elemento com o codigo lido
----------------------------------------------------------------------------*/

noR* apagaCodigo(noR* cabeca)
{
    char codigo[LIM_INSTRUCAO];
    int len=0;
    
    scanf("%s",codigo);
    len=strlen(codigo);
    if (len<10){
        cabeca=apagaVoo(cabeca,codigo);
    }
    else{
        cabeca=apagaReserva(cabeca,codigo);
    }
    return cabeca;
}

/*--------------------------------apagaReserva-------------------------------
Funcao utilizada para eliminar uma reserva com o codigo fornecido
----------------------------------------------------------------------------*/

noR* apagaReserva(noR*cabeca,char *codigo)
{
    noR * aux;
    aux=encontraReserva(cabeca,codigo);
    if(aux!=NULL){
        cabeca=apagaCodigoReserva(cabeca,codigo);
    }
    else
        printf("not found\n");
    return cabeca;
}

/*------------------------------adicionaListaReservas------------------------
Esta funcao valida se a reserva introduzida e valida, e adiciona-a ah lista
de reservas caso seja, alterando a capacidade do voo, ou apenas lista todas
as reservas desse voo de forma ordenada lexicograficamente
----------------------------------------------------------------------------*/

noR* adicionaListaReservas(noR *cabeca)
{
    char c;
    Data d;
    char codV[CODIGO_VOO],codR[LIM_INSTRUCAO];
    int num,i;
    noR *aux;
    scanf("%s %d-%d-%d",codV,&d.dia,&d.mes,&d.ano);
    if ((c=getchar())==' ' || c=='\t'){
        scanf("%s %d",codR,&num);
        aux=novoNoR(codV,codR,d,num,cabeca); /*no da nova reserva*/
        if (validaReserva(aux,cabeca)){
            cabeca=adicionaReserva(aux,cabeca);
            i=encontraVoo(codV,d);
            tabelaVoo[i].cp=tabelaVoo[i].cp-num; /*alteracao da capacidade*/
        }
        else{ /*caso nao seja valido*/
            free(aux->res.codRes);
            free(aux);
        }
    }
    else{
        if(validaEntradaVoo(codV,d)){ 
        /*para listar todas as reservas de um voo*/
           listaReservas(cabeca,codV,d); 
        }
    }
    return cabeca;
}

/*--------------------------------validaReserva-------------------------------
Funcao utilizada para validar uma reserva
----------------------------------------------------------------------------*/

int validaReserva(noR *ptr,noR *cabeca)
{
    int i;
    int num;
    noR * auxR;
    if ((i=validaCodigoReserva(ptr->res.codRes))==FALSE){
            printf("invalid reservation code\n");
            return FALSE;
        }
    if(i<10){
        printf("invalid reservation code\n");
        return FALSE;
    }
    num=encontraVoo(ptr->res.codVoo,ptr->res.dataVoo);
    if(num==NAO_EXISTE){
        printf("%s: flight does not exist\n",ptr->res.codVoo);
        return FALSE;
    }
    auxR=encontraReserva(cabeca,ptr->res.codRes);
    if(auxR!=NULL){
        printf("%s: flight reservation already used\n",ptr->res.codRes);
        return FALSE;
    }
    if(tabelaVoo[num].cp < ptr->res.numPas){ 
        /*se ultrapassa a capacidade restante*/
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

/*--------------------------------validaCodigoReserva-------------------------
Devolve o length do codigo caso seja valido e FALSE caso contrario
----------------------------------------------------------------------------*/

int validaCodigoReserva (char *codigo)
{
    int i;
    for(i=0;codigo[i]!='\0';i++){
        if((codigo[i]<'0' || codigo[i]>'9') &&
            (codigo[i]<'A' || codigo[i]>'Z')){
                return FALSE;
            }
    }
    return i;
}
/*--------------------------------encontraReserva----------------------------
Encontra a reserva e devolve o ponteiro para tal
----------------------------------------------------------------------------*/

noR * encontraReserva(noR *cabeca,char *codigo)
{
    noR *aux,*res=NULL;
    for(aux=cabeca;aux!=NULL;aux=aux->proximo){
        if (strcmp(codigo,aux->res.codRes)==0){
            res=aux;
            break;
            }
    }
    return res;
}

/*--------------------------------listaReservas-------------------------------
Escreve todas as reservas do voo fornecido
----------------------------------------------------------------------------*/

void listaReservas(noR *cabeca,char *codigo, Data d)
{
    noR *aux;
    for(aux=cabeca;aux!=NULL;aux=aux->proximo)
    {
        if(strcmp(aux->res.codVoo,codigo)==0 && 
            datasIguais(d,aux->res.dataVoo))
        printf("%s %d\n",aux->res.codRes,aux->res.numPas);
    }
}

/*--------------------------------encontraVoo---------------------------------
Devolve o indice do Voo se existir, e devolve NAO_EXISTE caso contrario
----------------------------------------------------------------------------*/

int encontraVoo(char *codigo, Data d)
{
    int i,res=NAO_EXISTE;
    for(i=0;i<numVoo;i++){
        if(strcmp(tabelaVoo[i].id,codigo)==0 &&
            datasIguais(d,tabelaVoo[i].dataPar)){
                res=i;
                return res;
            }
    }
    return res;
}

/*--------------------------------validaEntradaVoo---------------------------
Valida de o codigo de voo e a sua data sao validas
----------------------------------------------------------------------------*/
int validaEntradaVoo(char *codigo,Data d)
{
    int num;
    num=encontraVoo(codigo,d);
    if(num==NAO_EXISTE){
        printf("%s: flight does not exist\n",codigo);
        return FALSE;
    }
    if (!verificacaoData(d)){
        printf("invalid date\n");
        return FALSE;
    }
    return TRUE;
}

/*----------------------------------apagaVoo----------------------------------
Apaga da tabelaVoo todos os voos com este codigo e da lista de reserva,
todas as reservas de todos os voos com este codigo
----------------------------------------------------------------------------*/

noR* apagaVoo(noR* cabeca,char *codigo)
{
    int existe,i;
    Voo *ptr;
    if(!verificarIDVoo(codigo)){
        printf("not found\n");
    }
    else{
        for(i=0;i<numVoo;i++){
            ptr=&tabelaVoo[i];
            tabelaVoo[i]=chegada(ptr);
        }
        /*falta criar algum tipo de ciclo dentro do if de forma a que se 
        eliminine todos os voos com data anterior*/
        existe=encontraVooCodigo(codigo);
        if(existe!=NAO_EXISTE){
            apagaCodigoVoo(codigo);
            cabeca=apagaCodigoVooReserva(cabeca,codigo,
                    tabelaVoo[existe].dataPar);
        }
        else    
            printf("not found\n");
    }
    return cabeca;
}

/*--------------------------------apagaCodigoVoo------------------------------
Apaga todos os voos da tabelaVoo com o mesmo codigo de voo
----------------------------------------------------------------------------*/

void apagaCodigoVoo(char *codigo)
{
    int i,n;
    while((n=encontraVooCodigo(codigo))!=NAO_EXISTE){
        if(n==numVoo-1){
            numVoo--;
        }
        else{
            numVoo--;
            for(i=n;i<numVoo;i++){
                tabelaVoo[i]=tabelaVoo[i+1];
            }
        }
    }
}

/*-----------------------------encontraVooCodigo------------------------------
Encontra e devolve o indice do primeiro voo com o codigo fornecido, caso 
contrario nao existe
----------------------------------------------------------------------------*/

int encontraVooCodigo(char *codigo)
{
    int i,res=NAO_EXISTE,dataatual,aux;
    dataatual=calcularData(dataAtual);
    for(i=0;i<numVoo;i++){
        aux=calcularData(tabelaVoo[i].dataChg);
        if(strcmp(tabelaVoo[i].id,codigo)==0 && aux<dataatual){
                res=i;
                return res;
            }
    }
    return res;
}
