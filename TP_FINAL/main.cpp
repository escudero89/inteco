#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>

#include "include/punto.h"
#include "include/poblacion.h"

using namespace std;

int main() {

    srand(time(0));
    punto origen(0, 0);

    vector<punto> tomas2;
    tomas2.push_back(punto(-2,-2));
    tomas2.push_back(punto(2,2));
    tomas2.push_back(punto(-10,-10));
    tomas2.push_back(punto(10,-10));
    tomas2.push_back(punto(-10,10));
#if 1
do {
    string rama1 = "";
    string rama2 = "";

    Individuo C1(origen, tomas2, rama1, true);//, C2(origen, tomas2);
    Individuo C2(origen, tomas2, rama2, true);//, C2(origen, tomas2);

    cout << "padre1> " << C1.get_cromosoma() << endl;
    cout << "padre2> " << C2.get_cromosoma() << endl;

    cout << "Tomas sin cubrir: " << C1.actualizarTomasLibres();

    C1.cruzarCromosoma(C2, 0.5);

    cout << "hijo1> " << C1.get_cromosoma() << endl;
    cout << "Tomas sin cubrir: " << C1.actualizarTomasLibres() << endl;

    cout << "hijo2> " << C2.get_cromosoma() << endl;
    cout << "Tomas sin cubrir: " << C2.actualizarTomasLibres() << endl;

    C1.mutarCromosoma();
    cout << "hijo1 mutado> " << C1.get_cromosoma() << endl;
    cout << "Tomas sin cubrir: " << C1.actualizarTomasLibres() << endl;
} while (true);
#endif
    //C1.cruzarCromosoma(C2, 0.2);
#if 0

    vector<vector<double> > retorno;
    vector<double> aux;

        aux.push_back(origen.coordenadas[0]);
        aux.push_back(origen.coordenadas[1]);
        retorno.push_back(aux);
        aux.clear();

    for (unsigned int k = 0, kCant = tomas2.size(); k < kCant; k++ ) {
        aux.push_back(tomas2[k].coordenadas[0]);
        aux.push_back(tomas2[k].coordenadas[1]);

        retorno.push_back(aux);
        aux.clear();
    }

    printCSV<double>(retorno, "logs/puntos.dat", false);

    Individuo ind(origen, tomas2, "");

    Poblacion P(0.9,0.2,0.3,100,origen,tomas2);

    unsigned int tamanio;

    for(unsigned int k = 0, base_max = 1000 ; k < base_max ; k++) {

        vector<vector<double> > puntos;

        P.reproduccion();

        puntos = P.get_mejor_individuo().get_puntos_double();

        tamanio = puntos.size();
        vector<double> Vd;


        Vd.push_back((double)tamanio);
        Vd.push_back(-9999.0);

        puntos.insert(puntos.begin(),Vd);

        if (k % (base_max / 30) == 0) {
            printCSV<double>(puntos, "logs/puntos.dat", true);
        }
    }
    P.printFitness();
#endif
/*
    printCSV<double>(Field, "logs/field.dat", false);

    Field = C1.get_puntos_double();
    printCSV<double>(Field, "logs/puntos.dat", false);

*/
    return 0;
}
