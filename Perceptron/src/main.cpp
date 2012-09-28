#include <ctime>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include "../include/Capa.h"
#include "../include/perceptron.h"
#include "../../utils/utils.h"
#include "../include/record.h"
#include "../include/Red.h"

using namespace std;

int main(int argc, char **argv) {

// VALORES GENERALES //
    float tasa = 0.01;
    vector<vector<float> > patrones;

/// /////////////////////////////////////////////////////////////////////// ///


#if 0
// EJERCICIO 3 //

    // Inicializacion de valores
    vector<short> Neuronas_per_Capa;  //

    Neuronas_per_Capa.push_back(5);
    Neuronas_per_Capa.push_back(3);
    Neuronas_per_Capa.push_back(2);

    parseCSV<float>("data/concent.csv", patrones);

    int N = 2,                             // Dimension de patrones
        maxit = 500;                        // Cantidad de iteraciones

    // Trabajando con la red
    Red R(Neuronas_per_Capa, tasa, N);

    //R.estEntrenamiento(patrones, false, maxit);
    R.entrenar(patrones, patrones, maxit, 0.1);
//    float aciertos = R.estEntrenamiento(patrones, true);

  //  cout << "(3a) Porcentaje de aciertos: " << aciertos * 100<<" %"<< endl;


#endif

// EJERCICIO 3a //

#if 0
    /// MOMENTO DE GUARDAR PARA PLOTEAR ///

    vector<float> clases = R.get_clases();

    stringstream ss;

    for (unsigned int i = 0, M = patrones.size(); i < M; i++) {
        for (int j = 0; j < N; j++) {
            ss << patrones[i][j] << ",";
        }
        // Para el ultimo valor de ss le pongo mi 'y' de la red, no mi 'yDeseado'
        ss << clases[i] << endl;
    }

    // Lo guardo en un archivo
    Record MyRecord("ejercicio3a.log");
    MyRecord.add_record(ss);

 /// EJERCICIO 3a

#endif

#if 0
// EJERCICIO 3b //

    float alfa = 1;

    R.set_alfa(alfa);

    /// Una vez seteado el alfa, tengo que volver a entrenar/probar
    R.estEntrenamiento(patrones, false, maxit);
    float aciertos = R.estEntrenamiento(patrones, true);

    cout << "(3b) Porcentaje de aciertos: " << aciertos << endl;

    /// Analizar la convergencia

    // ...

/// EJERCICIO 3b
#endif

/// /////////////////////////////////////////////////////////////////////// ///


#if 1
// EJERCICIO 4 //

    // Inicializacion de valores
    vector<short> Neuronas_per_Capa;  //

    Neuronas_per_Capa.push_back(8);
    Neuronas_per_Capa.push_back(5);
    Neuronas_per_Capa.push_back(3);

    parseCSV<float>("data/iris.csv", patrones);

    int N = 4,                             // Cantidad de patrones
        maxit = 5,                         // Cantidad de iteraciones
        k = 10;                             // Cantidad de conjutos k

    // Trabajando con la red
    Red R(Neuronas_per_Capa, tasa, N);

    // Leave-one-out
    R.validacion_cruzada("data/iris.csv", 1, maxit);

    float error, desvio;

    cout << "LEAVE-ONE-OUT:\n";

    R.get_err_desvio(error, desvio);
    cout << "Error promedio: " << error << endl;
    cout << "Desvío promedio: " << desvio << endl << endl;

    // Leave-k-out
    R.validacion_cruzada("data/iris.csv", k, maxit);

    cout << "LEAVE-K-OUT con k=" << k << ":\n";

    R.get_err_desvio(error, desvio);
    cout << "Error promedio: " << error << endl;
    cout << "Desvío promedio: " << desvio << endl;

// EJERCICIO 4
#endif
    return 0;
}
