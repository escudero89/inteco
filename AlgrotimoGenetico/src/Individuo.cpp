#include "../include/Individuo.h"

Individuo::Individuo(int tam_cromosoma, int tipo_codificacion, int fitness_function)
{
    this->fitness_function = fitness_function;
    this->tipo_codificacion = tipo_codificacion;


    this->cromosoma.resize(tam_cromosoma);

    for(int i=0; i<tam_cromosoma; i++){

        cromosoma[i] = rand() % 2;
    }

    actualizarFenotipo();
    evaluarFitness();
}

float Individuo::evaluarFitness(){

    float ret;

    if(fitness_function == 0){

        float f = this->fenotipo[0];
        int c_max = 500;

        /* Funcion de fitnes propuesta por Goldberg pag:76*/
        ret = c_max - (-f * sin(sqrt(abs(f))));
        ret = (ret > 0 ? ret : 0);
        this->fitness = ret;
    }

    return ret;
}


void Individuo::actualizarFenotipo(){

    if(tipo_codificacion == 0){

        float min_val = -512;
        float max_val = 512;

        int v = strtol(cromosoma.c_str(), NULL, 2);
        float f = min_val + (max_val - min_val) * v / ( pow(2, cromosoma.size() ) -1 );

        vector<float> fen;
        fen.push_back(f);
        this->fenotipo = fen;

    }

}




