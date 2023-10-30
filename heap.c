#include "heap.h"
#include <stdlib.h>

struct StHeapNode
{
    int prioridade;
    void *item;
};

struct StHeapLista
{
    struct StHeapNode *array;
    size_t capac;
    size_t lenght;
};

typedef struct StHeapNode HeapNode;
typedef struct StHeapLista HeapLista;

Heap criarHeap(size_t capac)
{
    HeapLista *heap = malloc(sizeof(HeapLista));
    heap->capac = capac;
    heap->lenght = 0;
    heap->array = malloc(capac * sizeof(HeapNode));
    return heap;
}

void killHeap(Heap H)
{
    HeapLista *heap = H;
    free(heap->array);
    free(heap);
}

void heapifyDown(Heap H, size_t current_index)
{
    HeapLista *heap = H;
    size_t smallest_index = current_index;
    size_t left_child_index = 2 * current_index + 1;
    size_t right_child_index = 2 * current_index + 2;

    if (left_child_index < heap->lenght &&
        heap->array[left_child_index].prioridade < heap->array[smallest_index].prioridade)
    {
        smallest_index = left_child_index;
    }

    if (right_child_index < heap->lenght &&
        heap->array[right_child_index].prioridade < heap->array[smallest_index].prioridade)
    {
        smallest_index = right_child_index;
    }

    if (smallest_index != current_index)
    {
        /* Trocar os elementos na heap */
        HeapNode temp = heap->array[current_index];
        heap->array[current_index] = heap->array[smallest_index];
        heap->array[smallest_index] = temp;
        heapifyDown(heap, smallest_index);
    }
}

Item heapPop(Heap H)
{
     HeapLista *heap = H;
    if (heap->lenght == 0)
    {
        return NULL; // Heap está vazia
    }

    Item menor = heap->array[0].item;
    heap->array[0] = heap->array[heap->lenght - 1];
    heap->lenght--;
    heapifyDown(heap, 0);

    return menor;
}

void heapifyUp(Heap H, size_t current_index)
{
     HeapLista *heap = H;
    while (current_index > 0)
    {
        size_t parent_index = (current_index - 1) / 2;

        if (heap->array[current_index].prioridade < heap->array[parent_index].prioridade)
        {
            /* Trocar os elementos na heap */
            HeapNode temp = heap->array[current_index];
            heap->array[current_index] = heap->array[parent_index];
            heap->array[parent_index] = temp;

            current_index = parent_index;
        }
        else
        {
            break;
        }
    }
}

void heapPush(Heap H, Item item, int prioridade)
{
     HeapLista *heap = H;
    if (heap->lenght == heap->capac)
    {
        // A capacidade da heap foi atingida, pode ser necessário aumentar a capacidade
        return;
    }

    heap->array[heap->lenght].item = item;
    heap->array[heap->lenght].prioridade = prioridade;
    heap->lenght++;
    heapifyUp(heap, heap->lenght - 1);
}
