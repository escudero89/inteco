#include "../include/neurona_RBF.h"

neurona_RBF::neurona_RBF(int N)
{
    this->N = N;
    punto media(N), desvio(N);

    this->media = media;
    this->desvio = desvio;

}

float neurona_RBF::funcionDeActivacion(punto x){

    float sigma = 1;//desvio.sum()/N; //Hago un promedio de los desvios

    punto diff = x - media;
    diff = diff.pow2();
    float v = diff.sum();

    return exp((- v) /(2 * pow(sigma,2)) );

}
