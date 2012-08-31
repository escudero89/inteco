#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "../include/utils.h"

using namespace std;

class Perceptron {
    vector<float> *pesos;	// W(i)
    float umbral;			// w_0
    int N;					// cantidad de elementos que conforman el patron -1 (por el valor verdadero)
    float tasa; 			//tasa de aprendizaje

    float desvio, media;

	vector< vector<float> > *pesos_totales;	// Va juntando la progresion de todos los pesos

public:

    /* FUNCIONES DE INICIALIZACION Y SETS/GETS */
    Perceptron(int N, float tasa=1.5, float desvio=0.5, float media=0);
    void inicializar_neuronas(float desvio, float media);
    void set_tasa(float tasa) {
        this->tasa = tasa;
    }

    // A motivos de ploteo
    void add_pesos(vector <float> & pesos) {
		pesos_totales->push_back(pesos);
	}

    /* FUNCIONES DE ENTRENAMIENTO DE NEURONAS */
    float funcion_activacion(vector<float> &pesos, vector<float> &patrones, short tipo = 0);

    bool entrenar(vector<float> patrones);
    bool estEntrenamiento(vector<vector<float> > &estacion);

    //Trabaja con patron y devuelve si acerto o no
    bool trabajar(vector<float> patrones);

    //Trabaja con patrones y devuelve % de aciertos
    float estTrabajo(vector< vector<float> > &patrones, bool mostrar=false);

    float entrenamiento(vector< vector<float> > &patrones, vector< vector<float> > &trabajos, unsigned int maxIt = 3000, float tol = 0.1);

    /* FUNCION DE PRUEBA DE LAS NEURONAS (para obtener margenes de error) */
    float validacionCruzada(vector<conjuntoDatos> &V, unsigned int maxIt = 3000, float tol = 0.1);

};

#endif // PERCEPTRON_H
