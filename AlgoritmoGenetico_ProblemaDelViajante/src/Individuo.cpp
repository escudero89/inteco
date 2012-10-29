#include "../include/Individuo.h"

Individuo::Individuo(int tam_cromosoma,
                      int tipo_codificacion,
                       int fitness_function,
                       vector<vector<float> > ciudades)
{
    this->ciudades = ciudades;
    this->fitness_function = fitness_function;
    this->tipo_codificacion = tipo_codificacion;

    vector<int> rutas;
    for(int i=1; i<10; i++){
        rutas.push_back(i);
    }

    random_shuffle(rutas.begin(),rutas.end());

    cromosoma += dec2bin(0); //Empieza en la ciudad 0

    for(int i=0; i<rutas.size(); i++){
        cromosoma += dec2bin(rutas[i]);
    }
    cromosoma += dec2bin(0); //Termina en la ciudad 0

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

    if(fitness_function == 1){

        float f = this->fenotipo[0];
        /*Para asegurarme q sea positiva mi funcin de fitness*/
        int c_max = 30;

        /* Funcion de fitnes propuesta por Goldberg pag:76*/
        ret = c_max - ( f + 5 * sin(3*f) + 8 * cos(5*f));
        ret = (ret > 0 ? ret : 0);
        this->fitness = ret;

    }

    if(fitness_function == 2){
        float x = fenotipo[0];
        float y = fenotipo[1];

        /*Para asegurarme q sea positiva mi funcin de fitness*/
        int c_max = 25;

        /* Funcion de fitnes propuesta por Goldberg pag:76*/
        ret = c_max - pow((pow(x,2.0) + pow(y,2.0)), 0.25) * (pow( sin(50*pow((pow(x,2.0) + pow(y,2.0)),0.1)),2.0) +1);
        ret = (ret > 0 ? ret : 0);
        this->fitness = ret;


    }

    if(fitness_function == 3){

        int c_max = 1000;

        /* acumulamos las distancias entre la ciudad i e i+1 */
        float acum = 0;

        for(int i=0; i<fenotipo.size() - 1; i++){

            acum += ciudades[fenotipo[i]][fenotipo[i+1]];
        }

        this->fitness = ret = c_max - acum;


    }



    return ret;
}


void Individuo::actualizarFenotipo(){

    if(tipo_codificacion == 0){

        float min_val = -512;
        float max_val = 512;

        /*Decodificamos de binario a entero*/
        int v = strtol(cromosoma.c_str(), NULL, 2);

        /*Decodificamos de entero a real*/
        float f = min_val + (max_val - min_val) * v / ( pow(2, cromosoma.size() ) -1 );

        vector<float> fen;
        fen.push_back(f);
        this->fenotipo = fen;

    }

    if(tipo_codificacion == 1){

        float min_val = 0;
        float max_val = 20;

        /*Decodificamos de binario a entero*/
        int v = strtol(cromosoma.c_str(), NULL, 2);

        /*Decodificamos de entero a real*/
        float f = min_val + (max_val - min_val) * v / ( pow(2, cromosoma.size() ) -1 );

        vector<float> fen;
        fen.push_back(f);
        this->fenotipo = fen;

    }

    if(tipo_codificacion == 2){
        float min_val = -100;
        float max_val = 100;

        if(cromosoma.size() % 2 != 0){
            cout<<"ATENCION! El cromosoma debería ser par para "<<endl;
            cout<<"poder tener la misma resolucion en X y en Y"<<endl;
            getchar();
        }

        /* Obtenemos las dos coordenadas por separado, X e Y */
        string cord_x = cromosoma.substr(0,cromosoma.size()/2);
        string cord_y = cromosoma.substr(cromosoma.size()/2);

        /* Decodificamos de binario a entero */
        int v_x = strtol(cord_x.c_str(), NULL, 2);
        int v_y = strtol(cord_y.c_str(), NULL, 2);

        /* Decodificamos de entero a real */
        float f_x = min_val + (max_val - min_val) * v_x / ( pow(2.0, cromosoma.size()/2 ) -1 );
        float f_y = min_val + (max_val - min_val) * v_y / ( pow(2.0, cromosoma.size()/2 ) -1 );

        /* Devolvemos en el vector las dos coordenadas del fenotipo */
        vector<float> fen;
        fen.push_back(f_x);
        fen.push_back(f_y);

        this->fenotipo = fen;

    }

    if(tipo_codificacion == 3){

        if(cromosoma.size() % 11 != 0){
            cout<<"ATENCION! El cromosoma debería ser multiplo de 11"<<endl;
            getchar();
        }

        /* Obtenemos las ciudades por separado (en binario) */
        vector<string> ciudades_bin;
        ciudades_bin.resize(11);

        /* Voy tomando de a cuatro bits */
        for(int i = 0; i < 11; i++ ){
            ciudades_bin[i] = cromosoma.substr(i*4,4);
        }


        /* Decodificamos de binario a entero (sera el indice de la matiz) */
        vector<float> fen;
        fen.resize(11);

        for(int i = 0; i < 11; i++ ){
            fen[i] = strtol(ciudades_bin[i].c_str(), NULL, 2);
        }


        /* Actualizamos el fenotipo del individuo*/
        this->fenotipo = fen;

    }

}




