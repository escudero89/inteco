#include <ctime>
#include <cstdlib>
#include "../include/Individuo.h"
#include "../include/Poblacion.h"


using namespace std;

int main(int argc, char **argv) {

 srand( time(NULL) );


#if 1
/** EJERCICIO 2 **/

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
    vector< vector<float> > ciudades;

    ciudades.resize(10);
    for(int i=0;i<10;i++)
        ciudades[i].resize(10);

    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){

            ciudades[i][j] = float(rand()%100);

            if(i == j)
                ciudades[i][j] = 0;
            else

            if(j<i)
                ciudades[i][j] = ciudades[j][i];
        }
    }

cout<<"Ciudades: "<<endl;
printVectorVector<float>(ciudades);

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
             ciudades);

#endif
/* Mostramos los individuos creados */

for(int i=0; i<cantIndividuos; i++ ){
    cout<<i<<") "<<P.individuos[i].cromosoma<<endl;
}
getchar();


/* Bucle de evolución */

for(int i = 0; i <maxIt; i++ ){
  cout<<"ITERACION: "<<i<<endl;
  cout<<"Tamaño poblacion: "<<P.individuos.size()<<endl;
  mejor = P.getMejorIndividuo();

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
