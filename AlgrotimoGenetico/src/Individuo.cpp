#include "Individuo.h"

Individuo::Individuo(int tam_cromosoma)
{

    srand( time(NULL) );
    this->cromosoma.resize(tam_cromosoma);

    for(int i=0; i<tam_cromosoma; i++){

        cromosoma[i] = rand() % 2;
    }
}

float Individuo::evaluarFitness(int fitness_function){

    if(fitness_function == 0){

        float f = this->fenotipo[0];
        int c_max = 500;

        /* Funcion de fitnes propuesta por Goldberg pag:76*/
        float ret = c_max - (-f * sin(sqrt(abs(f))));
        ret = (ret > 0 ? ret : 0);

        return ret;

    }

}


void Individuo::actualizarFenotipo(int tipo_codificacion){

    if(tipo_codificacion == 0){

        float min_val = -512;
        float max_val = 512;

        int v = strtol(cromosoma.c_str(), NULL, 2);
        float f = min_val + (max_val - min_val) * v / ( pow(2, cromosoma.size() ) -1 );

        vector<float> fen;
        fen.pushback(f);
        this->fenotipo = fen;

    }


}




