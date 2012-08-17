#include <stdio.h>
#include <iostream>

#include "../include/perceptron.h"
#include "../include/utils.h"

using namespace std;

int main(int argc, char **argv) {
    Perceptron A(3);
    vector< vector<float> > V1;

    parseCSV("src/basket.txt", V1);
    printVectorVector <float> (V1);

    A.estEntrenamiento(V1);

    return 0;
}
