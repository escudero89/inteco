#include "../include/Capa.h"

Capa::Capa(short cant_neuronas, int N, float tasa, bool es_ultima) {
    this->tasa = tasa;
    this->es_ultima = es_ultima;
    this->miniptrones.reserve(cant_neuronas);
    this->output.resize(cant_neuronas);

    this->cant_neuronas = cant_neuronas;

    for (short i = 0; i < cant_neuronas; i++) {
        Miniptron P(N, tasa);
        this->miniptrones.push_back(P);
    }
}

/* Le pasamos una simple capa de patrones y la capa siguiente para obtener los pesos siguientes para el backwardpass */
vector<float> Capa::forward_pass(vector<float> input, Capa &capaSiguiente) {

    for (short i = 0; i < cant_neuronas ; i++ ) {
		 //Obtengo salida de cada neurona y la guardo en el vector output
		 output[i] = miniptrones[i].get_v(input);

         //debug
          cout<<miniptrones[i].get_v(input)<<"#"<<endl;
		 //end debug

		 //Me guardo en cada neurona los pesos "siguientes" para el backwardpass
		 miniptrones[i].set_pesos_siguientes(capaSiguiente.get_iesimos_pesos(i));

		 // Para debug
		 if(this->es_ultima){
            cout<<"ERROR, ojo que esta capa es la ultima"<<endl;
		 }

	}

    return output;
}
//Sobrecargo foward pass para cuando es la ultima capa
vector<float> Capa::forward_pass(vector<float> input){
//Obtengo salida de cada neurona y la guardo en el vector output

	for (short i = 0; i < cant_neuronas ; i++ ){
        output[i] = miniptrones[i].get_v(input);
	}
    return output;
}

vector<float> Capa::backward_pass(vector<float> &output, vector<float> yAnterior) {

    float y;

    gradiente_local.resize(cant_neuronas);
    variacion_pesos.resize(cant_neuronas);

    for (short i = 0; i < cant_neuronas ; i++ ) {
		y = miniptrones[i].get_salida();

        if (!es_ultima) {
            vector <float> pesos_siguientes;

            // El ouput aca es el gradiente local de la capa siguiente
            printVector(output);
            pesos_siguientes = miniptrones[i].get_pesos_siguientes();
            gradiente_local[i] =  0.5 * (1 + y) * (1 - y) * dot<float> (pesos_siguientes, output);
        } else {
            // Basada en la sigmoidea derivada de la diapositiva, el ouput es ydeseado
            gradiente_local[i] = 0.5 * (output[i] - y) * (1 + y) * (1 - y);
        }

        // Guardamos la variacion de los pesos para luego actualizarlos
		unsigned int N = yAnterior.size();
		variacion_pesos[i].resize(N);

		for(unsigned int j = 0; j<N ; j++) {
            variacion_pesos[i][j] = tasa * gradiente_local[i] * yAnterior[j]; //acomodar ese y
		}
	}

	return gradiente_local;
}

vector< vector<float> > Capa::get_pesos() {

    vector< vector<float> > pesos;
    pesos.resize(cant_neuronas);

    for (short i = 0; i < cant_neuronas ; i++ ) {
		pesos[i] = miniptrones[i].get_pesos();
	}

	return pesos;
}

vector<float> Capa::get_iesimos_pesos(int i){

    vector<float> i_esimos_pesos;
    i_esimos_pesos.resize(cant_neuronas);

    for(short j = 0; j < cant_neuronas; j++)
        i_esimos_pesos[j] = miniptrones[j].getPesoI(i);

    return i_esimos_pesos;

}

/* Actualiza los pesos de cada neurona */
void Capa::actualizar_pesos() {

    for(short i = 0; i < cant_neuronas; i++) {
        this->miniptrones[i].actualizar_pesos(variacion_pesos[i]);
    }

}
