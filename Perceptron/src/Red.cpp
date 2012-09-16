#include "../include/Red.h"
/*
aca hay q poner un vector P que va a tener los pesos de cada capa
Esoss pesos se consiguen de la funcion foward pass creo q el de red va a ser un vector de vector de vector
Luego llamamos a backward con el dato q guardamos en red

*/
Red::Red(vector<short> &Capas, float tasa, int N) {
    this->cant_capas = Capas.size();
	srand(time(NULL));

    this->input.resize(N);

	this->capas.resize(cant_capas);
	Capa C(Capas[0], N, tasa, (cant_capas == 1) ? 0 : Capas[1],(cant_capas == 1) ? true : false);
	capas[0] = C;

    //Creamos capas
    for(short i = 1; i < cant_capas - 1; i++) {
        Capa C(Capas[i], Capas[i-1], tasa, Capas[i+1]);
        capas[i] = C;
    }
    //Creamos la ultima capa

    if (cant_capas > 1) {
        Capa ultima(Capas[cant_capas - 1], Capas[cant_capas - 2], tasa, 0, true);
        capas[cant_capas-1] = ultima;
    }
}

vector<float> Red::forward_pass(vector<float> input){
    short cant_capas = this->capas.size();

    this->input = input;

    /*Pasamos un input y la capa siguiente para que pueda sacar de alli los
     pesos para el backward*/
    for(short i=0; i<cant_capas-1; i++) {
        input = capas[i].forward_pass(input, capas[i+1]);
    }
    //Hacemos el fowardpass con la ultima, (no le enviamos ninguna otra capa)
    input = capas[cant_capas-1].forward_pass(input);

    return input;
}

void Red::backward_pass(vector<float> ydeseado){
    short cant_capas = this->capas.size(),
        ultimo = cant_capas - 1;

    vector<float> old_grad;

	old_grad = capas[ultimo].backward_pass(ydeseado, yAnterior(ultimo - 1));

    for (short i = ultimo - 1 ; i >= 0 ; i--) {
        old_grad = capas[i].backward_pass(old_grad, yAnterior(i - 1));
    }

}

/* En base a los indices de las capas, retorna los y correspondientes */
vector<float> Red::yAnterior(short indiceCapa) {

    vector<float> yAnterior;

    if (indiceCapa >= 0) {
        yAnterior = this->capas[indiceCapa].get_output();
    } else {
        yAnterior = this->input;
    }

    return yAnterior;
}

/* Actualiza los pesos de cada una de las neuronas yendo por cada capa */
void Red::actualizar_pesos() {

    for(short i = 0; i < cant_capas; i++) {
        this->capas[i].actualizar_pesos();
    }
    /*
    vector<vector<float> > D = capas[2].get_pesos();
    printVectorVector<float>(D);
    cout << "---------------------------\n";*/
}

/*Entrena/prueba la red con un solo patron. Se considera que en los
ultimos elementos del patron viene el yDeseado.
Si probar = true entonces prueba la red con los patrones pasados y devuelve
TRUE si el resultado fue el correcto o FALSE si fue incorrecto
Si probar = false, entonces entrena la red actualizando los pesos correspondientes*/
bool Red::entrenarRed(vector<float> P, bool probar){//NO pasar el P por referencia

    vector <float> yDeseado;
    unsigned int yDeseadoFloat = int(P.back()); //Casteo

    P.pop_back();

    yDeseado.resize(capas.back().get_cant_neuronas(), -1);
    vector<float> salida = this->forward_pass(P);
    vector<float> salida2 = salida;
    yDeseado[yDeseadoFloat] = 1;

    bool acerto = false;
    bool yaSeActivoUna = false;
    if(probar){

       for(unsigned int i=0; i<salida.size(); i++){

           if (salida[i] > 0) {
               salida[i] = 1;
           }
           else{
                salida[i]=0;
           }

            if(salida[i] == 1){//Si se activo una neurona
                if(yaSeActivoUna){ //Pregunto si ya se habia activado otra
                    acerto = false; //Si ya se activo otra, entonces hay un error y devuelvo false
                    break;
                }

                yaSeActivoUna = true;

                if(i == yDeseadoFloat){ //si la que se activa es la que se tenia q activar
                    acerto = true;
                }
            }
        }

        cout<<"Salida de la red: "<<endl;
        printVector<float>(salida2);
        cout<<"Salida NORMALIZADA de la red: "<<endl;
        printVector<float>(salida);
        cout<<"Patron Real (segun archivo): "<<endl;
        printVector<float>(P);
        cout<<"Clase real (segun archivo): "<<yDeseadoFloat<<" (acerto: " << acerto << ")"<<endl;
        cout<<"____________________"<<endl;
        getchar();

    }
    else {
        this->backward_pass(yDeseado);
        this->actualizar_pesos();
    }

    return acerto;

}

float Red::estEntrenamiento(vector< vector<float> > &P, bool probar, int cant){

    int tam = P.size();

    if(probar){
        int aciertos = 0;
        for(int i=0; i<tam; i++){
            if(entrenarRed(P[i], true)){
                aciertos += 1;
            }
        }
        return float(float(aciertos)/float(tam));
    }

    else{
        for(int j=0; j<cant; j++){
            for(int i=0; i<tam; i++){
                entrenarRed(P[i]);
            }
        }
        return 123.0;

    } // fin else
} //fin funcion

/* Hace la validacion cruzada usando el leave-k-out */
float Red::validacion_cruzada(string path, short k) {
    vector< vector<float> > P;
    parseCSV<float>(path, P);
    return leave_k_out(P, k);
}

/* Leave-Something-Out */
float Red::leave_k_out(vector< vector<float> > &patrones, short k) {

    unsigned int indice = 0, contador = 0, N = patrones.size();
    float error = 0;

    while (indice + k - 1 < N) {

        contador++;

        vector< vector<float> > entrenamiento;
        vector< vector<float> > prueba;

        for (unsigned int i = 0; i < N; i++) {
            if (i == indice) {
                vector< vector<float> >::const_iterator inicio = patrones.begin();
                vector< vector<float> >::const_iterator first = patrones.begin() + i;
                vector< vector<float> >::const_iterator last = patrones.begin() + (i + k);
                vector< vector<float> >::const_iterator fin = patrones.end();

                prueba = vector< vector <float> >(first, last);

                entrenamiento = vector< vector <float> >(inicio, first);
                entrenamiento.insert(entrenamiento.end(), last, fin);

                /* DEBUG MODE ON ehh marcos :P */
                /*cout << "\n-------------------------------\n";
                cout << "\nEntrenamiento:\n";
                printVectorVector(entrenamiento, ',', "");
                cout << "\nPrueba:\n";
                printVectorVector(prueba, ',', "")*/;
                /* DEBUG MODE OFF */

                break;
            }
        }

        /// Aca llamo a una funcion que entrene las neuronas
        estEntrenamiento(entrenamiento);
        float err = estEntrenamiento(prueba, true);
        cout << err << endl;
        error += pow(err, 2);
        reinicializar_red();

        indice += k;
    }

    return sqrt(error/contador);
}
