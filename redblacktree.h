#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H


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
void RemoveNodeRB(DataStructure RBTree, TIPOCHAVE Chave);

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

#endif