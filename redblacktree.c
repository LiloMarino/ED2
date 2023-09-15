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
        VerificaInsertRB(RBTree, No);
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
                    VerificaInsertRB(RBTree, No);
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
                    VerificaInsertRB(RBTree, No);
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

void VerificaInsertRB(DataStructure RBTree, Node N)
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
            VerificaInsertRB(Tree, Avo);
        }
        else
        {
            /*Caso 4*/
            /*Pai é vermelho, mas o tio é preto ou nulo*/
            if (No == Pai->Dir && Pai == Avo->Esq)
            {
                /*Nó é filho da direita e pai da esquerda*/
                RotacionaEsquerda(Tree, Pai);
                VerificaInsertRB(Tree, Pai);
            }
            else if (No == Pai->Esq && Pai == Avo->Dir)
            {
                /*Nó é filho da esquerda e pai da direita*/
                RotacionaDireita(Tree, Pai);
                VerificaInsertRB(Tree, Pai);
            }
            else
            {
                /*Caso 5*/
                Pai->Preto = true;
                Avo->Preto = false;
                if (No == Pai->Esq && Pai == Avo->Esq)
                {
                    /*Nó é filho da esquerda e pai da esquerda*/
                    RotacionaDireita(Tree, Avo);
                }
                else
                {
                    /*Nó é filho da direita e pai da direita*/
                    RotacionaEsquerda(Tree, Avo);
                }
            }
        }
        PrintRB(Tree);
    }
}

void RotacionaEsquerda(DataStructure RBTree, Node N)
{
    Raiz *Tree = RBTree;
    NodeTree *No = N;
    NodeTree *Pai = No->Pai;
    NodeTree *FilhoDir = No->Dir;

    /*Tecnicamente consiste em trocar de posição o FilhoDir com o No
    Quem é Pai de No passará a ser Pai de FilhoDir e FilhoDir passará a ser pai de No*/
    Conecta(Tree, No, FilhoDir->Esq, true);                        // Para não perder nó, o No adota na sua direita o filho esquerdo do FilhoDir "Menor à direita"
    Conecta(Tree, Pai, FilhoDir, (Pai != NULL && No == Pai->Dir)); // O Pai de No adotará na mesma posição que No o filho direito de No, PAI -> FD
    Conecta(Tree, FilhoDir, No, false);                            // O filho direito de No adotará em sua esquerda o próprio No, pois FD > N
}

