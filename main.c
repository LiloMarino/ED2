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
    DataStructure Grafo = criarGrafo(true);
    adicionarVertice(Grafo, 0, 1, 10);
    adicionarVertice(Grafo, 0, 2, 5);
    adicionarVertice(Grafo, 2, 1, 3);
    adicionarVertice(Grafo, 1, 3, 1);
    adicionarVertice(Grafo, 2, 3, 8);
    adicionarVertice(Grafo, 2, 4, 2);
    adicionarVertice(Grafo, 3, 4, 4);
    adicionarVertice(Grafo, 3, 5, 4);
    adicionarVertice(Grafo, 4, 5, 6);
    printGrafo(Grafo);
    //buscarGrafoLargura(Grafo,0);
    executarDijkstra(Grafo,0);
    freeGrafo(Grafo);
    CriaGifDot(FNARQDOT);
}