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
    int Hmax; // Profundidade máxima da subárvore pertencente ao nó
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
    No->Hmax = 1;

    /*Atribui o nó a árvore*/
    if (Tree->No == NULL)
    {
        /*Primeiro nó da árvore*/
        Tree->No = No;
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
                    /*Insere*/
                    P->Dir = No;
                    No->Pai = P;
                    do
                    {
                        P->Hmax = GetHmaxAVL(P);
                        if (GetFbAVL(P) == 2 || GetFbAVL(P) == -2)
                        {
                            NodeTree *Pai = P->Pai;
                            AjustaAVL(AVLTree, P);
                            P = Pai;
                        }
                        else
                        {
                            P = P->Pai;
                        }
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
                    /*Insere*/
                    P->Esq = No;
                    No->Pai = P;
                    do
                    {
                        P->Hmax = GetHmaxAVL(P);
                        if (GetFbAVL(P) == 2 || GetFbAVL(P) == -2)
                        {
                            NodeTree *Pai = P->Pai;
                            AjustaAVL(AVLTree, P);
                            P = Pai;
                        }
                        else
                        {
                            P = P->Pai;
                        }
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
                printf("Erro: Chave %d já existe na árvore\n", Chave);
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

int GetHmaxAVL(Node N)
{
    NodeTree *No = N;
    int HmaxDir = (No->Dir != NULL) ? No->Dir->Hmax : 0;
    int HmaxEsq = (No->Esq != NULL) ? No->Esq->Hmax : 0;
    int Hmax = ((HmaxDir > HmaxEsq) ? HmaxDir : HmaxEsq) + 1;
    return Hmax;
}

int GetFbAVL(Node N)
{
    NodeTree *No = N;
    int HmaxDir = (No->Dir != NULL) ? No->Dir->Hmax : 0;
    int HmaxEsq = (No->Esq != NULL) ? No->Esq->Hmax : 0;
    int Fb = HmaxDir - HmaxEsq;
    return Fb;
}

void RemoveNodeAVL(DataStructure AVLTree, TIPOCHAVE Chave)
{
    PrintAVL(AVLTree);
    bool Print = true;
    Raiz *Tree = AVLTree;
    NodeTree *Rmv = GetNodeAVL(AVLTree, Chave);
    NodeTree *P = Rmv->Pai;
    if (Rmv == NULL)
    {
        printf("Erro: A chave %d não existe\n", Chave);
        return;
    }

    if (Rmv->Dir == NULL && Rmv->Esq == NULL)
    {
        /*Nó não tem filhos*/
        if (Rmv->Pai != NULL)
        {
            if (Rmv->Pai->Dir == Rmv)
            {
                /* Rmv é filho direito */
                Rmv->Pai->Dir = NULL;
            }
            else
            {
                /* Rmv é filho esquerdo */
                Rmv->Pai->Esq = NULL;
            }
        }
        else
        {
            /* A árvore se torna vazia */
            Tree->No = NULL;
        }
        Tree->NumTotalNos -= 1;
        free(Rmv);
    }
    else
    {
        /* O nó tem pelo menos 1 filho */

        /* Verifica se Rmv possui 2 filhos */
        if (Rmv->Dir != NULL && Rmv->Esq != NULL)
        {
            /*Possui 2 filhos*/

            /*Procura o filho maior à esquerda*/
            NodeTree *MaiorEsq = Rmv->Esq;
            while (MaiorEsq->Dir != NULL)
            {
                MaiorEsq = MaiorEsq->Dir;
            }
            TIPOCHAVE Aux = MaiorEsq->Chave;
            RemoveNodeAVL(AVLTree, Aux);
            Rmv->Chave = Aux;
        }
        else
        {
            /*Possui apenas 1 filho*/
            /*Verifica se o nó é filho direito ou filho esquerdo ou se ele é o primeiro nó*/
            if (Rmv->Pai != NULL)
            {
                if (Rmv->Pai->Dir == Rmv)
                {
                    /* Rmv é filho direito */
                    Rmv->Pai->Dir = (Rmv->Esq != NULL) ? Rmv->Esq : Rmv->Dir;
                    Rmv->Pai->Dir->Pai = Rmv->Pai;
                }
                else
                {
                    /* Rmv é filho esquerdo */
                    Rmv->Pai->Esq = (Rmv->Esq != NULL) ? Rmv->Esq : Rmv->Dir;
                    Rmv->Pai->Esq->Pai = Rmv->Pai;
                }
            }
            else
            {
                /* É o primeiro nó */
                Tree->No = (Rmv->Esq != NULL) ? Rmv->Esq : Rmv->Dir;
            }
            Tree->NumTotalNos -= 1;
            free(Rmv);
        }
    }

    /* Verifica se a árvore não foi desbalanceada e atualiza os Hmax */
    while (P != NULL)
    {
        P->Hmax = GetHmaxAVL(P);
        if (GetFbAVL(P) == 2 || GetFbAVL(P) == -2)
        {
            NodeTree *Pai = P->Pai;
            AjustaAVL(AVLTree, P);
            Print = false;
            P = Pai;
        }
        else
        {
            P = P->Pai;
        }
    }

    if (Print)
    {
        PrintAVL(AVLTree);
    }
}

void FreeAVL(DataStructure *AVLTree)
{
    Raiz *Tree = *AVLTree;
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
    PrintAVL(AVLTree);
    Raiz *Tree = AVLTree;
    NodeTree *P = N;
    NodeTree *U;
    NodeTree *V;
    if (GetFbAVL(P) > 0)
    {
        /* Positivo então direita */
        U = P->Dir;
        if (GetFbAVL(U) > 0)
        {
            /* Positivo então direita */
            V = U->Dir;

            /*Rotação RR*/
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
            if (P->Dir != NULL)
            {
                P->Dir->Pai = P;
            }

            U->Hmax += 1;
            P->Hmax -= 2;
        }
        else
        {
            /* Negativo então esquerda */
            V = U->Esq;

            /*Rotação RL*/
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
            P->Dir = V->Esq;
            U->Esq = V->Dir;
            V->Dir = U;
            U->Pai = V;
            V->Esq = P;
            P->Pai = V;
            if (P->Dir != NULL)
            {
                P->Dir->Pai = P;
            }
            if (U->Esq != NULL)
            {
                U->Esq->Pai = U;
            }

            V->Hmax += 1;
            U->Hmax -= 1;
            P->Hmax -= 2;
        }
    }
    else
    {
        /* Negativo então esquerda */
        U = P->Esq;
        if (GetFbAVL(U) > 0)
        {
            /* Positivo então direita */
            V = U->Dir;

            /*Rotação LR*/
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
            U->Dir = V->Esq;
            P->Esq = V->Dir;
            V->Dir = P;
            P->Pai = V;
            V->Esq = U;
            U->Pai = V;
            if (P->Esq != NULL)
            {
                P->Esq->Pai = P;
            }
            if (U->Dir != NULL)
            {
                U->Dir->Pai = U;
            }

            V->Hmax += 1;
            U->Hmax -= 1;
            P->Hmax -= 2;
        }
        else
        {
            /* Negativo então esquerda */
            V = U->Esq;

            /*Rotação LL*/
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
            if (P->Esq != NULL)
            {
                P->Esq->Pai = P;
            }

            U->Hmax += 1;
            P->Hmax -= 2;
        }
    }
    PrintAVL(AVLTree);
}

void PrintAVL(DataStructure AVLTree)
{
    ARQDOT = CriaLog(FNARQDOT, "dot");
    InicializaDot(ARQDOT);

    Raiz *Tree = AVLTree;
    NodeTree *No = Tree->No;
    LigaNo(ARQDOT, NULL, Tree->No);

    /*Insere o primeiro Nó no Stack de verificação*/
    Lista Stack = createLst(-1);
    insertLst(Stack, No);

    /*Percorre a árvore em largura marcando as ligações*/
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
