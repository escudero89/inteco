#ifndef RED_H
#define RED_H

#include <iostream>
#include <cassert>
#include <vector>

#include "Capa.h"

using namespace std;

class Red {
    short cant_capas;
    vector<Capa> capas;
    vector<float> input;
    vector< vector< vector<float> > > pesos; //esto queda horriblemente mal, pero pasa por no hacer un buen disenio desde el principio

public:
    Red(vector<short> &Capas, float tasa, int N);

    void reinicializar_red() {
        for (short i = 0; i < cant_capas; i++ ) {
            capas[i].reinicializar_capa();
        }
    }

    vector<float> forward_pass(vector<float> input);
    void backward_pass(vector<float> ydeseado);

    vector<float> yAnterior(short indiceCapa);

    void actualizar_pesos();

    float validacion_cruzada(string path, short k = 1);

    float leave_k_out(vector< vector<float> > &patrones, short k = 1);

    bool entrenarRed(vector<float> P, bool probar = false);

    float estEntrenamiento(vector< vector<float> > &P, bool probar = false, int cant = 1);

    void set_alfa(float alfa) {
        for (short i = 0; i < cant_capas; i++ ) {
            capas[i].set_alfa(alfa);
        }
    }
};

#endif // RED_H
