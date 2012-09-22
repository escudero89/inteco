#include "../include/Red_RBF.h"

Red_RBF::Red_RBF(int N, vector<short> neuronas, float tasa)
{
    srand(time(NULL));
    this->N = N;
    this->tasa = tasa;

    this->capa_0.resize(neuronas[0]);
    this->capa_1.resize(neuronas[1]);

}


vector< vector<punto> > Red_RBF::k_means(vector<punto> V, int k, float tolerancia, float desvio, float media){

     /**   ------   Inicio k medias aleatoriamente   ------  **/
    vector<punto> medias;
    medias.resize(k);
    vector<punto> medias_old;
    medias_old.resize(k);

    for(int i = 0; i<k; i++){

        medias[i] = punto(this->N); //los puntos son de dimension N
    }
    /**   ------   FIN creacion medias aleatoriamente   ------  **/


    /**   ------   Creo Subconjuntos   ------  **/
    int tamV = V.size();
    vector< vector<punto> > subConjuntos;
    vector<float> aux;
    aux.resize(k);
    float residuo = 0;

    do {
    residuo = 0;
    subConjuntos.clear();
    /* Recorro todos los puntos */
    for(int i=0; i<tamV; i++){

        /* calculo las distancias de todas las medias al punto V[i] y las guardo en aux*/
        for(int j=0; j<k; j++){

            aux[j] = V[i].distancia(medias[j]);

        }

        /* Busco el minimo y me guardo la posicion en la que esta ese minimo*/
        vector<float>::iterator p = min_element(aux.begin(), aux.end());
        int posicion = distance(p, aux.begin());

        /* Pusheo el punto en el subconjunto correspondiente dado por posicion*/
        subConjuntos[posicion].push_back(V[i]);
    }

    /**   ------  FIN Creacion Subconjuntos   ------  **/


    /**   ------  Calcular Nuenvos Centroides   ------  **/
    /* Itero por los subconjuntos y calculo nuevos centroides */
    /* Me guardo las medias anteriores para medir el error */

    medias_old = medias;
    for(int i=0; i<k; i++){

        int tamSubConj = subConjuntos[i].size();
        vector<float> acum; acum.resize(this->N,0);
        punto nuevoCentroide(acum);

        for(int j=0; j<tamSubConj; j++){

            nuevoCentroide = subConjuntos[i][j] + nuevoCentroide;
        }

        nuevoCentroide = nuevoCentroide / subConjuntos[i].size();

        medias[k] = nuevoCentroide;

    }

    /**   ------  FIN Calcular Nuenvos Centroides   ------  **/

    /*Establezco una condicion de corte. El debe ser residuo < tolerancia*/
    /*El residuo es la norma 2 del vector diferencia entre las medias antiguas y nuevas*/

    float residuo = 0;

    for(int i=0; i<k; i++){
        residuo += pow(medias[i].distancia(medias_old[i]),2);
    }

    residuo = sqrt(residuo);

    } while(residuo > tolerancia);

    /* Ahora calculamos los desvios para esas medias */
    vector<float> vectorCero; vectorCero.resize(this->N,0);
    punto puntoCero(vectorCero);
    vector<punto> desvios;
    desvios.resize(k, puntoCero);

    for(int i = 0; i<k; i++){

        for(int j=0; j<subConjuntos[i].size(); j++){

            desvios[i] = (subConjuntos[i][j] - medias[i]).pow2() + desvios[i];
        }

        desvios[i] = (desvios[i]/subConjuntos[i].size()).raizCuadrada();
    }
    vector< vector<punto> > media_y_desvio;

    media_y_desvio.push_back(medias);
    media_y_desvio.push_back(desvios);

return media_y_desvio; // y tambien los sigmas por referencia!!

}
