#include "../include/som.h"

void SOM::inicializar_som() {

	float pos_x = 0,
		  pos_y = 0;

	// Utilizo una grilla rectangular para ubicar las neuronas
	for (unsigned int k = 0; k < this->cant; k++) {
		Neurona Nodo(this->N, pos_x, pos_y);
		neuronas[k] = Nodo;

		pos_x++;

		// Si superamos el ancho de la grilla
		if (pos_x >= cant_x) {
			pos_x = 0;
			pos_y++;
		}
	}
}

/// Hay dos Fases en el proceso adaptativo: ordenamiento y convergencia (p452)
// En el ordenamiento, la tasa suele ser mas alta, y descender en el tiempo
void SOM::adaptation(const vector<vector<float> > &samples, float tasa, float var,
                   unsigned int maxit, bool tasa_fija) {

    this->tasa = tasa;
    this->varianza = var;

    this->tasa_fija = tasa_fija;

    this->tao_1 = 1000 * (log(varianza));   // Haykin, pag452;
    this->tao_2 = 1000;

    sampling(samples, maxit);
}

// Se encarga de llamar varias epocas de sampling
void SOM::sampling(const vector<vector<float> > &samples, unsigned int maxit) {
	for (unsigned int it = 0; it < maxit; it++) {

	    // Diapositiva p29 (SOM)
        if (!tasa_fija) {
            updating_som(it);
        }

		sampling(samples);
	}
}

// Voy tomando de a vectores x, que representa el patron de activacion que se
// esta aplicando a la red.
void SOM::sampling(const vector<vector<float> > &samples) {

	// En cada iteracion, ingresamos una sola muestra
	for (unsigned int muestra = 0, cnt = samples.size(); muestra < cnt; muestra++) {

		// Obtenemos el primer valor como minimo
		float min = neuronas[0].get_distancia(samples[muestra]);
		unsigned int idx = 0;

		/// SIMILARITY MATCHING (Haykin p454)
		// Recorro cada neurona, y voy buscando la minima distancia
		for (unsigned int j = 1; j < cant; j++) {

			float distancia = neuronas[j].get_distancia(samples[muestra]);

			// El idx me indica cual neurona tiene el minimo
			if (min > distancia) {
				min = distancia;
				idx = j;
			}

		}

		// Acto seguido, actualizo los pesos
		updating(samples[muestra], idx);
	}

}

// Ya tengo la neurona que se activo, ahora actualizo los pesos
void SOM::updating(const vector<float> &samples, unsigned int idx) {

		// Recorro cada neurona de la red
		for (unsigned int j = 0; j < cant; j++) {

			// formula 9.13, haykin
			float delta = tasa_n * topologic_neigh(j, idx);

			// Dejamos que la neurona se encargue del "forgeting term" (p451)
			neuronas[j].update(samples, delta);
		}

}

// Actualizamos algunas "variables" del SOM para que vayan "decreciendo"
void SOM::updating_som(unsigned int iteration) {

    float n = iteration; // es necesario castearlo

	// Disminuimos el ancho que cubre a los vecinos
    var_n = varianza * exp(-n / tao_1);
    tasa_n = tasa * exp(-n / tao_2);

}

// Obtengo la distancia entre dos neuronas de la red (Haykin 9.5, p450)
float SOM::distancia_neuronal(unsigned int j, unsigned int i) {

	float pos_x = pow(neuronas[j].get_posx() - neuronas[i].get_posx(), 2),
		  pos_y = pow(neuronas[j].get_posy() - neuronas[i].get_posy(), 2),
		  pos = pos_x + pos_y;

	return pos;
}
