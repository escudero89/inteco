#include "../include/Miniptron.h"

Miniptron::Miniptron(int N, float tasa, float a) {

    this -> N = N;
    this -> tasa = tasa;
	this -> a = a;

    inicializar_neuronas();

}

/* La funcion de inializacion de neuronas esta aparte para que sea mas sencillo reinicializarla */
void Miniptron::inicializar_neuronas(float desvio, float media) {

    delta_anterior.resize(N);
    pesos.resize(N);

    this->salida = 0;

    for (int i = 0; i <= N; i++) {
        float r = ( rand() % 1001 * 0.002 - 1) * desvio + media;

        if (i == N) {
            this -> umbral = r;
        } else {
            pesos[i] = r;
        }
    }
}

/* Obtiene el vector de 'y' al hacer <patrones, pesos> */
float Miniptron::get_v(vector<float> patrones, bool pop) {
    if (pop) {
        patrones.pop_back();
    }

    this->salida = funcion_activacion(pesos, patrones, 's');
    return salida;
}

/* A partir de un conjunto Delta W_ij, cambia los pesos */
void Miniptron::actualizar_pesos(vector <float> &delta) {

    unsigned int i = 0;

    for ( ; i < pesos.size(); i ++) {
        pesos[i] = pesos[i] + delta[i];
    }
    this->umbral += delta[i];

    this->delta_anterior = delta;
}

/* Funcion de activacion */
float Miniptron::funcion_activacion(const vector<float> &pesos, const vector<float> &patrones, char tipo) {
    float retorno = 0,
        producto_punto = dot<float>(pesos, patrones, "Miniptron::funcion_activacion") - this->umbral;

    switch(tipo) {

        // sigmoidea
        case 's': // a es una constante cualquiera que define la empinacion
            float eaz; eaz = exp(-30 * producto_punto);
            retorno = (1 - eaz) / (1 + eaz);
            break;

        default: // Lineal
            retorno = (producto_punto > 0) ? 1 : -1;
    }

    return retorno;
}
