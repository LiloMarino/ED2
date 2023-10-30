#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>
#include <stdbool.h>

typedef void *Item;
typedef void *Heap;

/**
 * @brief Cria uma heap com uma capacidade especificada
 * @param capac Capacidade inicial da heap
 * @return Ponteiro para a heap
 */
Heap criarHeap(size_t capac);

/**
 * @brief Adiciona um novo elemento à heap
 * @param H Ponteiro para o Heap
 * @param item Elemento a ser adicionado à heap
 * @param prioridade Prioridade associada ao elemento
 */
void heapPush(Heap H, Item item, int prioridade);

/**
 * @brief Remove e retorna o elemento de maior prioridade da heap
 * @param H Ponteiro para o Heap
 * @return Elemento de maior prioridade removido da heap
 */
Item heapPop(Heap H);

/**
 * @brief Verifica se o Heap está vazio
 * @param H Ponteiro para o Heap
 * @return Retorna verdadeiro caso esteja vazio e falso caso contrário
 */
bool isEmptyHeap(Heap H);

/**
 * @brief Libera a memória alocada para a heap
 * @param H Heap a ser destruída
 */
void killHeap(Heap H);

/**
 * @brief Restaura a propriedade de heap da árvore a partir de um determinado índice
 * @param H Ponteiro para o Heap
 * @param current_index Índice a partir do qual a propriedade de heap será restaurada
 */
void heapifyDown(Heap H, size_t current_index);

/**
 * @brief Restaura a propriedade de heap subindo na árvore a partir de um determinado índice
 * @param H Ponteiro para o Heap
 * @param current_index Índice a partir do qual a propriedade de heap será restaurada
 */
void heapifyUp(Heap H, size_t current_index);

#endif
