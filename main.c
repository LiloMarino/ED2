#include "redblacktree.h"
#include "dot.h"
#include "Bibliotecas/geradores.h"

FILE *ARQDOT;
char *FNARQDOT;

int main()
{
    /*Inicia as operações da árvore e registra em vários .dot para a visualização separada*/

    FNARQDOT = "../logs/TesteRB";

    DataStructure RBTree = NovaArvoreRB();
    InsereRB(RBTree, 24);
    InsereRB(RBTree, 10);
    InsereRB(RBTree, 32);
    InsereRB(RBTree, 5);
    InsereRB(RBTree, 15);
    InsereRB(RBTree, 28);
    InsereRB(RBTree, 49);
    InsereRB(RBTree, 12);
    InsereRB(RBTree, 14);
    RemoveRB(RBTree, 15);
    RemoveRB(RBTree, 10);
    RemoveRB(RBTree, 32);
    FreeRB(&RBTree);
    CriaPngDot(FNARQDOT);
}