#include <stdio.h>
#include <iostream>

#include "../include/perceptron.h"
#include "../include/utils.h"

using namespace std;

int main(int argc, char **argv) {
    Perceptron A(3, 0.4);
    vector< vector<float> > V1;

    parseCSV <float> ("src/basket.txt", V1);
    printVectorVector <float> (V1);


    //Entrenamiento
    for(int i=0; i<30; i++)
        A.estEntrenamiento(V1);

    //Prueba
    A.estTrabajo(V1, true);

    return 0;
}
