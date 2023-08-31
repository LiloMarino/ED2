#ifndef DOT_H
#define DOT_H

#include <stdio.h>
#include "avltree.h"

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
 * @brief Cria o png a partir do .dot
 * @param nome Nome do arquivo .dot
 */
void CriaPngDot(const char nome[]);

#endif
