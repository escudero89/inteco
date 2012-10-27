#ifndef MINIPTRON_H
#define MINIPTRON_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <cmath>

#include "../../utils/utils.h"
#include "record.h"

using namespace std;

class Miniptron {
public:
    int N;
    float tasa, a, salida;
    vector<float> pesos;	// W(i)
    vector<float> pesos_siguientes, delta_anterior;

public:

    /* FUNCIONES DE INICIALIZACION */

    Miniptron(int N, float tasa=1.5, int cant_neur_siguientes=0, float a = 1);

    void inicializar_neuronas(float desvio=0.5, float media=0);

    /* FUNCIONES QUE DEFINEN PARAMETROS */

    void actualizar_pesos(vector <float> &delta);

    void set_tasa(float &tasa) {
        this->tasa = tasa;
    }

    void set_pesos_siguientes(vector<float> pesos_siguientes){
        this->pesos_siguientes = pesos_siguientes;
    }

    /* FUNCIONES QUE OBTIENEN PARAMETROS */

    float get_salida() {
        return salida;
    }

    vector<float> get_pesos() {
        return pesos;
    }

    float get_peso_i(int i) {
        return pesos[i];
    }

    vector<float> get_pesos_siguientes(){
        return this->pesos_siguientes;
    }

    float get_v(vector<float> patrones, bool pop = false);

    vector<float> get_delta_anterior() { return delta_anterior; }

    /* FUNCIONES DE ENTRENAMIENTO DE NEURONAS */
    float funcion_activacion(const vector<float> &pesos,const vector<float> &patrones, char tipo = 0);


    Miniptron& operator=(const Miniptron &rhs) {

		if (this != &rhs) {
			this->N = rhs.N;
            this->tasa = rhs.tasa;
            this->a = rhs.a;
            this->salida = rhs.salida;
            this->pesos = rhs.pesos;
            this->pesos_siguientes = rhs.pesos_siguientes;
            this->delta_anterior = rhs.delta_anterior;
		}

		return *this;
	}

    /// Para SWARM
    void forzar_pesos(vector<float> &nuevos_pesos) {
        pesos = nuevos_pesos;
    }

};

#endif // MINIPTRON_H
