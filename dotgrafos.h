#ifndef DOT_GRAFOS_H
#define DOT_GRAFOS_H

#include <stdio.h>
#include <stdbool.h>

#define MOSTRAR_TEMPO 0 /* 1 = True, 0 = False, Define se mostra no terminal o tempo de criação dos arquivos */

typedef void *ArqDot;

extern FILE* ARQDOT;
extern char* FNARQDOT;

/**
 * @brief Inicializa o arquivo .dot já aberto
 * @param fdot Ponteiro para o arquivo .dot
 * @param direcionado Indica se o grafo é direcionado ou não
 */
void InicializaDot(ArqDot fdot, bool direcionado);

/**
 * @brief Termina e fecha o arquivo .dot
 * @param fdot Ponteiro para o arquivo .dot
 */
void TerminaDot(ArqDot fdot);

/**
 * @brief Cria o vértice com as especificações dadas
 * @param fdot Ponteiro para o arquivo .dot
 * @param vertice Número do vértice
 * @param cor Cor do vértice
 */
void CriaVertice(ArqDot fdot, int vertice, const char *fillcolor);

/**
 * @brief Liga o src->dest
 * @param fdot Ponteiro para o arquivo .dot
 * @param src  Número do vértice de origem
 * @param dest Número do vértice de destino
 * @param peso Peso da aresta
 * @param direcionado Indica se o grafo é direcionado ou não
 */
void CriaAresta(ArqDot fdot, int src, int dest, int peso, bool direcionado);

/**
 * @brief Copia o .dot porém não fecha o arquivo
 * @param NomeArqDot Nome do arquivo .dot 
 * @return Ponteiro para o arquivo .dot
 */
ArqDot CopiaDot(char *NomeArqDot);

/**
 * @brief Cria um gif a partir dos .dot
 * @param nome Nome do arquivo .dot
 * @note É necessário para funcionar corretamente ter instalado o graphviz e o imagemagick
 * Comandos de instalação:
 * sudo apt install graphviz
 * sudo apt install imagemagick
 * Para verificar se foi instalado corretamente:
 * dot -V
 * convert --version
 */
void CriaGifDot(const char nome[]);

#endif