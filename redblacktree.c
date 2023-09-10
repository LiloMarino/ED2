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
    Raiz *Tree = RBTree;

    /*Inicializa o nó*/
    Tree->NumTotalNos += 1;
    NodeTree *No = calloc(1, sizeof(NodeTree));
    No->Chave = Chave;
}

Node GetNodeRB(DataStructure RBTree, TIPOCHAVE Chave)
{
    /*Procura o nó com a Chave especificada*/
    Raiz *Tree = RBTree;
    NodeTree *P = Tree->No;
    do
    {
        if (P->Chave == Chave)
        {
            /* É igual, portanto, retorna*/
            return P;
        }
        else
        {
            if (P->Chave < Chave)
            {
                /* Se é maior então direita */
                P = P->Dir;
            }
            else if (P->Chave > Chave)
            {
                /* Se é menor então esquerda */
                P = P->Esq;
            }
        }
    } while (P != NULL);
    return NULL;
}

TIPOCHAVE GetChaveRB(Node N)
{
    NodeTree *No = N;
    return No->Chave;
}

void RemoveNodeRB(DataStructure RBTree, TIPOCHAVE Chave)
{
}

void FreeRB(DataStructure *RBTree)
{
    Raiz *Tree = *RBTree;
    NodeTree *No = Tree->No;
    NodeTree *Clear = NULL;
    while (Tree->NumTotalNos > 0)
    {
        bool Vazio = true;
        if (No->Dir != NULL)
        {
            /*Primeiro filho diferente de NULL encontrado do nó*/
            No = No->Dir;
            Vazio = false;
        }
        else if (No->Esq != NULL)
        {
            /*Primeiro filho diferente de NULL encontrado do nó*/
            No = No->Esq;
            Vazio = false;
        }
        if (Vazio)
        {
            /*Nó não tem filhos*/
            Clear = No;
            No = No->Pai;
            free(Clear);
            Tree->NumTotalNos -= 1;
            if (No != NULL)
            {
                /*Atribui NULL ao filho desalocado*/
                if (No->Dir != NULL)
                {
                    No->Dir = NULL;
                }
                else if (No->Esq != NULL)
                {
                    No->Esq = NULL;
                }
            }
            else
            {
                /*Nó raiz*/
                free(Tree);
                *RBTree = NULL;
                return;
            }
        }
    }
    /*Árvore vazia*/
    free(Tree);
    *RBTree = NULL;
    return;
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
