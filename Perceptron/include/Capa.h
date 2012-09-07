#ifndef CAPA_H
#define CAPA_H

#include <vector>

#include "Miniptron.h"

class Capa {
public:
    float tasa;
    vector<Miniptron> miniptrones;

    Capa(){};
    Capa(short cant_neuronas, float tasa, int N);
    Capa(const Capa &CC) {
        this->tasa = CC.tasa;
        this->miniptrones = CC.miniptrones;
    }
};

#endif // CAPA_H
