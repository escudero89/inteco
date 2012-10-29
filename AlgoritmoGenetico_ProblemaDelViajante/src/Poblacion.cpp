#include "../include/Poblacion.h"

Poblacion::Poblacion(int cantIndividuos,
                      int tamCromosoma,
                      float brecha,
                      int tipo_codificacion,
                      int fitness_function,
                      float prob_cruza,
                      float prob_mut,
                      int maxima_poblacion,
                      int minima_poblacion,
                      vector<vector<float> > const &ciudades)
{
    this->ciudades = ciudades;
    this->maxima_poblacion = maxima_poblacion;
    this->minima_poblacion = minima_poblacion;
    this->prob_cruza = prob_cruza;
    this->prob_mut = prob_mut;

    this->brecha_generacional = brecha;
    Individuo I(tamCromosoma, tipo_codificacion, fitness_function, ciudades);

    this->individuos.resize(cantIndividuos, I);

    for(int i = 0; i<cantIndividuos; i++){
        Individuo I(tamCromosoma, tipo_codificacion, fitness_function, ciudades);
        individuos[i] = I;
    }

}

void Poblacion::cruzar(Individuo padre_1,
                        Individuo padre_2,
                         Individuo &hijo_1,
                          Individuo &hijo_2){

    /** Se usa ORDER CROSSOVER (OX) **/

    cout<<"Cromosomas de los padres"<<endl;
    cout<<"Padre_1: "<<padre_1.cromosoma<<endl;
    cout<<"Padre_2: "<<padre_2.cromosoma<<endl;
//    getchar();

    padre_1.cromosoma.erase(40,4);
    padre_1.cromosoma.erase(0,4);
    padre_2.cromosoma.erase(40,4);
    padre_2.cromosoma.erase(0,4);

    int fen_size = padre_1.fenotipo.size()-2;


    /*Obtenemos 2 puntos de cruza*/
    int punto_cruza_1 = rand() % fen_size;
    int punto_cruza_2 = rand() % fen_size;

    cout<<"Puntos de cruza: "<<endl;
    cout<<punto_cruza_1<<endl;
    cout<<punto_cruza_2<<endl;
//    getchar();

    /* los ordenamos */
    if(punto_cruza_1 > punto_cruza_2)
        swap(punto_cruza_1, punto_cruza_2);


    cout<<"Puntos de cruza Ordenados: "<<endl;
    cout<<punto_cruza_1<<endl;
    cout<<punto_cruza_2<<endl;
//    getchar();

    /*Limpio los cromosomas*/
    hijo_1.cromosoma.clear();
    hijo_2.cromosoma.clear();

    /*Armo vectores de string binarios (para facilitar la cruza) */
    vector<string> hijo_1_vec;
    vector<string> hijo_2_vec;
    vector<string> padre_1_vec;
    vector<string> padre_2_vec;
    padre_1_vec.resize(fen_size);
    padre_2_vec.resize(fen_size);

    if(fen_size!= 9)
    {
        cout<<"FENSIZE DISTINTO DE 9"<<endl;
        getchar();
    }

    for(int i=0; i<fen_size; i++){
        padre_1_vec[i] = padre_1.cromosoma.substr(i*4, 4);
        padre_2_vec[i] = padre_2.cromosoma.substr(i*4, 4);
    }

    cout<<"Vectores binarios Padre 1 y Padre 2"<<endl;
    printVector<string>(padre_1_vec);cout<<endl;
    printVector<string>(padre_2_vec);cout<<endl;
//    getchar();

    /*A partir de ahora trabajo con los vectores de string*/

    /*Corto los padres en 3 pedazos segun los puntos de cruza*/

    /*Corto padre_1*/
    vector<string> P1c1;
    P1c1.assign(padre_1_vec.begin(),padre_1_vec.begin() + punto_cruza_1);

    vector<string> P1c2;
    P1c2.assign(padre_1_vec.begin()+punto_cruza_1, padre_1_vec.begin() + punto_cruza_2);

    vector<string> P1c3;
    P1c3.assign(padre_1_vec.begin()+punto_cruza_2, padre_1_vec.end());

    /*Corto padre_2*/
    vector<string> P2c1;
    P2c1.assign(padre_2_vec.begin(),padre_2_vec.begin() + punto_cruza_1);

    vector<string> P2c2;
    P2c2.assign(padre_2_vec.begin()+punto_cruza_1,padre_2_vec.begin() + punto_cruza_2);

    vector<string> P2c3;
    P2c3.assign(padre_2_vec.begin()+punto_cruza_2,padre_2_vec.end());


    cout<<"Segmentos de cortado"<<endl;
    cout<<"P1c1: "<<endl;
    printVector<string>(P1c1);
    cout<<"P1c2: "<<endl;
    printVector<string>(P1c2);
    cout<<"P1c3: "<<endl<<endl;
    printVector<string>(P1c3);
    cout<<"P2c1: "<<endl;
    printVector<string>(P2c1);
    cout<<"P2c2: "<<endl;
    printVector<string>(P2c2);
    cout<<"P2c3: "<<endl;
    printVector<string>(P2c3);
//    getchar();

    /** Cruza (OX), para obtener hijo 1 */
    hijo_1_vec = P1c2;

    cout<<"Hijo_1_vec: "<<endl;
    printVector<string>(hijo_1_vec);
//    getchar();

    /**hacer mas eficiente mejorando el orden**/
    P2c1.insert(P2c1.begin(), P2c3.begin(), P2c3.end());
    P2c1.insert(P2c1.end(),P2c2.begin(), P2c2.end());

    cout<<"P2c1 con todo insertado"<<endl;
    printVector<string>(P2c1);
//    getchar();

    /*Vectores auxiliares*/
    vector<string> delante;
    vector<string> detras;

    /*Mientras el tamaño del hijo sea menor que el del padre*/
    int pos = 0;
    cout<<"Inicio WHILE"<<endl;
//    getchar();
    while(hijo_1_vec.size() + delante.size() + detras.size()< padre_1_vec.size()){

        cout<<"Tamanio hijo_1_vec: "<<hijo_1_vec.size();
        cout<<"Tamanio padre_1_vec: "<<padre_1_vec.size();


        /*Si no encuentra el elemento*/
        cout<<"Elemento a buscar: "<<endl;
        cout<<P2c1[pos]<<endl;
        cout<<"En: "<<endl;
        printVector<string> (hijo_1_vec);
//        getchar();

        if( find(hijo_1_vec.begin(), hijo_1_vec.end(), P2c1[pos]) == hijo_1_vec.end()){

            cout<<"El elemento no estaba, lo puede agregar..."<<endl;
//            getchar();

            /*y si no se fue de rango*/
            if(hijo_1_vec.size() + delante.size() < (padre_1_vec.size() - punto_cruza_1)){

                cout<<"entra por delante"<<endl;
//                getchar();

                delante.push_back(P2c1[pos]);

                printVector<string>(delante);
//                getchar();
            }
            else{
                cout<<"entra por detras"<<endl;
//                getchar();

                detras.push_back(P2c1[pos]);

                printVector<string>(detras);
//                getchar();
            }

        }else{
        cout<<"El elemento estaba, no lo agrega"<<endl;
        }

        pos++;

    }
        cout<<"Salio de WHILE"<<endl;
//        getchar();

        /* doy vuelta el detras */
        reverse(detras.begin(),detras.end());

        detras.insert(detras.end(), hijo_1_vec.begin(), hijo_1_vec.end());
        /*junto todo*/
        detras.insert(detras.end(), delante.begin(), delante.end());

        detras.insert(detras.begin(), "0000");
        detras.insert(detras.end(), "0000");

        cout<<"++++VECTOR MUTADO+++++"<<endl;
        printVector<string>(detras);
//        getchar();

        /*llevamos todo devuelta al string binario*/
        for(int i=0; i<detras.size(); i++){
            hijo_1.cromosoma += detras[i];
        }



    /**Cruza (OX) para obtener hijo 2**/
    /* Limpiamos vectores */
    detras.clear();
    delante.clear();
    P1c1.clear();
    P1c2.clear();
    P1c3.clear();
    P2c1.clear();
    P2c2.clear();
    P2c3.clear();

    P1c1.assign(padre_1_vec.begin(),padre_1_vec.begin() + punto_cruza_1);
    P1c2.assign(padre_1_vec.begin()+punto_cruza_1, padre_1_vec.begin() + punto_cruza_2);
    P1c3.assign(padre_1_vec.begin()+punto_cruza_2, padre_1_vec.end());
    P2c1.assign(padre_2_vec.begin(),padre_2_vec.begin() + punto_cruza_1);
    P2c2.assign(padre_2_vec.begin()+punto_cruza_1,padre_2_vec.begin() + punto_cruza_2);
    P2c3.assign(padre_2_vec.begin()+punto_cruza_2,padre_2_vec.end());







    /** Cruza (OX), para obtener hijo 1 */
    hijo_2_vec = P2c2;

    cout<<"Hijo_2_vec: "<<endl;
    printVector<string>(hijo_2_vec);
//    getchar();

    /**hacer mas eficiente mejorando el orden**/
    P1c1.insert(P1c1.begin(), P1c3.begin(), P1c3.end());
    P1c1.insert(P1c1.end(),P1c2.begin(), P1c2.end());

    cout<<"P1c1 con todo insertado"<<endl;
    printVector<string>(P1c1);
//    getchar();


    /*Mientras el tamaño del hijo sea menor que el del padre*/
    pos = 0;
    cout<<"Inicio WHILE"<<endl;
//    getchar();
    while(hijo_2_vec.size() + delante.size() + detras.size()< padre_2_vec.size()){

        cout<<"Tamanio hijo_2_vec: "<<hijo_2_vec.size();
        cout<<"Tamanio padre_2_vec: "<<padre_2_vec.size();


        /*Si no encuentra el elemento*/
        cout<<"Elemento a buscar: "<<endl;
        cout<<P1c1[pos]<<endl;
        cout<<"En: "<<endl;
        printVector<string> (hijo_2_vec);
//        getchar();

        if( find(hijo_2_vec.begin(), hijo_2_vec.end(), P1c1[pos]) == hijo_2_vec.end()){

            cout<<"El elemento no estaba, lo puede agregar..."<<endl;
//            getchar();

            /*y si no se fue de rango*/
            if(hijo_2_vec.size() + delante.size() < (padre_2_vec.size() - punto_cruza_1)){

                cout<<"entra por delante"<<endl;
//                getchar();

                delante.push_back(P1c1[pos]);

                printVector<string>(delante);
//                getchar();
            }
            else{
                cout<<"entra por detras"<<endl;
//                getchar();

                detras.push_back(P1c1[pos]);

                printVector<string>(detras);
//                getchar();
            }

        }else{
        cout<<"El elemento estaba, no lo agrega"<<endl;
        }

        pos++;

    }
        cout<<"Salio de WHILE"<<endl;
//        getchar();

        /* doy vuelta el detras */
        reverse(detras.begin(),detras.end());

        detras.insert(detras.end(), hijo_2_vec.begin(), hijo_2_vec.end());
        /*junto todo*/
        detras.insert(detras.end(), delante.begin(), delante.end());

        detras.insert(detras.begin(), "0000");
        detras.insert(detras.end(), "0000");

        cout<<"++++VECTOR MUTADO+++++"<<endl;
        printVector<string>(detras);
//        getchar();

        /*llevamos todo devuelta al string binario*/
        for(int i=0; i<detras.size(); i++){
            hijo_2.cromosoma += detras[i];
        }

}



