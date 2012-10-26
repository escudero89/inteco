#include "../include/neurona.h"

neurona::neurona(int N, float tasa)
{
    this->N = N;
    this -> tasa = tasa;
    this->pesos.resize(N+1);
    inicializar();
}

void neurona::inicializar(float media, float desvio){

 for (int i = 0; i < N+1; i++) {
        float r =( rand() % 1001 * 0.002 - 1) * desvio + media;
        pesos[i] = r;
    }

}

float neurona::funcionDeActivacion(vector<float> entradas){

    float retorno;

    // funcion signo de activacion
    if ( dot(entradas, pesos, "neurona") > 0)
        retorno = 1;
    else
        retorno = -1;

    return retorno;
}

void neurona::entrenar(vector<float> entrada, float yDeseado){

    entrada.push_back(1); //para el umbral;

    float y = funcionDeActivacion(entrada);

    for(int i=0; i<pesos.size(); i++){
        pesos[i] = pesos[i] + tasa * (yDeseado - y) * entrada[i];
    }

}

bool neurona::probar(vector<float> entrada, float yDeseado){

    entrada.push_back(1); //para el umbral;

    float y = funcionDeActivacion(entrada);

    if(y == yDeseado)
        return true;
    else
        return false;
}
