#ifndef GRAFOS_H
#define GRAFOS_H

#include <stdbool.h>

typedef void *DataStructure;
typedef void *Node;

DataStructure criarGrafo();

bool existsVerticeIn(DataStructure grafo, int vertice);

void adicionarVertice(DataStructure grafo, int src, int dest);

void freeGrafo(DataStructure grafo);

void buscarGrafoLargura(DataStructure grafo);

#endif