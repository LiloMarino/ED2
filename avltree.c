#include "avltree.h"

struct StNodeTree
{
    TIPOCHAVE Chave;
    struct StNodeTree *Dir;
    struct StNodeTree *Esq;
    int Hdir;
    int Hesq;
};

struct StRaiz
{
    int NumTotalNos;
    struct StNodeTree *No;
};

typedef struct StNodeTree NodeTree;
typedef struct StRaiz Raiz;

DataStructure NovaArvoreAVL()
{
    return DataStructure();
}

Node InsereAVL(DataStructure AVLTree, TIPOCHAVE Chave)
{
    return Node();
}

Node GetNodeAVL(DataStructure AVLTree, TIPOCHAVE Chave)
{
    return Node();
}

TIPOCHAVE GetChaveAVL(DataStructure AVLTree, Node No)
{
    return TIPOCHAVE();
}

void RemoveNodeAVL(DataStructure AVLTree, Node No)
{
}

void FreeAVL(DataStructure AVLTree)
{
}
