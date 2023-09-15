#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <stdbool.h>

typedef void *DataStructure; // Ponteiro para a estrutura de dados especificada
typedef void *Node; // Ponteiro para um nó
typedef int TIPOCHAVE; // Tipo do dado contido em cada nó

/**
 * @brief Cria uma nova árvore Red-Black
 * @return Retorna o ponteiro para a árvore Red-Black
 */
DataStructure NovaArvoreRB();

/**
 * @brief Insere o nó com a chave especificada na árvore
 * @param RBTree Ponteiro para a árvore Red-Black
 * @param Chave Conteúdo do nó a ser inserido
 * @return Retorna o ponteiro para o nó
 */
Node InsereRB(DataStructure RBTree, TIPOCHAVE Chave);

/**
 * @brief Faz as verificações dos casos de inserção da árvore Red-Black
 * @param RBTree Ponteiro para a árvore Red-Black
 * @param N Nó da árvore Red-Black a ser analisado
 */
void VerificaInsertRB(DataStructure RBTree, Node N);

/**
 * @brief Realiza o Single Rotate Right
 * @param RBTree Ponteiro para a árvore Red-Black
 * @param N Nó filho
 */
void RotacionaDireita(DataStructure RBTree, Node N);

/**
 * @brief Realiza o Single Rotate Left
 * @param RBTree Ponteiro para a árvore Red-Black
 * @param N Nó filho
 */
void RotacionaEsquerda(DataStructure RBTree, Node N);

/**
 * @brief Dado uma chave a função retornará o nó respectivo a chave
 * @param RBTree Ponteiro para a árvore Red-Black
 * @param Chave Conteúdo do nó 
 * @return Retorna o ponteiro para o nó
 */
Node GetNodeRB(DataStructure RBTree, TIPOCHAVE Chave);

/**
 * @brief Dado um nó retorna a chave respectiva ao nó
 * @param N Nó da árvore Red-Black
 * @return Retorna a chave
 */
TIPOCHAVE GetChaveRB(Node N);

/**
 * @brief Dado uma chave remove o nó que possui a chave especificada
 * @param RBTree Ponteiro para a árvore Red-Black
 * @param Chave Conteúdo do nó 
 */
void RemoveRB(DataStructure RBTree, TIPOCHAVE Chave);

/**
 * @brief Semelhante ao VerificaInsertRB ele faz as verificações de remoção e corrige a árvore
 * @param RBTree Ponteiro para a árvore Red-Black
 * @param N Nó da árvore Red-Black
 */
void FixRemoveRB(DataStructure RBTree, Node N);

/**
 * @brief Realiza o free da árvore
 * @param RBTree Ponteiro para a árvore Red-Black
 */
void FreeRB(DataStructure *RBTree);

/**
 * @brief Mostra uma imagem da árvore Red-Black utilizando o .dot
 * @param RBTree Ponteiro para a árvore Red-Black
 */
void PrintRB(DataStructure RBTree);

/**
 * @brief Faz a conexão do nó pai com o nó filho, ou seja, o P adota o F
 * @param RBTree Ponteiro para a árvore Red-Black
 * @param P Nó pai
 * @param F Nó filho
 * @param Dir Determina se o filho será filho da direita caso seja true, 
 * e filho da esquerda caso seja false.
 */
void Conecta(DataStructure RBTree, Node P, Node F, bool Dir);

#endif