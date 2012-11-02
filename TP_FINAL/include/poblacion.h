#ifndef POBLACION_H
#define POBLACION_H

#include <vector>

#include "individuo.h"

using namespace std;

class Poblacion {
    vector<Individuo> v_individuos;


public:
    Poblacion();
    void generarPoblacion();
};

#endif // POBLACION_H
