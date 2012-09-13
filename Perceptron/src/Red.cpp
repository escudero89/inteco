#include "../include/Red.h"
/*
aca hay q poner un vector P que va a tener los pesos de cada capa
Esoss pesos se consiguen de la funcion foward pass creo q el de red va a ser un vector de vector de vector
Luego llamamos a backward con el dato q guardamos en red

*/
Red::Red(vector<short> &Capas, float tasa, int N) {
    this->cant_capas = Capas.size();
	srand(time(NULL));

	this->capas.resize(cant_capas);

	Capa C(Capas[0], N, tasa);
	capas[0] = C;
    //Creamos capas
    for(short i = 1; i < cant_capas - 1; i++) {
        Capa C(Capas[i], Capas[i-1], tasa);
        capas[i] = C;
    }
    //Creamos la ultima capa
    short neuronas_capa = (cant_capas - 2 < 0) ? N : Capas[cant_capas - 2];

    Capa ultima(Capas[cant_capas - 1], neuronas_capa, tasa, true);
    capas[cant_capas-1] = ultima;
}

vector<float> Red::forward_pass(vector<float> input){
    short cant_capas = this->capas.size();

    this->input = input;

    //Pasamos un input y la capa siguiente para que pueda sacar de alli los pesos para el backward
    for(short i=0; i<cant_capas-1; i++) {
        cout<<"Capa: "<<i<<endl;
        input = capas[i].forward_pass(input, capas[i+1]);
    }
    //Hacemos el fowardpass con la ultima, (no le enviamos ninguna otra capa)
    cout<<"Capa Ultima: "<<cant_capas-1<<endl;
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

    // Agregamos un -1 al final para el bias
    yAnterior.push_back(-1);

    return yAnterior;
}

/* Actualiza los pesos de cada una de las neuronas yendo por cada capa */
void Red::actualizar_pesos() {

    for(short i = 0; i < cant_capas; i++) {
        this->capas[i].actualizar_pesos();
    }

}
