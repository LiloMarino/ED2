#ifndef DOT_GRAFOS_H
#define DOT_GRAFOS_H

#include <stdio.h>

#define MOSTRAR_TEMPO 0 /* 1 = True, 0 = False, Define se mostra no terminal o tempo de criação dos arquivos */

typedef void *ArqDot;

extern FILE* ARQDOT;
extern char* FNARQDOT;

/**
 * @brief Inicializa o arquivo .dot já aberto
 * @param fdot Ponteiro para o arquivo .dot
 */
void InicializaDot(ArqDot fdot);

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
 */
void CriaAresta(ArqDot fdot, int src, int dest, int peso);

/**
 * @brief Copia o .dot porém não fecha o arquivo
 * @param NomeArqDot Nome do arquivo .dot 
 * @return Ponteiro para o arquivo .dot
 */
ArqDot CopiaDot(char *NomeArqDot);

/**
 * @brief Cria o png a partir do .dot
 * @param nome Nome do arquivo .dot
 */
void CriaPngDot(const char nome[]);

#endif