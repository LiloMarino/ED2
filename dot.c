#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "dot.h"
#include "redblacktree.h"
#include "Bibliotecas/geradores.h"
#include "Bibliotecas/efficiency.h"
#include "Bibliotecas/learquivo.h"

void InicializaDot(ArqDot fdot)
{
    fprintf(fdot, "digraph Tree {\n");
    fprintf(fdot, "    node [shape=circle];\n");
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

void CriaNo(ArqDot fdot, Node N, const char *fillcolor)
{
    TIPOCHAVE Chave = GetChaveFB(N);
    fprintf(fdot,"\"%d\" [label=\"%d\", fillcolor=\"%s\"];\n",Chave, Chave, fillcolor);
}

void LigaNo(ArqDot fdot, Node pai, Node filho)
{
    if (filho == NULL)
    {
        return;
    }
    if (pai == NULL)
    {
        TIPOCHAVE Chave = GetChaveFB(filho);
        fprintf(fdot, "\tRaiz -> %d;\n", Chave);
    }
    else
    {
        TIPOCHAVE Chave1 = GetChaveFB(pai);
        TIPOCHAVE Chave2 = GetChaveFB(filho);
        fprintf(fdot, "\t%d -> %d;\n", Chave1, Chave2);
    }
    fflush(fdot);
}

void MarcaNoRemovido(ArqDot fdot, Node removido)
{
    TIPOCHAVE Chave = GetChaveFB(removido);
    fprintf(fdot, "\t%d [shape=none, label=\"X\", color=red, fontcolor=red, fontsize=20, width=0.3, height=0.3];\n", Chave);
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