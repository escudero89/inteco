#ifndef POBLACION_H
#define POBLACION_H

#include <vector>
#include <algorithm>
#include <iterator>

#include "individuo.h"
#include "record.h"

using namespace std;

class Poblacion {

    float prob_mutacion,
          brecha_generacional,
          fitness_masCapo;

    unsigned int tam_poblacion;

    punto origen;

    vector<punto> tomas;
    vector<vector <double> > M, fitness_values;

    vector<Individuo> v_individuos;

    unsigned int idx_mejorIndividuo;

    Record myRecord;


public:
    Poblacion(float, float, unsigned int, punto, vector<punto> &, string);

    vector<Individuo> reproduccion();
    Individuo getMejorIndividuo();

    void cruzar(int , int , Individuo &, Individuo &);
    void mutar(Individuo &I);

    vector<vector<double> > generarMatrizBloques(unsigned int, unsigned int);
    vector<vector<double> > get_matrizBloques() { return M; }
    vector<vector<double> > generarMatrizBloques_desdeArchivo(string = "logs/field_base.csv");

    Individuo get_mejor_individuo() { return v_individuos[0]; }
    double get_fitness() { return fitness_masCapo; }

    void printFitness(bool append = false) {
        printCSV<double>(fitness_values, "logs/fitness.dat", append);
        fitness_values.clear(); }

    void printCromosomas();
};

#endif // POBLACION_H
