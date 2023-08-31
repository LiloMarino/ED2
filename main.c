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
    ARQDOT = CriaLog(FNARQDOT, "dot");
    InicializaDot(ARQDOT);

    InsereAVL(AVLTree,12);
    InsereAVL(AVLTree,10);
    InsereAVL(AVLTree,5);

    TerminaDot(ARQDOT);
    CriaPngDot(FNARQDOT);
    FreeAVL(&AVLTree);

    /*Rotação LR*/
    AVLTree = NovaArvoreAVL();
    FNARQDOT = "../logs/RotacaoLR";
    ARQDOT = CriaLog(FNARQDOT, "dot");
    InicializaDot(ARQDOT);

    InsereAVL(AVLTree,12);
    InsereAVL(AVLTree,5);
    InsereAVL(AVLTree,10);

    TerminaDot(ARQDOT);
    CriaPngDot(FNARQDOT);
    FreeAVL(&AVLTree);

    /*Rotação RR*/
    AVLTree = NovaArvoreAVL();
    FNARQDOT = "../logs/RotacaoRR";
    ARQDOT = CriaLog(FNARQDOT, "dot");
    InicializaDot(ARQDOT);

    InsereAVL(AVLTree,5);
    InsereAVL(AVLTree,10);
    InsereAVL(AVLTree,12);

    TerminaDot(ARQDOT);
    CriaPngDot(FNARQDOT);
    FreeAVL(&AVLTree);

    /*Rotação RL*/
    AVLTree = NovaArvoreAVL();
    FNARQDOT = "../logs/RotacaoRL";
    ARQDOT = CriaLog(FNARQDOT, "dot");
    InicializaDot(ARQDOT);

    InsereAVL(AVLTree,5);
    InsereAVL(AVLTree,12);
    InsereAVL(AVLTree,10);

    TerminaDot(ARQDOT);
    CriaPngDot(FNARQDOT);
    FreeAVL(&AVLTree);

    /*Exclusão em AVL*/
    AVLTree = NovaArvoreAVL();
    FNARQDOT = "../logs/Exclusao";
    ARQDOT = CriaLog(FNARQDOT, "dot");
    InicializaDot(ARQDOT);

    InsereAVL(AVLTree,2);
    InsereAVL(AVLTree,4);
    InsereAVL(AVLTree,3);
    InsereAVL(AVLTree,1);
    InsereAVL(AVLTree,5);
    InsereAVL(AVLTree,6);

    TerminaDot(ARQDOT);
    CriaPngDot(FNARQDOT);
    FreeAVL(&AVLTree);

    /*Realiza todos os frees*/
}