#include <vector>

#include "../include/poblacion.h"
#include "../include/individuo.h"

Poblacion::Poblacion(float prob_cruza,
                     float prob_mutacion,
                     float brecha_generacional,
                     unsigned int tam_poblacion,
                     punto origen,
                     vector<punto> &tomas) {

    this->prob_cruza = prob_cruza;
    this->prob_mutacion = prob_mutacion;
    this->brecha_generacional = brecha_generacional;
    this->tam_poblacion = tam_poblacion;
    this->origen = origen;
    this->tomas = tomas;
    this->M = generarMatrizBloques(100,100);
    printCSV<double>(M, "logs/field.dat", false);

    for( unsigned int k = 0; k<tam_poblacion; k++){
        Individuo I (origen, tomas);
        this->v_individuos.push_back(I);
    }

}


vector<Individuo> Poblacion::reproduccion(){

    //Metodo de competencias
    vector<Individuo> seleccionados;

    //Elitismo
    seleccionados.push_back(getMejorIndividuo());

    int cant_competidores = (tam_poblacion < 5 ) ? tam_poblacion : 5;
    vector<double> fitness;
    vector<int> competidores,
                ganador;

    ganador.resize(2);


    while(true){

        for(int j=0;j<2;j++){

            competidores.clear();
            fitness.clear();
            ganador.clear();

            for(int k = 0; k<cant_competidores; k++){

                //Elijo individuos aleatoriamente
                int elegido = rand()%tam_poblacion;
                competidores.push_back( elegido );

                //Me fijo el fitness
                fitness.push_back(v_individuos[elegido].evaluarFitness(M));

            }

            vector<double>::iterator minimo;
            minimo = min_element(fitness.begin(),fitness.end());

            ganador[j] = distance(fitness.begin(), minimo);

        }

        // Cruza
        if(get_rand() < prob_cruza){

            Individuo hijo_1(origen, tomas, "",false),
                      hijo_2(origen, tomas, "",false);

            this->cruzar(ganador[0], ganador[1], hijo_1, hijo_2);

            //Mutacion
            if(get_rand() < prob_mutacion){

                this->mutar(hijo_1);

            }

            if(get_rand() < prob_mutacion){

                this->mutar(hijo_2);

            }


            seleccionados.push_back(hijo_1);
            if(seleccionados.size() == tam_poblacion){
                break;
            }

            seleccionados.push_back(hijo_2);
            if(seleccionados.size() == tam_poblacion){
                break;
            }
        }


        // Brecha Generacional
        if( get_rand() < brecha_generacional){
            seleccionados.push_back(v_individuos[ganador[0]]);

            if(seleccionados.size() == tam_poblacion){
                break;
            }
        }

        if( get_rand() < brecha_generacional){
            seleccionados.push_back(v_individuos[ganador[1]]);
            if(seleccionados.size() == tam_poblacion){
                break;
            }
        }

    }//end while

    //Cambio la poblacion anterior
    this->v_individuos = seleccionados;

    return seleccionados;

}//end reproduccion


void Poblacion::cruzar(int padre_1, int padre_2, Individuo &hijo_1, Individuo &hijo_2){

    hijo_1 = v_individuos[padre_1];
    hijo_2 = v_individuos[padre_2];

    hijo_1.cruzarCromosoma(hijo_2, get_rand());

}

void Poblacion::mutar(Individuo &I){

    cout << "\n\n\nMUTACIOOOOOOOOOOOOOOOOON!!!!!\n\n\n";

    I.mutarCromosoma();
}


Individuo Poblacion::getMejorIndividuo(){

    //si se pone muy lento esto puede hacerse MUCHO mas eficiente
    Individuo masCapo = v_individuos[0];
    float fitness_masCapo = masCapo.evaluarFitness(M);
    float fitness_nuevo;

    for(unsigned int k = 1; k<v_individuos.size(); k++){

        fitness_nuevo = v_individuos[k].evaluarFitness(M);

        if(fitness_nuevo < fitness_masCapo){

            masCapo = v_individuos[k];
            fitness_masCapo = fitness_nuevo;

        }


    }

    return masCapo;

}


/*
"Me retonar una matriz de ceros y unos al azar, de [cant_rows x cant_cols]"
Recibe: las dimensiones
Salida: la matriz de randoms
*/
vector<vector<double> > Poblacion::generarMatrizBloques(unsigned int cant_rows,
                                                        unsigned int cant_cols) {
    vector<vector<double> > Field;
    vector<double> P1;

    for (unsigned int i = 0 ; i < cant_rows ; i++) {
        for (unsigned int j = 0 ; j < cant_cols ; j++) {
            P1.push_back(round(rand()%11/10)); // 0 libre, 1 ocupado : cerca 10% de probabilidad
            cout << P1[j] << "\t";
        }
        cout << endl;
        Field.push_back(P1);
        P1.clear();
    }

    return Field;
}
