#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>

#include "include/punto.h"
#include "include/individuo.h"

using namespace std;

int main() {

    srand(time(NULL));

    string rama = "";

    punto origen(0, 0);

    vector<punto> tomas;
    tomas.push_back(punto(10,10));
    tomas.push_back(punto(-10,-10));
    tomas.push_back(punto(10,-10));
    tomas.push_back(punto(-10,10));

    Individuo C(origen, tomas);

    C.autocompletar();
    cout << "Cromosoma:\n" << C.get_cromosoma();

    return 0;
}
