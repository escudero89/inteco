#include <stdio.h>
#include <iostream>

#include "../include/perceptron.h"
#include "../include/utils.h"

using namespace std;

int main(int argc, char **argv) {
    Perceptron A(0.5,3);
    vector<float> V1;
    V1.push_back(190.0);
    V1.push_back(90.0);
    V1.push_back(23.0);
    V1.push_back(1.0);

    A.entrenar(V1);
    return 0;
}
