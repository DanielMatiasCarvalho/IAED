/*-------------------------------Projeto 2------------------------------------
Neste projeto, pretende-se a construção de um sistema de gestão de voos,
possuindo a definicao de voos, aeroportos, a consulta ao mesmos, a criacao
de reservas para voos,eliminacao de voos e de reservas.
Autor:Daniel Carvalho
Número: 102556
Ultima atualizacao: 18-04-2022 16:00
-----------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

int main()
{
    char c;
    noR *cabecaReserva=NULL; /*Cabeca da lista de todas as reservas*/
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
            case 'r': cabecaReserva=adicionaListaReservas(cabecaReserva);
                    break;
            case 'e': cabecaReserva=apagaCodigo(cabecaReserva);
                    break;
            }
    }
    apagarListaR(cabecaReserva);
    return 0;
}