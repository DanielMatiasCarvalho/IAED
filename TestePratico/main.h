#ifndef MAIN_H
#define MAIN_H

#define LIM_N_AER 40 /*Limite do numero de aeroportos*/
#define DENTRO 3000 /*Utilizada para ler do stdin a cidade do aeroporto*/
#define FORA 4000 /*Utilizada para ler do stdin a cidade do aeroporto*/
#define ID_AER 4 /*Limite do tamanho da string do ID do aeroporto*/
#define PAIS 31 /*Limite do tamanho da string do pais*/
#define CIDADE 51 /*Limite do tamanho da string da cidade*/
#define TRUE 1
#define FALSE 0
#define CODIGO_VOO 9 /*Limite do vetor do codigo dos voos*/
#define LIM_N_VOO 30000 /*Numero maximo de voos aceites*/
#define MAX_DUR_VOO 12 /*Duração maxima de um voo*/
#define CP_MIN 10 /*Capacidade minima de um voo*/
#define PAR 1000 /*Constate auxiliar das funções do comando 'p',indicando que*/
                /*se trata dos aeroportos de partida*/
#define CHG 2000 /*Constate auxiliar das funções do comando 'c',indicando que*/ 
                /*se trata dos aeroportos de chegada*/
#define DIA 24 /*Horas de um dia*/
#define HORA 60 /*Minutos de uma hora*/
#define LIM_INSTRUCAO 65536 /*Limite de caracteres de uma instrucao*/
#define NAO_EXISTE -1 /*caso uma variavel nao exista*/

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

typedef struct stru_noR {
    Reserva res;
    struct stru_noR *proximo;
}noR;

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
void escreverVoo(Voo *v);
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
void apagaCodigoVoo(char *codigo);
noR * novoNoR(char* codigoVoo,char *codigoRes,Data d,int num,noR *cabeca);
noR * apagarListaR(noR * cabeca);
noR * apagaCodigoReserva(noR *cabeca,char *codigo);
noR * apagaCodigoVooReserva(noR *cabeca,char *codigo, Data data);
noR* apagaCodigo(noR *cabeca);
noR* apagaVoo(noR *cabeca,char *codigo);
noR* apagaReserva(noR* cabeca,char *codigo);
noR * adicionaReserva(noR *atual,noR *cabeca);
noR* adicionaListaReservas(noR *cabeca);
int validaReserva(noR *ptr,noR *cabeca);
int encontraVoo(char *codigo, Data d);
noR * encontraReserva(noR *cabeca,char *codigo);
int validaEntradaVoo(char *codigo,Data d);
void listaReservas(noR *cabeca,char *codigo, Data d);
int validaCodigoReserva (char *codigo);
int encontraVooCodigo(char *codigo);

#endif