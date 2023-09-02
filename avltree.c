#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Bibliotecas/geradores.h"
#include "Bibliotecas/listadupla.h"
#include "avltree.h"
#include "dot.h"

struct StNodeTree
{
    TIPOCHAVE Chave;
    struct StNodeTree *Pai;
    struct StNodeTree *Dir;
    struct StNodeTree *Esq;
    int Fb;
};

struct StRaiz
{
    int NumTotalNos;
    struct StNodeTree *No;
};

typedef struct StNodeTree NodeTree;
typedef struct StRaiz Raiz;

DataStructure NovaArvoreAVL()
{
    Raiz *Tree = calloc(1, sizeof(Raiz));
    return Tree;
}

Node InsereAVL(DataStructure AVLTree, TIPOCHAVE Chave)
{
    Raiz *Tree = AVLTree;

    /*Inicializa o nó*/
    Tree->NumTotalNos += 1;
    NodeTree *No = calloc(1, sizeof(NodeTree));
    No->Chave = Chave;

    /*Atribui o nó a árvore*/
    if (Tree->No == NULL)
    {
        /*Primeiro nó da árvore*/
        Tree->No = No;
        LigaNo(ARQDOT, NULL, No);
    }
    else
    {
        /*Procura a posição que nó pertence e o insere*/
        NodeTree *P = Tree->No;
        do
        {
            if (P->Chave < Chave)
            {
                /* Se é maior então direita */
                if (P->Dir == NULL)
                {
                    P->Dir = No;
                    LigaNo(ARQDOT, P, No);
                    No->Pai = P;
                    do
                    {
                        P->Fb += 1;
                        if (P->Fb == 2)
                        {
                            AjustaAVL(AVLTree, P);
                        }
                        P = P->Pai;
                    } while (P != NULL);
                    return No;
                }
                else
                {
                    P = P->Dir;
                }
            }
            else if (P->Chave > Chave)
            {
                /* Se é menor então esquerda */
                if (P->Esq == NULL)
                {
                    P->Esq = No;
                    LigaNo(ARQDOT, P, No);
                    No->Pai = P;
                    do
                    {
                        P->Fb -= 1;
                        if (P->Fb == -2)
                        {
                            AjustaAVL(AVLTree, P);
                        }
                        P = P->Pai;
                    } while (P != NULL);
                    return No;
                }
                else
                {
                    P = P->Esq;
                }
            }
            else
            {
                /* Não pode ser igual */
                printf("Erro: Chave já existe na árvore\n");
                free(No);
                Tree->NumTotalNos -= 1;
                return NULL;
            }
        } while (true);
    }
    return No;
}

Node GetNodeAVL(DataStructure AVLTree, TIPOCHAVE Chave)
{
    /*Procura o nó com a Chave especificada*/
    Raiz *Tree = AVLTree;
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

TIPOCHAVE GetChaveAVL(Node N)
{
    NodeTree *No = N;
    return No->Chave;
}

int GetFbAVL(Node N)
{
    NodeTree *No = N;
    return No->Fb;
}

void RemoveNodeAVL(DataStructure AVLTree, Node N)
{
}

void FreeAVL(DataStructure *AVLTree)
{
    Raiz *Tree = *AVLTree;
    NodeTree *No = Tree->No;
    NodeTree *Clear = NULL;
    while (Tree->NumTotalNos != 0)
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
                *AVLTree = NULL;
                return;
            }
        }
    }
    /*Árvore vazia*/
    free(Tree);
    *AVLTree = NULL;
    return;
}

void AjustaAVL(DataStructure AVLTree, Node N)
{
    Raiz *Tree = AVLTree;
    NodeTree *P = N;
    NodeTree *U;
    NodeTree *V;
    if (P->Fb > 0)
    {
        /* Positivo então direita */
        U = P->Dir;
        if (U->Fb > 0)
        {
            /* Positivo então direita */
            V = U->Dir;

            /*Rotacao RR*/
            if (P->Pai != NULL)
            {
                if (P->Pai->Dir == P)
                {
                    /* P é filho direito */
                    P->Pai->Dir = U;
                }
                else
                {
                    /* P é filho esquerdo */
                    P->Pai->Esq = U;
                }
            }
            else
            {
                /* Se torna o primeiro elemento */
                Tree->No = U;
            }
            P->Dir = U->Esq;
            U->Pai = P->Pai;
            U->Esq = P;
            P->Pai = U;
        }
        else
        {
            /* Negativo então esquerda */
            V = U->Esq;

            /*Rotacao RL*/
            if (P->Pai != NULL)
            {
                if (P->Pai->Dir == P)
                {
                    /* P é filho direito */
                    P->Pai->Dir = V;
                }
                else
                {
                    /* P é filho esquerdo */
                    P->Pai->Esq = V;
                }
            }
            else
            {
                /* Se torna o primeiro elemento */
                Tree->No = V;
            }
            V->Pai = P->Pai;
            V->Esq = P;
            P->Pai = V;
            V->Dir = U;
            U->Pai = V;
        }
    }
    else
    {
        /* Negativo então esquerda */
        U = P->Esq;
        if (U->Fb > 0)
        {
            /* Positivo então direita */
            V = U->Dir;

            /*Rotacao LR*/
            if (P->Pai != NULL)
            {
                if (P->Pai->Dir == P)
                {
                    /* P é filho direito */
                    P->Pai->Dir = V;
                }
                else
                {
                    /* P é filho esquerdo */
                    P->Pai->Esq = V;
                }
            }
            else
            {
                /* Se torna o primeiro elemento */
                Tree->No = V;
            }
            V->Pai = P->Pai;
            V->Esq = U;
            U->Pai = V;
            V->Dir = P;
            P->Pai = V;
        }
        else
        {
            /* Negativo então esquerda */
            V = U->Esq;

            /*Rotacao LL*/
            if (P->Pai != NULL)
            {
                if (P->Pai->Dir == P)
                {
                    /* P é filho direito */
                    P->Pai->Dir = U;
                }
                else
                {
                    /* P é filho esquerdo */
                    P->Pai->Esq = U;
                }
            }
            else
            {
                /* Se torna o primeiro elemento */
                Tree->No = U;
            }
            P->Esq = U->Dir;
            U->Pai = P->Pai;
            U->Dir = P;
            P->Pai = U;
        }
    }
    PrintAVL(AVLTree);
}

void PrintAVL(DataStructure AVLTree)
{
    TerminaDot(ARQDOT);
    ARQDOT = CriaLog(FNARQDOT, "dot");
    InicializaDot(ARQDOT);

    Raiz *Tree = AVLTree;
    NodeTree *No = Tree->No;
    Lista Stack = createLst(-1);
    /*Insere o primeiro Nó no Stack de verificação*/
    insertLst(Stack, No);

    /*Percorre a árvore em largura marcando as ligações*/
    while (!isEmptyLst(Stack))
    {
        No = popLst(Stack);
        /*Marca as ligações do Nó no .dot*/
        LigaNo(ARQDOT, No, No->Dir);
        LigaNo(ARQDOT, No, No->Esq);

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
}
