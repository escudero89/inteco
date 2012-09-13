#include "../include/Miniptron.h"

Miniptron::Miniptron(int N, float tasa, float a) {

    this -> N = N - 1; // @@ Guarda N - 1 en vez de N para poder contar el y_deseado
    this -> tasa = tasa;
	this -> a = a;

    inicializar_neuronas();

}

/* La funcion de inializacion de neuronas esta aparte para que sea mas sencillo reinicializarla */
void Miniptron::inicializar_neuronas(float desvio, float media) {

    pesos.reserve(N);

    this->salida = 0;

    for (int i = 0; i <= N; i++) {
        float r = ( rand() % 1001 * 0.002 - 1) * desvio + media;

        if (i == N) {
            this -> umbral = r;
        } else {
            pesos.push_back(r);
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
void Miniptron::set_pesos(vector <float> &delta) {

    /// Estoy considerando que el primer valor del delta es el W_ij que se le aplica al umbral.
    /// Por lo que hay que revisar ese tema. La otra es poner el umbral dentro de pesos.
    /// Analizar este tema no es un detalle menor (?).
    this->umbral = delta[0];

    for (unsigned int i = 0 ; i < pesos.size(); i ++) {
        pesos[i] = pesos[i] + pesos[i] * delta[i + 1];
    }
}

/* Funcion de activacion */
float Miniptron::funcion_activacion(vector<float> &pesos, vector<float> &patrones, char tipo) {
    float retorno = 0,
        producto_punto = dot<float>(pesos, patrones) - this->umbral;

    switch(tipo) {

        // sigmoidea
        case 's': // a es una constante cualquiera que define la empinacion
            float eaz; eaz = exp(-a * producto_punto);
            retorno = (1 - eaz) / (1 + eaz);
            break;

        default: // Lineal
            retorno = (producto_punto > 0) ? 1 : -1;
    }

    return retorno;
}
