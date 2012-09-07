#include "../include/Miniptron.h"

Miniptron::Miniptron(int N, float tasa) {

    this -> N = N - 1; // @@ Guarda N - 1 en vez de N para poder contar el y_deseado
    this -> tasa = tasa;

    this -> pesos = new vector<float>;

    // Inicializamos semilla
    srand(time(NULL));

    inicializar_neuronas();
}

/* La funcion de inializacion de neuronas esta aparte para que sea mas sencillo reinicializarla */
void Miniptron::inicializar_neuronas(float desvio, float media) {
    pesos->resize(N);

    for (int i = 0; i <= N; i++) {
        float r = ( rand() % 1001 * 0.002 - 1) * desvio + media;

        if (i == N) {
            this -> umbral = r;
        } else {
            pesos -> at(r);
        }
    }
}

/* Funcion de activacion */
float Miniptron::funcion_activacion(vector<float> &pesos, vector<float> &patrones, short tipo) {
    float retorno = 0,
        producto_punto = dot<float>(pesos, patrones) - this->umbral;

    switch(tipo) {
        default: // Lineal
            retorno = (producto_punto > 0) ? 1 : -1;
    }

    return retorno;
}

/* Entrenar y trabajar tenian el mismo bloque, asi que los uni aca */
float Miniptron::entrenar_helper(vector<float> &patrones) {
    // Le pongo el ydeseado. Y eliminamos el ultimo elemento
    float ydeseado = patrones.back(), y;
    patrones.pop_back();

    y = funcion_activacion(*pesos, patrones);

    return ydeseado - y;
}

/* Realiza el entrenamiento de las neuronas al recibir una fila de patrones  */
bool Miniptron::entrenar(vector<float> patrones) {

    float aux = 0, factorDeCambio = tasa * entrenar_helper(patrones);

    unsigned int tamanio = patrones.size();

    for (unsigned int i = 0; i < tamanio; i++) {
        aux = pesos->at(i) + factorDeCambio * patrones[i];
        pesos->at(i) = aux;
    }

    return true;
}

bool Miniptron::estEntrenamiento(vector<vector<float> > &estacion) {
    for(unsigned int i = 0; i < estacion.size() ; i++) {
        entrenar(estacion[i]);
    }
    return true;
}

/* Trabaja con patron y devuelve si acerto o no */
bool Miniptron::trabajar(vector<float> patrones){
    bool esCorrecto;

    // entrenar_helper devuelve [ ydeseado - y ]
    (entrenar_helper(patrones) == 0) ? esCorrecto = true : esCorrecto = false;

    return esCorrecto;
}

/* Trabaja con patrones y devuelve % de aciertos */
float Miniptron::estTrabajo(vector< vector<float> > &patrones){
    int aciertos = 0, errores = 0;

    for (unsigned int i=0; i<patrones.size(); i++) {
        if ( trabajar( patrones[i] ) ) {
            aciertos++;
        } else {
            errores++;
        }
    }
    float porcentaje = (float(aciertos) / float(patrones.size()));

    return porcentaje;
}

/* Realiza un entrenamiento hasta que el error sea menor que la tolerancia dada
   y durante una cierta cantidad de epocas dadas por maxIt
   El error es obtenido haciendo trabajar el Miniptron con datos que nunca vio */
float Miniptron::entrenamiento(vector< vector<float> > &patrones, vector< vector<float> > &trabajos, unsigned int maxIt, float tol) {
    float error = 100000;
    for (unsigned int i = 0; i < maxIt ; i++) {
        estEntrenamiento(patrones);
        error = 1 - estTrabajo(trabajos);

        if (error < tol) {
            break;
        }
    }

    return error;
}

float Miniptron::validacionCruzada(vector<conjuntoDatos> &V, unsigned int maxIt,float tol){
    float err_promedio = 0;
    unsigned int n = V.size();

    for (unsigned int i = 0; i < n ; i++ ) {
        entrenamiento(V.at(i).entrenamiento, V.at(i).control, maxIt, tol);
        err_promedio += estTrabajo(V.at(i).prueba);
        inicializar_neuronas();
    }

    err_promedio /= n;
    return err_promedio;
}
