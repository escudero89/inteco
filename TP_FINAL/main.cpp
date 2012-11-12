#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>

#include "../utils/utils.h"
#include "include/poblacion.h"

using namespace std;

int main() {

    srand(time(0));
    vector<double> puntos;

    string
        directorio = "espiral",
        archivo = "logs/" + directorio + "/points_base.csv";

//    parseCSV<double>(archivo, puntos);

    vector<punto> tomas2;
    punto origen(7, 3);

    tomas2.push_back(punto(-5,5));
//    tomas2.push_back(punto(20,4));
//    tomas2.push_back(punto(90,7));
//    tomas2.push_back(punto(88,32));

#if 1

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

    Poblacion P(0.4,0.2,300,origen,tomas2);

    unsigned int tamanio;

    P.printFitness();

    // OCULTAMOS SALIDA
    streambuf * old;
    old = cout.rdbuf();

    for(unsigned int k = 0, base_max = 1500 ; true ; k++) {

        vector<vector<double> > puntos;

        cout.rdbuf(0);
        P.reproduccion();

        // Visible
        cout.rdbuf(old);
        cout << "Generacion [" << k << "]. Mejor fitness: " << P.get_fitness() << endl;


        if (k % (base_max / 50) == 0) {
            puntos = P.get_mejor_individuo().get_puntos_double();

            tamanio = puntos.size();
            vector<double> Vd;


            Vd.push_back((double)tamanio);
            Vd.push_back(-9999.0);

            puntos.insert(puntos.begin(),Vd);

            printCSV<double>(puntos, "logs/puntos.dat", true);
            P.printFitness(true);
        }
    }

#endif
/*
    printCSV<double>(Field, "logs/field.dat", false);

    Field = C1.get_puntos_double();
    printCSV<double>(Field, "logs/puntos.dat", false);

*/
    return 0;
}
