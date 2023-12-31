#include <iostream>
#include <cmath>
#include <chrono>
#include <cstdlib>
#include <set>
using namespace std;

// Función recursiva para contar las formas posibles de subir la escalera sin pisar escalones rotos
long long int contarFormasFuerzaBruta(int E[], int n, int p) {
    if (n == 0) {
        return 1;
    }
    
    int formas = 0;
    
    // Iterar sobre todas las posibles combinaciones de saltos
    for (int k = 0; k <= n; k++) {
        // Verificar si el salto es una potencia de p menor o igual a n
        int salto = pow(p, k);
        if (salto > n) {
            break;
        }
        
        // Verificar si el salto no pisa un escalón roto
        if (E[n - salto] != -1) {
            formas += contarFormasFuerzaBruta(E, n - salto, p);
        }
    }
    
    return formas;
}
    

int main(int argc, char *argv[])
{
    if (argc != 4) {
        fprintf(stderr, "Run as ./saltosFB n r p\n");
        exit(EXIT_FAILURE);
    }
    srand(time(NULL));

    int n = atoi(argv[1]); // Número de escalones
    int r = atoi(argv[2]); // Número de escalones rotos
    int p = atoi(argv[3]); // Potencia de salto de Super Mario

    int E[n + 1];
    set<int> escalones_rotos;

    // Inicializar el array de escalones rotos
    for (int i = 0; i <= n; i++)
        E[i] = 0;

    // Marcar los escalones rotos
    while (escalones_rotos.size() < r)
    {
        int roto = 1 + rand() % n;
        if (escalones_rotos.find(roto) == escalones_rotos.end())
        {
            escalones_rotos.insert(roto);
            //cout << "ESCALÓN N° "<< roto << " ROTO" << endl;
            //cout << "Ingrese el escalón roto: ";
            //cin >> roto;
            E[roto] = -1;
        }
    }
    auto tiempo_inicial = chrono::high_resolution_clock::now();

    long long int formas_FB = contarFormasFuerzaBruta(E, n, p);

    auto tiempo_final = chrono::high_resolution_clock::now();

    chrono::duration<double> duracion = tiempo_final - tiempo_inicial;
    double tiempo_total = duracion.count();

    // Mostrar el resultado
    cout << "NÚMERO DE FORMAS POSIBLES: " << formas_FB << endl;
    cout << "TIEMPO DE EJECUCIÓN: " << tiempo_total << " [s]" << endl;

    return 0;
}
