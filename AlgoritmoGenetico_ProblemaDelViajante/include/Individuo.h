#ifndef INDIVIDUO_H
#define INDIVIDUO_H

#include <cstdlib>
#include <cmath>

#include <string>
#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include <algorithm>

#include "../../utils/utils.h"

using namespace std;

class Individuo
{
    public:
        string cromosoma;
        vector<float> fenotipo;
        float fitness;
        int tipo_codificacion;
        int fitness_function;
        vector< vector<float> > ciudades;

    public:
        Individuo(int tam_cromosoma,
                    int tipo_codificacion,
                    int fitness_function,
                    vector<vector<float> > ciudades);

        /* Estas funciones variaran segun el problema */
        float evaluarFitness();
        void actualizarFenotipo();
        float getFitness(){return fitness;}






    string dec2bin(unsigned n){
        const int size=sizeof(n)*8;
        std::string res;
        bool s=0;
        for (int a=0;a<size;a++){
            bool bit=n>>(size-1);
            if (bit)
                s=1;
            if (s)
                res.push_back(bit+'0');
            n<<=1;
        }
        if (!res.size())
            res.push_back('0');


        while(res.size()<4){
            res.insert(res.begin(),'40');
        }

    return res;
}



};

#endif // INDIVIDUO_H
