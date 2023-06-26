#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <unordered_set>
#include <fstream>

using namespace std;

const int INF = numeric_limits<int>::max();

// Estructura para representar una arista en el grafo
struct Edge {
    int to;
    int weight;

    Edge(int to, int weight) : to(to), weight(weight) {}
};

// Función para encontrar el camino más barato hacia alguna ciudad con puerto marítimo utilizando Dijkstra
int DijkstraWithPorts(int S, const vector<vector<Edge>>& graph, const unordered_set<int>& portCities) {
    int n = graph.size();
    vector<int> distances(n, INF); // Distancias mínimas desde el nodo inicial
    vector<bool> visited(n, false); // Nodos visitados

    distances[S] = 0; // Distancia al nodo inicial es 0

    while (true) {
        int currNode = -1;
        int minDistance = INF;

        // Encuentra el nodo no visitado con la distancia mínima actual
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && distances[i] < minDistance) {
                currNode = i;
                minDistance = distances[i];
            }
        }

        if (currNode == -1) {
            break; // No quedan nodos por visitar
        }

        if (portCities.count(currNode) > 0) {
            return distances[currNode]; // Se encontró una ciudad con puerto marítimo
        }

        visited[currNode] = true;

        // Actualiza las distancias de los nodos adyacentes
        for (const Edge& edge : graph[currNode]) {
            int neighbor = edge.to;
            int weight = edge.weight;

            if (!visited[neighbor] && distances[currNode] != INF && distances[currNode] + weight < distances[neighbor]) {
                distances[neighbor] = distances[currNode] + weight;
            }
        }
    }

    return -1; // No se encontró ninguna ciudad con puerto marítimo alcanzable desde el nodo inicial
}

// Función para generar el código DOT para visualizar el grafo con Graphviz
string generateDotCode(const vector<vector<Edge>>& graph, const unordered_set<int>& portCities) {
    string dotCode = "digraph G {\n";

    int n = graph.size();

    // Agregar nodos al código DOT
    for (int i = 0; i < n; ++i) {
        dotCode += "    " + to_string(i);
        if (portCities.count(i) > 0) {
            dotCode += " [shape=box]";
        }
        dotCode += ";\n";
    }

    // Agregar aristas al código DOT
    for (int i = 0; i < n; ++i) {
        for (const Edge& edge : graph[i]) {
            dotCode += "    " + to_string(i) + " -> " + to_string(edge.to) + " [label=\"" + to_string(edge.weight) + "\"];\n";
        }
    }

    dotCode += "}\n";

    return dotCode;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Run as ./grafos n k m" << endl;
        return 1;
    }

    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    int m = atoi(argv[3]);

    // Grafo ponderado de las ciudades representado como una lista de adyacencia
    vector<vector<Edge>> cityGraph(n); // El tamaño del grafo de ciudades es n

    // Grafo ponderado de las islas representado como una lista de adyacencia
    vector<vector<Edge>> islandGraph(m);

    // Generar k ciudades con puertos marítimos
    unordered_set<int> portCities;
    srand(time(nullptr));

    int S = 0; // Nodo inicial

    while (portCities.size() < k) {
        int portCity = rand() % n;
        if(portCity != S){ //VERIFICA
            portCities.insert(portCity);
        }
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
    for (int portCity : portCities) {
        int weight = rand() % 10 + 1; // Peso aleatorio entre 1 y 10
        cityGraph[portCity].push_back(Edge(portCity, weight)); // Conexión a sí mismo
    }

    // Agregar aristas aleatorias para las islas
    for (int i = 0; i < m; ++i) {
        for (int j = i + 1; j < m; ++j) {
            int weight = rand() % 10 + 1; // Peso aleatorio entre 1 y 10
            islandGraph[i].push_back(Edge(j, weight));
            islandGraph[j].push_back(Edge(i, weight));
        }
    }

    // Fusionar los grafos de las ciudades y las islas
    vector<vector<Edge>> graph(n + m);
    for (int i = 0; i < n; ++i) {
        graph[i] = cityGraph[i];
    }
    for (int i = 0; i < m; ++i) {
        for (const Edge& edge : islandGraph[i]) {
            int adjustedTo = edge.to + n; // Ajustar los índices de las islas
            graph[i + n].push_back(Edge(adjustedTo, edge.weight));
        }
    }

    
    

    int shortestDistance = DijkstraWithPorts(S, graph, portCities);

    if (shortestDistance != -1) {
        cout << "Distancia mínima hacia una ciudad con puerto marítimo desde el nodo S: " << shortestDistance << endl;
    } else {
        cout << "No se encontró ninguna ciudad con puerto marítimo alcanzable desde el nodo " << S << endl;
    }


    // Crear archivo Graphviz
    ofstream dotFile("graph.dot");
    if (!dotFile) {
        cerr << "Error al abrir el archivo graph.dot" << endl;
        return 1;
    }

    // Escribir encabezado del archivo
    dotFile << "digraph G {" << endl;

    // Escribir nodos
    for (int i = 0; i < n; ++i) {
        dotFile << "  " << i << " [";
        if (i == S) {
            dotFile << "style=filled, fillcolor=skyblue, ";
        }
        if (portCities.count(i) > 0) {
            dotFile << "shape=circle, style=filled, fillcolor=green, ";
        }
        dotFile << "label=\"" << i << "\"];" << endl;
    }

    // Escribir aristas
    for (int i = 0; i < n; ++i) {
        for (const Edge& edge : graph[i]) {
            dotFile << "  " << i << " -> " << edge.to << " [label=\"" << edge.weight << "\"];" << endl;
        }
    }

    // Escribir cierre del archivo
    dotFile << "}" << endl;

    // Cerrar archivo
    dotFile.close();

    cout << "Archivo graph.dot generado correctamente." << endl;

    return 0;
}
