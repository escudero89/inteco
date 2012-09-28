#include <iostream>
#include <vector>

#include "../include/neurona.h"
#include "../include/som.h"
#include "../../Perceptron/include/record.h"

#include "../../utils/utils.h"

using namespace std;

int main() {

    // cant_x | cant_y | N
    SOM Som(5, 5, 3);

    // Imprimo?
    if (false) {
        //Som.set_print(true);
    }

    vector<vector<float> > datos;

    // rectangle.csv, circle.csv, T.csv
    string trabajar = "clouds";

    parseCSV<float>("data/" + trabajar + "/" + trabajar + ".csv", datos);

// Segun haykin
    /// ORDENAMIENTO
    Som.adaptation(datos, 0.1, 5, 1000);

    /// CONVERGENCIA
    Som.adaptation(datos, 0.01, 1, 1600, true);

    datos = Som.get_pesos();

    printCSV<float>(datos, "logs/" + trabajar + ".csv");

    return 0;
}
