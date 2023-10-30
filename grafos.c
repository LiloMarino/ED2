#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "grafos.h"
#include "dotgrafos.h"
#include "Bibliotecas/listadupla.h"
#include "Bibliotecas/geradores.h"

struct StVertice
{
    int valor;
    int numArestas;
    struct StAresta *arestas;
};

struct StAresta
{
    int peso;
    struct StVertice *vertice;
};

struct StGrafo
{
    bool direcionado;
    int numVertices;
    struct StVertice **vertices;
};

struct StVerifica
{
    int valor;
    bool verificado;
};

typedef struct StVertice Vertice;
typedef struct StAresta Aresta;
typedef struct StGrafo Grafo;
typedef struct StVerifica Verifica;

DataStructure criarGrafo(bool direcionado)
{
    Grafo *grafo = calloc(1, sizeof(Grafo));
    grafo->direcionado = direcionado;
    return grafo;
}

bool existsVerticeIn(DataStructure grafo, int vertice)
{
    Grafo *G = grafo;
    for (int i = 0; i < G->numVertices; i++)
    {
        if (G->vertices[i]->valor == vertice)
        {
            return true;
        }
    }
    return false;
}

Node searchVertice(DataStructure grafo, int vertice)
{
    Grafo *G = grafo;
    for (int i = 0; i < G->numVertices; i++)
    {
        if (G->vertices[i]->valor == vertice)
        {
            return G->vertices[i];
        }
    }
    return NULL;
}

int searchVerticeID(DataStructure grafo, int vertice)
{
    Grafo *G = grafo;
    for (int i = 0; i < G->numVertices; i++)
    {
        if (G->vertices[i]->valor == vertice)
        {
            return i;
        }
    }
    return -1;
}

void adicionarVertice(DataStructure grafo, int src, int dest, int peso)
{
    Grafo *G = grafo;
    bool foundSrc = existsVerticeIn(G, src);
    bool foundDest = existsVerticeIn(G, dest);
    if (!foundSrc)
    {
        /* Criar um novo vértice e inserir no array de vertices do grafo */
        Vertice *v = calloc(1, sizeof(Vertice));
        v->valor = src;
        G->numVertices++;
        G->vertices = realloc(G->vertices, G->numVertices * sizeof(Vertice *));
        G->vertices[G->numVertices - 1] = v;
    }
    if (!foundDest)
    {
        /* Criar um novo vértice e inserir no array de vertices do grafo */
        Vertice *v = calloc(1, sizeof(Vertice));
        v->valor = dest;
        G->numVertices++;
        G->vertices = realloc(G->vertices, G->numVertices * sizeof(Vertice *));
        G->vertices[G->numVertices - 1] = v;
    }
    /* Adiciona a aresta entre os dois vértices */
    Vertice *S = NULL;
    Vertice *D = NULL;
    for (int i = 0; i < G->numVertices; i++)
    {
        if (G->vertices[i]->valor == src)
        {
            S = G->vertices[i];
        }

        if (G->vertices[i]->valor == dest)
        {
            D = G->vertices[i];
        }
    }
    S->numArestas++;
    S->arestas = realloc(S->arestas, S->numArestas * sizeof(Aresta));
    S->arestas[S->numArestas - 1].vertice = D;
    S->arestas[S->numArestas - 1].peso = peso;
    if (!G->direcionado)
    {
        /*Se não for direcionado então faz a ligação de volta*/
        D->numArestas++;
        D->arestas = realloc(D->arestas, D->numArestas * sizeof(Aresta));
        D->arestas[D->numArestas - 1].vertice = S;
        D->arestas[D->numArestas - 1].peso = peso;
    }
}

void freeGrafo(DataStructure grafo)
{
    Grafo *G = grafo;
    for (int i = 0; i < G->numVertices; i++)
    {
        free(G->vertices[i]->arestas);
        free(G->vertices[i]);
    }
    free(G->vertices);
    free(G);
}

void buscarGrafoLargura(DataStructure grafo, int inicio)
{
    if (!existsVerticeIn(grafo, inicio))
    {
        printf("Não exite o vértice %d no grafo\n", inicio);
        return;
    }

    Grafo *G = grafo;
    Vertice *V = searchVertice(G, inicio);
    ARQDOT = CopiaDot(FNARQDOT);

    Verifica vrfy[G->numVertices];
    for (int i = 0; i < G->numVertices; i++)
    {
        vrfy[i].valor = G->vertices[i]->valor;
        vrfy[i].verificado = false;
    }
    vrfy[searchVerticeID(G, V->valor)].verificado = true;

    Lista Stack = createLst(-1);
    insertLst(Stack, V);
    while (!isEmptyLst(Stack))
    {
        V = popLst(Stack);
        CriaVertice(ARQDOT, V->valor, "green");
        /*Insere os Arestas conectadas para o Stack de verificação*/
        for (int i = 0; i < V->numArestas; i++)
        {
            int index = searchVerticeID(G, V->arestas[i].vertice->valor);
            if (!vrfy[index].verificado)
            {
                vrfy[index].verificado = true;
                insertLst(Stack, V->arestas[i].vertice);
            }
        }
        TerminaDot(ARQDOT);
        ARQDOT = CopiaDot(FNARQDOT);
    }
    TerminaDot(ARQDOT);
    killLst(Stack);
}

