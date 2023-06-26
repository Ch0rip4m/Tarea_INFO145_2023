//Implementar Dijkstra para las ciudades
//Implementar BFS (Breadth-First Search Algorithm) o MSCP para los archipiélagos

#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <unordered_set>

const int INF = std::numeric_limits<int>::max();

// Estructura para representar una arista en el grafo
struct Edge {
    int to;
    int weight;
    
    Edge(int to, int weight) : to(to), weight(weight) {}
};

// Función para encontrar la ruta más corta utilizando el algoritmo de Dijkstra
void Dijkstra(int start, const std::vector<std::vector<Edge>>& graph, std::vector<int>& distances) {
    int n = graph.size();
    std::vector<bool> visited(n, false); // Nodos visitados
    
    distances[start] = 0; // Distancia al nodo inicial es 0
    
    for (int i = 0; i < n - 1; ++i) {
        int minDistance = INF;
        int minIndex = -1;
        
        // Encuentra el nodo con la distancia mínima no visitado
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && distances[j] < minDistance) {
                minDistance = distances[j];
                minIndex = j;
            }
        }
        
        if (minIndex == -1) {
            break; // No hay más nodos alcanzables
        }
        
        visited[minIndex] = true;
        
        // Actualiza las distancias de los nodos adyacentes
        for (const Edge& edge : graph[minIndex]) {
            int neighbor = edge.to;
            int weight = edge.weight;
            
            if (!visited[neighbor] && distances[minIndex] != INF && distances[minIndex] + weight < distances[neighbor]) {
                distances[neighbor] = distances[minIndex] + weight;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    // Ejemplo de uso del algoritmo de Dijkstra
    
    if (argc != 3) {
        fprintf(stderr, "Run as ./grafos n k\n");
        exit(EXIT_FAILURE);
    }
    
    int n = atoi(argv[1]); // Número total de ciudades
    int k = atoi(argv[2]); // Número de ciudades con puertos marítimos
    
    if (k > n) {
        fprintf(stderr, "k must be less than or equal to n\n");
        exit(EXIT_FAILURE);
    }
    
    // Ajustar el tamaño del grafo para incluir las ciudades con puertos marítimos
    int graphSize = n + k;

    // Grafo ponderado representado como una lista de adyacencia
    std::vector<std::vector<Edge>> graph(graphSize);
    
    // Generar k ciudades con puertos marítimos
    std::unordered_set<int> portCities;
    srand(time(nullptr));
    while (portCities.size() < k) {
        int portCity = rand() % n;
        portCities.insert(portCity);
    }
    
    // Agregar aristas aleatorias al grafo
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int weight = rand() % 10 + 1; // Peso aleatorio entre 1 y 10
            graph[i].push_back(Edge(j, weight));
            graph[j].push_back(Edge(i, weight));
        }
    }
    
    // Conectar las ciudades con puertos marítimos a las otras ciudades
    int portIndex = n;
    for (int portCity : portCities) {
        int weight = rand() % 10 + 1; // Peso aleatorio entre 1 y 10
        graph[portCity].push_back(Edge(portIndex, weight));
        graph[portIndex].push_back(Edge(portCity, weight));
        ++portIndex;
    }
    
    int start = 0; // Nodo inicial
    
    // Vector para almacenar las distancias mínimas desde el nodo inicial
    std::vector<int> distances(graphSize, INF);
    
    Dijkstra(start, graph, distances);
    
    // Imprimir las distancias mínimas desde el nodo inicial
    for (int i = 0; i < n; ++i) {
        std::cout << "Distancia mínima desde " << start << " a " << i << ": " << distances[i] << std::endl;
    }
    
    return 0;
}
