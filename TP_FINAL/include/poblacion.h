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
    vector<vector <double> > M, fitness_values;

    vector<Individuo> v_individuos;

    unsigned int idx_mejorIndividuo;


public:
    Poblacion(float, float, float, unsigned int, punto, vector<punto> &);

    vector<Individuo> reproduccion();
    Individuo getMejorIndividuo();

    void cruzar(int , int , Individuo &, Individuo &);
    void mutar(Individuo &I);

    vector<vector<double> > generarMatrizBloques(unsigned int, unsigned int);
    vector<vector<double> > get_matrizBloques() { return M; }
    vector<vector<double> > generarMatrizBloques_desdeArchivo(string = "logs/field_base.csv");

    Individuo get_mejor_individuo() { return v_individuos[idx_mejorIndividuo]; }

    void printFitness() { printCSV<double>(fitness_values, "logs/fitness.dat", false); }
};

#endif // POBLACION_H
