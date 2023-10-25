#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grafos.h"
#include "Bibliotecas/listadupla.h"

struct StVertice
{
    int valor;
    struct Vertice *vertices[];
};

struct StGrafo
{
    int numVertices;
    struct Vertice *vertices[];
};

typedef struct StVertice Vertice;
typedef struct StGrafo Grafo;

DataStructure criarGrafo()
{
    Grafo *grafo = calloc(1,sizeof(Grafo));
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
    }
    if (!foundDest)
    {
        // Criar um novo vértice e inserir no array de vertices do grafo
    }
    // Adicionar aresta entre os dois vértices
}

void freeGrafo(DataStructure grafo)
{
    Grafo *G = grafo;
}

void buscarGrafoLargura(DataStructure grafo)
{
    Grafo *G = grafo;
}

void printVertice(Node vertice);