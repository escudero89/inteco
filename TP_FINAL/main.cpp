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
    vector<punto> vpunto;
    Individuo ind(origen, tomas2, "");
    Poblacion P(0.6,0.4,0.5,30,origen,tomas2);
    for(unsigned int k = 0 ; k < 1000 ; k++) {
        P.reproduccion();
        cout << "Mejor cromosoma > " << ind.get_cromosoma();

    }

    ind = P.getMejorIndividuo();
    vpunto = ind.get_puntos();
    cout << endl;
    for(unsigned int i = 0; i< ind.get_puntos().size();i++)
        cout << vpunto[i].coordenadas[0] << "," << vpunto[i].coordenadas[1] << endl;
#endif
/*
    printCSV<double>(Field, "logs/field.dat", false);

    Field = C1.get_puntos_double();
    printCSV<double>(Field, "logs/puntos.dat", false);

*/
    return 0;
}
