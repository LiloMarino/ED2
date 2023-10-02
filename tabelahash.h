#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>

typedef void *DataStructure; // Ponteiro para a estrutura de dados especificada
typedef void *Node; // Ponteiro para um nó
typedef int TIPOCHAVE; // Tipo do dado contido em cada nó

/**
 * @brief Cria uma nova tabela hash
 * @param tamanho Tamanho do array da tabela hash
 * @return Retorna o ponteiro para a tabela hash
 */
DataStructure HashCreate(int tamanho);

/**
 * @brief Insere o nó com a chave especificada na tabela
 * @param HTable Ponteiro para a tabela hash
 * @param Chave Chave a ser inserida
 * @return Retorna o ponteiro para o nó
 */
Node HashInsert(DataStructure HTable, TIPOCHAVE Chave);


/**
 * @brief Faz o hashing para determinada chave
 * @param HTable Ponteiro para a tabela hash
 * @param Chave Chave a ser inserida
 * @return Retorna o índice do nó
 */
int HashingDobra(DataStructure HTable, TIPOCHAVE Chave);

/**
 * @brief Dado uma chave a função retornará o nó respectivo a chave
 * @param HTable Ponteiro para a tabela hash
 * @param Chave Chave a ser inserida
 * @return Retorna o ponteiro para o nó
 */
Node HashGetNode(DataStructure HTable, TIPOCHAVE Chave);

/**
 * @brief Dado um nó retorna sua chave
 * @param N Nó da tabela hash 
 * @return Retorna a chave respectiva ao nó
 */
TIPOCHAVE HashGetChave(Node N);

/**
 * @brief Dado uma chave remove o nó que possui a chave especificada
 * @param HTable Ponteiro para a tabela hash
 * @param Chave Chave a ser inserida
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