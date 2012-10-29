#include <ctime>
#include <cstdlib>
#include "../include/Individuo.h"
#include "../include/Poblacion.h"

using namespace std;

int main(int argc, char **argv) {
 srand( time(NULL) );

#if 0
/**      EJERCICIO 1 A y B      **/
/* Parametros del algoritmo genetico */

    int cantIndividuos = 30;
    int tamCromosoma = 10;
    float brecha = 0.5;
    int tipo_codificacion = 0;
    int fitness_function = 0;
    float prob_cruza = 0.9;
    float prob_mut = 0.1;
    vector<Individuo> nueva_generacion;
    int mejor;
    vector<float> fenotipo;
    int maxIt = 100;
    float fitnessBuscado = 1000;
    int maxima_poblacion = cantIndividuos + int(cantIndividuos * 0.25);
    int minima_poblacion = cantIndividuos - int(cantIndividuos * 0.25);


/* Creamos la poblacion */

 Poblacion P(cantIndividuos,
            tamCromosoma,
             brecha,
             tipo_codificacion,
             fitness_function,
             prob_cruza,
             prob_mut,
             maxima_poblacion,
             minima_poblacion);


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

/* Mostramos la solucion encontrada
    Ejercicio a): 420.911
    Ejerciico b): 1.8181

*/
cout<<endl<<endl;
cout<<"------------------------------------"<<endl;
cout<<"SOLUCION ENCONTRADA: "<<fenotipo[0]<<endl;
cout<<"------------------------------------"<<endl;

    /** FIN EJERCICIO 1 A y B**/
#endif


/** --------------------------------------------------- **/
/** --------------------------------------------------- **/
/** --------------------------------------------------- **/


#if 1
/** EJERCICIO 1 C **/

/* Parametros del algoritmo genetico */

    int cantIndividuos = 30;
    int tamCromosoma = 30;
    float brecha = 0.9;
    int tipo_codificacion = 2;
    int fitness_function = 2;
    float prob_cruza = 0.5;
    float prob_mut = 0.1;
    vector<Individuo> nueva_generacion;
    int mejor;
    vector<float> fenotipo;
    int maxIt = 1000;
    float fitnessBuscado = 1000;
    int maxima_poblacion = cantIndividuos + int(float(cantIndividuos) * 0.25);
    int minima_poblacion = cantIndividuos - int(float(cantIndividuos) * 0.25);


/* Creamos la poblacion */

 Poblacion P(cantIndividuos,
            tamCromosoma,
             brecha,
             tipo_codificacion,
             fitness_function,
             prob_cruza,
             prob_mut,
             maxima_poblacion,
             minima_poblacion);


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
cout<<"x: "<<fenotipo[0]<<endl;
cout<<"y: "<<fenotipo[1]<<endl;
cout<<"------------------------------------"<<endl;


/** FIN EJERCICIO 1 C **/
#endif




return 0;
}
