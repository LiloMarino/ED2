#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "dot.h"
#include "avltree.h"
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

void LigaNo(ArqDot fdot, Node pai, Node filho)
{
    if (filho == NULL)
    {
        return;
    }
    if (pai == NULL)
    {
        TIPOCHAVE Chave = GetChaveAVL(filho);
        int Fb = GetFbAVL(filho);
        fprintf(fdot, "    Raiz -> \"%d\nFb:%d\"\n", Chave, Fb);
    }
    else
    {

        TIPOCHAVE Chave1 = GetChaveAVL(pai);
        TIPOCHAVE Chave2 = GetChaveAVL(filho);
        int Fb1 = GetFbAVL(pai);
        int Fb2 = GetFbAVL(filho);
        fprintf(fdot, "    \"%d\nFb:%d\" -> \"%d\nFb:%d\"\n", Chave1, Fb1, Chave2, Fb2);
    }
    fflush(fdot);
}

void MarcaNoRemovido(ArqDot fdot, Node removido)
{
    TIPOCHAVE Chave = GetChaveAVL(removido);
    fprintf(fdot, "    %d [shape=none, label=\"X\", color=red, fontcolor=red, fontsize=20, width=0.3, height=0.3];\n", Chave);
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
        printf("\nTempo para gerar o %s\n", nomepng);
        iniciarTempo();
        system(command);
        finalizarTempo();
        n++;
        sprintf(nomearq, "%s-%d.dot", nome, n);
        sprintf(nomepng, "%s-%d.png", nome, n);
        vrfy = fopen(nomearq, "r");
    }
}