#include <stdio.h>
#include <iostream>

#include "../include/perceptron.h"
#include "../include/utils.h"

using namespace std;

int main(int argc, char **argv) {

    Perceptron A(3, 0.4);
	
    vector< vector<float> > Ventrenamiento;
    vector< vector<float> > Vprueba;
    vector< vector<float> > Vcontrol;

    parseCSV <float> ("data/700datos_entrenamiento.csv", Ventrenamiento);
    parseCSV <float> ("data/200datos_prueba.csv", Vprueba);
    parseCSV <float> ("data/100datos_control.csv", Vcontrol);

    //Entrenamiento
    cout<<"Resultados de precision del entrenamiento: ";
    cout<<A.entrenamiento(Ventrenamiento,Vcontrol,1) * 100<<"%"<<endl;
    //Prueba
    cout<<"Resultados de precision con valores nunca vistos: ";
    cout<<A.estTrabajo(Vprueba) * 100<<"%"<<endl;

    return 0;
}
