#ifndef NEURONA_RBF_H
#define NEURONA_RBF_H

#include <vector>

#include "../include/punto.h"
using namespace std;

class neurona_RBF
{
    private:
        int N;
        punto media;
        punto desvio;

    public:
        neurona_RBF(int N);
        //neurona_RBF(){} /// OJO! constructor vacio
        void set_media(punto media){this->media = media;}
        void set_desvio(punto desvio){this->desvio = desvio;}
        float funcionDeActivacion(punto x);
};


#endif // NEURONA_RBF_H
