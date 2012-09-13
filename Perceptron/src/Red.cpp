#include "../include/Red.h"
/*
aca hay q poner un vector P que va a tener los pesos de cada capa
Esoss pesos se consiguen de la funcion foward pass creo q el de red va a ser un vector de vector de vector
Luego llamamos a backward con el dato q guardamos en red

*/
Red::Red(vector<short> &Capas, float tasa, int N) {
    short cant_capas = Capas.size();
	srand(time(NULL));

	this->capas.resize(cant_capas);

	Capa C(Capas[0], N, tasa);
	capas[0] = C;

    for(short i = 1; i<cant_capas; i++){
        Capa C(Capas[i], Capas[i-1]+1, tasa);
        capas[i] = C;
    }
}

vector<float> Red::forward_pass(vector<float> input){
    short cant_capas = this->capas.size();

	input.pop_back();

    for(short i=0; i<cant_capas; i++) {
        input = capas[i].forward_pass(input);
	}

    return input;
}

void Red::backward_pass(vector<float> ydeseado){
    short cant_capas = this->capas.size(),
        ultimo = cant_capas - 1;

    vector<float> old_grad;

	old_grad = capas[ultimo].backward_pass(ydeseado);

    for (short i = ultimo - 1 ; i >= 0 ; i--) {
        vector< vector<float> > pesos = capas[i + 1].get_pesos();
        old_grad = capas[i].backward_pass(old_grad, pesos);
    }

}
