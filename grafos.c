#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grafos.h"
#include "Bibliotecas/listadupla.h"

struct Vertice {
    int valor;
    struct Vertice** vertices;
} 

struct Grafo {
    int numVertices;
    struct Vertice** vertices;
}

typedef struct Vertice;
typedef struct Grafo;

