#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>

#include "include/punto.h"
#include "include/poblacion.h"

using namespace std;

int main() {

    srand(time(NULL));

    string rama = "2aaa(l((ax(aaa)(dasd)(dasd))a(r(ddada)(ada)a))(ada))";

    punto origen(0, 0);
/*
    vector<punto> tomas;
    tomas.push_back(punto(5,5));
    tomas.push_back(punto(10,10));
    tomas.push_back(punto(-5,-5));
    tomas.push_back(punto(-10,10));

    Individuo C(origen, tomas, rama);
    short direccion = 4;
    cout<<"Completado forzoso"<<endl;

    double idxazar = 0.2;
    cout << idxazar << endl;
//    string ans = C.forzar_completado(origen, direccion, tomas[2]);
    cout << C.get_spliced_cromosoma(idxazar) << endl;
    cout << C.intercambiarCromosoma("eaea");
//    cout<<endl<<endl<<ans;
//    C.autocompletar();
//    cout << "Cromosoma:\n" << C.get_cromosoma();
*/

/// EJEMPLO DE CRUZA

    vector<punto> tomas2;
    tomas2.push_back(punto(1,1));
    tomas2.push_back(punto(-1,-1));
    tomas2.push_back(punto(-3,-3));
    tomas2.push_back(punto(3,3));
/*
    string ramas1 = "1dada",
        ramas2 = "2aiia";

    Individuo C1(origen, tomas2);
    Individuo C2(origen, tomas2);

    C1.autocompletar();
    C2.autocompletar();

    vector<punto> pos1_r, pos2_r;

    string h1_r, h2_r,
        h1 = C1.get_spliced_cromosoma(0.5, h1_r, pos1_r),
        h2 = C2.get_spliced_cromosoma(0.5, h2_r, pos2_r),
        h1_a = C1.get_cromosoma(),
        h2_a = C2.get_cromosoma();

    cout << "Cromosoma hijo 1: " << C1.intercambiarCromosoma(h2) << endl;
    //cout << "Cromosoma hijo 2: " << C2.intercambiarCromosoma(h1);

    C1.forzarCromosoma(h1_a, h1_r, pos1_r, h1);

    cout << "Cromosoma final: "<< C1.get_cromosoma();
*/

/// Ejemplo de fitness
    Individuo C1(origen, tomas2);

    C1.autocompletar();
    cout << "Cromosoma final: " << C1.get_cromosoma() << endl;

    vector<vector<double> > Field;
    vector<double> P1;

    Poblacion P;
    Field = P.generarMatrizBloques(20, 20);

    cout << "Precio total: "  << C1.evaluarFitness(Field);

/// A ver si puedo guardarlo

    printCSV<double>(Field, "logs/field.dat", false);

    Field = C1.get_puntos_double();
    printCSV<double>(Field, "logs/puntos.dat", false);

    return 0;
}
