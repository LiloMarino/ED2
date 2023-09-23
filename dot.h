#ifndef DOT_H
#define DOT_H

#include <stdio.h>
#include "avltree.h"
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
 * @brief Cria o nó com as especificações dadas
 * @param fdot Ponteiro para o arquivo .dot
 * @param N Ponteiro para o nó
 * @param cor Cor do nó
 */
void CriaNo(ArqDot fdot, Node N, const char *fillcolor);

/**
 * @brief Cria o array com as especificações dadas
 * @param fdot Ponteiro para o arquivo .dot
 * @param nome Nome do array
 * @param tamanho Tamanho do array
 */
void CriaArray(ArqDot fdot, const char *nome, int tamanho);

/**
 * @brief Liga o nó ao índice do array
 * @param fdot Ponteiro para o arquivo .dot
 * @param nome Nome do array
 * @param indice Indice do elemento do array
 * @param elemento Elemento do array
 */
void LigaArray(ArqDot fdot, const char *nome, int indice, Node elemento);

/**
 * @brief Liga o Pai->Filho
 * @param fdot Ponteiro para o arquivo .dot
 * @param All Ponteiro para a árvore radial
 * @param pai Ponteiro para o pai
 * @param filho Ponteiro para o filho
 */
void LigaNo(ArqDot fdot, Node pai, Node filho);

/**
 * @brief Marca o nó como removido no .dot
 * @param fdot Ponteiro para o arquivo .dot
 * @param All Ponteiro para a árvore radial
 * @param removido Ponteiro para o nó removido
 */
void MarcaNoRemovido(ArqDot fdot, Node removido);

/**
 * @brief Copia o .dot do .geo para o primeiro arquivo .qry
 * @param fdot Ponteiro para o arquivo .dot
 * @param OutputGeo Caminho para o .dot do .geo
 */
void CopiaDot(ArqDot fdot, const char *NomeArqDot);

/**
 * @brief Cria o png a partir do .dot
 * @param nome Nome do arquivo .dot
 */
void CriaPngDot(const char nome[]);

#endif
