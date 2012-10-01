#include <iostream>

#include "../include/neurona.h"
#include "../include/som.h"
#include "../../Perceptron/include/record.h"

#include "../../utils/utils.h"

#include <math.h>
#include <algorithm>

using namespace std;

vector<conjuntoDatos> particionar(string path, int cantConj,
                 float porEntr,
                 float porPruebas,
                 float porControl){

    // Leemos el archivo csv y lo pasamos al vector V
    vector< vector<float> > V;
    parseCSV(path, V);

    // Buscamos la cantidad de elementos q tendra cada vector longE, longP y longC
    int n = V.size();
    double longE = 0, longP = 0, longC = 0;

    double  fracE = modf( (porEntr * n) / 100, &longE),
            fracP = modf( (porPruebas * n) / 100, &longP),
            fracC = modf( (porControl * n) / 100, &longC);

    double aux = 0;
    while ( (longE + longP + longC) != n)
        {
            aux=max(max(fracE,fracP),fracC);
            if (aux == fracE)
                longE += 1;
                else
                    if(aux == fracP)
                        longP += 1;
                        else
                            longC += 1;

        } // end while

    // Creamos cantConj Conjuntos
    vector< vector<float> > v1,v2,v3;

    vector<conjuntoDatos> particiones;

    for(int i = 0; i<cantConj; i++)
    {
        random_shuffle(V.begin(),V.end()); //revolvemos el vector
        v1.insert(v1.begin(),V.begin(),V.begin()+longE);
        v2.insert(v2.begin(),V.begin()+longE,V.begin()+longE+longP);
        v3.insert(v3.begin(),V.begin()+longE+longP,V.end());
        conjuntoDatos P;
        P.entrenamiento = v1;
        P.control = v2;
        P.prueba = v3;

        particiones.push_back(P);
        v1.clear();
        v2.clear();
        v3.clear();
    }

    return particiones;

}

int main() {

    /// VIGILAR VARIANZA SI CAMBIAS CANT_X/Y
    // cant_x | cant_y | N | cant_clases
    SOM Som(10, 10, 5, 2);

    // Imprimo?
    if (false) {
        Som.set_print(true);
    }

    vector<vector<float> > datos;

    vector<string> trabajos;
    trabajos.push_back("data/clouds/clouds.csv");
    trabajos.push_back("data/phoneme/phoneme.csv");

    vector<vector<float> > results;
    results.resize(2);

    for (unsigned int k = 0, M = trabajos.size(); k < M; k++) {
        string a_trabajar = trabajos[k];
    /*
    string trabajar = "phoneme";
    string a_trabajar("data/" + trabajar + "/" + trabajar + ".csv");
*/
    // Validacion cruzada

        float resultados = 0;

        int N = 3; // cantidad de iteraciones
        vector<conjuntoDatos> conjDatos = particionar(a_trabajar, N, 80, 19, 1);

        for (int j = 0; j < N; j++) {

            // Guardo ydeseado en el SOM
            Som.save_labels(conjDatos[j].entrenamiento);

            // Segun haykin
            /// ORDENAMIENTO
            Som.adaptation(conjDatos[j].entrenamiento, 0.1, 3, 1000);

            /// CONVERGENCIA
            Som.adaptation(conjDatos[j].entrenamiento, 0.01, 1, 5000, true);

            resultados += Som.set_labels(conjDatos[j].prueba);

            datos = Som.get_pesos();

        }
        results[k].push_back(resultados);
        cout << "\nPorcentaje de aciertos, resultado de la Validacion Cruzada: " << resultados/N * 100 << endl;
    }

    printCSV<float>(results, "aver.csv");
//    printCSV<float>(datos, "logs/" + trabajar + "_haykin.csv");

// CON 100 neuronas me dio (y estos valores de entrenamiento)
/// CON CLOUDS:
// Porcentaje de aciertos: 85.44%
/// CON PHONEME:
// Porcentaje de aciertos: 77.9978%
// Porcentaje de aciertos, resultado de la Validacion Cruzada: 61.7284% (con 3 pruebas, 25 neuronas)

// ¿Estos valores estan bien? Ni idea jajaj


    return 0;
}
