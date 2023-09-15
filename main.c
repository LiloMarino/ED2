#include "redblacktree.h"
#include "dot.h"
#include "Bibliotecas/geradores.h"

FILE *ARQDOT;
char *FNARQDOT;

int main()
{
    /*Inicia as operações da árvore e registra em vários .dot para a visualização separada*/

    FNARQDOT = "../logs/TesteRB";
    // InsereRB(RBTree,24);
    // InsereRB(RBTree,10);
    // InsereRB(RBTree,32);
    // InsereRB(RBTree,5);
    // InsereRB(RBTree,15);
    // InsereRB(RBTree,28);
    // InsereRB(RBTree,49);
    // InsereRB(RBTree,12);
    // InsereRB(RBTree,14);
    // //RemoveNodeRB(RBTree,15);
    // RemoveNodeRB(RBTree,10);
    // RemoveNodeRB(RBTree,32);

    DataStructure RBTree = NovaArvoreRB();
    InsereRB(RBTree, 1);
    InsereRB(RBTree, 2);
    InsereRB(RBTree, 3);
    FreeRB(&RBTree);
    RBTree = NovaArvoreRB();
    InsereRB(RBTree, 1);
    InsereRB(RBTree, 3);
    InsereRB(RBTree, 2);
    FreeRB(&RBTree);
    RBTree = NovaArvoreRB();
    InsereRB(RBTree, 3);
    InsereRB(RBTree, 2);
    InsereRB(RBTree, 1);
    FreeRB(&RBTree);
    RBTree = NovaArvoreRB();
    InsereRB(RBTree, 3);
    InsereRB(RBTree, 1);
    InsereRB(RBTree, 2);
    FreeRB(&RBTree);

    CriaPngDot(FNARQDOT);
}