#ifndef CAPA_H
#define CAPA_H

#include <vector>
#include <cassert>

#include "Miniptron.h"

class Capa {
public:
    short cant_neuronas;
    float tasa, alfa;
    bool es_ultima;
    vector<Miniptron> miniptrones;
    vector<float> output, gradiente_local;
    vector< vector<float> > variacion_pesos;

public:
    Capa(short cant_neuronas, int N, float tasa = 0.1, int cant_neur_siguientes = 0, bool es_ultima=false);
    Capa(){};

	Capa& operator=(const Capa &rhs) {

		if (this != &rhs) {
			this->cant_neuronas = rhs.cant_neuronas;
			this->tasa = rhs.tasa;
			this->alfa = rhs.alfa;
			this->es_ultima = rhs.es_ultima;
			this->miniptrones = rhs.miniptrones;
			this->output = rhs.output;
			this->gradiente_local = rhs.gradiente_local;
			this->variacion_pesos = rhs.variacion_pesos;

		}

		return *this;
	}

    void reinicializar_capa() {
        for (short i = 0; i < cant_neuronas; i++) {
            miniptrones[i].inicializar_neuronas();
        }
    }

	vector<float> get_output() { return output; }
    int get_cant_neuronas() {return cant_neuronas;}
    // A partir de una entrada input, obtengo una salida modificada por pesos
    vector<float> forward_pass(vector<float> input, Capa &capa_siguiente);
    vector<float> forward_pass(vector<float> input);

    vector<float> backward_pass(vector<float> &output, vector<float> yAnterior);

    vector<vector<float> > get_pesos();

    vector<float> get_iesimos_pesos(int i);

    void set_alfa(float alfa) { this->alfa = alfa; }

    void actualizar_pesos();
};

#endif // CAPA_H
