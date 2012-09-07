#include "../include/Capa.h"

Capa::Capa(short cant_neuronas, float tasa, int N) {
    this->tasa = tasa;
    this->miniptrones.reserve(cant_neuronas);

    for (short i = 0; i < cant_neuronas; i++) {
        Miniptron P(N, tasa);
        this->miniptrones[i] = P;
    }
}