void printGrafo(DataStructure grafo)
{
    Grafo *G = grafo;
    Vertice *V = G->vertices[0];
    ARQDOT = CriaLog(FNARQDOT, "dot");
    InicializaDot(ARQDOT, G->direcionado);

    Verifica vrfy[G->numVertices];
    for (int i = 0; i < G->numVertices; i++)
    {
        vrfy[i].valor = G->vertices[i]->valor;
        vrfy[i].verificado = false;
    }
    vrfy[0].verificado = true;

    Lista Stack = createLst(-1);
    insertLst(Stack, V);
    while (!isEmptyLst(Stack))
    {
        V = popLst(Stack);
        /*Insere os Arestas conectadas para o Stack de verificação*/
        for (int i = 0; i < V->numArestas; i++)
        {
            int j;
            for (j = 0; j < G->numVertices; j++)
            {
                if (vrfy[j].valor == V->arestas[i].vertice->valor)
                {
                    break;
                }
            }
            if (!vrfy[j].verificado)
            {
                vrfy[j].verificado = true;
                insertLst(Stack, V->arestas[i].vertice);
                if (!G->direcionado)
                {
                    CriaAresta(ARQDOT, V->valor, V->arestas[i].vertice->valor, V->arestas[i].peso, G->direcionado);
                }
            }
            if (G->direcionado)
            {
                CriaAresta(ARQDOT, V->valor, V->arestas[i].vertice->valor, V->arestas[i].peso, G->direcionado);
            }
        }
    }
    TerminaDot(ARQDOT);
    killLst(Stack);
}

void executarDijkstra(DataStructure grafo, int inicio)
{
    /* Verifica se o vértice existe */
    Grafo *G = grafo;
    if (!existsVerticeIn(G, inicio))
    {
        printf("Não exite o vértice %d no grafo\n", inicio);
        return;
    }
    else
    {
        /* Encontra o índice do vértice inicial */
        int indexInicial = searchVerticeID(G, inicio);

        /* Inicializa os vetores */
        int dist[G->numVertices];
        int pred[G->numVertices];
        bool aberto[G->numVertices];
        for (int i = 0; i < G->numVertices; i++)
        {
            aberto[i] = true;
        }

        inicializaDijkstra(G, dist, pred, indexInicial);

        while (existeAberto(G, aberto))
        {
            int index = menorDist(G, aberto, dist);
            aberto[index] = false;

            /* Atualizar as distâncias e predecessores dos vizinhos de 'index' */
            Vertice *V = G->vertices[index];
            int vizinhoIndex;
            for (int i = 0; i < V->numArestas; i++)
            {
                vizinhoIndex = searchVerticeID(G, V->arestas[i].vertice->valor);
                relaxaAresta(G, index, dist, pred, vizinhoIndex);
            }
        }
    }
}

void inicializaDijkstra(DataStructure grafo, int dist[], int pred[], int indexInicial)
{
    Grafo *G = grafo;
    for (int v = 0; v < G->numVertices; v++)
    {
        dist[v] = INT_MAX / 2;
        pred[v] = -1;
    }
    dist[indexInicial] = 0;
}

bool existeAberto(DataStructure grafo, bool aberto[])
{
    Grafo *G = grafo;
    for (int i = 0; i < G->numVertices; i++)
    {
        if (aberto[i])
        {
            return true;
        }
    }
    return false;
}

int menorDist(DataStructure grafo, bool aberto[], int dist[])
{
    Grafo *G = grafo;
    int i;
    for (i = 0; i < G->numVertices; i++)
    {
        if (aberto[i])
        {
            break;
        }
    }

    if (i == searchVerticeID(G, G->vertices[i]->valor))
    {
        return -1;
    }
    else
    {
        int menor = i;
        for (i = menor + 1; i < G->numVertices; i++)
        {
            if (aberto[i] && (dist[menor] > dist[i]))
            {
                menor = i;
            }
        }
        return menor;
    }
}

void relaxaAresta(DataStructure grafo, int index, int dist[], int pred[], int vizinhoIndex)
{
    Grafo *G = grafo;
    Vertice *atual = G->vertices[index];
    Aresta *aresta = atual->arestas;

    while (aresta != NULL)
    {
        Vertice *vizinho = aresta->vertice;
        int pesoAresta = aresta->peso;
        int novaDistancia = dist[index] + pesoAresta;

        if (novaDistancia < dist[vizinhoIndex])
        {
            dist[vizinhoIndex] = novaDistancia;
            pred[vizinhoIndex] = index;
        }
        aresta = aresta->proximaAresta;
    }
}
