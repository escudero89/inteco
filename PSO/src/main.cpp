#include <iostream>
#include <math.h>

#include "../include/particle.h"
#include "../include/swarm.h"
#include "../../utils/utils.h"

using namespace std;

/// Esta funcion controla las funciones que voy a tener (para evaluar performance)
// Input: Un char que me dice que funcion, y equis con [x,y]
double funciones (vector<double> equis, char function = 'a') {

    double retorno, xy,
        x = equis[0],
        y = equis[1];

    switch(function) {

        case 'a':
            retorno = -x * sin(sqrt(fabs(x)));
            break;

        case 'b':
            retorno = x + 5 * sin(3 * x) + 8 * cos(5 * x);
            break;

        case 'c':
            xy = pow(x, 2) + pow(y, 2);
            retorno = pow(xy, 0.25) * (pow(sin(50 * pow(xy, 0.1)), 2) + 1);
            break;

        case 'd':
            retorno = pow(x - 1,2) - 1;
            break;

        default:
            retorno = -1;
            cout << "Error en la seleccion de funciones." << endl;
    }

    return retorno;

}

int main() {

    srand(time(0));

    // a en rango [-512, 512]
    // b en rango [0, 20]
    // c en rango [-100, 100]

    Swarm S(30, 1, 'b', 0, 20);

    vector<double> pos;

    pos = S.EvaluarSwarm(30);

    cout << "\nPosicion final de pesos [x, y]:\n";
    printVector<double>(pos);

    return 0;
}
