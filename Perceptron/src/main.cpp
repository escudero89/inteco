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

    vector<float> p;
    p.push_back(1);
    p.push_back(1);
    p.push_back(1);

    vector<short> c;
    c.push_back(3);
    c.push_back(2);
    c.push_back(1);

    Red R(c,0.2,3);

    vector<float> ydeseado;
    ydeseado.push_back(3);

    vector<float> a = R.forward_pass(p);
    R.backward_pass(ydeseado);


    for(int i=0;i<300;i++){
        R.forward_pass(p);
        R.backward_pass(ydeseado);
        R.actualizar_pesos();
    }

    a = R.forward_pass(p);
    cout<<endl<<"****  Resultado Final foward: ****"<<endl;
    printVector<float>(a);

    cout << "\n vieeeja pruebo aca yo \n";

    //@Marcos, si queres ver como funciona, es sencillo, modifica los atributos de abajo y miralo un poquito
    // Explicacion en la que me base: http://es.wikipedia.org/wiki/Validaci%C3%B3n_cruzada

    int cuantos_push_back = 5;
    short k = 2;

    vector<vector<float> > probandoo;

    for (int i = 0 ; i < cuantos_push_back ; i++) {
        vector<float> am;
        am.resize(3, i);
        probandoo.push_back(am);
    }

    R.leave_k_out(probandoo, k);

//    vector<float> d;
//    d.push_back(1);
//    R.backward_pass(d);
//    printVector<float>(p);

//    p = R.forward_pass(p);





/******************************************************************************

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
        A.entrenamiento(vec_entrenamiento,vec_control,500,0.1);

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
        Perceptron A(4, 0.1, is_recording);

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

******************************************************************************/

    return 0;
}
