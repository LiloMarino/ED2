#include "tabelahash.h"
#include "dot.h"
#include "Bibliotecas/geradores.h"

FILE *ARQDOT;
char *FNARQDOT;

int main()
{
    /*Inicia as operações da tabela hash e registra em vários .dot para a visualização separada*/
    FNARQDOT = "../logs/TesteHash";


    CriaPngDot(FNARQDOT);
}