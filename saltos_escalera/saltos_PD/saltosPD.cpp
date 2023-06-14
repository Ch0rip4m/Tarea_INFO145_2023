#include <iostream>
#include <cmath>
using namespace std;


// Función para contar las formas posibles de subir la escalera sin pisar escalones rotos
int contarFormasDinamica(int E[], int n, int p) {
    int formas[n + 1];
    formas[0] = 1;
    
    // Calcular las formas posibles para cada escalón
    for (int i = 1; i <= n; i++) {
        formas[i] = 0;
        
        // Iterar sobre las posibles potencias de salto
        for (int j = 0; pow(p, j) <= i; j++) {
            int salto = pow(p, j);
            
            // Si el salto no pisa un escalón roto, sumar las formas posibles anteriores
            if (E[i - salto] != -1)
                formas[i] += formas[i - salto];
        }
    }
    
    return formas[n];
}

int main(int argc, char* argv[]) {
    int n = atoi(argv[1]);  // Número de escalones
    int r = atoi(argv[2]);  // Número de escalones rotos
    int p = atoi(argv[3]);  // Potencia de salto de Super Mario
    
    int E[n + 1];
    
    // Inicializar el array de escalones rotos
    for (int i = 0; i <= n; i++)
        E[i] = 0;
    
    // Marcar los escalones rotos
    for (int i = 0; i < r; i++) {
        int roto;
        cout << "Ingrese el escalón roto: ";
        cin >> roto;
        E[roto] = -1;
    }
    
    int formasDinamica = contarFormasDinamica(E, n, p);
    
    // Mostrar el resultado
    cout << "NÚMERO DE FORMAS POSIBLES:  " << formasDinamica << endl;
    
    return 0;
}
