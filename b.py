def dijkstra(graph, start):
    def heappop(heap):
        # Remove e retorna o menor elemento da lista, mantendo a propriedade de heap
        if len(heap) == 1:
            return heap.pop()
        smallest = heap[0]
        heap[0] = heap.pop()
        current_index = 0
        while True:
            left_child_index = 2 * current_index + 1
            right_child_index = 2 * current_index + 2
            smallest_index = current_index

            if left_child_index < len(heap) and heap[left_child_index] < heap[smallest_index]:
                smallest_index = left_child_index
            if right_child_index < len(heap) and heap[right_child_index] < heap[smallest_index]:
                smallest_index = right_child_index

            if smallest_index == current_index:
                break

            heap[current_index], heap[smallest_index] = heap[smallest_index], heap[current_index]
            current_index = smallest_index

        return smallest

    def heappush(heap, item):
        # Adiciona um novo elemento ao heap
        heap.append(item)
        current_index = len(heap) - 1
        while current_index > 0:
            parent_index = (current_index - 1) // 2
            if heap[current_index] < heap[parent_index]:
                heap[current_index], heap[parent_index] = heap[parent_index], heap[current_index]
                current_index = parent_index
            else:
                break

    # Inicialização
    distances = {node: float('infinity') for node in graph}
    distances[start] = 0
    priority_queue = [(0, start)]

    while priority_queue:
        current_distance, current_node = heappop(priority_queue)

        # Relaxamento
        for neighbor, weight in graph[current_node].items():
            distance = current_distance + weight
            if distance < distances[neighbor]:
                distances[neighbor] = distance
                heappush(priority_queue, (distance, neighbor))

    return distances

# Exemplo de um grafo ponderado
graph = {
    'A': {'B': 1, 'C': 4},
    'B': {'A': 1, 'C': 2, 'D': 5},
    'C': {'A': 4, 'B': 2, 'D': 1},
    'D': {'B': 5, 'C': 1}
}

start_node = 'A'
result = dijkstra(graph, start_node)

print(f"Distâncias mínimas a partir do nó {start_node}:")
for node, distance in result.items():
    print(f"{node}: {distance}")
