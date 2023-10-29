#include "grafos.h"
#include "dotgrafos.h"
#include "Bibliotecas/geradores.h"
#include "Bibliotecas/utilities.h"

FILE *ARQDOT;
char *FNARQDOT;

int main()
{
    /*Inicia as operações da tabela hash e registra em vários .dot para a visualização separada*/
    FNARQDOT = "../logs/Grafo";
    DataStructure Grafo = criarGrafo(false);
    adicionarVertice(Grafo, 0, 1, 1);
    adicionarVertice(Grafo, 0, 2, 1);
    adicionarVertice(Grafo, 1, 3, 1);
    adicionarVertice(Grafo, 1, 4, 1);
    adicionarVertice(Grafo, 2, 5, 1);
    printGrafo(Grafo);
    buscarGrafoLargura(Grafo,0);
    freeGrafo(Grafo);
    CriaGifDot(FNARQDOT);
}