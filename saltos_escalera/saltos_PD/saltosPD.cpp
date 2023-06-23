#include <iostream>
#include <cmath>
#include <chrono>
#include <cstdlib>
#include <set>
using namespace std;

// Función para contar las formas posibles de subir la escalera sin pisar escalones rotos
long long int contarFormasDinamica(int E[], int n, int p) {
    int formas[n + 1];
    formas[0] = 1;
    
    // Calcular las formas posibles para cada escalón
    for (int i = 1; i <= n; i++) {
        formas[i] = 0;
        
        // Iterar sobre las posibles potencias de salto
        for (int k = 0; pow(p, k) <= i; k++) {
            int salto = pow(p, k);
            
            // Si el salto no pisa un escalón roto, sumar las formas posibles anteriores
            if (E[i - salto] != -1)
                formas[i] += formas[i - salto];
        }
    }
    
    return formas[n];
}

int main(int argc, char* argv[]) 
{
    srand(time(NULL));

    int n = atoi(argv[1]);  // Número de escalones
    int r = atoi(argv[2]);  // Número de escalones rotos
    int p = atoi(argv[3]);  // Potencia de salto de Super Mario
    
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
            cout << "ESCALÓN N° "<< roto << " ROTO" << endl;
            //cout << "Ingrese el escalón roto: ";
            //cin >> roto;
            E[roto] = -1;
        }
    }

    auto tiempo_inicial = chrono::high_resolution_clock::now();
    
    long long int formas_PD = contarFormasDinamica(E, n, p);

    auto tiempo_final = chrono::high_resolution_clock::now();
    
    chrono::duration<double> duracion = tiempo_final - tiempo_inicial;
    double tiempo_total = duracion.count();
    
    // Mostrar el resultado
    cout << "NÚMERO DE FORMAS POSIBLES:  " << formas_PD << endl;
    cout << "TIEMPO DE EJECUCIÓN: " << tiempo_total << " [s]" << endl;
    
    return 0;
}
