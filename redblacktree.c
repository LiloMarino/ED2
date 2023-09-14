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
        Tree->No = No;
        VerificaRB(RBTree, No);
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
                    Conecta(RBTree, P, No, true);
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
                    Conecta(RBTree, P, No, false);
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
    if (Pai == NULL)
    {
        /*Caso 1*/
        /*Primeiro nó da árvore*/
        No->Preto = true;
        return;
    }
    else if (Pai->Preto)
    {
        /*Caso 2*/
        /*O pai é preto*/
        return;
    }
    else
    {
        NodeTree *Avo = Pai->Pai;
        NodeTree *Tio = (Avo->Esq == Pai) ? Avo->Dir : Avo->Esq; // Se o filho esquerdo do avô é o pai então o filho direito é o tio, senão o contrário
        PrintRB(Tree);
        if (Tio != NULL && !Tio->Preto)
        {
            /*Caso 3*/
            /*Pai e Tio são vermelhos*/
            Pai->Preto = true;
            Tio->Preto = true;
            Avo->Preto = false;
            VerificaRB(Tree, Avo);
        }
        else
        {
            /*Caso 4*/
            /*Pai é vermelho, mas o tio é preto ou nulo*/
            if (No == Pai->Dir && Pai == Avo->Esq)
            {
                /*Nó é filho da direita e pai da esquerda*/
                RotacionaEsquerda(Tree, No);
                VerificaRB(Tree, Pai);
            }
            else if (No == Pai->Esq && Pai == Avo->Dir)
            {
                /*Nó é filho da esquerda e pai da direita*/
                RotacionaDireita(Tree, No);
                VerificaRB(Tree, Pai);
            }
            else
            {
                /*Caso 5*/
                Pai->Preto = true;
                Avo->Preto = false;
                if (No == Pai->Esq && Pai == Avo->Esq)
                {
                    /*Nó é filho da esquerda e pai da esquerda*/
                    RotacionaDireita(Tree, Pai);
                }
                else
                {
                    /*Nó é filho da direita e pai da direita*/
                    RotacionaEsquerda(Tree, Pai);
                }
            }
        }
        PrintRB(Tree);
    }
}

void RotacionaDireita(DataStructure RBTree, Node N)
{
    NodeTree *No = N;
    NodeTree *Pai = No->Pai;
    NodeTree *Avo = Pai->Pai;
    Conecta(RBTree, Pai, No->Dir, true); // Verificar se está correto!
    Conecta(RBTree, No, Pai, false);
    Conecta(RBTree, Avo, No, false);
}

void RotacionaEsquerda(DataStructure RBTree, Node N)
{
    NodeTree *No = N;
    NodeTree *Pai = No->Pai;
    NodeTree *Avo = Pai->Pai;

    Conecta(RBTree, Pai, No->Esq, true);
    Conecta(RBTree, No, Pai, false);
    Conecta(RBTree, Avo, No, true);
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
        NodeTree *Irmao = (Pai->Dir == Rmv) ? Pai->Esq : Pai->Dir;
        if ((Rmv->Dir != NULL && !Rmv->Dir->Preto) || (Rmv->Esq != NULL && !Rmv->Esq->Preto))
        {
            /* 1 ou 2 Filhos Rubros */

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
        else if (Rmv->Dir == NULL && Rmv->Esq == NULL && Irmao != NULL && !Irmao->Preto)
        {
            /*Irmão é vermelho Caso 3.1*/
            Pai->Preto = false;
            Irmao->Preto = true;
            if (Pai->Esq == Rmv)
            {
                Pai->Dir = NULL;
                if (Irmao->Esq != NULL)
                {
                    Conecta(RBTree, Pai, Irmao->Esq, true);
                }
                Conecta(RBTree, Irmao, Pai, false);
            }
            else
            {
                Pai->Esq = NULL;
                if (Irmao->Dir != NULL)
                {
                    Conecta(RBTree, Pai, Irmao->Dir, true);
                }
                Conecta(RBTree, Irmao, Pai, true);
            }
            Pai->Dir = (Pai->Dir == Rmv) ? NULL : Pai->Dir;
            Pai->Esq = (Pai->Esq == Rmv) ? NULL : Pai->Esq;
            free(Rmv);
            return;
        }
        else if (Rmv->Dir == NULL && Rmv->Esq == NULL && Irmao == NULL || Irmao->Preto)
        {
            /*O irmão é preto e os filhos do irmão são pretos Caso 3.2*/
            Irmao->Preto = false;
            Pai->Dir = (Pai->Dir == Rmv) ? NULL : Pai->Dir;
            Pai->Esq = (Pai->Esq == Rmv) ? NULL : Pai->Esq;
            free(Rmv);
            return;
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

void Conecta(DataStructure RBTree, Node P, Node F, bool Dir)
{
    Raiz *Tree = RBTree;
    NodeTree *Pai = P;
    NodeTree *Filho = F;
    if (Pai == NULL)
    {
        Tree->No = Filho;
    }
    else
    {
        if (Dir)
        {
            Pai->Dir = Filho;
        }
        else
        {
            Pai->Esq = Filho;
        }
    }
    if (Filho != NULL)
    {
        Filho->Pai = Pai;
    }
}
