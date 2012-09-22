#include "../include/neurona_RBF.h"

neurona_RBF::neurona_RBF(int N)
{
    this->N = N;

    this->media.resize(N);
    this->desvio.resize(N);
}
