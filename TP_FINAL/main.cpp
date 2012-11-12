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
    vector<vector<double> > puntos;

    string
        directorio = "espiral",
        archivo = "logs/" + directorio + "/points_base.csv";

    parseCSV<double>(archivo, puntos);

    if (puntos.empty()) {
        cout <<  "ERROR LEYENDO ARCHIVO DE DATOS points_base.csv";
        getchar();
    }

    vector<punto> tomas;
    punto origen(puntos[0][0], puntos[0][1]);

    for (unsigned int i = 1; i < puntos.size(); i++) {
        tomas.push_back(punto(puntos[i][0],puntos[i][1]));
    }

// punto origen = punto(puntos[0][0], puntos[0][1]);
// tomas.clear();
//    tomas.push_back(punto(20,4));
//    tomas.push_back(punto(90,7));
//    tomas.push_back(punto(88,32));

    vector<vector<double> > retorno;
    vector<double> aux;

        aux.push_back(origen.coordenadas[0]);
        aux.push_back(origen.coordenadas[1]);
        retorno.push_back(aux);
        aux.clear();

    for (unsigned int k = 0, kCant = tomas.size(); k < kCant; k++ ) {
        aux.push_back(tomas[k].coordenadas[0]);
        aux.push_back(tomas[k].coordenadas[1]);

        retorno.push_back(aux);
        aux.clear();
    }

    printCSV<double>(retorno, "logs/puntos.dat", false);

    Individuo ind(origen, tomas, "");

    Poblacion P(0.4,0.2,300,origen,tomas);

    unsigned int tamanio;

    P.printFitness();

    // OCULTAMOS SALIDA
    streambuf * old;
    old = cout.rdbuf();

    for(unsigned int k = 0, base_max = 1500 ; true ; k++) {

        cout.rdbuf(0);
        P.reproduccion();

        // Visible
        cout.rdbuf(old);
        cout << "Generacion [" << k << "]. Mejor fitness: " << P.get_fitness() << endl;


        if (k % (base_max / 50) == 0) {
            vector<vector<double> > puntos;
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

    return 0;
}
