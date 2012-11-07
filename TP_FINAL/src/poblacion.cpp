#include <vector>

#include "../include/poblacion.h"
#include "../include/individuo.h"

Poblacion::Poblacion() {
    //ctor
}

/*
"Me retonar una matriz de ceros y unos al azar, de [cant_rows x cant_cols]"
Recibe: las dimensiones
Salida: la matriz de randoms
*/
vector<vector<double> > Poblacion::generarMatrizBloques(unsigned int cant_rows,
                                                        unsigned int cant_cols) {
    vector<vector<double> > Field;
    vector<double> P1;

    for (unsigned int i = 0 ; i < cant_rows ; i++) {
        for (unsigned int j = 0 ; j < cant_cols ; j++) {
            P1.push_back(rand()%2); // 0 libre, 1 ocupado
            cout << P1[j] << "\t";
        }
        cout << endl;
        Field.push_back(P1);
        P1.clear();
    }

    return Field;
}
