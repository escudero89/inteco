#include "../include/Red_RBF.h"

Red_RBF::Red_RBF(int N, vector<short> neuronas, float tasa)
{
    srand(time(NULL));
    this->N = N;
    this->tasa = tasa;

    neurona_RBF porDefecto_0(N);
    neurona porDefecto_1(N, tasa);

    this->capa_0.resize(neuronas[0], porDefecto_0);
    this->capa_1.resize(neuronas[1], porDefecto_1);

}


vector< vector<punto> > Red_RBF::k_means(vector<punto> V,
                                          int k,
                                           float tolerancia,
                                            float desvio, float media){

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
    subConjuntos.resize(k);

    /* Recorro todos los puntos */
    for(int i=0; i<tamV; i++){

        /* calculo las distancias de todas las medias al punto V[i] y las guardo en aux*/
        for(int j=0; j<k; j++){
            aux[j] = V[i].distancia(medias[j]);
        }

        /* Busco el minimo y me guardo la posicion en la que esta ese minimo*/
        vector<float>::iterator p = min_element(aux.begin(), aux.end());
        int posicion = distance(aux.begin(),p);

        /* Pusheo el punto en el subconjunto correspondiente dado por posicion*/

        subConjuntos[posicion].push_back(V[i]);

    }

    /**   ------  FIN Creacion Subconjuntos   ------  **/

    /** Pregunto si se encontraron las medias, sino, relanzo el k-means**/
        for(int i=0; i<k; i++){

            if(subConjuntos[i].size()== 0){
                cout<<"No se pudieron encontrar las "<<k<<" medias."<<endl;
                cout<<"Presione cualquier tecla para relanzar..."<<endl;
                getchar();
                return this->k_means(V,k,tolerancia,desvio,media);
                break;
            }

        }
    /** FIN verificacion**/


    /**   ------  Calcular Nuevos Centroides   ------  **/
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

        nuevoCentroide = nuevoCentroide / tamSubConj;

        medias[i] = nuevoCentroide;

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

        for(unsigned int j=0; j<subConjuntos[i].size(); j++){

            desvios[i] = (subConjuntos[i][j] - medias[i]).pow2() + desvios[i];
        }

        desvios[i] = (desvios[i]/subConjuntos[i].size()).raizCuadrada();
    }
    vector< vector<punto> > media_y_desvio;

    media_y_desvio.push_back(medias);
    media_y_desvio.push_back(desvios);

return media_y_desvio; // y tambien los sigmas por referencia!!

}


void Red_RBF::entrenarCapa0(vector<punto> patrones, int k){
    vector< vector<punto> > out;

    out = k_means(patrones, k);

    for(int i = 0; i<capa_0.size(); i++){

        capa_0[i].set_media(out[0][i]);
        capa_0[i].set_desvio(out[1][i]);

    }


}

vector<float> Red_RBF::probarCapa0(punto P){
     int tam = capa_0.size();
     vector<float> salida;
     salida.resize(tam);

     for(int i = 0; i <tam; i++){
        salida[i] = capa_0[i].funcionDeActivacion(P);
     }

    return salida;
}

void Red_RBF::entrenarCapa1(vector<punto> patrones, vector<float> yDeseado){

    vector<float> salidas;

    for(int i = 0; i<patrones.size(); i++){

        salidas = probarCapa0(patrones[i]);
        salidas.push_back(yDeseado[i]);

        //Entreno cada neurona de la capa 1
        for(int j = 0; j<capa_1.size(); j++){

                capa_1[j].entrenar(salidas);
        }


    }

}


float Red_RBF::probarRed(vector< vector<float> > V){

    float error = 0;


return error;
}


