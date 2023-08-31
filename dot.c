#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "dot.h"
#include "avltree.h"
#include "Bibliotecas/learquivo.h"
#include "Bibliotecas/efficiency.h"

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

void LigaNo(ArqDot fdot, Node pai, Node filho)
{
    if (pai == NULL)
    {
        TIPOCHAVE Chave = GetChaveAVL(filho);
        fprintf(fdot, "    Raiz -> \"%d\"\n", Chave);
    }
    else
    {
        TIPOCHAVE Chave1 = GetChaveAVL(pai);
        TIPOCHAVE Chave2 = GetChaveAVL(filho);
        fprintf(fdot, "    \"%d\" -> \"%d\"\n", Chave1, Chave2);
    }
    fflush(fdot);
}

void MarcaNoRemovido(ArqDot fdot, Node removido)
{
    TIPOCHAVE Chave = GetChaveAVL(removido);
    fprintf(fdot, "    %d [shape=none, label=\"X\", color=red, fontcolor=red, fontsize=20, width=0.3, height=0.3];\n", Chave);
    fflush(fdot);
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
        char command[2*strlen(nomearq) + 30];
        sprintf(command, "dot -Tpng %s -o %s", nomearq, nomepng);
        printf("\nTempo para gerar o %s\n",nomepng);
        iniciarTempo();
        system(command);
        finalizarTempo();
        n++;
        sprintf(nomearq, "%s-%d.dot", nome, n);
        sprintf(nomepng, "%s-%d.png", nome, n);
        vrfy = fopen(nomearq, "r");
    }
}