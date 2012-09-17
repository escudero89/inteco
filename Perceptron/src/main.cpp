#include <ctime>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include "../include/Capa.h"
#include "../include/perceptron.h"
#include "../include/utils.h"
#include "../include/record.h"
#include "../include/Red.h"

using namespace std;

int main(int argc, char **argv) {

# if 0
    vector<vector<float> > P_entrenamiento, P_prueba;
   parseCSV<float>("data/xor600a.csv",P_entrenamiento);
   parseCSV<float>("data/xor100a.csv",P_prueba);
    vector<short> C;
    C.push_back(2);
    C.push_back(2);

    Red R(C,0.1,2);
    R.set_alfa(0);

    R.entrenar(P_entrenamiento,P_prueba,100,0.1);
    //R.estEntrenamiento(P_entrenamiento,false,50);
    //cout<<R.estEntrenamiento(P_prueba,true,1);

# endif

#if 1
    vector<short> C;
    C.push_back(2);
    C.push_back(2);

    Red R(C,0.1,2);
    R.set_alfa(0);

   vector<vector<float> > P_entrenamiento, P_prueba;

   parseCSV<float>("data/xor600a.csv",P_entrenamiento);
   parseCSV<float>("data/xor100a.csv",P_prueba);

   R.estEntrenamiento(P_entrenamiento,false,50);
   cout<<R.estEntrenamiento(P_prueba,true) * 100<<" %";

    //cout<<"Porcentaje de Aciertos: ";
    //cout<<R.validacion_cruzada("data/xor600a.csv",50) * 100<<" %"<<endl;
#endif


// VALORES GENERALES //
    float tasa = 0.2;
    vector<vector<float> > patrones;

/// /////////////////////////////////////////////////////////////////////// ///

#if 1

// EJERCICIO 3 //

    // Inicializacion de valores
    vector<short> Neuronas_per_Capa;  //

    Neuronas_per_Capa.push_back(2);
    Neuronas_per_Capa.push_back(2);

    parseCSV<float>("data/concent.csv", patrones);

    int N = 2,                             // Cantidad de patrones
        maxit = 5;                        // Cantidad de iteraciones

    // Trabajando con la red
    Red R(Neuronas_per_Capa, tasa, N);

    R.estEntrenamiento(patrones, false, maxit);
    float aciertos = R.estEntrenamiento(patrones, true);

    cout << "(3a) Porcentaje de aciertos: " << aciertos << endl;

#if 1

// EJERCICIO 3a //

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

#endif /// EJERCICIO 3a

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

#endif /// EJERCICIO 3b

#endif // EJERCICIO 3

/// /////////////////////////////////////////////////////////////////////// ///

#if 0

// EJERCICIO 4 //

    // Inicializacion de valores
    vector<short> Neuronas_per_Capa;  //

    Neuronas_per_Capa.push_back(8);
    Neuronas_per_Capa.push_back(2);

    parseCSV<float>("data/iris.csv", patrones);

    int N = 2,                             // Cantidad de patrones
        maxit = 5,                         // Cantidad de iteraciones
        k = 1;                             // Cantidad de conjutos k

    // Trabajando con la red
    Red R(Neuronas_per_Capa, tasa, N);

    // Leave-one-out
    R.validacion_cruzada("data/iris.csv", 1, maxit);

    float error, desvio;

    cout << "LEAVE-ONE-OUT:\n";

    R.get_err_desvio(error, desvio);
    cout << "Error promedio: " << error << endl;
    cout << "Desvío promedio: " << desvio << endl;

    // Leave-k-out
    R.validacion_cruzada("data/iris.csv", k, maxit);

    cout << "LEAVE-K-OUT con k=" << k << ":\n";

    R.get_err_desvio(error, desvio);
    cout << "Error promedio: " << error << endl;
    cout << "Desvío promedio: " << desvio << endl;

#endif // EJERCICIO 4

    return 0;
}
