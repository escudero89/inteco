#include <iostream>
#include <vector>

#include "../include/neurona.h"
#include "../include/som.h"
#include "../../Perceptron/include/record.h"

#include "../../utils/utils.h"

using namespace std;

int main() {

#if 0

    // cant_x | cant_y | N
    SOM Som(5, 5, 2);

    vector<vector<float> > datos;

    // rectangle.csv, circle.csv, T.csv
    string trabajar = "rectangle";

    parseCSV<float>("data/" + trabajar + ".csv", datos);

// Segun diapositiva

    /// ORDENAMIENTO GLOBAL [diapos p29 SOM]
    // datos, tasa, varianza, maxit, tasa_fija
    Som.adaptation(datos, 0.8, 5, 1000);

    /// TRANSICION
    Som.adaptation(datos, 0.2, 3, 1000);

    /// CONVERGENCIA
    Som.adaptation(datos, 0.1, 1, 3000, true);

    datos = Som.get_pesos();

    printCSV<float>(datos, "logs/" + trabajar + "_diapos.csv");

/*
// Segun hayken
    /// ORDENAMIENTO
    Som.adaptation(datos, 0.1, 5, 1000);

    /// CONVERGENCIA
    Som.adaptation(datos, 0.01, 1, 12500, true);

    datos = Som.get_pesos();

    printCSV<float>(datos, "logs/" + trabajar + "_hayken.csv");
*/
#endif

#if 1

    // cant_x | cant_y | N | tasa | varianza
    SOM Som(25, 1, 2);

    vector<vector<float> > datos;

    // rectangle.csv, circle.csv, T.csv
    string trabajar = "T";

    parseCSV<float>("data/" + trabajar + ".csv", datos);

// Segun diapositiva

    /// ORDENAMIENTO GLOBAL [diapos p29 SOM]
    // datos, tasa, varianza, maxit, tasa_fija
    Som.adaptation(datos, 0.8, 5, 750);

    /// TRANSICION
    Som.adaptation(datos, 0.2, 3, 1000);

    /// CONVERGENCIA
    Som.adaptation(datos, 0.1, 1, 3000, true);

    datos = Som.get_pesos();

    printCSV<float>(datos, "logs/" + trabajar + "_diapos_single.csv");

/*
// Segun hayken
    /// ORDENAMIENTO
    Som.adaptation(datos, 0.1, 5, 1000);

    /// CONVERGENCIA
    Som.adaptation(datos, 0.01, 1, 12500, true);

    datos = Som.get_pesos();

    printCSV<float>(datos, "logs/" + trabajar + "_hayken_single.csv");
*/

#endif

    return 0;
}
