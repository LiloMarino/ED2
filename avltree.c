#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Bibliotecas/geradores.h"
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
        LigaNo(ARQDOT, No, NULL);
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
                    LigaNo(ARQDOT, No, P);
                    do
                    {
                        P->Fb += 1;
                        if (P->Fb == 2)
                        {
                            AjustaAVL(P);
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
                    LigaNo(ARQDOT, No, P);
                    do
                    {
                        P->Fb -= 1;
                        if (P->Fb == -2)
                        {
                            AjustaAVL(P);
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

void AjustaAVL(Node N)
{
    TerminaDot(ARQDOT);
    ARQDOT = CriaLog(FNARQDOT, "dot");
    InicializaDot(ARQDOT);
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
            U->Pai = P->Pai;
            LigaNo(ARQDOT, U, P->Pai);
            U->Esq = P;
            LigaNo(ARQDOT, U, P);
            P->Pai = U;
            LigaNo(ARQDOT, P, U);
        }
        else
        {
            /* Negativo então esquerda */
            V = U->Esq;

            /*Rotacao RL*/
            V->Pai = P->Pai;
            LigaNo(ARQDOT, V, P->Pai);
            V->Esq = P;
            LigaNo(ARQDOT, V, P);
            P->Pai = V;
            LigaNo(ARQDOT, P, V);
            V->Dir = U;
            LigaNo(ARQDOT, V, U);
            U->Pai = V;
            LigaNo(ARQDOT, U, V);
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
            V->Pai = P->Pai;
            LigaNo(ARQDOT, V, P->Pai);
            V->Esq = U;
            LigaNo(ARQDOT, V, U);
            U->Pai = V;
            LigaNo(ARQDOT, U, V);
            V->Dir = P;
            LigaNo(ARQDOT, V, P);
            P->Pai = V;
            LigaNo(ARQDOT, P, V);
        }
        else
        {
            /* Negativo então esquerda */
            V = U->Esq;

            /*Rotacao LL*/
            U->Pai = P->Pai;
            LigaNo(ARQDOT, U, P->Pai);
            U->Dir = P;
            LigaNo(ARQDOT, U, P);
            P->Pai = U;
            LigaNo(ARQDOT, P, U);
        }
    }
}