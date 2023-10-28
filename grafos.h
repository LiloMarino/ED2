#ifndef GRAFOS_H
#define GRAFOS_H

#include <stdbool.h>

typedef void *DataStructure;
typedef void *Node;

/**
 * @brief Cria o gráfico
 * @return Retorna o ponteiro para o grafo
 */
DataStructure criarGrafo();

/**
 * @brief Verifica se existe o vértice no grafo
 * @param grafo Ponteiro para o grafo
 * @param vertice Número do vertice 
 * @return Se existir o vértice no grafo ele retorna verdadeiro, caso contrário retorna falso
 */
bool existsVerticeIn(DataStructure grafo, int vertice);

/**
 * @brief Procura o vértice
 * @param grafo Ponteiro para o grafo
 * @param vertice Número do vertice 
 * @return Retorna o vértice
 */
Node searchVertice(DataStructure grafo, int vertice);

/**
 * @brief Procura o vértice
 * @param grafo Ponteiro para o grafo
 * @param vertice Número do vertice 
 * @return Retorna o índice do vértice
 */
int searchVerticeID(DataStructure grafo, int vertice);

/**
 * @brief Adiciona um vértice ao grafo
 * @param grafo Ponteiro para o grafo
 * @param src Número do vértice de origem 
 * @param dest Número do vértice de destino 
 */
void adicionarVertice(DataStructure grafo, int src, int dest);

/**
 * @brief Realiza o free do grafo
 * @param grafo Ponteiro para o grafo
 */
void freeGrafo(DataStructure grafo);

/**
 * @brief Realiza busca em largura do grafo e marca com verde os nós percorridos
 * @param grafo Ponteiro para o grafo
 * @param inicio Número do vértice de inicio
 */
void buscarGrafoLargura(DataStructure grafo, int inicio);

/**
 * @brief Printa o grafo
 * @param grafo Ponteiro para o grafo
 */
void printGrafo(DataStructure grafo);

/**
 * @brief Executa o algoritmo de Dijkstra
 * @param grafo Ponteiro para o grafo
 * @param inicio Número do vértice de início
 */
void executarDijkstra(DataStructure grafo, int inicio);

#endif