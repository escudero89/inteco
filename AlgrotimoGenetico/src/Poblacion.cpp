#include "../include/Poblacion.h"

Poblacion::Poblacion(int cantIndividuos, int tamCromosoma, float brecha, int tipo_codificacion, int fitness_function, float prob_cruza, float prob_mut)
{
    this->prob_cruza = prob_cruza;
    this->prob_mut = prob_mut;

    this->brecha_generacional = brecha;
    Individuo I(tamCromosoma, tipo_codificacion, fitness_function);

    this->individuos.resize(cantIndividuos, I);

}

void Poblacion::cruzar(Individuo I1, Individuo I2, Individuo &I3, Individuo &I4){
    int punto_cruza = rand() % I1.cromosoma.size();
    I3.cromosoma = I1.cromosoma;
    I4.cromosoma = I2.cromosoma;

    string c1 = I1.cromosoma.substr(0,punto_cruza);
    string c2 = I2.cromosoma.substr(punto_cruza);

    I3.cromosoma.replace(punto_cruza, c2.size(), c2);
    I4.cromosoma.replace(punto_cruza, c1.size(), c1);


    cout<<I4.cromosoma.size()<<endl;

    getchar();

    if((I3.cromosoma.size()!=I1.cromosoma.size()) || (I2.cromosoma.size()!=I4.cromosoma.size()))
        cout<<"Hay problema con la cruza";

}

void Poblacion::mutar(Individuo &I){
    int m = rand() % I.cromosoma.size();
    if( I.cromosoma[m] == '1')
        I.cromosoma[m] = '0';
    else
        I.cromosoma[m] = '1';

}

void Poblacion::reproduccion(vector<Individuo> &nueva_generacion){

    /** REPRODUCCION: SELECCION - CRUZA - MUTACION **/

    /* SELECCION: METODO POR COMPETENCIAS */

    /*Paso por referencia el vector donde voy
     a poner los individuos de la nueva generacion: &nueva_generacion    */

    /*Cantidad de individuos que tendra la nueva generacion:
     el valor anterior mas un valor al azar no mayor a su diez porciento               */
    int cant_indv_nuevos = individuos.size() + rand() % int((0.1) * individuos.size());

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

         /*Me guardo el ganador 2*/
         ganador_1 = competidores[ganador_1];


         /*Elijo 5 competidores al azar*/
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
         int ganador_2 = distance(fitness_competidores.begin(), p);

         /*Me guardo el ganador 1*/
         ganador_2 = competidores[ganador_2];



        // CRUZA

            if((rand() % 1001)/1000 < this->prob_cruza  ){

                Individuo hijo_1 = individuos[ganador_1];
                Individuo hijo_2 = individuos[ganador_2];

                cruzar(individuos[ganador_1], individuos[ganador_2], hijo_1, hijo_2);

                nueva_generacion.push_back(hijo_1);
                nueva_generacion.push_back(hijo_2);

                }

        // MUTACION
            if((rand()% 1001)/1000 < this->prob_mut){
                mutar(individuos[ganador_1]);
                nueva_generacion.push_back(individuos[ganador_1]);
            }

            if((rand()% 1001)/1000 < this->prob_mut){
                mutar(individuos[ganador_2]);
                nueva_generacion.push_back(individuos[ganador_2]);
            }

    }

}
