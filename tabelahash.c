#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Bibliotecas/geradores.h"
#include "Bibliotecas/listadupla.h"
#include "tabelahash.h"
#include "dot.h"

struct StTabela
{
    Lista *Elemento;
    unsigned int Tamanho;
};

typedef struct StTabela Tabela;

DataStructure HashCreate(unsigned int Tamanho)
{
    Tabela *HTable = malloc(1, sizeof(Tabela));
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
    unsigned int Indice = HashingDobra(Chave, Table->Tamanho);
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

unsigned int HashingDobra(TIPOCHAVE Chave, unsigned int Tamanho)
{
    /*Descobre quantos dígitos tem o tamanho*/
    unsigned int tam = Tamanho;
    int digitos;
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
    unsigned int Hash = atoi(string);
    return Hash % Tamanho;
}

TIPOCHAVE HashGetChave(DataStructure HTable, TIPOCHAVE Chave)
{
    Tabela *Table = HTable;
    Lista L = Table->Elemento[HashingDobra(Chave, Table->Tamanho)];
    if (L != NULL)
    {
        Iterador I = createIterador(L, false);
        while (!isIteratorEmpty(L, I))
        {
            TIPOCHAVE *Elemento = getIteratorNext(L, I);
            if (*Elemento == Chave)
            {
                killIterator(I);
                return *Elemento;
            }
        }
        killIterator(I);
    }
    return -1;
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
            Del = getNextLst(Afetados, Del);
        }
    }
    /*Elemento não existe*/
    printf("Chave %d não existe!", Chave);
}

void HashFree(DataStructure *HTable)
{
    Tabela *Table = HTable;
    for (int i = 0; i < Table->Tamanho; i++)
    {
        Lista L = Table->Elemento[i];
        if (L != NULL)
        {
            killLst(L);
        }
    }
    free(Table->Elemento);
    free(Table);
}

void PrintHash(DataStructure HTable)
{
    Tabela *Table = HTable;
    
    for (int i = 0; i < Table->Tamanho; i++)
    {
        Lista L = Table->Elemento[i];
        if (L != NULL)
        {
            Iterador I = createIterador(L, false);
            while (!isIteratorEmpty(L, I))
            {
                TIPOCHAVE *Elemento = getIteratorNext(L, I);
            }
            killIterator(I);
        }
    }
}
