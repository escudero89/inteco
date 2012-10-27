#ifndef INDIVIDUO_H
#define INDIVIDUO_H

#include <cstdlib>
#include <cmath>

#include <string>
#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
using namespace std;

class Individuo
{
    public:
        string cromosoma;
        vector<float> fenotipo;
        float fitness;
        int tipo_codificacion;
        int fitness_function;

    public:
        Individuo(int tam_cromosoma, int tipo_codificacion, int fitness_function);

        /* Estas funciones variaran segun el problema */
        float evaluarFitness();
        void actualizarFenotipo();
        float getFitness(){return fitness;}




};

#endif // INDIVIDUO_H
