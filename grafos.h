#ifndef GRAFOS_H
#define GRAFOS_H

#include <stdbool.h>

typedef void *DataStructure;
typedef void *Node;

/**
 * @brief Cria o gráfico
 * @param direcionado Indica se o grafo é direcionado ou não
 * @return Retorna o ponteiro para o grafo
 */
DataStructure criarGrafo(bool direcionado);

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
 * @param peso Peso do caminho entre o vértice de origem e o vértice de destino
 * @note Se o peso for 0 então é considerado que não existe peso entre os nós do grafo
 */
void adicionarVertice(DataStructure grafo, int src, int dest, int peso);

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
 * @brief Executa o algoritmo de Dijkstra e printa o resultado
 * @param grafo Ponteiro para o grafo
 * @param inicio Número do vértice de início
 */
void executarDijkstra(DataStructure grafo, int inicio);

/**
 * @brief Verifica se há vértices abertos no grafo
 * @param grafo Ponteiro para o grafo
 * @param aberto Vetor indicando se os vértices estão abertos
 * @return true se há vértices abertos, false caso contrário
 */
bool existeAberto(DataStructure grafo, bool aberto[]);

/**
 * @brief Encontra o índice do vértice com a menor distância entre os vértices abertos
 * @param grafo Ponteiro para o grafo
 * @param aberto Vetor indicando se os vértices estão abertos
 * @param dist Vetor de distâncias
 * @return Índice do vértice com a menor distância
 */
int menorDist(DataStructure grafo, bool aberto[], int dist[]);

/**
 * @brief Relaxa as arestas do vértice atual, atualizando distâncias e predecessores se necessário
 * @param grafo Ponteiro para o grafo
 * @param index Índice do vértice atual
 * @param dist Vetor de distâncias
 * @param pred Vetor de predecessores
 * @param vizinhoIndex Índice do vértice vizinho
 */
void relaxaAresta(DataStructure grafo, int index, int dist[], int pred[], int vizinhoIndex);

/**
 * @brief Imprime as distâncias mínimas na tela
 * @param grafo Ponteiro para o grafo
 * @param inicio Número do vértice de início
 * @param dist Vetor de distâncias mínimas
 */
void printDistMinima(DataStructure grafo, int inicio, int dist[]);

#endif