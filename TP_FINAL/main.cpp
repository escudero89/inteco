#include <iostream>
#include <string>

#include "include/individuo.h"
#include "include/punto.h"
using namespace std;

int main() {

    string rama = "2ala+a";

    punto origen(0, 0);
    Individuo C(rama, origen);

    origen = C.obtenerPuntoPosicion(rama);

    cout << "Hello world!" << endl;
    cout << C.obtenerSubramaje(3) << endl;
    origen.printPunto();
    return 0;
}
