#ifndef MINIPTRON_H
#define MINIPTRON_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <cmath>

#include "utils.h"
#include "record.h"

using namespace std;

class Miniptron {

    int N;
    float umbral, tasa, a, salida;
    vector<float> pesos;	// W(i)
    vector<float> pesos_siguientes;
public:

    /* FUNCIONES DE INICIALIZACION */

    Miniptron(int N, float tasa=1.5, float a = 1);

    void inicializar_neuronas(float desvio=0.5, float media=0);

    /* FUNCIONES QUE DEFINEN PARAMETROS */

    void set_pesos(vector <float> &delta);

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

    float getPesoI(int i) {
        return pesos[i];
    }

    vector<float> get_pesos_siguientes(){
        return this->pesos_siguientes;
    }
    float get_v(vector<float> patrones, bool pop = false);

    /* FUNCIONES DE ENTRENAMIENTO DE NEURONAS */
    float funcion_activacion(vector<float> &pesos, vector<float> &patrones, char tipo = 0);

};

#endif // MINIPTRON_H
