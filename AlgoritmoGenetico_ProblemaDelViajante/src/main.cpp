#include <ctime>
#include <cstdlib>
#include "../include/Individuo.h"
#include "../include/Poblacion.h"
#include "../../RBF_Network/include/punto.h"
#include "../../RBF_Network/src/punto.cpp"


using namespace std;

int main(int argc, char **argv) {

 srand( time(NULL) );


#if 1
/** EJERCICIO 2 **/


/* Creacion de ciudades */

vector<vector<float> > v;
v.resize(10);

    v[0].push_back(0);
    v[0].push_back(0);

    v[1].push_back(0);
    v[1].push_back(1);

    v[2].push_back(0);
    v[2].push_back(2);

    v[3].push_back(0);
    v[3].push_back(3);

    v[4].push_back(0);
    v[4].push_back(4);

    v[5].push_back(5);
    v[5].push_back(5);

    v[6].push_back(5);
    v[6].push_back(4);

    v[7].push_back(5);
    v[7].push_back(3);

    v[8].push_back(5);
    v[8].push_back(2);

    v[9].push_back(5);
    v[9].push_back(1);



    vector<punto> VP;

    for(int i=0; i<10; i++){
        punto p1(v[i]);
        VP.push_back(p1);
    }
    /* Repito la primera ciudad */
    VP.push_back(VP[0]);
    vector<vector <float> > ciudades1;
    ciudades1.resize(11);

    for(int i=0; i<11; i++){
        ciudades1[i].resize(11);
    }

    /* Convertimos ciudades en distancias */
    for(int i = 0; i<11; i++){
        for(int j=0; j<11; j++){
            ciudades1[i][j] = VP[i].distancia(VP[j]);
        }

    }

    /* Mostramos matriz de distancias */
    cout<<"Distancias: "<<endl;
    printVectorVector<float>(ciudades1, '\t');
    getchar();


/* Parametros del algoritmo genetico */

    int cantIndividuos = 30;
    int tamCromosoma = 11 * 4; //Cantidad de ciudades * bits p/codificar
    float brecha = 0.2;
    int tipo_codificacion = 3;
    int fitness_function = 3;
    float prob_cruza = 0.7;
    float prob_mut = 0.1;
    vector<Individuo> nueva_generacion;
    int mejor;
    vector<float> fenotipo;
    int maxIt = 100;
    float fitnessBuscado = 100000;
    int maxima_poblacion = cantIndividuos + int(float(cantIndividuos) * 0.25);
    int minima_poblacion = cantIndividuos - int(float(cantIndividuos) * 0.25);


/* Creamos la poblacion */
#if 1
 Poblacion P(cantIndividuos,
            tamCromosoma,
             brecha,
             tipo_codificacion,
             fitness_function,
             prob_cruza,
             prob_mut,
             maxima_poblacion,
             minima_poblacion,
             ciudades1);

#endif
/* Mostramos los individuos creados */
cout<<"Individuos Iniciales"<<endl;
for(int i=0; i<cantIndividuos; i++ ){
    cout<<i<<") "<<P.individuos[i].cromosoma<<endl;
}
getchar();


/* Bucle de evolución */

for(int i = 0; i <maxIt; i++ ){
  cout<<"ITERACION: "<<i<<endl;
  cout<<"Tamaño poblacion: "<<P.individuos.size()<<endl;
  mejor = P.getMejorIndividuo();

  /*Mostramos el mejor*/
  printVector<float> (P.individuos[mejor].fenotipo);
  //getchar();

  if(P.individuos[mejor].fitness > fitnessBuscado || i == maxIt - 1){
    fenotipo = P.individuos[mejor].fenotipo;
    break;
  }

  P.reproduccion(nueva_generacion);
  P.individuos = nueva_generacion;
  P.actualizarFenotipo();
  P.evaluarFitness();

}

/* Mostramos la solucion encontrada*/
cout<<endl<<endl;
cout<<"------------------------------------"<<endl;
cout<<"SOLUCION ENCONTRADA: "<<endl;
printVector<float>(fenotipo);
cout<<"------------------------------------"<<endl;


/** FIN EJERCICIO 1 C **/
#endif






return 0;
}
