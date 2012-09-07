#ifndef MINIPTRON_H
#define MINIPTRON_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <sstream>

#include "utils.h"
#include "record.h"

using namespace std;

class Miniptron {
public:
    float umbral, tasa;
    int N;

    vector<float> *pesos;	// W(i)


    /* FUNCIONES DE INICIALIZACION Y SETS/GETS */
    Miniptron(int N, float tasa=1.5);
    void inicializar_neuronas(float desvio=0.5, float media=0);

    void set_tasa(float tasa) {
        this->tasa = tasa;
    }

    Miniptron(const Miniptron &CP){
        this->umbral = CP.umbral;
        this->tasa = CP.tasa;
        this->N = CP.N;
    }

    /* FUNCIONES DE ENTRENAMIENTO DE NEURONAS */
    float funcion_activacion(vector<float> &pesos, vector<float> &patrones, short tipo = 0);

    bool entrenar(vector<float> patrones);
    bool estEntrenamiento(vector<vector<float> > &estacion);

    float entrenar_helper(vector<float> &patrones);

	/* FUNCIONES DE PRUEBA DE NEURONAS */
    bool trabajar(vector<float> patrones);
    float estTrabajo(vector< vector<float> > &patrones);

    float entrenamiento(vector< vector<float> > &patrones, vector< vector<float> > &trabajos, unsigned int maxIt = 3000, float tol = 0.1);

    /* FUNCION DE PRUEBA DE LAS NEURONAS (para obtener margenes de error) */
    float validacionCruzada(vector<conjuntoDatos> &V, unsigned int maxIt = 3000, float tol = 0.1);

};

#endif // MINIPTRON_H
