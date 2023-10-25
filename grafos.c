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
    struct StVertice **vertices;
};

struct StGrafo
{
    int numVertices;
    struct StVertice **vertices;
};

struct StVerifica
{
    int valor;
    bool verificado;
};

typedef struct StVertice Vertice;
typedef struct StGrafo Grafo;
typedef struct StVerifica Verifica;

DataStructure criarGrafo()
{
    Grafo *grafo = calloc(1, sizeof(Grafo));
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

void adicionarVertice(DataStructure grafo, int src, int dest)
{
    Grafo *G = grafo;
    bool foundSrc = existsVerticeIn(G, src);
    bool foundDest = existsVerticeIn(G, dest);
    if (!foundSrc)
    {
        // Criar um novo vértice e inserir no array de vertices do grafo
        Vertice *v = calloc(1, sizeof(Vertice));
        v->valor = src;
        G->numVertices++;
        G->vertices = realloc(G->vertices, G->numVertices * sizeof(Vertice *));
        G->vertices[G->numVertices - 1] = v;
    }
    if (!foundDest)
    {
        // Criar um novo vértice e inserir no array de vertices do grafo
        Vertice *v = calloc(1, sizeof(Vertice));
        v->valor = dest;
        G->numVertices++;
        G->vertices = realloc(G->vertices, G->numVertices * sizeof(Vertice *));
        G->vertices[G->numVertices - 1] = v;
    }
    // Adicionar aresta entre os dois vértices
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
    S->vertices = realloc(S->vertices, S->numArestas * sizeof(Vertice *));
    S->vertices[S->numArestas - 1] = D;
    D->numArestas++;
    D->vertices = realloc(D->vertices, D->numArestas * sizeof(Vertice *));
    D->vertices[D->numArestas - 1] = S;
}

void freeGrafo(DataStructure grafo)
{
    Grafo *G = grafo;
    for (int i = 0; i < G->numVertices; i++)
    {
        free(G->vertices[i]->vertices);
        free(G->vertices[i]);
    }
    free(G->vertices);
    free(G);
}

void buscarGrafoLargura(DataStructure grafo)
{
    Grafo *G = grafo;
    Vertice *V = G->vertices[0];
    ARQDOT = CriaLog(FNARQDOT, "dot");
    InicializaDot(ARQDOT);

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
        CriaVertice(ARQDOT,V->valor,"green");
        /*Insere os Arestas conectadas para o Stack de verificação*/
        for (int i = 0; i < V->numArestas; i++)
        {
            int j;
            for (j = 0; j < G->numVertices; j++)
            {
                if (vrfy[j].valor == V->vertices[i]->valor)
                {
                    break;
                }
            }
            if (!vrfy[j].verificado)
            {
                vrfy[j].verificado = true;
                insertLst(Stack, V->vertices[i]);
            }
            CriaAresta(ARQDOT,V->valor,V->vertices[i]->valor);
        }
        CopiaDot(ARQDOT,FNARQDOT);
    }
    TerminaDot(ARQDOT);
    killLst(Stack);
}

void printVertice(Node vertice);