#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>

#include "include/punto.h"
#include "include/poblacion.h"

using namespace std;


///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////

 MARCOS UNA DE DOS:
 a) Los puntos guardados son siempre los mismos.
 b) Tiene menos de busqueda el algoritmo genetico.

 ¿POR QUE?
 Llama a print_tubes() una vez y lo vas a ver.
 O recorre puntos.dat, y vas a ver que siempre
 tiene la misma cantidad de tuberias...

 Sospechosoooooo

 HASTA LAS MANOSSS :D

 Te veo en unas horas. Saludos.

///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////



int main() {

    srand(time(0));
    punto origen(0, 0);

    vector<punto> tomas2;
    tomas2.push_back(punto(10,10));
    tomas2.push_back(punto(-10,-10));
    tomas2.push_back(punto(10,-10));
    tomas2.push_back(punto(-10,10));
#if 0
    string rama = "4aaaaai(x(didaaaaaaiiaaaadaadiaaa)(aa(l(iidaiaaaaaaadaaaaaaada)(aaadaadaaidaaaiaaadaiaaaiaidaaaaaaaaaaaaaaaaaaaadaiadiaaaaadiaada)))(aiaiaaaadaaaaiadaaiaaaaaaaaaaia))";

    Individuo C1(origen, tomas2, rama, false);//, C2(origen, tomas2);

   cout << "Entrando \n";
    C1.get_puntos();
cout << C1.get_cromosoma() << endl;
cout << C1.get_puntos().size() << " \\ " << C1.get_direcciones().size() << endl;
    for (unsigned int i = 0 ; i<C1.get_direcciones().size(); i++) {
        cout << C1.getDirByIndex(i) << "\t";
    }
#endif
    //C1.cruzarCromosoma(C2, 0.2);
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

    printCSV<double>(retorno, "logs/puntos.dat", true);


    Individuo ind(origen, tomas2, "");

    Poblacion P(0.4,0.1,0.5,30,origen,tomas2);

    vector<vector<double> > puntos;

    unsigned int tamanio;

    for(unsigned int k = 0 ; k < 500 ; k++) {

        P.reproduccion();

        puntos = P.getMejorIndividuo().get_puntos_double();

        tamanio = puntos.size();
        vector<double> Vd;


        Vd.push_back((double)tamanio);
        Vd.push_back(-9999.0);


        puntos.insert(puntos.begin(),Vd);

        printCSV<double>(puntos, "logs/puntos.dat", true);

    }

#endif
/*
    printCSV<double>(Field, "logs/field.dat", false);

    Field = C1.get_puntos_double();
    printCSV<double>(Field, "logs/puntos.dat", false);

*/
    return 0;
}
