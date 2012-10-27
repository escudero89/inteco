#include "../include/Poblacion.h"

Poblacion::Poblacion(int cantIndividuos, int tamCromosoma, float brecha, int tipo_codificacion, int fitness_function, float prob_cruza, float prob_mut)
{
    this->prob_cruza = prob_cruza;
    this->prob_mut = prob_mut;

    this->brecha_generacional = brecha;
    Individuo I(tamCromosoma, tipo_codificacion, fitness_function);

    this->individuos.resize(cantIndividuos, I);

    for(int i = 0; i<cantIndividuos; i++){
        Individuo I(tamCromosoma, tipo_codificacion, fitness_function);
        individuos[i] = I;
    }

}

void Poblacion::cruzar(Individuo I1, Individuo I2, Individuo &I3, Individuo &I4){
    int punto_cruza = rand() % I1.cromosoma.size();

    I3.cromosoma.clear();
    I4.cromosoma.clear();

    string c1 = I1.cromosoma.substr(0,punto_cruza);
    string c2 = I2.cromosoma.substr(punto_cruza);

    string c3 = I1.cromosoma.substr(punto_cruza);
    string c4 = I2.cromosoma.substr(0,punto_cruza);

    I3.cromosoma.append(c1);
    I3.cromosoma.append(c2);

    I4.cromosoma.append(c3);
    I4.cromosoma.append(c4);

    /*Muestra la cruza (para debug):*/
    cout<<"Padre 1: "<<I1.cromosoma<<endl;
    cout<<"Padre 2: "<<I2.cromosoma<<endl;
    cout<<"Punto de cruza: "<<punto_cruza<<endl;
    cout<<"Hijo 1: "<<I3.cromosoma<<endl;
    cout<<"Hijo 2: "<<I4.cromosoma<<endl;
   // getchar();

    if((I3.cromosoma.size()!=I1.cromosoma.size()) || (I2.cromosoma.size()!=I4.cromosoma.size()))
        cout<<"Hay problema con la cruza";

}

void Poblacion::mutar(Individuo &I){
    int m = rand() % I.cromosoma.size();

    cout<<"Mutacion: "<<endl;
    cout<<"Cromosoma sin mutar: "<<I.cromosoma<<endl;
    cout<<"Punto de mutacion: "<<m<<endl;

    if( I.cromosoma[m] == '1')
        I.cromosoma[m] = '0';
    else
        I.cromosoma[m] = '1';

    cout<<"Cromosoma mutado: "<<I.cromosoma<<endl;

}

void Poblacion::reproduccion(vector<Individuo> &nueva_generacion){

    /** REPRODUCCION: SELECCION - CRUZA - MUTACION **/

    /* SELECCION: METODO POR COMPETENCIAS */

    /*Paso por referencia el vector donde voy
     a poner los individuos de la nueva generacion: &nueva_generacion    */
     nueva_generacion.clear();

    /*Cantidad de individuos que tendra la nueva generacion:
     el valor anterior mas un valor al azar no mayor a su 25%               */

    int variacion = (rand() % int((0.25) * individuos.size())) -
                            int((0.25) * individuos.size()/2);
    int cant_indv_nuevos =  individuos.size() + variacion;

    /*Cantidad de inviduos a competir*/
    int cant_competidores = 5;

    /*Vector de los individuos competidores y su
    correspondiente fitness                     */
    vector<int> competidores;
    competidores.resize(cant_competidores);
    vector<float> fitness_competidores;
    fitness_competidores.resize(cant_competidores);

    /* Repito hasta completar el numero de individuos nuevos que quiero */
    while(nueva_generacion.size() < cant_indv_nuevos){


        /*Elijo 5 competidores al azar*/
        for(int j = 0; j<cant_competidores; j++){
            competidores[j] = ( rand() % individuos.size() );
         }

        /*Obtengo los fitness de cada uno*/
        for(int j = 0; j<cant_competidores; j++){
            fitness_competidores[j] = individuos[competidores[j]].getFitness();
         }

         /*Los hago competir*/
         vector<float>::iterator p;
         p = max_element(fitness_competidores.begin(), fitness_competidores.end());
         int ganador_1 = distance(fitness_competidores.begin(), p);

         /*Me guardo el ganador 1*/
         ganador_1 = competidores[ganador_1];


         /*Elijo otros 5 competidores al azar*/
        for(int j = 0; j<cant_competidores; j++){
            competidores[j] = ( rand() % individuos.size() );
         }

        /*Obtengo los fitness de cada uno*/
        for(int j = 0; j<cant_competidores; j++){
            fitness_competidores[j] = individuos[competidores[j]].getFitness();
         }

         /*Los hago competir*/
         vector<float>::iterator q;
         q = max_element(fitness_competidores.begin(), fitness_competidores.end());
         int ganador_2 = distance(fitness_competidores.begin(), q);

         /*Me guardo el ganador 2*/
         ganador_2 = competidores[ganador_2];


        /*Los padres pasan a la siguiente generacion segun una probabilidad
        definida a partir del parametro brecha_generacional */
            if((rand()%1001)/1000 < brecha_generacional){
                nueva_generacion.push_back(individuos[ganador_1]);

                if(nueva_generacion.size() >= cant_indv_nuevos){

                    break;
                }

                nueva_generacion.push_back(individuos[ganador_2]);

                if(nueva_generacion.size() >= cant_indv_nuevos){
                    break;
                }
            }

        /* CRUZA: dos padres generan dos hijos. La probabilidad de cruza
            viene dada por el parametro prob_cruza */

            if((rand() % 1001)/1000 < this->prob_cruza  ){
                cout<<"Ganadores: "<<endl;
                cout<<ganador_1<<endl;
                cout<<ganador_2<<endl;


                Individuo hijo_1 = individuos[ganador_1];
                Individuo hijo_2 = individuos[ganador_2];

                cruzar(individuos[ganador_1], individuos[ganador_2], hijo_1, hijo_2);

                nueva_generacion.push_back(hijo_1);

                if(nueva_generacion.size() >= cant_indv_nuevos){
                    break;
                }

                nueva_generacion.push_back(hijo_2);

                if(nueva_generacion.size()>=cant_indv_nuevos){
                    break;
                }

            }

        /* MUTACION: mutamos un bit por cromosoma segun la probabilidad
           prob_mut                                                     */

            if((rand()% 1001)/1000 < this->prob_mut){
                mutar(individuos[ganador_1]);
                nueva_generacion.push_back(individuos[ganador_1]);

                if(nueva_generacion.size()>=cant_indv_nuevos){
                    break;
                }
            }


            if((rand()% 1001)/1000 < this->prob_mut){
                mutar(individuos[ganador_2]);
                nueva_generacion.push_back(individuos[ganador_2]);

                if(nueva_generacion.size()>=cant_indv_nuevos){
                    break;
                }
            }

    /* Se repite el bucle hasta completar la cantidad de individuos deseada
       para la nueva generacion                                                */
    }

}

void Poblacion::evaluarFitness(){

    for(unsigned int i=0; i<individuos.size();i++){
        individuos[i].evaluarFitness();
    }
}

void Poblacion::actualizarFenotipo(){
    for(unsigned int i=0; i<individuos.size();i++){
        individuos[i].actualizarFenotipo();
    }
}

int Poblacion::getMejorIndividuo(){
    vector<float> v;
    v.resize(individuos.size());

    for(unsigned int i=0; i<individuos.size();i++){
             v[i] = individuos[i].fitness;
    }

    return distance(v.begin(), max_element(v.begin(), v.end()));
}
