#include <stdio.h>
#include <iostream>
#include "../include/perceptron.h"
#include "../include/utils.h"

using namespace std;

int main(int argc, char **argv) {

#if 0 /// Ejercicio 1a

//Problema OR//

//Creamos perceptron
Perceptron A(3,0.5);

//Cargamos los datos
vector< vector<float> > vec_entrenamiento;
vector< vector<float> > vec_control;
vector< vector<float> > vec_prueba;
parseCSV("data/700datos_entrenamiento.csv",vec_entrenamiento);
parseCSV("data/200datos_prueba.csv",vec_prueba);
parseCSV("data/100datos_control.csv",vec_control);

//Entrenamos Perceptron
A.entrenamiento(vec_entrenamiento,vec_control,500,0.05);

//Probamos perceptron y visualizamos porcentaje de aciertos
cout<<"Porcentaje de aciertos: "<<A.estTrabajo(vec_prueba) * 100 <<"%"<<endl;#endif

//Problema XOR

#endif

#if 0 /// Ejercicio 1b

#endif

#if 0 /// Ejercicio 2 a
    Perceptron A(4, 0.9);

//Creacion de Vector con conjuntos de particiones de datos
      vector<conjuntoDatos> V1;
      V1 = particionar("data/eje2a.csv",5,70,20,10);

    cout<<"Porcentaje de aciertos: "<<A.validacionCruzada(V1) * 100 <<"%"<<endl;#endif
#endif

#if 0 /// Ejercicio 2 b
    Perceptron A(4, 0.9);
    vector<conjuntoDatos> V1;

    V1 = particionar("data/eje2b_10.csv",50,70,20,10);
    cout<<"Porcentaje de aciertos (10%): "<<A.validacionCruzada(V1) * 100 <<"%"<<endl;

    V1 = particionar("data/eje2b_50.csv",50,70,20,10);
    cout<<"Porcentaje de aciertos (50%): "<<A.validacionCruzada(V1) * 100 <<"%"<<endl;

    V1 = particionar("data/eje2b_70.csv",50,70,20,10);
    cout<<"Porcentaje de aciertos (70%): "<<A.validacionCruzada(V1) * 100 <<"%"<<endl;
#endif
    return 0;
}
