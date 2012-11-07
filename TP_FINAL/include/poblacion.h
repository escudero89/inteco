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

    vector<vector<double> > generarMatrizBloques(unsigned int, unsigned int);
};

#endif // POBLACION_H
