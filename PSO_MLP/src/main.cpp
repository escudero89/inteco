#include <iostream>
#include <vector>
#include <cmath>

#include "../../utils/utils.h"

/** Incluimos Perceptron **/
#include "../include/Red.h"

using namespace std;

double funciones (vector<double> equis) {

    return 0;
}

int main() {

    srand(time(0));

    /// Inicializo los conjuntos de prueba y entrenamiento

    vector<vector<float> > Ve;
    vector<vector<float> > Vp;

    vector<conjuntoDatos> C = particionar("data/clouds.csv",1,80,19,1);
    Ve = C[0].entrenamiento;
    Vp = C[0].prueba;

    /// Creo mi MLP

    vector<short> neuronasPorCapa;
    neuronasPorCapa.push_back(12);
    neuronasPorCapa.push_back(2);

    Red R(neuronasPorCapa, 0.001, 2);
    R.set_alfa(0.0008);

    float
        aciertos,
        maxit = 1000,
        tol = 0.2;

    /// Entrenamiento de MLP con sus propias funciones

    cout << "\nResultados de 'clouds' con MLP (clasico): " << endl;

    aciertos = (1 - R.entrenar(Ve, Vp, maxit, tol)) * 100;

    cout <<"\nPorcentaje de aciertos: " << aciertos << endl;

    /// Entrenamiento usando SWARM
    cout << "\n--------------------------------------------------------------\n";
    R.reinicializar_red();

    cout << "\nResultados de 'clouds' con MLP (con PSO): " << endl;

    aciertos = (1 - R.swarmEntrenar(Ve, Vp, maxit / 50, tol)) * 100;

    cout << "\nPorcentaje de aciertos: " << aciertos << endl;

    return 0;
}
