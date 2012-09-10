#include "../include/Red.h"

Red::Red(vector<short> &Capas, float tasa, int N) {
    short cant_capas = Capas.size();
    this->capas.reserve(cant_capas);
    this->capas.resize(cant_capas);

    for(short i=0; i<cant_capas; i++){
        Capa C(Capas[i],N,tasa);
        capas[i] = C;
        //cout<<(capas[i]).cant_neuronas;
    }
    cout<<capas.size()<<endl;
}

vector<float> Red::forward_pass(vector<float> input){
    short cant_capas = this->capas.size();

    for(short i=0; i<cant_capas; i++)
    {
        input = (this->capas[i]).forward_pass(input);

    }

    return input;
}
