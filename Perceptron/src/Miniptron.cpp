#include "../include/Miniptron.h"

Miniptron::Miniptron(int N, float tasa, int cant_neur_siguientes, float a) {

    this -> N = N;
    this -> tasa = tasa;
	this -> a = a;
    delta_anterior.resize(N + 1); /// Mas uno por el umbral
    pesos_siguientes.resize(cant_neur_siguientes);
    inicializar_neuronas();

}

/* La funcion de inializacion de neuronas esta aparte para que sea mas sencillo reinicializarla */
void Miniptron::inicializar_neuronas(float desvio, float media) {

    /// Mas uno por el umbral
    pesos.resize(N + 1);

    this->salida = 0;

    /// Uno extra para el umbral. Nada de ponerlo aparte.
    for (int i = 0; i <= N; i++) {
        float r =( rand() % 1001 * 0.002 - 1) * desvio + media;
        pesos[i] = r;
    }
}

/* Obtiene el vector de 'y' al hacer <patrones, pesos> */
float Miniptron::get_v(vector<float> patrones, bool pop) {
    if (pop) {
        patrones.pop_back();
    }
    /// Agrego un valor extra para el umbral
    patrones.push_back(1);
/*
        cout << "MINIPTRON {BEGIN}\n";

        printVector<float>(pesos);
        printVector<float>(patrones);
*/
    this->salida = funcion_activacion(pesos, patrones, 's');
/*
        cout << "MINIPTRON {END}\n\n";

        cout << "Salida: " << salida << endl << endl;
*/
    return salida;
}

/* A partir de un conjunto Delta W_ij, cambia los pesos */
void Miniptron::actualizar_pesos(vector <float> &delta) {

    for ( unsigned int i = 0; i < pesos.size(); i ++) {
        pesos[i] = pesos[i] + delta[i];
    }
/*
    cout << "Nuevos Pesos y Delta usado:\n";
    printVector<float>(pesos);
    printVector<float>(delta);
    cout << endl;
*/
    this->delta_anterior = delta;
}

/* Funcion de activacion */
float Miniptron::funcion_activacion(const vector<float> &pesos, const vector<float> &patrones, char tipo) {
    float retorno = 0,
        producto_punto = dot<float>(pesos, patrones, "Miniptron::funcion_activacion");
    cout << "Producto punto: " << producto_punto << endl;

    switch(tipo) {

        // sigmoidea
        case 's': // a es una constante cualquiera que define la empinacion
            float eaz;
            eaz = exp(-a * producto_punto);
            retorno = (2 / (1 + eaz)) - 1;
            break;

        default: // Lineal
            retorno = (producto_punto > 0) ? 1 : -1;
    }

    return retorno;
}
