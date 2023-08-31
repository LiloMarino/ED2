#ifndef AVLTREE_H
#define AVLTREE_H


typedef void *DataStructure; // Ponteiro para a estrutura de dados especificada
typedef void *Node; // Ponteiro para um nó
typedef int TIPOCHAVE; // Tipo do dado contido em cada nó

DataStructure NovaArvoreAVL();

Node InsereAVL(DataStructure AVLTree, TIPOCHAVE Chave);

Node GetNodeAVL(DataStructure AVLTree, TIPOCHAVE Chave);

TIPOCHAVE GetChaveAVL(DataStructure AVLTree, Node No);

void RemoveNodeAVL(DataStructure AVLTree, Node No);

void FreeAVL(DataStructure AVLTree);

#endif