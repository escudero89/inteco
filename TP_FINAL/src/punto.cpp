#include "../include/punto.h"

// Este constructor construye un punto aleatorio
punto::punto(int dimension, float desvio, float media)
{
    this->coordenadas.resize(dimension);

    for(short i = 0; i<dimension; i++){

        this->coordenadas[i] =( rand() % 1001 * 0.002 - 1) * desvio + media;
    }
}

// Constructor nuevo que crea punto bidimensionales
punto::punto (float x, float y) {

     this->coordenadas.resize(2);
     this->coordenadas[0] = x;
     this->coordenadas[1] = y;

}

// Este otro constructor construye un punto a partir de un vector dado
punto::punto(vector<float> coordenadas){
    this->coordenadas = coordenadas;
}

//Sobrecargamos operadores, los necesito para simplificar el k-means
punto punto::operator+(const punto&  other){

    int tam = this->coordenadas.size();
    vector<float> V;
    V.resize(tam);

    for(int i=0; i<tam; i++){

        V[i] = this->coordenadas[i] + other.coordenadas[i];
    }

    return punto(V);
}

punto punto::operator-(const punto&  other){

    int tam = this->coordenadas.size();
    vector<float> V;
    V.resize(tam);

    for(int i=0; i<tam; i++){

        V[i] = this->coordenadas[i] - other.coordenadas[i];
    }

    return punto(V);
}

punto punto::operator/(float N){

    int tam = this->coordenadas.size();
    vector<float> V;
    V.resize(tam);

    for(int i=0; i<tam; i++){

        V[i] = this->coordenadas[i]/N;
    }

    return punto(V);
}

float punto::distancia(punto A){

    punto d = *this - A;
    int cant = this->coordenadas.size();
    float dist = 0;

    for(int i = 0; i<cant; i++){

        dist += pow(d.coordenadas[i],2);
    }

    return sqrt(dist); //sacar esta raiz si es muy lento
}

punto punto::pow2(){

    int tam = this->coordenadas.size();
    vector<float> V;
    V.resize(tam);

    for(int i=0; i<tam; i++){

        V[i] = pow(this->coordenadas[i],2);
    }

    return punto(V);
}

punto punto::raizCuadrada(){

    int tam = this->coordenadas.size();
    vector<float> V;
    V.resize(tam);

    for(int i=0; i<tam; i++){

        V[i] = sqrt(this->coordenadas[i]);
    }

    return punto(V);
}

void punto::printPunto(){

    for(unsigned int i = 0; i<this->coordenadas.size(); i++){

        cout<<this->coordenadas[i]<<" -- ";

    }
    cout<<endl;

}


float punto::sum(){

    float acum = 0;
    for(unsigned int i = 0; i<coordenadas.size(); i++){

        acum += coordenadas[i];

    }

    return acum;
}
