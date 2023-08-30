#include "avltree.h"

struct StNo
{
    TIPOCHAVE chave;
    struct StNo *dir;
    struct StNo *esq;
    int Hdir;
    int Hesq;
};

struct StRaiz
{
    int numTotalNos;
    struct StNo *No;
};

typedef struct StNo No;
typedef struct StRaiz Raiz;