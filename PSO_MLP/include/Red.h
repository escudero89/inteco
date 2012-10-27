#ifndef RED_H
#define RED_H

#include <iostream>
#include <cassert>
#include <vector>

#include "../../Perceptron/include/Capa.h"

using namespace std;

class Red {

    short cant_capas, cant_neuronas, cant_pesos, N;
    vector<Capa> capas;
    vector<float> input;
    vector<float> clases;
    vector<float> errores;

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

    float validacion_cruzada(string path, short k = 1, unsigned int cant_iteraciones = 1);

    float leave_k_out(vector< vector<float> > &patrones, short k = 1, unsigned int cant_iteraciones = 1);

    bool entrenarRed(vector<float> P, bool probar = false);

    float estEntrenamiento(vector< vector<float> > &P, bool probar = false, int cant = 1);

    void set_alfa(float alfa) {
        for (short i = 0; i < cant_capas; i++ ) {
            capas[i].set_alfa(alfa);
        }
    }

    float entrenar(vector<vector<float> > &E,vector<vector<float> > &P, int maxit, float tol);

    /* Necesito una funcion que me devuelva un vector con las clases que asigno a cada valor */
    vector<float> get_clases() {
        return clases;
    }

    /// FUNCIONES DE VALIDACION DE ERRORES ///
    float get_error();
    void get_err_desvio(float &media, float &desvio);

    void show_pesos() {
        for (short i = 0; i < cant_capas; i++) {
            vector<vector<float> > pesos = capas[i].get_pesos();
            cout << "Capa [" << i << "]\n";
            printVectorVector<float>(pesos);
        }
        cout << endl;
    }

    /// FUNCIONES PROGRAMADAS PARA EL SWARM
    float swarmEntrenar(vector<vector<float> > &E,vector<vector<float> > &P, int maxit, float tol);

    vector<vector<float> > transmutar_pesos(vector<float> &);
    void forzar_pesos(vector<float> &);

};

#endif // RED_H
