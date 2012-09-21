#include <iostream>
#include <vector>

#include "../include/neurona.h"
#include "../include/som.h"

#include "../../utils/utils.h"

using namespace std;

int main() {

    // cant_x | cant_y | N | tasa | varianza
    SOM Som(5, 5, 2, 0.1, 5);

    vector<vector<float> > datos;

    parseCSV<float>("data/circle.csv", datos);

    Som.sampling(datos, 15500); // mas o menos 500xcant_neuronas

    datos = Som.get_pesos();

    printVectorVector<float>(datos);

    return 0;
}
