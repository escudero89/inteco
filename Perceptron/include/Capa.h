#ifndef CAPA_H
#define CAPA_H

#include <vector>

#include "Miniptron.h"

class Capa {
    short cant_neuronas;
    float tasa;
    vector<Miniptron> miniptrones;
    vector<float> output;

public:
    Capa(short cant_neuronas, int N, float tasa = 0.1);

    // A partir de una entrada input, obtengo una salida modificada por pesos
    vector<float> forward_pass(vector<float> input);

    vector<float> backward_pass(vector<float> output);
};

#endif // CAPA_H
