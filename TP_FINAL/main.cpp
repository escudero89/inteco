#include <iostream>

#include "include/individuo.h"
#include "include/punto.h"
using namespace std;

int main() {

    punto origen(0, 0);
    Individuo C("2aadaiaa", origen);

    origen = C.obtenerPuntoPosicion("2aadaiaa");

    cout << "Hello world!" << endl;
    origen.printPunto();
    return 0;
}
