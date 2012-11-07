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


bool punto::operator==(punto N){

    int tam = this->coordenadas.size();

    for(int i=0; i<tam; i++){
        if(N.coordenadas[i] != this->coordenadas[i]){
            return false;
        }
    }

    return true;
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


float punto::distancia_manhattan(punto A, punto &d, bool resolucion_baja){

    d = A - *this;
    int cant = this->coordenadas.size();
    float dist = 0;

    for(int i = 0; i<cant; i++){
        dist += abs(d.coordenadas[i]);
    }

    if(cant == 2) {
        if (!resolucion_baja) {
            d.coordenadas[0] = (d.coordenadas[0] != 0) ? d.coordenadas[0] / abs(d.coordenadas[0]) : 0;
            d.coordenadas[1] = (d.coordenadas[1] != 0) ? d.coordenadas[1] / abs(d.coordenadas[1]) : 0;
        } else {///esto ANDA NO TOCAR

            if(abs(d.coordenadas[0]) > abs(d.coordenadas[1])){

                d.coordenadas[0]=1 * d.coordenadas[0]/abs(d.coordenadas[0]);
                d.coordenadas[1]=0;

            } else{

                d.coordenadas[1]=1 * d.coordenadas[1]/abs(d.coordenadas[1]);
                d.coordenadas[0]=0;

            }

        }
    }
    return dist;
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

        cout<<"\t"<<this->coordenadas[i];

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

unsigned int punto::menor_distancia(vector<punto> VP, short &menor_dist, punto &d_toma){

    punto trash(0, 0);
    float d, min = distancia_manhattan(VP[0], trash);
    unsigned int min_i = 0;

    for (unsigned int i = 1; i< VP.size(); i++){
        d = distancia_manhattan(VP[i], trash);
        if( d < min ){
            min = d;
            min_i = i;
        }

    }
    distancia_manhattan(VP[min_i], d_toma);

    menor_dist = min;
    return min_i;

}
