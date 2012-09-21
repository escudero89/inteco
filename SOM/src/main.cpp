#include <iostream>
#include <vector>

#include "../include/neurona.h"
#include "../include/som.h"
#include "../../Perceptron/include/record.h"

#include "../../utils/utils.h"

using namespace std;

int main() {

#if 0

    // cant_x | cant_y | N | tasa | varianza
    SOM Som(5, 5, 2, 0.1, 5);

    vector<vector<float> > datos;

    // rectangle.csv, circle.csv, T.csv
    string trabajar = "circle";

    parseCSV<float>("data/" + trabajar + ".csv", datos);

    Som.sampling(datos, 12500); // mas o menos 500xcant_neuronas

    datos = Som.get_pesos();

    printCSV<float>(datos, "logs/" + trabajar + "_retorno.csv");

#endif

#if 1

    // cant_x | cant_y | N | tasa | varianza
    SOM Som(25, 1, 2, 0.1, 5);

    vector<vector<float> > datos;

    // rectangle.csv, circle.csv, T.csv
    string trabajar = "T";

    parseCSV<float>("data/" + trabajar + ".csv", datos);

    Som.sampling(datos, 12500); // mas o menos 500xcant_neuronas

    datos = Som.get_pesos();

    printCSV<float>(datos, "logs/" + trabajar + "_single.csv");

#endif

    return 0;
}
