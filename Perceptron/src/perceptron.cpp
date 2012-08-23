#include "../include/perceptron.h"
#include "../include/utils.h"

Perceptron::Perceptron(int N, float tasa, float desvio, float media)
{
    this -> N = N;
    this -> tasa = tasa;

    inicializar_neuronas(desvio, media);
}

/* La funcion de inializacion de neuronas esta aparte para que sea mas sencillo reinicializarla */
void Perceptron::inicializar_neuronas(float desvio, float media) {
    this -> pesos = new vector<float>;
    this -> pesos_totales = new vector< vector<float> >; // para ploteo

    // Inicializamos semilla
    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        float r = ( rand() % 1001 * 0.002 - 1) * desvio + media;
        pesos -> push_back(r);
    }

    // Guardo el umbral por las dudas
    this -> umbral = pesos -> at(0);
}

/* Funcion de activacion */
float Perceptron::funcion_activacion(vector<float> &pesos, vector<float> &patrones, short tipo) {
    float retorno = 0;

    switch(tipo) {
        case 1: // Lineal
            retorno = (dot<float>(pesos, patrones) > 0) ? 1 : -1;

        default: // Lineal
            retorno = (dot<float>(pesos, patrones) > 0) ? 1 : -1;
    }

    return retorno;
}

/* Realiza el entrenamiento de las neuronas al recibir una fila de patrones  */
bool Perceptron::entrenar(vector<float> patrones) {

    // Le pongo el ydeseado. Y eliminamos el ultimo elemento
    float ydeseado = patrones.back();
    patrones.pop_back();

    // para hacer producto punto con el umbral
    patrones.insert(patrones.begin(), -1);

    float y = funcion_activacion(*pesos, patrones), //Funcion de activacion
          aux = 0,
          factorDeCambio = tasa * (ydeseado - y);

    unsigned int tamanio = patrones.size();

    for (unsigned int i = 0; i < tamanio; i++) {
//        cout << pesos->at(i);

        aux = pesos->at(i) + factorDeCambio * patrones[i];
        pesos->at(i) = aux;

//        cout << " ... " << pesos->at(i) << endl;
    }

    return true;
}


bool Perceptron::estEntrenamiento(vector<vector<float> > &estacion) {
    for(unsigned int i = 0; i < estacion.size() ; i++) {
        entrenar(estacion[i]);
		// Cada vez que cambiabmos los pesos, actualizamos pesos_totales, para ploteo
		add_pesos(*this->pesos);
    }
    return true;
}

bool Perceptron::trabajar(vector<float> patrones){
    float ydeseado = patrones.back();
    patrones.pop_back();

    // para hacer producto punto con el umbral
    patrones.insert(patrones.begin(), -1);

    float y = funcion_activacion(*pesos, patrones); //Funcion de activacion
    bool esCorrecto;

    if (y == ydeseado)
        esCorrecto = true;
    else
        esCorrecto = false;

    return esCorrecto;

}

float Perceptron::estTrabajo(vector< vector<float> > &patrones, bool mostrar){
    int aciertos = 0, errores = 0;

    for(unsigned int i=0; i<patrones.size(); i++){
        if ( trabajar( patrones[i] ) ) {
            aciertos++;
        } else {
            errores++;
        }
    }
    float porcentaje = (float(aciertos) / float(patrones.size()));

    if(mostrar){
        cout<<"Resultados:"<<endl;
        cout<<"Porcentaje de aciertos: "<<porcentaje * 100<<"%"<<endl;
        cout<<"Aciertos: "<<aciertos<<endl;
        cout<<"Errores: "<<errores<<endl;
    }

	// Genera archivos para ploteo
	genPlot2D <float> (*(this->pesos_totales), patrones);

    return porcentaje;
}

/* Realiza un entrenamiento hasta que el error sea menor que la tolerancia dada
   y durante una cierta cantidad de epocas dadas por maxIt */
float Perceptron::entrenamiento(vector< vector<float> > &patrones, vector< vector<float> > &trabajos, unsigned int maxIt, float tol) {
    float error = 100;
    for (unsigned int i = 0; i < maxIt ; i++) {
        estEntrenamiento(patrones);
        error = estTrabajo(trabajos);

        if (error < tol)
            break;
    }
    return error;
}
