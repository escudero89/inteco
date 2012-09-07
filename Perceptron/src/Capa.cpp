#include "../include/Capa.h"

Capa::Capa(short cant_neuronas, float tasa, int N) {

    this->tasa = tasa;
    vector<Miniptron> VP;

    for (short i = 0; i < cant_neuronas; i++) {
        Miniptron P(N, tasa);
        VP.push_back(P);
    }

    this->miniptrones = VP;
}