void Poblacion::mutar(Individuo &I){
   int punto_1 = rand() % (I.fenotipo.size()-2);
   int punto_2 = rand() % (I.fenotipo.size()-2);

    I.cromosoma.erase(40,4);
    I.cromosoma.erase(0,4);
    vector<string> I_vec;

    for(int i=0; i<(I.fenotipo.size()-2); i++){
        I_vec.push_back(I.cromosoma.substr(i*4, 4));
    }

    string remplazo = I_vec[punto_2];
    I_vec[punto_2] = I_vec[punto_1];
    I_vec[punto_1] = remplazo;

    I.cromosoma.clear();

    for(int i=0; i<(I.fenotipo.size()-2); i++){
        I.cromosoma += I_vec[i];
    }

    remplazo = "0000";
    I.cromosoma.insert(0, remplazo);

    I.cromosoma.insert(40, remplazo);

 }

void Poblacion::reproduccion(vector<Individuo> &nueva_generacion){

    /** REPRODUCCION: SELECCION - CRUZA - MUTACION **/

    /* SELECCION: METODO POR COMPETENCIAS */

    /*Paso por referencia el vector donde voy
     a poner los individuos de la nueva generacion: &nueva_generacion    */
     nueva_generacion.clear();

    /*Cantidad de individuos que tendra la nueva generacion:
     el valor anterior mas un valor al azar no mayor a su 25%               */

    int variacion = (rand() % int(0.1 * float(individuos.size()) +1)) -
                            int((0.1 * float(individuos.size()))/2);

    int cant_indv_nuevos =  individuos.size() + variacion;

    if(cant_indv_nuevos > maxima_poblacion)
        cant_indv_nuevos = maxima_poblacion;

    if(cant_indv_nuevos < minima_poblacion)
        cant_indv_nuevos = minima_poblacion;

    /*Cantidad de inviduos a competir*/
    int cant_competidores = 5;

    /*Vector de los individuos competidores y su
    correspondiente fitness                     */
    vector<int> competidores;
    competidores.resize(cant_competidores);
    vector<float> fitness_competidores;
    fitness_competidores.resize(cant_competidores);

    /*ELITISMO*/
    nueva_generacion.push_back(individuos[getMejorIndividuo()]);

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
                /* MUESTRA GANADORES
                cout<<"Ganadores: "<<endl;
                cout<<ganador_1<<endl;
                cout<<ganador_2<<endl;
                */


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
