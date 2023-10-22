#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Estrutura para representar um nó da lista de adjacência
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Estrutura para representar o grafo
typedef struct Graph {
    int numVertices;
    Node* adjacencyList[MAX_VERTICES];
} Graph;

// Função para inicializar um grafo com n vértices
Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;

    for (int i = 0; i < numVertices; ++i) {
        graph->adjacencyList[i] = NULL;
    }

    return graph;
}

// Função para adicionar uma aresta ao grafo
void addEdge(Graph* graph, int src, int dest) {
    // Adiciona a aresta de src para dest
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = dest;
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;

    // Adiciona a aresta de dest para src (grafo não direcionado)
    newNode = (Node*)malloc(sizeof(Node));
    newNode->data = src;
    newNode->next = graph->adjacencyList[dest];
    graph->adjacencyList[dest] = newNode;
}

// Função para realizar a busca em largura no grafo
void BFS(Graph* graph, int startVertex) {
    // Array para rastrear os vértices visitados
    int visited[MAX_VERTICES] = {0};

    // Fila para armazenar os vértices a serem processados
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    // Marca o vértice inicial como visitado e o enfileira
    visited[startVertex] = 1;
    queue[rear++] = startVertex;

    // Loop principal da BFS
    while (front < rear) {
        // Desenfileira um vértice e o imprime
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        // Percorre todos os vértices adjacentes ao vértice atual
        Node* temp = graph->adjacencyList[currentVertex];
        while (temp != NULL) {
            int adjVertex = temp->data;

            // Se o vértice adjacente não foi visitado, marca como visitado e o enfileira
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                queue[rear++] = adjVertex;
            }

            temp = temp->next;
        }
    }
}

int main() {
    // Cria um grafo com 5 vértices
    Graph* graph = createGraph(5);

    // Adiciona arestas ao grafo
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);

    // Realiza a busca em largura a partir do vértice 0
    printf("BFS a partir do vertice 0: ");
    BFS(graph, 0);

    return 0;
}
