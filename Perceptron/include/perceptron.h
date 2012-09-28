#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <sstream>

#include "../../utils/utils.h"
#include "record.h"

using namespace std;

class Perceptron {
    float
        umbral,			// w_0
        tasa, 			//tasa de aprendizaje
        desvio, media;

    int N;		// cantidad de elementos que conforman el patron -1 (por el valor verdadero)

    vector<float> *pesos;	// W(i)
	vector< vector<float> > *pesos_totales;	// Va juntando la progresion de todos los pesos

    bool is_ploting;
    bool is_recording;
	Record myRecord;    // Para recording

public:

    /* FUNCIONES DE INICIALIZACION Y SETS/GETS */
    Perceptron(int N, float tasa=1.5, bool is_recording = true, float desvio=0.5, float media=0);
    void inicializar_neuronas(float desvio, float media);
    void set_tasa(float tasa) {
        this->tasa = tasa;
    }

    // A motivos de ploteo
    void add_pesos(vector <float> pesos, bool is_ploting = false) {
		pesos.push_back(this->umbral);
		pesos_totales->push_back(pesos);
	}

	void set_ploting (bool is_ploting = false) {
        this->is_ploting = is_ploting;
	}

    /* FUNCIONES DE ENTRENAMIENTO DE NEURONAS */
    float funcion_activacion(vector<float> &pesos, vector<float> &patrones, short tipo = 0);

    bool entrenar(vector<float> patrones);
    bool estEntrenamiento(vector<vector<float> > &estacion);

    float entrenar_helper(vector<float> &patrones);

	/* FUNCIONES DE PRUEBA DE NEURONAS */
    bool trabajar(vector<float> patrones);
    float estTrabajo(vector< vector<float> > &patrones, bool mostrar=false);

    float entrenamiento(vector< vector<float> > &patrones, vector< vector<float> > &trabajos, unsigned int maxIt = 3000, float tol = 0.1);

    /* FUNCION DE PRUEBA DE LAS NEURONAS (para obtener margenes de error) */
    float validacionCruzada(vector<conjuntoDatos> &V, unsigned int maxIt = 3000, float tol = 0.1);

};

#endif // PERCEPTRON_H
