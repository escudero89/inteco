#include "../include/Capa.h"

Capa::Capa(short cant_neuronas, int N, float tasa) {
    this->tasa = tasa;

    this->miniptrones.reserve(cant_neuronas);
    this->output.reserve(cant_neuronas);

    this->cant_neuronas = cant_neuronas;

    for (short i = 0; i < cant_neuronas; i++) {
        Miniptron P(N, tasa);
        this->miniptrones[i] = P;
    }
}

/* Le pasamos una simple capa de patrones */
vector<float> Capa::forward_pass(vector<float> input) {

    for (short i = 0; i < cant_neuronas ; i++ ) {
        output.push_back(miniptrones[i].get_v(input));
    }

    return output;
}

// vector<float> Capa::backward_pass(vector<float> output) {}
