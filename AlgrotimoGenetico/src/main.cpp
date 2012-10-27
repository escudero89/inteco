#include <ctime>
#include <cstdlib>
#include "../include/Individuo.h"
#include "../include/Poblacion.h"

using namespace std;

int main(int argc, char **argv) {
 srand( time(NULL) );

    int cantIndividuos = 30;
    int tamCromosoma = 1024;
    float brecha = 0.5;
    int tipo_codificacion = 0;
    int fitness_function = 0;
    float prob_cruza = 0.9;
    float prob_mut = 0.1;

 Poblacion P(cantIndividuos,
            tamCromosoma,
             brecha,
             tipo_codificacion,
             fitness_function,
             prob_cruza,
             prob_mut);

 vector<Individuo> nueva_generacion;
 P.reproduccion(nueva_generacion);



return 0;
}
