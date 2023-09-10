#ifndef AVLTREE_H
#define AVLTREE_H


typedef void *DataStructure; // Ponteiro para a estrutura de dados especificada
typedef void *Node; // Ponteiro para um nó
typedef int TIPOCHAVE; // Tipo do dado contido em cada nó

/**
 * @brief Cria uma nova árvore AVL
 * @return Retorna o ponteiro para a árvore AVL
 */
DataStructure NovaArvoreAVL();

/**
 * @brief Insere o nó com a chave especificada na árvore
 * @param AVLTree Ponteiro para a árvore AVL
 * @param Chave Conteúdo do nó a ser inserido
 * @return Retorna o ponteiro para o nó
 */
Node InsereAVL(DataStructure AVLTree, TIPOCHAVE Chave);

/**
 * @brief Dado uma chave a função retornará o nó respectivo a chave
 * @param AVLTree Ponteiro para a árvore AVL
 * @param Chave Conteúdo do nó 
 * @return Retorna o ponteiro para o nó
 */
Node GetNodeAVL(DataStructure AVLTree, TIPOCHAVE Chave);

/**
 * @brief Dado um nó retorna a chave respectiva ao nó
 * @param N Nó da árvore AVL
 * @return Retorna a chave
 */
TIPOCHAVE GetChaveAVL(Node N);

/**
 * @brief Obtém a profundidade máxima (Hmax) do nó N 
 * @param N Nó da árvore AVL
 * @return Retorna a profundidade máxima do nó (por padrão é 1)
 */
int GetHmaxAVL(Node N);

/**
 * @brief Dado um nó retorna seu fator de balanceamento
 * @param N Nó da árvore AVL
 * @return Retorna o fator de balanceamento
 */
int GetFbAVL(Node N);

/**
 * @brief Dado uma chave remove o nó que possui a chave especificada
 * @param AVLTree Ponteiro para a árvore AVL
 * @param Chave Conteúdo do nó 
 */
void RemoveNodeAVL(DataStructure AVLTree, TIPOCHAVE Chave);

/**
 * @brief Realiza o free da árvore
 * @param AVLTree Ponteiro para a árvore AVL
 */
void FreeAVL(DataStructure *AVLTree);

/**
 * @brief Realiza o ajuste na AVL quando o fator de degração for acionado
 * @param AVLTree Ponteiro para a árvore AVL
 * @param N Nó a ser ajustado com Fb == 2 ou Fb == -2 (P)
 */
void AjustaAVL(DataStructure AVLTree, Node N);

/**
 * @brief Mostra uma imagem da árvore AVL utilizando o .dot
 * @param AVLTree Ponteiro para a árvore AVL
 */
void PrintAVL(DataStructure AVLTree);

#endif