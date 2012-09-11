#ifndef CAPA_H
#define CAPA_H

#include <vector>

#include "Miniptron.h"

class Capa {
public:
    short cant_neuronas;
    float tasa;
	
    vector<Miniptron> miniptrones;
    vector<float> output;

public:
    Capa(short cant_neuronas, int N, float tasa = 0.1);
    Capa(){};
	
	Capa& operator=(const Capa &rhs) {
		
		if (this != &rhs) {
			this->cant_neuronas = rhs.cant_neuronas;
			this->tasa = rhs.tasa;
			this->miniptrones = rhs.miniptrones;
			this->output = rhs.output;
		}
		
		return *this;
	}
	
    // A partir de una entrada input, obtengo una salida modificada por pesos
    vector<float> forward_pass(vector<float> input);

    vector<float> backward_pass(vector<float> output);
};

#endif // CAPA_H
