#ifndef POBLACION_H
#define POBLACION_H

#include "Individuo.h"
#include <algorithm>
#include <cstdio>

class Poblacion
{
    private:
        vector<Individuo> individuos;
        float brecha_generacional;
        float prob_cruza;
        float prob_mut;


    public:
        Poblacion(int cantIndividuos, int tamCromosoma, float brecha, int tipo_codificacion, int fitness_function, float prob_cruza, float prob_mut);
        void reproduccion(vector<Individuo> &indv_seleccionados);
        void cruzar(Individuo I1, Individuo I2, Individuo &I3, Individuo &I4);
        void mutar(Individuo &I);
        float getProbCruza(){return prob_cruza;}
        float getProbMut(){return prob_mut;}

};

#endif // POBLACION_H
