#ifndef RED_H
#define RED_H

#include <iostream>
#include <cassert>
#include <vector>

#include "Capa.h"

using namespace std;

class Red {
    short cant_capas;
    vector<Capa> capas;
    vector<float> input;
    vector< vector< vector<float> > > pesos; //esto queda horriblemente mal, pero pasa por no hacer un buen disenio desde el principio

public:
    Red(vector<short> &Capas, float tasa, int N);

    vector<float> forward_pass(vector<float> input);
    void backward_pass(vector<float> ydeseado);

    vector<float> yAnterior(short indiceCapa);

    void actualizar_pesos();
};

#endif // RED_H
