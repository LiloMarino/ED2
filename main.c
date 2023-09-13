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



    InsereRB(RBTree,10);
    InsereRB(RBTree,8);
    // InsereRB(RBTree,12);
    // InsereRB(RBTree,7);
    // InsereRB(RBTree,9);
    // InsereRB(RBTree,11);
    // InsereRB(RBTree,14);
    // InsereRB(RBTree,6);
    // RemoveNodeRB(RBTree,12);
    // RemoveNodeRB(RBTree,14);
    // RemoveNodeRB(RBTree,11);
    CriaPngDot(FNARQDOT);
    FreeRB(&RBTree);

}