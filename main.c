#include "avltree.h"
#include "dot.h"
#include "Bibliotecas/geradores.h"

FILE *ARQDOT;
char *FNARQDOT;

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
    DeleteDuplicates(FNARQDOT, "dot");
    FreeAVL(&AVLTree);

    /*Rotação LR*/
    AVLTree = NovaArvoreAVL();
    FNARQDOT = "../logs/RotacaoLR";

    InsereAVL(AVLTree,12);
    InsereAVL(AVLTree,5);
    InsereAVL(AVLTree,10);

    CriaPngDot(FNARQDOT);
    DeleteDuplicates(FNARQDOT, "dot");
    FreeAVL(&AVLTree);

    /*Rotação RR*/
    AVLTree = NovaArvoreAVL();
    FNARQDOT = "../logs/RotacaoRR";

    InsereAVL(AVLTree,5);
    InsereAVL(AVLTree,10);
    InsereAVL(AVLTree,12);

    CriaPngDot(FNARQDOT);
    DeleteDuplicates(FNARQDOT, "dot");
    FreeAVL(&AVLTree);

    /*Rotação RL*/
    AVLTree = NovaArvoreAVL();
    FNARQDOT = "../logs/RotacaoRL";

    InsereAVL(AVLTree,5);
    InsereAVL(AVLTree,12);
    InsereAVL(AVLTree,10);

    CriaPngDot(FNARQDOT);
    DeleteDuplicates(FNARQDOT, "dot");
    FreeAVL(&AVLTree);

    /*Exclusão em AVL*/
    AVLTree = NovaArvoreAVL();
    FNARQDOT = "../logs/Exclusao";

    InsereAVL(AVLTree,2);
    InsereAVL(AVLTree,4);
    InsereAVL(AVLTree,3);
    InsereAVL(AVLTree,1);
    InsereAVL(AVLTree,5);
    InsereAVL(AVLTree,6);

    CriaPngDot(FNARQDOT);
    DeleteDuplicates(FNARQDOT, "dot");
    FreeAVL(&AVLTree);
}