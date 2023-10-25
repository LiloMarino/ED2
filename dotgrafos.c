#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "dotgrafos.h"
#include "Bibliotecas/geradores.h"
#include "Bibliotecas/efficiency.h"
#include "Bibliotecas/learquivo.h"

void InicializaDot(ArqDot fdot)
{
    fprintf(fdot, "digraph Tree {\n");
    fprintf(fdot, "\tnode [shape=circle];\n");
    fflush(fdot);
}

void TerminaDot(ArqDot fdot)
{
    if (fdot != NULL)
    {
        fprintf(fdot, "}");
        fclose(fdot);
    }
}

void CriaVertice(ArqDot fdot, int vertice, const char *fillcolor)
{
    fprintf(fdot, "\t%d [label=\"%d\", fontcolor=\"white\" style=filled, fillcolor=\"%s\"];\n", vertice, vertice, fillcolor);
}

void CriaAresta(ArqDot fdot, int src, int dest)
{
    fprintf(fdot, "\t%d -> %d;\n", src, dest);
    fflush(fdot);
}

void CopiaDot(ArqDot fdot, const char *NomeArqDot)
{
    char fn[strlen(NomeArqDot) + 5];
    strcpy(fn, NomeArqDot);
    strcat(fn, ".dot");
    FILE *faux = fopen(fn, "r");
    if (!faux)
    {
        printf("Erro ao copiar DOT");
    }
    else
    {
        char *buf = NULL;
        while (leLinha(faux, &buf))
        {
            if (buf[0] != '}')
            {
                fprintf(fdot, "%s", buf);
            }
        }
    }
    fflush(fdot);
    fclose(faux);
}

void CriaPngDot(const char nome[])
{
    char nomearq[strlen(nome) + 6];
    char nomepng[strlen(nome) + 6];

    int n = 1;
    sprintf(nomearq, "%s.dot", nome);
    sprintf(nomepng, "%s.png", nome);

    // Verifica se o arquivo já existe
    FILE *vrfy = fopen(nomearq, "r");
    while (vrfy != NULL)
    {
        fclose(vrfy);
        char command[2 * strlen(nomearq) + 30];
        sprintf(command, "dot -Tpng %s -o %s", nomearq, nomepng);
#if MOSTRAR_TEMPO != 0
        printf("\nTempo para gerar o %s\n", nomepng);
        iniciarTempo();
#endif
        system(command);
#if MOSTRAR_TEMPO != 0
        finalizarTempo();
#endif
        n++;
        sprintf(nomearq, "%s-%d.dot", nome, n);
        sprintf(nomepng, "%s-%d.png", nome, n);
        vrfy = fopen(nomearq, "r");
    }
}