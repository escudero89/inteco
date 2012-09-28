#include "../include/neurona.h"

Neurona::Neurona(int N, float pos_x, float pos_y) {

	this->N = N;
	this->pos_x = pos_x;
	this->pos_y = pos_y;

	pesos.resize(N);
	inicializar_pesos();

}

void Neurona::inicializar_pesos(float desvio, float media) {

    /// Inicializamos los pesos al azar con valores chicos
    for (unsigned int i = 0; i < N; i++) {
        float r = (rand() % 1001 * 0.002 - 1) * desvio + media;
        pesos[i] = r;
    }

}

// Me actualiza los pesos de la neurona usando la formula 9.13 (Haykin, p451)
void Neurona::update(const vector<float> &patron, float delta) {

	for (unsigned int i = 0; i < N; i++) {
		pesos[i] += delta * (patron[i] - pesos[i]);
	}

}

// Trato de buscar el nivel de parecido entre el patron y los pesos, se puede
// hacer tanto haciendo producto punto y buscando el maximo, o haciendo la
// distancia euclidiana y buscando el minimo.
float Neurona::get_distancia(const vector<float> &patron) {

	float retorno = 0;

	for (unsigned int k = 0, cnt = patron.size(); k < cnt; k++) {
		retorno += pow(pesos[k] - patron[k], 2);
	}

	return sqrt(retorno);

}
