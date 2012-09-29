#include <iostream>
#include <vector>

#include "../include/neurona.h"
#include "../include/som.h"
#include "../../Perceptron/include/record.h"

#include "../../utils/utils.h"

using namespace std;

int main() {

    /// VIGILAR VARIANZA SI CAMBIAS CANT_X/Y
    // cant_x | cant_y | N | cant_clases
    SOM Som(10, 10, 5, 2);

    // Imprimo?
    if (true) {
        Som.set_print(true);
    }

    vector<vector<float> > datos;

    string trabajar = "phoneme";

    parseCSV<float>("data/" + trabajar + "/" + trabajar + ".csv", datos);

    // Guardo ydeseado en el SOM
    Som.save_labels(datos);

    // Segun haykin
    /// ORDENAMIENTO
    Som.adaptation(datos, 0.1, 3, 1000);

    /// CONVERGENCIA
    Som.adaptation(datos, 0.01, 1, 5000, true);

    Som.set_labels(datos);

    datos = Som.get_pesos();

    printCSV<float>(datos, "logs/" + trabajar + "_haykin.csv");

// CON 100 neuronas me dio (y estos valores de entrenamiento)
/// CON CLOUDS:
// Porcentaje de aciertos: 85.44%
/// CON PHONEME:
// Porcentaje de aciertos: 77.9978%

// ¿Estos valores estan bien? Ni idea jajaj


    return 0;
}
