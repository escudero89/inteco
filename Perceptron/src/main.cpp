#include <stdio.h>
#include <iostream>
#include "../include/perceptron.h"
#include "../include/utils.h"

using namespace std;

int main(int argc, char **argv) {

    Perceptron A(3, 0.01);

///Creacion de Vector con conjuntos de particiones de datos
      vector<conjuntoDatos> V1;
      V1 = particionar("data/1000datos_xor2.csv",5);
      for(int i = 0; i<5; i++){
          cout<<"**** CONJUNTO DE DATOS "<<i<<" ****"<<endl;

          cout<<"Particion Entrenamiento n°"<<i<<endl;
          printVectorVector((V1.at(i)).entrenamiento);

          cout<<"Particion Prueba n°"<<i<<endl;
          printVectorVector((V1.at(i)).prueba);

          cout<<"Particion Control n°"<<i<<endl;
          printVectorVector((V1.at(i)).control);
       }



    return 0;
}
