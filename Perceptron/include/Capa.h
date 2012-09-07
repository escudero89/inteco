#ifndef CAPA_H
#define CAPA_H

#include <vector>

#include "Miniptron.h"

class Capa {
    float tasa;
    vector<Miniptron> miniptrones;

public:
    Capa(short cant_neuronas, float tasa, int N);
};

#endif // CAPA_H
