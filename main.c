#include "avltree.h"
#include "dot.h"
#include "Bibliotecas/geradores.h"

FILE *ARQDOT;
char *FNARQDOT;
#define TESTE 1

int main()
{
    DataStructure AVLTree = NovaArvoreAVL();
    FNARQDOT = "../logs/Teste";

    InsereAVL(AVLTree,8);
    InsereAVL(AVLTree,3);
    InsereAVL(AVLTree,14);
    InsereAVL(AVLTree,7);
    InsereAVL(AVLTree,5);
    InsereAVL(AVLTree,17);
    InsereAVL(AVLTree,6);
    InsereAVL(AVLTree,10);
    InsereAVL(AVLTree,16);
    InsereAVL(AVLTree,9);
    InsereAVL(AVLTree,11);
    InsereAVL(AVLTree,4);
    InsereAVL(AVLTree,13);
    InsereAVL(AVLTree,2);
    InsereAVL(AVLTree,12);
    InsereAVL(AVLTree,1);
    InsereAVL(AVLTree,15);

    CriaPngDot(FNARQDOT);
    FreeAVL(&AVLTree);
}

#if TESTE == 0
int main()
{
    /*Inicia as operações da árvore e registra em vários .dot para a visualização separada*/

    /*Rotação LL*/
    DataStructure AVLTree = NovaArvoreAVL();
    FNARQDOT = "../logs/RotacaoLL";

    InsereAVL(AVLTree,12);
    InsereAVL(AVLTree,10);
    InsereAVL(AVLTree,5);

    CriaPngDot(FNARQDOT);
    FreeAVL(&AVLTree);

    /*Rotação LR*/
    AVLTree = NovaArvoreAVL();
    FNARQDOT = "../logs/RotacaoLR";

    InsereAVL(AVLTree,12);
    InsereAVL(AVLTree,5);
    InsereAVL(AVLTree,10);

    CriaPngDot(FNARQDOT);
    FreeAVL(&AVLTree);

    /*Rotação RR*/
    AVLTree = NovaArvoreAVL();
    FNARQDOT = "../logs/RotacaoRR";

    InsereAVL(AVLTree,5);
    InsereAVL(AVLTree,10);
    InsereAVL(AVLTree,12);

    CriaPngDot(FNARQDOT);
    FreeAVL(&AVLTree);

    /*Rotação RL*/
    AVLTree = NovaArvoreAVL();
    FNARQDOT = "../logs/RotacaoRL";

    InsereAVL(AVLTree,5);
    InsereAVL(AVLTree,12);
    InsereAVL(AVLTree,10);

    CriaPngDot(FNARQDOT);
    FreeAVL(&AVLTree);

    /*Exclusão em AVL*/
    AVLTree = NovaArvoreAVL();
    FNARQDOT = "../logs/Exclusao";

    InsereAVL(AVLTree,15);
    InsereAVL(AVLTree,8);
    InsereAVL(AVLTree,23);
    InsereAVL(AVLTree,2);
    InsereAVL(AVLTree,20);
    InsereAVL(AVLTree,12);
    RemoveNodeAVL(AVLTree,15);

    CriaPngDot(FNARQDOT);
    FreeAVL(&AVLTree);
}
#endif