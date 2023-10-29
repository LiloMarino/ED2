#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

// void executarDijkstra(DataStructure grafo, int inicio)
// {
//     /* Verifica se o vértice existe */
//     Grafo *G = grafo;
//     if (!existsVerticeIn(G, inicio))
//     {
//         printf("Não exite o vértice %d no grafo\n", inicio);
//         return;
//     }

//     /* Encontra o vértice inicial */
//     Vertice *V = searchVertice(G, inicio);

//     /* Inicializa o vetor que indica se os nós estão "abertos" ou não*/
//     Verifica vrfy[G->numVertices];
//     for (int i = 0; i < G->numVertices; i++)
//     {
//         vrfy[i].valor = G->vertices[i]->valor;
//         vrfy[i].verificado = false;
//     }
//     vrfy[searchVerticeID(G, V->valor)].verificado = true;

//     inicializaDijkstra();
// }

// void inicializaDijkstra(DataStructure grafo, int *d, int *p, int indexInicial)
// {
//     int v;
//     for (v = 0; v < g->vertices; v++)
//     {
//         d[v] = INT_MAX / 2;
//         p[v] = -1;
//     }
//     d[indexInicial] = 0;
// }

// void relaxa(GRAFO *g, int *d, int *p, int u, int v)
// {
//     ADJACENCIA *ad = g->adj[u].cab;
//     while (ad && ad->vertice != v)
//         ad = ad->prox;
//     if (ad)
//     {
//         if (d[v] > d[u] + ad->peso)
//         {
//             d[v] = d[u] + ad->peso;
//             p[v] = u;
//         }
//     }
// }

// int *dijkstra(GRAFO *g, int s) {

// int p[g-›vertices];
// bool aberto [g-›vertices];
// InicializaD (g, d,p, s);
// int i;
// for (i=0; i‹g-›vertices; i++)
// aberto [i] = true;
// while (existeAberto (g, aberto)) {
// int u = menorDist (g, aberto,d) ;
// aberto [u] = false;
// ADJACENCIA *ad = g->adj [u].cab;
// while (ad) {
// relaxa (g,d,p,u, ad-›vertice);
// ad = ad->prox;
// }
// }
// }
// return (d);
// }