#ifndef POBLACION_H
#define POBLACION_H

#include <vector>
#include <algorithm>
#include <iterator>

#include "individuo.h"

using namespace std;

class Poblacion {

    float prob_cruza,
          prob_mutacion,
          brecha_generacional;

    unsigned int tam_poblacion;

    punto origen;

    vector<punto> tomas;
    vector<vector <double> > M;


    vector<Individuo> v_individuos;


public:
    Poblacion(float, float, float, unsigned int, punto, vector<punto> &);

    vector<Individuo> reproduccion();
    Individuo getMejorIndividuo();

    void cruzar(int , int , Individuo &, Individuo &);
    void mutar(Individuo &I);

    vector<vector<double> > generarMatrizBloques(unsigned int, unsigned int);
    vector<vector<double> > get_matrizBloques() { return M; }
};

#endif // POBLACION_H
