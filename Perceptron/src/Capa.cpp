#include "../include/Capa.h"

Capa::Capa(short cant_neuronas, int N, float tasa) {
    this->tasa = tasa;

    this->miniptrones.reserve(cant_neuronas);
    this->output.reserve(cant_neuronas);

    this->cant_neuronas = cant_neuronas;

    for (short i = 0; i < cant_neuronas; i++) {
        Miniptron P(N, tasa);
        this->miniptrones.push_back(P);
    }
}

/* Le pasamos una simple capa de patrones */
vector<float> Capa::forward_pass(vector<float> input, vector< vector<float> > &P) {
    vector< vector<float> > P;
    P.resize(cant_neuronas);

    for (short i = 0; i < cant_neuronas ; i++ ) {
		 P[i] = miniptrones[i].get_pesos();
		output.push_back(miniptrones[i].get_v(input));
	}

    return output;
}

vector<float> Capa::backward_pass(vector<float> &output, vector< vector<float> > pesos) {

    float y;
    gradiente_local.resize(cant_neuronas);
    variacion_pesos.resize(cant_neuronas);

    for (short i = 0; i < cant_neuronas ; i++ ) {
		y = miniptrones[i].get_salida();

        if (pesos.size()) {
            vector <float> old_gradiente = output;
            // El ouput aca es el gradiente local de la capa siguiente
            printVector(pesos[i]);
            printVector(old_gradiente);
            gradiente_local[i] =  0.5 * (1 + y) * (1 - y) * dot<float> (pesos[i], old_gradiente);
        } else {
            // Basada en la sigmoidea derivada de la diapositiva, el ouput es ydeseado
            gradiente_local[i] = 0.5 * (output[i] - y) * (1 + y) * (1 - y);
        }

        // Guardamos la variacion de los pesos para luego actualizarlos
		variacion_pesos[i] = tasa * gradiente_local[i] * y;
	}

	return gradiente_local;
}

vector< vector<float> > Capa::get_pesos() {

    vector< vector<float> > pesos;
    pesos.resize(cant_neuronas);

    for (short i = 0; i < cant_neuronas ; i++ ) {
		pesos[i] = miniptrones[i].get_pesos();
	}

	return pesos;
}
