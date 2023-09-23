#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Bibliotecas/geradores.h"
#include "Bibliotecas/listadupla.h"
#include "tabelahash.h"
#include "dot.h"

struct StTabela
{
    Lista *Elemento;
    int Tamanho;
};

typedef struct StTabela Tabela;

DataStructure HashCreate(int Tamanho)
{
    Tabela *HTable = malloc(sizeof(Tabela));
    HTable->Elemento = calloc(Tamanho, sizeof(Lista));
    HTable->Tamanho = Tamanho;
    return HTable;
}

Node HashInsert(DataStructure HTable, TIPOCHAVE Chave)
{
    Tabela *Table = HTable;
    if (Chave == -1)
    {
        /*Chave inválida*/
        return NULL;
    }
    int Indice = HashingDobra(Chave, Table->Tamanho);
    TIPOCHAVE *Elemento = malloc(sizeof(TIPOCHAVE));
    *Elemento = Chave;
    if (Table->Elemento[Indice] != NULL)
    {
        /*Não existe nenhum elemento na posição*/
        Table->Elemento[Indice] = createLst(-1);
        return insertLst(Table->Elemento[Indice], Elemento);
    }
    else
    {
        /*Existe pelo menos um elemento na posição*/
        return insertLst(Table->Elemento[Indice], Elemento);
    }
}

int HashingDobra(TIPOCHAVE Chave, int Tamanho)
{
    /*Descobre quantos dígitos tem o tamanho*/
    int tam = Tamanho;
    size_t digitos;
    for (digitos = 0; tam > 0; digitos++)
    {
        tam /= 10;
    }

    char string[64]; // Suporta até 64 dígitos
    sprintf(string, "%d", Chave);
    while (strlen(string) >= digitos)
    {
        /*Faz as dobras de 2 em 2*/
        char dobra[5];
        char num[3];
        for (int i = 0; i < 2; i++)
        {
            strncpy(dobra, string, 4);
            char ini = dobra[i];
            char fim = dobra[3 - i];
            num[i] = (((ini - '0') + (fim - '0')) % 10) + '0';
        }
        char aux = num[0];
        num[0] = num[1];
        num[1] = aux;
        sprintf(string, "%s%s", num, string + 4);
    }
    int Hash = atoi(string);
    return Hash % Tamanho;
}

Node HashGetNode(DataStructure HTable, TIPOCHAVE Chave)
{
    Tabela *Table = HTable;
    Lista L = Table->Elemento[HashingDobra(Chave, Table->Tamanho)];
    if (L != NULL)
    {
        Iterador I = createIterador(L, false);
        while (!isIteratorEmpty(I))
        {
            TIPOCHAVE *Elemento = getIteratorNext(L, I);
            if (*Elemento == Chave)
            {
                killIterator(I);
                return Elemento;
            }
        }
        killIterator(I);
    }
    return NULL;
}

TIPOCHAVE HashGetChave(Node N)
{
    TIPOCHAVE *Elemento = N;
    return (Elemento != NULL) ? *Elemento : -1;
}

void HashRemove(DataStructure HTable, TIPOCHAVE Chave)
{
    Tabela *Table = HTable;
    Lista L = Table->Elemento[HashingDobra(Chave, Table->Tamanho)];
    if (L != NULL)
    {
        Posic Del = getFirstLst(L);
        while (Del != NULL)
        {
            TIPOCHAVE *Elemento = getLst(Del);
            if (*Elemento == Chave)
            {
                /*Elemento encontrado*/
                removeLst(L, Del);
                return;
            }
            Del = getNextLst(L, Del);
        }
    }
    /*Elemento não existe*/
    printf("Chave %d não existe!", Chave);
}

void HashFree(DataStructure *HTable)
{
    Tabela *Table = *HTable;
    for (int i = 0; i < Table->Tamanho; i++)
    {
        Lista L = Table->Elemento[i];
        if (L != NULL)
        {
            while (!isEmptyLst(L))
            {
                TIPOCHAVE *Elemento = popLst(L);
                free(Elemento);
            }
        }
    }
    free(Table->Elemento);
    free(Table);
}

void PrintHash(DataStructure HTable)
{
    Tabela *Table = HTable;
    ARQDOT = CriaLog(FNARQDOT, "dot");
    InicializaDot(ARQDOT);
    CriaArray(ARQDOT, "Tabela", Table->Tamanho);

    for (int i = 0; i < Table->Tamanho; i++)
    {
        Lista L = Table->Elemento[i];
        if (L != NULL)
        {
            TIPOCHAVE *ElementoAnterior;
            Posic P = getFirstLst(L);
            if (P != NULL)
            {
                /*Obtém o primeiro elemento da lista se ele existir*/
                ElementoAnterior = getLst(P);
                LigaArray(ARQDOT,"Tabela",i,ElementoAnterior);
                P = getNextLst(L, P);
            }
            while (P != NULL)
            {
                /*Obtém os próximos elementos da lista*/
                TIPOCHAVE *Elemento = getLst(P);
                LigaNo(ARQDOT,ElementoAnterior,Elemento);
                ElementoAnterior = Elemento;
                P = getNextLst(L, P);
            }
        }
    }
    TerminaDot(ARQDOT);
}
