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
    InsereRB(RBTree,24);
    InsereRB(RBTree,10);
    InsereRB(RBTree,32);
    InsereRB(RBTree,5);
    CriaPngDot(FNARQDOT);
    FreeRB(&RBTree);

}