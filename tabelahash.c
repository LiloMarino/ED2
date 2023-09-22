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
    Tabela *HTable = malloc(1,sizeof(Tabela));
    HTable->Elemento = calloc(Tamanho,sizeof(Lista));
    HTable->Tamanho = Tamanho;
    return HTable;
}

Node HashInsert(DataStructure HTable, TIPOCHAVE Chave)
{
    Tabela *Table = HTable;
    unsigned int Indice = HashingDobra(Chave,Table->Tamanho);
    TIPOCHAVE *Elemento = malloc(sizeof(TIPOCHAVE));
    *Elemento = Chave;
    if(Table->Elemento[Indice] != NULL)
    {
        /*Não existe nenhum elemento na posição*/
        Table->Elemento[Indice] = createLst(-1);
        insertLst(Table->Elemento[Indice],Elemento);
    }
    else
    {
        /*Existe pelo menos um elemento na posição*/
        insertLst(Table->Elemento[Indice],Elemento);
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

Node HashGetNode(DataStructure HTable, TIPOCHAVE Chave)
{
    Tabela *Table = HTable;
}

TIPOCHAVE HashGetChave(Node N)
{
    Elemento *Elem = N;
}

void HashRemove(DataStructure HTable, TIPOCHAVE Chave)
{
    Tabela *Table = HTable;
}

void HashFree(DataStructure *HTable)
{
    Tabela *Table = HTable;
}

void PrintHash(DataStructure HTable)
{
    Tabela *Table = HTable;
}
