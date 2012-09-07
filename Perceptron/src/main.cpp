#include <stdio.h>
#include <iostream>
#include <sstream>
#include "../include/perceptron.h"
#include "../include/utils.h"
#include "../include/record.h"

using namespace std;

int main(int argc, char **argv) {

/// Para guardar

bool is_recording = false, // pasar a falso si no queremos crear archivo
    is_ploting = false;

Record myRecord;
myRecord.start(is_recording);

stringstream ss;

#if 1 /// Ejercicio 1a

    //---------- Problema OR ---------//

    //Creamos perceptron
    Perceptron A(3, 0.5, is_recording);
    A.set_ploting(is_ploting);

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
    ss << "Porcentaje de aciertos OR: " << A.estTrabajo(vec_prueba) * 100 << "%" << endl;

#endif

#if 0 /// Ejercicio 1b

    //---------- Problema XOR ---------//

    //Creamos perceptron
    Perceptron A(3, 0.5, is_recording);

    //Cargamos los datos
    vector< vector<float> > vec_entrenamiento;
    vector< vector<float> > vec_control;
    vector< vector<float> > vec_prueba;
    parseCSV("data/xor700.csv",vec_entrenamiento);
    parseCSV("data/xor200.csv",vec_prueba);
    parseCSV("data/xor100.csv",vec_control);

    //Entrenamos Perceptron
    A.entrenamiento(vec_entrenamiento,vec_control,500,0.3);

    //Probamos perceptron y visualizamos porcentaje de aciertos
    ss<<"Porcentaje de aciertos: "<<A.estTrabajo(vec_prueba) * 100 <<"%"<<endl;

#endif

#if 0 /// Ejercicio 2 a
    Perceptron A(4, 0.01, is_recording);

//Creacion de Vector con conjuntos de particiones de datos
      vector<conjuntoDatos> V1;
      V1 = particionar("data/eje2a.csv",10,70,20,10);

    ss<<"Porcentaje de aciertos: "<<A.validacionCruzada(V1,900,0.16) * 100 <<"%"<<endl;
#endif

#if 0 /// Ejercicio 2 b
    Perceptron A(4, 0.9, is_recording);
    vector<conjuntoDatos> V1;

    V1 = particionar("data/eje2b_10.csv",5,70,20,10);
    ss<<"Porcentaje de aciertos (10%): "<<A.validacionCruzada(V1) * 100 <<"%"<<endl;

    V1 = particionar("data/eje2b_50.csv",5,70,20,10);
    ss<<"Porcentaje de aciertos (50%): "<<A.validacionCruzada(V1) * 100 <<"%"<<endl;

    V1 = particionar("data/eje2b_70.csv",5,70,20,10);
    ss<<"Porcentaje de aciertos (70%): "<<A.validacionCruzada(V1) * 100 <<"%"<<endl;

#endif

    myRecord.add_record(ss, is_recording);
    myRecord.finish(is_recording);

    return 0;
}
