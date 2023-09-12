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
    bool Preto;
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
    NodeTree *No = calloc(1, sizeof(NodeTree)); // Como é calloc já atribui por padrão vermelho ao nó, ou seja, preto = false = 0 e !preto = vermelho
    No->Chave = Chave;

    /*Atribui o nó a árvore*/
    if (Tree->No == NULL)
    {
        /*Primeiro nó da árvore*/
        No->Preto = true;
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
                    VerificaRB(RBTree, No);
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
                    VerificaRB(RBTree, No);
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

void VerificaRB(DataStructure RBTree, Node N)
{
    Raiz *Tree = RBTree;
    NodeTree *No = N;
    NodeTree *Pai = No->Pai;
    if (Pai->Preto)
    {
        /*Caso 0*/
        return;
    }
    else
    {
        PrintRB(RBTree);
        NodeTree *Avo = Pai->Pai;
        NodeTree *Bisavo = (Avo != NULL) ? Avo->Pai : NULL;
        NodeTree *Tio = (Avo->Esq == Pai) ? Avo->Dir : Avo->Esq; // Se o filho esquerdo do avô é o pai então o filho direito é o tio, senão o contrário
        if (Tio != NULL && !Tio->Preto)
        {
            /*Caso 1*/
            Pai->Preto = !Pai->Preto;
            Avo->Preto = (Bisavo != NULL) ? !Avo->Preto : true; // Se Bisavô é NULL então é a raiz
            Tio->Preto = !Tio->Preto;
            if (Bisavo == NULL || Bisavo->Preto)
            {
                PrintRB(RBTree);
                return;
            }
            else
            {
                printf("ZIKOU\n");
            }
        }
        else if (Tio == NULL || Tio->Preto)
        {
            if (Pai->Esq == No)
            {
                /*Caso 3*/
                if (Bisavo != NULL)
                {
                    if (Bisavo->Dir == Avo)
                    {
                        Bisavo->Dir = Pai;
                    }
                    else
                    {
                        Bisavo->Esq = Pai;
                    }
                }
                else
                {
                    Tree->No = Pai;
                }
                Pai->Pai = Bisavo;
                if (Avo->Dir == Pai)
                {
                    Avo->Dir = NULL;
                }
                else
                {
                    Avo->Esq = NULL;
                }
                Pai->Dir = Avo;
                Avo->Pai = Pai;
                /*Recolori*/
                Pai->Preto = true;
                Avo->Preto = false;
                PrintRB(RBTree);
                return;
            }
            else if (Pai->Dir == No)
            {
                /*Caso 2*/
                Pai->Dir = NULL;
                if (Tio == Avo->Dir)
                {
                    Avo->Esq = No;
                }
                else
                {
                    Avo->Dir = No;
                }
                No->Pai = Avo;
                No->Esq = Pai;
                Pai->Pai = No;
                PrintRB(RBTree);
                VerificaRB(RBTree, Pai);
                return;
            }
        }
    }
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
    Raiz *Tree = RBTree;
    NodeTree *Rmv = GetNodeRB(RBTree, Chave);
    NodeTree *Pai = Rmv->Pai;
    if (Rmv == NULL)
    {
        printf("Erro: A chave %d não existe\n", Chave);
        return;
    }
    PrintRB(RBTree);
    if (!Rmv->Preto)
    {
        if (Rmv->Dir == NULL && Rmv->Esq == NULL)
        {
            /*Nó não tem filhos*/
            if (Pai != NULL)
            {
                if (Pai->Dir == Rmv)
                {
                    /* Rmv é filho direito */
                    Pai->Dir = NULL;
                }
                else
                {
                    /* Rmv é filho esquerdo */
                    Pai->Esq = NULL;
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
            /*Procura o sucessor*/
            NodeTree *Sucessor = Rmv->Dir;
            while (Sucessor->Esq != NULL)
            {
                Sucessor = Sucessor->Esq;
            }
            TIPOCHAVE Aux = Sucessor->Chave;
            RemoveNodeRB(RBTree, Aux);
            /*Altera o valor da chave pela chave do sucessor*/
            Rmv->Chave = Aux;
        }
    }
    else
    {
        if (Rmv->Dir != NULL && !Rmv->Dir->Preto && Rmv->Esq != NULL && !Rmv->Esq->Preto)
        {
            /* 2 Filhos Rubros */
            
            /*Procura o sucessor*/
            NodeTree *Sucessor = Rmv->Dir;
            while (Sucessor->Esq != NULL)
            {
                Sucessor = Sucessor->Esq;
            }
            TIPOCHAVE Aux = Sucessor->Chave;
            RemoveNodeRB(RBTree, Aux);
            /*Altera o valor da chave pela chave do sucessor*/
            Rmv->Chave = Aux;
        }
        else
        {
            printf("ZIKOU!\n");
        }
    }
    PrintRB(RBTree);
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

    /*Percorre a árvore em largura criando os nós marcando as ligações*/
    Lista Stack = createLst(-1);
    insertLst(Stack, Tree->No);
    LigaNo(ARQDOT, NULL, Tree->No);

    while (!isEmptyLst(Stack))
    {
        No = popLst(Stack);
        /*Marca as ligações do Nó no .dot*/
        LigaNo(ARQDOT, No, No->Esq);
        LigaNo(ARQDOT, No, No->Dir);
        if (No->Preto)
        {
            CriaNo(ARQDOT, No, "black");
        }
        else
        {
            CriaNo(ARQDOT, No, "red");
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

    TerminaDot(ARQDOT);
}
