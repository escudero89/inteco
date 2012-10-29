#ifndef POBLACION_H
#define POBLACION_H

#include "Individuo.h"
#include <algorithm>
#include <cstdio>

class Poblacion
{
    public:
        vector<Individuo> individuos;
        float brecha_generacional;
        float prob_cruza;
        float prob_mut;
        int maxima_poblacion;
        int minima_poblacion;
        vector<vector<float> > ciudades;


    public:
        Poblacion(      int cantIndividuos,
                        int tamCromosoma,
                        float brecha,
                        int tipo_codificacion,
                        int fitness_function,
                        float prob_cruza,
                        float prob_mut,
                        int maxima_poblacion,
                        int minima_poblacion,
                        vector<vector<float> > const &ciudades);

        void reproduccion(vector<Individuo> &indv_seleccionados);
        void cruzar(Individuo I1, Individuo I2, Individuo &I3, Individuo &I4);
        void mutar(Individuo &I);
        float getProbCruza(){return prob_cruza;}
        float getProbMut(){return prob_mut;}
        void evaluarFitness();
        void actualizarFenotipo();
        int getMejorIndividuo();



};

#endif // POBLACION_H
