#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

class Perceptron {
    vector<float> *pesos;	// W(i)    
    float umbral;			// w_0
    int N;					// cantidad de elementos que conforman el patron -1 (por el valor verdadero)
    float tasa; 			//tasa de aprendizaje
	
	vector< vector<float> > *pesos_totales;	// Va juntando la progresion de todos los pesos

public:

    Perceptron(int N, float tasa=1.5, float desvio=0.5, float media=0);

    bool entrenar(vector<float> patrones);
    bool estEntrenamiento(vector<vector<float> > &estacion);
    bool trabajar(vector<float> patrones); //Trabaja con patron y devuelve si acerto o no
    float estTrabajo(vector< vector<float> > &patrones, bool mostrar=false); //Trabaja con patrones y devuelve % de aciertos

    float entrenamiento(vector< vector<float> > &patrones, vector< vector<float> > &trabajos, unsigned int maxIt = 3000, float tol = 0.1);

    void set_tasa(float tasa) {
        this->tasa = tasa;
    }

    float dot(vector<float> &V1, vector<float> &V2);
	
	// Para ploteo
	void add_pesos(vector <float> & pesos) {
		pesos_totales->push_back(pesos);
	}
	
	
};

#endif // PERCEPTRON_H