void RotacionaDireita(DataStructure RBTree, Node N)
{
    Raiz *Tree = RBTree;
    NodeTree *No = N;
    NodeTree *Pai = No->Pai;
    NodeTree *FilhoEsq = No->Esq;

    /*Tecnicamente consiste em trocar de posição o FilhoEsq com o No
    Quem é Pai de No passará a ser Pai de FilhoEsq e FilhoEsq passará a ser pai de No*/
    Conecta(Tree, No, FilhoEsq->Dir, false);                       // Para não perder nó, o No adota na sua esquerda o filho direito do FilhoEsq "Maior à esquerda"
    Conecta(Tree, Pai, FilhoEsq, (Pai != NULL && No == Pai->Dir)); // O Pai de No adotará na mesma posição que No o filho esquerdo de No, PAI -> FE
    Conecta(Tree, FilhoEsq, No, true);                             // O filho esquerdo de No adotará em sua direita o próprio No, pois FE < N
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

void RemoveRB(DataStructure RBTree, TIPOCHAVE Chave)
{
    Raiz *Tree = RBTree;
    NodeTree *Rmv = GetNodeRB(Tree, Chave);
    NodeTree *Pai = Rmv->Pai;
    if (Rmv == NULL)
    {
        printf("Erro: A chave %d não existe\n", Chave);
        return;
    }
    PrintRB(Tree);

    if (Rmv->Esq == NULL || Rmv->Dir == NULL)
    {
        /* Caso 1: O nó não possui filhos ou apenas um filho não nulo */
        NodeTree *Filho = (Rmv->Esq == NULL) ? Rmv->Dir : Rmv->Esq;
        Conecta(Tree, Pai, Filho, (Pai != NULL && Rmv == Pai->Dir)); // O pai do nó removido adotará o filho não nulo do nó

        /*Se o nó removido era preto, chama FixRemoveRB para corrigir*/
        if (Rmv->Preto)
        {
            if (Filho != NULL && !Filho->Preto)
            {
                Filho->Preto = true;
            }
            else
            {
                FixRemoveRB(Tree, Rmv);
            }
        }
        free(Rmv);
        Tree->NumTotalNos -= 1;
    }
    else
    {
        /* Caso 2: O nó possui dois filhos */
        NodeTree *Sucessor = Rmv->Dir;
        while (Sucessor->Esq != NULL)
        {
            Sucessor = Sucessor->Esq;
        }
        TIPOCHAVE Aux = Sucessor->Chave;
        RemoveRB(Tree, Sucessor->Chave);
        Rmv->Chave = Aux;
    }
    PrintRB(Tree);
}

void FixRemoveRB(DataStructure RBTree, Node N)
{
    Raiz *Tree = RBTree;
    NodeTree *No = N;

    if (Tree->No == NULL)
    {
        /*Removeu o último nó*/
        return;
    }

    while (No != Tree->No && (No == NULL || No->Preto))
    {
        /*Verifica se irmão é filho direito ou esquerdo*/
        if (No == No->Pai->Esq || No->Pai->Esq == NULL)
        {
            NodeTree *Irmao = No->Pai->Dir;

            if (Irmao == NULL)
            {
                return;
            }

            /*Caso 1: O irmão é vermelho*/
            if (!Irmao->Preto)
            {
                Irmao->Preto = true;
                No->Pai->Preto = false;
                RotacionaEsquerda(Tree, No->Pai);
                Irmao = No->Pai->Dir;
            }

            /*Caso 2: Ambos os filhos do irmão são pretos*/
            if ((Irmao->Esq == NULL || Irmao->Esq->Preto) && (Irmao->Dir == NULL || Irmao->Dir->Preto))
            {
                Irmao->Preto = false;
                No = No->Pai;
            }
            else
            {
                /*Caso 3: O filho direito do irmão é preto*/
                if (Irmao->Dir == NULL || Irmao->Dir->Preto)
                {
                    Irmao->Esq->Preto = true;
                    Irmao->Preto = false;
                    RotacionaDireita(Tree, Irmao);
                    Irmao = No->Pai->Dir;
                }

                /*Caso 4: O filho direito do irmão é vermelho*/
                Irmao->Preto = No->Pai->Preto;
                No->Pai->Preto = true;
                Irmao->Dir->Preto = true;
                RotacionaEsquerda(Tree, No->Pai);
                No = Tree->No; // Isso sai do loop
            }
        }
        else
        {
            NodeTree *Irmao = No->Pai->Esq;

            if (Irmao == NULL)
            {
                return;
            }

            /* Caso 1: O irmão é vermelho*/
            if (!Irmao->Preto)
            {
                Irmao->Preto = true;
                No->Pai->Preto = false;
                RotacionaDireita(Tree, No->Pai);
                Irmao = No->Pai->Esq;
            }

            /* Caso 2: Ambos os filhos do irmão são pretos*/
            if ((Irmao->Dir == NULL || Irmao->Dir->Preto) && (Irmao->Esq == NULL || Irmao->Esq->Preto))
            {
                Irmao->Preto = false;
                No = No->Pai;
            }
            else
            {
                /* Caso 3: O filho esquerdo do irmão é preto*/
                if (Irmao->Esq == NULL || Irmao->Esq->Preto)
                {
                    Irmao->Dir->Preto = true;
                    Irmao->Preto = false;
                    RotacionaEsquerda(Tree, Irmao);
                    Irmao = No->Pai->Esq;
                }

                /* Caso 4: O filho esquerdo do irmão é vermelho*/
                Irmao->Preto = No->Pai->Preto;
                No->Pai->Preto = true;
                Irmao->Esq->Preto = true;
                RotacionaDireita(Tree, No->Pai);
                No = Tree->No; // Isso sai do loop
            }
        }
    }

    if (No != NULL)
    {
        No->Preto = true;
    }
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
    if (Tree->No != NULL)
    {
        insertLst(Stack, Tree->No);
    }
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
