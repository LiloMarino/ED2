#include "redblacktree.h"
#include "dot.h"
#include "Bibliotecas/geradores.h"

FILE *ARQDOT;
char *FNARQDOT;

int main()
{
    /*Inicia as operações da árvore e registra em vários .dot para a visualização separada*/

    DataStructure RBTree = NovaArvoreRB();
    FNARQDOT = "../logs/TesteRB";

    CriaPngDot(FNARQDOT);
    FreeRB(&RBTree);

}