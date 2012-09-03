#include "../include/perceptron.h"

Perceptron::Perceptron(int N, float tasa, bool is_recording, float desvio, float media) {

    this -> N = N;
    this -> tasa = tasa;

    this -> is_recording = is_recording;

    this -> desvio = desvio;
    this -> media = media;

    this -> pesos = new vector<float>;
    this -> pesos_totales = new vector< vector<float> >; // para ploteo

    inicializar_neuronas(desvio, media);
}

/* La funcion de inializacion de neuronas esta aparte para que sea mas sencillo reinicializarla */
void Perceptron::inicializar_neuronas(float desvio, float media) {
    // @TODO hacer un mejor manejo de memoria en los vectores
    pesos->clear();
    pesos_totales->clear();

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
// Sacar fuera de la funcion el producto punto
float Perceptron::funcion_activacion(vector<float> &pesos, vector<float> &patrones, short tipo) {
    float retorno = 0,
        producto_punto = dot<float>(pesos, patrones);

    switch(tipo) {
        case 1: // Lineal
            retorno = (producto_punto > 0) ? 1 : -1;

        default: // Lineal
            retorno = (producto_punto > 0) ? 1 : -1;
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

/* Trabaja con patron y devuelve si acerto o no */
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

/* Trabaja con patrones y devuelve % de aciertos */
float Perceptron::estTrabajo(vector< vector<float> > &patrones, bool mostrar){
    int aciertos = 0, errores = 0;

    for (unsigned int i=0; i<patrones.size(); i++) {
        if ( trabajar( patrones[i] ) ) {
            aciertos++;
        } else {
            errores++;
        }
    }
    float porcentaje = (float(aciertos) / float(patrones.size()));

    if (mostrar) {
        stringstream ss;

        ss << "Resultados:" << endl;
        ss << "Porcentaje de aciertos: " << porcentaje * 100 << "%" << endl;
        ss << "Aciertos: " << aciertos << endl;
        ss << "Errores: " << errores << endl;

		// Genera archivos para ploteo y para grabar
        myRecord.add_record(ss, is_recording);        
        genPlot2D <float> (*(this->pesos_totales), patrones);
    }

    return porcentaje;
}

/* Realiza un entrenamiento hasta que el error sea menor que la tolerancia dada
   y durante una cierta cantidad de epocas dadas por maxIt
   El error es obtenido haciendo trabajar el perceptron con datos que nunca vio */
float Perceptron::entrenamiento(vector< vector<float> > &patrones, vector< vector<float> > &trabajos, unsigned int maxIt, float tol) {
    float error = 100000;
    for (unsigned int i = 0; i < maxIt ; i++) {
        estEntrenamiento(patrones);
        error = 1 - estTrabajo(trabajos);

        if (error < tol) {
            stringstream ss;
            ss << "\n[[Salio por ERROR en entrenamiento de: " << error << "]]\n";
            myRecord.add_record(ss, is_recording);
            break;
        }
    }
    return error;
}

float Perceptron::validacionCruzada(vector<conjuntoDatos> &V, unsigned int maxIt,float tol){
    float err_promedio = 0;
    unsigned int n = V.size();

    for (unsigned int i = 0; i < n ; i++ ) {
        entrenamiento(V.at(i).entrenamiento, V.at(i).control, maxIt, tol);
        err_promedio += estTrabajo(V.at(i).prueba);        
        inicializar_neuronas(this->desvio, this->media);
		
		cout << i <<" . ";
    }

    err_promedio /= n;
    return err_promedio;
}
