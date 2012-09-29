#ifndef NEURONA_H
#define NEURONA_H

#include <cmath>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>

#include "../../utils/utils.h"

using namespace std;

class Neurona {

    vector<float> pesos;
    vector<float> clases; // guardo puntajes para determinar q clase es

    // Cantidad de pesos y clase ganadora
    unsigned int N,
                 clase_ganadora;
	float pos_x,
		  pos_y;

public:
	Neurona() {};
    Neurona(int N, float pos_x, float pos_y, unsigned int cant_clases);
	Neurona(const Neurona &cpy) {
		this->N = cpy.N;
		this->pesos = cpy.pesos;
		this->pos_x = cpy.pos_x;
		this->pos_y = cpy.pos_y;
		this->clases = cpy.clases;
	}

	void inicializar_pesos(float desvio = 0.5, float media = 0);

	void update(const vector<float> &patron, float delta);

    void clase(unsigned int id_clase, float amount) {
        clases[id_clase] += amount;
    }

    void determinar_clase_ganadora();

    unsigned int get_clase() { return clase_ganadora; }

	// GETS and SETS
	void set_pesos(const vector<float> &pesos) {
        this->pesos = pesos;
    }

	vector<float> get_pesos() {
		return pesos;
	}

	float get_distancia(const vector<float> &patron);

	float get_posx() { return pos_x; }
	float get_posy() { return pos_y; }
};

#endif // NEURONA_H
