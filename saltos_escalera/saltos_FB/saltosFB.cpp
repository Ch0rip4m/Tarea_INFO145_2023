#include <iostream>
#include <cmath>
using namespace std;

// Función recursiva para contar las formas posibles de subir la escalera sin pisar escalones rotos
int contarFormasFuerzaBruta(int E[], int n, int p) {
    // Si ya estamos en el último escalón, retornamos 1 para indicar que se alcanzó el objetivo
    if (n == 1)
        return 1;
    
    int formas = 0;
    
    // Iteramos sobre las posibles potencias de salto
    for (int i = 0; pow(p, i) <= n; i++) {
        int salto = pow(p, i);
        
        // Si el salto no pisa un escalón roto, llamamos recursivamente para el siguiente escalón
        if (n - salto >= 1 && E[n - salto] != -1)
            formas += contarFormasFuerzaBruta(E, n - salto, p);
    }
    
    return formas;
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
    
    
    int formasFuerzaBruta = contarFormasFuerzaBruta(E, n, p);
    
    // Mostrar el resultado
    cout << "NÚMERO DE FORMAS POSIBLES: " << formasFuerzaBruta << endl;
    
    return 0;
}
