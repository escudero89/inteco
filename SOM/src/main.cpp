#include <iostream>
#include <vector>

#include "../include/neurona.h"
#include "../include/som.h"

#include "../../utils/utils.h"

using namespace std;

int main() {

    // cant_x | cant_y | N | tasa | varianza
    SOM Som(10, 10, 2, 0.1, 5);

    vector<vector<float> > datos;

    parseCSV<float>("data/rectangle.csv", datos);

    Som.sampling(datos, 500*100);

    datos = Som.get_pesos();

    printVectorVector<float>(datos);

    return 0;
}
