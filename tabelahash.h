#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>

typedef void *DataStructure; // Ponteiro para a estrutura de dados especificada
typedef void *Node; // Ponteiro para um nó
typedef int TIPOCHAVE; // Tipo do dado contido em cada nó

/**
 * @brief Cria uma nova tabela hash
 * @return Retorna o ponteiro para a tabela hash
 */
DataStructure HashCreate();

/**
 * @brief Insere o nó com a chave especificada na tabela
 * @param HTable Ponteiro para a tabela hash
 * @param Chave Conteúdo do nó a ser inserido
 * @return Retorna o ponteiro para o nó
 */
Node HashInsert(DataStructure HTable, TIPOCHAVE Chave);

/**
 * @brief Dado uma chave a função retornará o nó respectivo a chave
 * @param HTable Ponteiro para a tabela hash
 * @param Chave Conteúdo do nó 
 * @return Retorna o ponteiro para o nó
 */
Node HashGetNode(DataStructure HTable, TIPOCHAVE Chave);

/**
 * @brief Dado um nó retorna a chave respectiva ao nó
 * @param N Nó da tabela hash
 * @return Retorna a chave
 */
TIPOCHAVE HashGetChave(Node N);

/**
 * @brief Dado uma chave remove o nó que possui a chave especificada
 * @param HTable Ponteiro para a tabela hash
 * @param Chave Conteúdo do nó 
 */
void HashRemove(DataStructure HTable, TIPOCHAVE Chave);

/**
 * @brief Realiza o free da tabela
 * @param HTable Ponteiro para a tabela hash
 */
void HashFree(DataStructure *HTable);

/**
 * @brief Mostra uma imagem da tabela hash utilizando o .dot
 * @param HTable Ponteiro para a tabela hash
 */
void PrintHash(DataStructure HTable);

#endif