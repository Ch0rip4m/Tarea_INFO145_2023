//Implementar Dijkstra para las ciudades
//Implementar BFS (Breadth-First Search Algorithm) o MSCP para los archipiélagos

//Implementar Dijkstra para las ciudades
//Implementar BFS (Breadth-First Search Algorithm) para las islas

#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <unordered_set>
#include <queue>

using namespace std;

const int INF = numeric_limits<int>::max();

// Estructura para representar una arista en el grafo
struct Edge {
    int to;
    int weight;

    Edge(int to, int weight) : to(to), weight(weight) {}
};

// Función para encontrar el camino más barato hacia alguna ciudad con puerto marítimo utilizando Dijkstra
int DijkstraWithPorts(int start, const vector<vector<Edge>>& graph, const unordered_set<int>& portCities) {
    int n = graph.size();
    vector<int> distances(n, INF); // Distancias mínimas desde el nodo inicial
    vector<bool> visited(n, false); // Nodos visitados

    distances[start] = 0; // Distancia al nodo inicial es 0

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, start));

    while (!pq.empty()) {
        int currNode = pq.top().second;
        pq.pop();

        if (portCities.count(currNode) > 0) {
            return distances[currNode]; // Se encontró una ciudad con puerto marítimo
        }

        if (visited[currNode]) {
            continue;
        }

        visited[currNode] = true;

        // Actualiza las distancias de los nodos adyacentes
        for (const Edge& edge : graph[currNode]) {
            int neighbor = edge.to;
            int weight = edge.weight;

            if (!visited[neighbor] && distances[currNode] != INF && distances[currNode] + weight < distances[neighbor]) {
                distances[neighbor] = distances[currNode] + weight;
                pq.push(make_pair(distances[neighbor], neighbor));
            }
        }
    }

    return -1; // No se encontró ninguna ciudad con puerto marítimo alcanzable desde el nodo inicial
}

// Función para realizar la búsqueda en anchura (BFS) para las islas
void BFSForIslands(int start, const vector<vector<Edge>>& graph, vector<bool>& visited) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int currNode = q.front();
        q.pop();

        // Procesar el nodo actual, si es necesario

        // Recorrer los nodos adyacentes
        for (const Edge& edge : graph[currNode]) {
            int neighbor = edge.to;

            // Si el nodo adyacente no ha sido visitado, agregarlo a la cola y marcarlo como visitado
            if (!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = true;

                // Procesar la arista (currNode, neighbor) si es necesario
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Run as ./grafos n k m" << endl;
        return 1;
    }

    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    int m = atoi(argv[3]);

    // Ajustar el tamaño del grafo para incluir las ciudades con puertos marítimos y las islas
    int cityGraphSize = n + k;
    int islandGraphSize = m;

    // Grafo ponderado de las ciudades representado como una lista de adyacencia
    vector<vector<Edge>> cityGraph(cityGraphSize);

    // Grafo ponderado de las islas representado como una lista de adyacencia
    vector<vector<Edge>> islandGraph(islandGraphSize);

    // Generar k ciudades con puertos marítimos
    unordered_set<int> portCities;
    srand(time(nullptr));
    while (portCities.size() < k) {
        int portCity = rand() % n;
        portCities.insert(portCity);
    }

    // Agregar aristas aleatorias al grafo de las ciudades (dirigido)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                int weight = rand() % 10 + 1; // Peso aleatorio entre 1 y 10
                cityGraph[i].push_back(Edge(j, weight));
            }
        }
    }

    // Conectar las ciudades con puertos marítimos a las otras ciudades
    int portIndex = n;
    for (int portCity : portCities) {
        int weight = rand() % 10 + 1; // Peso aleatorio entre 1 y 10
        cityGraph[portCity].push_back(Edge(portIndex, weight));
        ++portIndex;
    }

    // Agregar aristas aleatorias para las islas
    for (int i = 0; i < islandGraphSize; ++i) {
        for (int j = i + 1; j < islandGraphSize; ++j) {
            int weight = rand() % 10 + 1; // Peso aleatorio entre 1 y 10
            islandGraph[i].push_back(Edge(j, weight));
            islandGraph[j].push_back(Edge(i, weight));
        }
    }

    // Realizar la búsqueda en anchura (BFS) para las islas
    vector<bool> islandVisited(islandGraphSize, false);
    for (int i = 0; i < islandGraphSize; ++i) {
        if (!islandVisited[i]) {
            BFSForIslands(i, islandGraph, islandVisited);
        }
    }

    // Fusionar los grafos de las ciudades y las islas
    vector<vector<Edge>> graph(cityGraphSize + islandGraphSize);
    for (int i = 0; i < cityGraphSize; ++i) {
        graph[i] = cityGraph[i];
    }
    for (int i = 0; i < islandGraphSize; ++i) {
        for (const Edge& edge : islandGraph[i]) {
            int adjustedTo = edge.to + cityGraphSize; // Ajustar los índices de las islas
            graph[i + cityGraphSize].push_back(Edge(adjustedTo, edge.weight));
        }
    }

    int start = 0; // Nodo inicial

    int shortestDistance = DijkstraWithPorts(start, graph, portCities);

    if (shortestDistance != -1) {
        cout << "Distancia mínima hacia una ciudad con puerto marítimo desde el nodo S: " << shortestDistance << endl;
    } else {
        cout << "No se encontró ninguna ciudad con puerto marítimo alcanzable desde el nodo " << start << endl;
    }

    return 0;
}

