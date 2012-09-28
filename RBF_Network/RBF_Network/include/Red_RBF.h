#ifndef RED_RBF_H
#define RED_RBF_H

#include <vector>
#include <time.h>
#include <algorithm>
#include <stdio.h>
#include <iostream>

#include "../include/neurona_RBF.h"
#include "../include/neurona.h"
#include "../include/punto.h"


using namespace std;

class Red_RBF
{
    private:
        int N; /* dimension de los datos de entrada */
        float tasa;
        vector<neurona_RBF> capa_0;
        vector<neurona> capa_1;

    public:
        Red_RBF(int N, vector<short> neuronas, float tasa);
        vector< vector<punto> > k_means(vector<punto> V, int k, float tolerancia = 0.01, float desvio=0.5, float media=0);
        void entrenarCapa0(vector<punto> patrones, int k);
        vector<float> probarCapa0(punto P);
        void entrenarCapa1(vector<punto> patrones, vector< vector<float> > yDeseado);
        float probarCapa1(vector<punto> patrones, vector< vector<float> > yDeseado);
        void entrenarRed(vector< vector<float> > V, int maxit = 1);
        float probarRed(vector< vector<float> > V);
};

#endif // RED_RBF_H
