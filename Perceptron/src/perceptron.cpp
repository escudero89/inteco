#include "../include/perceptron.h"

Perceptron::Perceptron(float umbral, int N, float tasa, float desvio, float media)
{
    this -> umbral = umbral;
    this -> N = N;
    this -> tasa = tasa;
    this -> pesos = new vector<float>;

    // El primer valor del vector de pesos sera el umbral
    pesos->push_back(umbral);

    // Inicializamos semilla
    srand(time(NULL));

    for (int i = 1; i < N; i++) {
        float r = ( rand() % 101 * 0.02 - 1) * desvio + media;
        pesos -> push_back(r);
    }
}

/* Podemos comentar bien que hace esta funcion  */
bool Perceptron::entrenar(vector<float> patrones) {

    // Le pongo el ydeseado. Y eliminamos el ultimo elemento
    float ydeseado = patrones.back();
    patrones.pop_back();

    // @@ Esto esta mal, tiene que hacer el producto punto tambien con el elemento de umbral
    float y = 0,// dot(pesos(pesos.begin() + 1, pesos.end()), patrones);
          aux = 0,
          factorDeCambio = tasa * (ydeseado - y);

    unsigned int tamanio = patrones.size();

    // Hay que revisar aca que tira error y no se porque
    for (unsigned int i = 0; i < tamanio; i++) {
        aux = pesos->at(i + 1) + factorDeCambio * patrones[i];
        pesos->at(i + 1) = aux;
    }

    return true;
}

/* Esta funcion la usamos para hacer producto punto entre vectores */
float Perceptron::dot(vector<float> V1, vector<float> V2) {

    float sol = 0;

    if (V1.size() == V2.size()) {
        for (unsigned int i = 0; i < V1.size(); i++) {
            sol += V1[i] * V2[i];
        }
    } else {
        cout << "Error haciendo el producto escalar, distinta longitud.";
        exit (1);
    }

    return sol;
}

// Esto es para ver el archivo CSV (lo saque de internet, aun no lo vi)
    /*
    std::vector<std::string> getNextLineAndSplitIntoTokens(std::istream& str)
    {
        std::vector<std::string>   result;
        std::string                line;
        std::getline(str,line);

        std::stringstream          lineStream(line);
        std::string                cell;

        while(std::getline(lineStream,cell,','))
        {
            result.push_back(cell);
        }
        return result;
    }*/
