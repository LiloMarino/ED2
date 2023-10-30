#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "dotgrafos.h"
#include "Bibliotecas/geradores.h"
#include "Bibliotecas/efficiency.h"
#include "Bibliotecas/learquivo.h"
#include "Bibliotecas/path.h"

void InicializaDot(ArqDot fdot, bool direcionado)
{
    if (direcionado)
    {
        fprintf(fdot, "digraph Tree {\n");
    }
    else
    {
        fprintf(fdot, "graph Tree {\n");
    }
    fprintf(fdot, "\tnode [shape=circle];\n");
    fprintf(fdot, "\tlayout=sfdp;\n");
    fprintf(fdot, "\trankdir=LR;\n");
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
    fprintf(fdot, "\tv%d [label=\"v%d\", fontcolor=\"white\" style=filled, fillcolor=\"%s\"];\n", vertice, vertice, fillcolor);
    fflush(fdot);
}

void CriaAresta(ArqDot fdot, int src, int dest, int peso, bool direcionado)
{
    if (direcionado)
    {
        if (peso > 0)
        {
            fprintf(fdot, "\tv%d -> v%d [label=\" %d\"];\n", src, dest, peso);
        }
        else
        {
            fprintf(fdot, "\tv%d -> v%d;\n", src, dest);
        }
    }
    else
    {
        if (peso > 0)
        {
            fprintf(fdot, "\tv%d -- v%d [label=\" %d\"];\n", src, dest, peso);
        }
        else
        {
            fprintf(fdot, "\tv%d -- v%d;\n", src, dest);
        }
    }
    fflush(fdot);
}

ArqDot CopiaDot(char *NomeArqDot)
{
    FILE *fdot;
    char *fn = CriaLogNome(NomeArqDot, "dot", &fdot);
    fn = realloc(fn, (strlen(fn) + 5) * sizeof(char));
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
    free(fn);
    return fdot;
}

void CriaGifDot(const char nome[])
{
    char nomearq[strlen(nome) + 6];
    char nomepng[strlen(nome) + 6];
    char *path = getPath(nome);

    int n = 1;
    sprintf(nomearq, "%s.dot", nome);
    sprintf(nomepng, "%s.png", nome);

    // Verifica se o arquivo já existe
    FILE *vrfy = fopen(nomearq, "r");
    char command[2 * strlen(nomearq) + 30];

    /* Realiza um loop criando uma imagem para cada .dot */
    while (vrfy != NULL)
    {
        fclose(vrfy);
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
        sprintf(nomearq, "%s_%d.dot", nome, n);
        sprintf(nomepng, "%s_%d.png", nome, n);
        vrfy = fopen(nomearq, "r");
    }

    /* Cria um gif com as imagens geradas */
    sprintf(command, "convert -delay 50 -loop 0 %s/*.png  %s.gif", path, nome);
    system(command);
    free(path);
}