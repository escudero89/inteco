#include "../include/perceptron.h"
#include "../include/utils.h"

Perceptron::Perceptron(int N, float tasa, float desvio, float media)
{
    this -> N = N;
    this -> tasa = tasa;
    this -> pesos = new vector<float>;

    // Inicializamos semilla
    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        float r = ( rand() % 1001 * 0.002 - 1) * desvio + media;
        pesos -> push_back(r);
    }

    // Guardo el umbral por las dudas
    this -> umbral = pesos -> at(0);
}

/* Podemos comentar bien que hace esta funcion  */
bool Perceptron::entrenar(vector<float> patrones) {

    // Le pongo el ydeseado. Y eliminamos el ultimo elemento
    float ydeseado = patrones.back();
    patrones.pop_back();

    // para hacer producto punto con el umbral
    patrones.insert(patrones.begin(), -1);

    float y = (dot(*pesos, patrones) > 0) ? 1 : -1, //Funcion de activacion
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
    }
    return true;
}

bool Perceptron::trabajar(vector<float> patrones){
    float ydeseado = patrones.back();
    patrones.pop_back();

    // para hacer producto punto con el umbral
    patrones.insert(patrones.begin(), -1);

    float y = (dot(*pesos, patrones) > 0) ? 1 : -1; //Funcion de activacion
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

/* Esta funcion la usamos para hacer producto punto entre vectores */
float Perceptron::dot(vector<float> &V1, vector<float> &V2) {

    float sol = 0;

    if (V1.size() == V2.size()) {
        for (unsigned int i = 0; i < V1.size(); i++) {
            sol += V1[i] * V2[i];
        }
    } else {
        cout << "Error haciendo el producto escalar, distinta longitud.\n";
        cout << "V1: " << V1.size() << endl;
        printVector(V1);
        cout << "\nV2: "<< V2.size() << endl;
        printVector(V2);
        exit (1);
    }

    return sol;
}
