#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Bibliotecas/geradores.h"
#include "Bibliotecas/listadupla.h"
#include "redblacktree.h"
#include "dot.h"

struct StNodeTree
{
    TIPOCHAVE Chave;
    struct StNodeTree *Pai;
    struct StNodeTree *Dir;
    struct StNodeTree *Esq;
    bool vermelho;
};

struct StRaiz
{
    int NumTotalNos;
    struct StNodeTree *No;
};

typedef struct StNodeTree NodeTree;
typedef struct StRaiz Raiz;

DataStructure NovaArvoreRB()
{
    Raiz *Tree = calloc(1, sizeof(Raiz));
    return Tree;
}

Node InsereRB(DataStructure RBTree, TIPOCHAVE Chave)
{
    return Node();
}

Node GetNodeRB(DataStructure RBTree, TIPOCHAVE Chave)
{
    return Node();
}

TIPOCHAVE GetChaveRB(Node N)
{
    return TIPOCHAVE();
}

void RemoveNodeRB(DataStructure RBTree, TIPOCHAVE Chave)
{
}

void FreeRB(DataStructure *RBTree)
{
}

void PrintRB(DataStructure RBTree)
{
    ARQDOT = CriaLog(FNARQDOT, "dot");
    InicializaDot(ARQDOT);

    Raiz *Tree = RBTree;
    NodeTree *No = Tree->No;

    /*Percorre a árvore em largura criando os nós */
    Lista Stack = createLst(-1);
    insertLst(Stack, Tree->No);

    while (!isEmptyLst(Stack))
    {
        No = popLst(Stack);
        if (No->vermelho)
        {
            CriaNo(ARQDOT, No, "red");
        }
        else
        {
            CriaNo(ARQDOT, No, "black");
        }

        /*Insere os filhos do Nó para o Stack de verificação*/
        if (No->Dir != NULL)
        {
            insertLst(Stack, No->Dir);
        }
        if (No->Esq != NULL)
        {
            insertLst(Stack, No->Esq);
        }
    }
    killLst(Stack);

    /*Percorre a árvore em largura marcando as ligações*/
    Stack = createLst(-1);
    insertLst(Stack, Tree->No);
    LigaNo(ARQDOT, NULL, Tree->No);

    while (!isEmptyLst(Stack))
    {
        No = popLst(Stack);
        /*Marca as ligações do Nó no .dot*/
        LigaNo(ARQDOT, No, No->Esq);
        LigaNo(ARQDOT, No, No->Dir);

        /*Insere os filhos do Nó para o Stack de verificação*/
        if (No->Dir != NULL)
        {
            insertLst(Stack, No->Dir);
        }
        if (No->Esq != NULL)
        {
            insertLst(Stack, No->Esq);
        }
    }
    killLst(Stack);

    TerminaDot(ARQDOT);
}
