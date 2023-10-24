#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grafos.h"
#include "Bibliotecas/listadupla.h"

struct Vertice {
    int valor;
    struct Vertice** vertices;
} 

struct Grafo {
    int numVertices;
    struct Vertice** vertices;
}

typedef struct Vertice;
typedef struct Grafo;


DataStructure criarGrafo() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;

    for (int i = 0; i < numVertices; ++i) {
        graph->adjacencyList[i] = NULL;
    }

    return graph;
}

void adicionarVertice(Graph* graph, int src, int dest) {
    // Adiciona a aresta de src para dest
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = dest;
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;

    // Adiciona a aresta de dest para src (grafo não direcionado)
    newNode = (Node*)malloc(sizeof(Node));
    newNode->data = src;
    newNode->next = graph->adjacencyList[dest];
    graph->adjacencyList[dest] = newNode;

    
    /*Inicializa o nó*/
    Tree->numTotalNos += 1;
    NodeTree *No = calloc(1, sizeof(NodeTree));
    No->x = x;
    No->y = y;
    No->info = i;
    No->filhos = malloc(Tree->numSetores * sizeof(NodeTree *));
    for (int i = 0; i < Tree->numSetores; i++)
    {
        No->filhos[i] = NULL;
    }
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

/**
 * @brief Desaloca a memória alocada pelo nó da árvore
 * @param n Nó da árvore radial
 */
void freeNode(Node n, bool ClearTotal)
{
    NodeTree *No = n;
    if (ClearTotal)
    {
        FreeFigura(No->info); // Atenção aqui, é necessário analisar esta parte dependendo da informação contida no nó
        No->info = NULL;
    }
    free(No->filhos);
    free(No);
}

/**
 * @brief Realiza o free na árvore
 * @param t Endereço para a árvore radial
 * @param ClearTotal Diz se é para dar free() até nos conteúdos dos nós desalocando tudo para o término do programa
 * ou se é apenas para dar free() para a reconstrução da árvore
 */
void freeRadialTree(RadialTree t, bool ClearTotal)
{
    /** @warning É necessário passar o endereço do ponteiro da árvore para esta função*/
    Raiz *Tree = *((Raiz **)t);
    NodeTree *No = Tree->node;
    NodeTree *Clear = NULL;
    int i;
    while (Tree->numTotalNos != 0)
    {
        bool Vazio = true;
        for (i = 0; i < Tree->numSetores; i++)
        {
            if (No->filhos[i] != NULL)
            {
                Vazio = false;
                break;
            }
        }
        if (Vazio)
        {
            /*Nó não tem filhos*/
            Clear = No;
            No = No->pai;
            freeNode(Clear, ClearTotal);
            if (No != NULL)
            {
                /*Atribui NULL ao filho desalocado*/
                for (i = 0; i < Tree->numSetores; i++)
                {
                    if (No->filhos[i] != NULL)
                    {
                        No->filhos[i] = NULL;
                        break;
                    }
                }
            }
            else
            {
                /*Nó raiz*/
                Tree->node = NULL;
                free(Tree);
                *(void **)t = NULL;
                return;
            }
        }
        else
        {
            /*Primeiro filho diferente de NULL encontrado do nó*/
            No = No->filhos[i];
        }
    }
}