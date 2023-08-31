#include "avltree.h"
#include "dot.h"
#include "Bibliotecas/geradores.h"

FILE *ARQDOT;
char *FNARQDOT;

int main()
{
    /*Inicia as operações da árvore e registra em vários .dot para a visualização separada*/

    /*Rotação LL*/
    DataStructure AVL1 = NovaArvoreAVL();
    FNARQDOT = "../logs/RotacaoLL";
    ARQDOT = CriaLog(FNARQDOT, "dot");
    InicializaDot(ARQDOT);



    TerminaDot(ARQDOT);
    CriaPngDot(FNARQDOT);
    FreeAVL(AVL1);

    /*Rotação LR*/
    DataStructure AVL2 = NovaArvoreAVL();
    FNARQDOT = "../logs/RotacaoLR";
    ARQDOT = CriaLog(FNARQDOT, "dot");
    InicializaDot(ARQDOT);



    TerminaDot(ARQDOT);
    CriaPngDot(FNARQDOT);
    FreeAVL(AVL2);

    /*Rotação RR*/
    DataStructure AVL3 = NovaArvoreAVL();
    FNARQDOT = "../logs/RotacaoRR";
    ARQDOT = CriaLog(FNARQDOT, "dot");
    InicializaDot(ARQDOT);



    TerminaDot(ARQDOT);
    CriaPngDot(FNARQDOT);
    FreeAVL(AVL3);

    /*Rotação RL*/
    DataStructure AVL4 = NovaArvoreAVL();
    FNARQDOT = "../logs/RotacaoRL";
    ARQDOT = CriaLog(FNARQDOT, "dot");
    InicializaDot(ARQDOT);


    TerminaDot(ARQDOT);
    CriaPngDot(FNARQDOT);
    FreeAVL(AVL4);

    /*Exclusão em AVL*/
    DataStructure AVL5 = NovaArvoreAVL();
    FNARQDOT = "../logs/Exclusao";
    ARQDOT = CriaLog(FNARQDOT, "dot");
    InicializaDot(ARQDOT);



    TerminaDot(ARQDOT);
    CriaPngDot(FNARQDOT);
    FreeAVL(AVL5);

    /*Realiza todos os frees*/
}