#include <iostream>
#include <vector>

#include "../include/neurona.h"
#include "../include/som.h"
#include "../../Perceptron/include/record.h"

#include "../../utils/utils.h"

using namespace std;

int main() {

// Lo dejo acomodado para 25 neuronas. Para 100 uso varianza 3 y 18 

#if 0

    // cant_x | cant_y | N
    SOM Som(5, 5, 2);

    // Imprimo?
    if (true) {
        Som.set_print(true);
    }

    vector<vector<float> > datos;

    // rectangle.csv, circle.csv, T.csv
    string trabajar = "rectangle";

    parseCSV<float>("data/" + trabajar + ".csv", datos);

// Segun haykin
    /// ORDENAMIENTO
    Som.adaptation(datos, 0.1, 2.25, 1000);

    /// CONVERGENCIA
    Som.adaptation(datos, 0.01, 1, 5000, true);

    datos = Som.get_pesos();

    printCSV<float>(datos, "logs/" + trabajar + "_haykin.csv");

#endif

#if 0

    // cant_x | cant_y | N | tasa | varianza
    SOM Som(25, 1, 2);

    // Imprimo?
    if (true) {
        Som.set_print(true);
    }

    vector<vector<float> > datos;

    // rectangle.csv, circle.csv, T.csv
    string trabajar = "T";

    parseCSV<float>("data/" + trabajar + ".csv", datos);

// Segun haykin (mi varianza tiene que ser mas grande, debido al a unidimensionalidad
    /// ORDENAMIENTO
    Som.adaptation(datos, 0.1, 5, 1000);

    /// CONVERGENCIA
    Som.adaptation(datos, 0.001, 1, 5000, true);

    datos = Som.get_pesos();

    printCSV<float>(datos, "logs/" + trabajar + "_haykin.csv");
#endif

    return 0;
}
