#include <iostream>
using namespace std;


int main(int argc, char* argv[]){
    int n = atoi(argv[1]), i, j;
    // imprimir caracteres
    for (i = 0; i < n; i++){
        for (j = 0; j<i; j++ ){
            cout << argv[2];
        }
        cout << endl;
    }
    return 0;
}
