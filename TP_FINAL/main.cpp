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
    punto origen(0, 0);

    vector<punto> tomas2;
    tomas2.push_back(punto(10,10));
    tomas2.push_back(punto(-10,-10));
    tomas2.push_back(punto(10,-10));
    tomas2.push_back(punto(-10,10));
/*
    Individuo C1(origen, tomas2, "2a(x(a(l(ada)(aa)))(ai)(ada))", false);//, C2(origen, tomas2);

   cout << "Entrando \n";
    C1.get_puntos();
cout << C1.get_cromosoma() << endl;
cout << C1.get_puntos().size() << " \\ " << C1.get_direcciones().size() << endl;
    for (unsigned int i = 0 ; i<C1.get_direcciones().size(); i++) {
        cout << C1.getDirByIndex(i) << "\t";
    }
*/
    //C1.cruzarCromosoma(C2, 0.2);

    vector<punto> vpunto;
    Individuo ind(origen, tomas2, "");
    Poblacion P(0.4,0.1,0.5,2,origen,tomas2);
    for(unsigned int k = 0 ; k < 400 ; k++) {
        P.reproduccion();
        ind = P.getMejorIndividuo();
        vpunto = ind.get_puntos();

        for(unsigned int i = 0; i< ind.get_puntos().size();i++)
            vpunto[i].printPunto();

        cout << "Mejor cromosoma > " << ind.get_cromosoma();

    }

/*
    printCSV<double>(Field, "logs/field.dat", false);

    Field = C1.get_puntos_double();
    printCSV<double>(Field, "logs/puntos.dat", false);

*/
    return 0;
}
