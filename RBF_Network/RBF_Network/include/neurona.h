#ifndef NEURONA_H
#define NEURONA_H

#include <vector>
#include <stdlib.h>

#include "../../../utils/utils.h"


using namespace std;

class neurona
{
    private:
        vector<float> pesos;
        float tasa;
        int N;

    public:
        neurona(int N, float tasa);
        neurona(){}; ///Ojo! constructor vacio
        void inicializar(float media = 0, float desvio = 0.5);
        float funcionDeActivacion(vector<float> entradas);
        void entrenar(vector<float> entrada, float yDeseado);
        bool probar(vector<float> entrada, float yDeseado);
};

#endif // NEURONA_H
