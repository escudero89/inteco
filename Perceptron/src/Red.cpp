#include "../include/Red.h"

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
	

	
	//input = capas[0].forward_pass(input);
    return input;
}
