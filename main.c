#include "tabelahash.h"
#include "dot.h"
#include "Bibliotecas/geradores.h"
#include "Bibliotecas/utilities.h"

FILE *ARQDOT;
char *FNARQDOT;

int main()
{
    /*Inicia as operações da tabela hash e registra em vários .dot para a visualização separada*/
    FNARQDOT = "../logs/TesteHash";
    DataStructure HTable = HashCreate(20);
    InicializaRand();
    HashInsert(HTable,11233);
    for (int i = 0; i < 100; i++)
    {
        int n = GerarNumeroInt(0,1000000);
        HashInsert(HTable,n);
        if (Chance(0.1))
        {
            PrintHash(HTable);
            HashRemove(HTable,n);
        }
    }
    PrintHash(HTable);
    HashFree(&HTable);
    CriaPngDot(FNARQDOT);
}