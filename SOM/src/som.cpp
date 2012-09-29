#include "../include/som.h"

void SOM::inicializar_som() {

	float pos_x = 0,
		  pos_y = 0;

    tasa_old = -1;

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

    // El hayking toma 1000, pero creo que es la cantidad de iteraciones maxima
    this->tao_1 = maxit / (log(varianza));   // Haykin, pag452;
    this->tao_2 = maxit;

    sampling(samples, maxit);

    // Luego de que termino, almaceno mi tasa de aprendizaje, para hacerla decrecer linealmente mas tarde (p465)
    tasa_old = tasa_n;
}

// Se encarga de llamar varias epocas de sampling
void SOM::sampling(const vector<vector<float> > &samples, unsigned int maxit) {
	for (unsigned int it = 0; it < maxit; it++) {

        updating_som(it, (float) maxit);

        // Si esta activado printCSV, guardo cada 20 iteraciones los pesos (o 200, si es convergencia)
		//if (is_printingCSV && it%( (tasa_fija)? 5 : 1) == 0 && (!tasa_fija || it < 200)) {
        if (is_printingCSV && it%20 == 0) {
		    cout << it << " . "; cout << "[ " << tasa_n << " | " << var_n << " ]" << endl;
		    vector<vector<float> > datos(get_pesos());
            printCSV<float> (datos, "logs/buffer.csv", true);
		}

		sampling(samples, it, maxit);

	}
	cout << "\n";
}

// Voy tomando de a vectores x, que representa el patron de activacion que se
// esta aplicando a la red.
void SOM::sampling(const vector<vector<float> > &samples, float it, float maxit) {

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
		updating(samples[muestra], idx, it, maxit);
	}

}

// Ya tengo la neurona que se activo, ahora actualizo los pesos
void SOM::updating(const vector<float> &samples, unsigned int idx, float it, float maxit) {

		// Recorro cada neurona de la red
		for (unsigned int j = 0; j < cant; j++) {

            float delta;

            if (tasa_fija) {
                // decrece a cero el topologic neigh
                float topologic = topologic_neigh(j, idx);
                delta = tasa_n * ( (1 - it/maxit) * topologic );
            } else {
                // formula 9.13, haykin
                delta = tasa_n * topologic_neigh(j, idx);
			}

			// Dejamos que la neurona se encargue del "forgeting term" (p451)
			neuronas[j].update(samples, delta);
		}

}

// Actualizamos algunas "variables" del SOM para que vayan "decreciendo"
void SOM::updating_som(unsigned int iteration, float maxit) {

    float n = iteration; // es necesario castearlo

    if (tasa_fija) {
        var_n = varianza;
        // Decrezco la tasa de aprendizaje linealmente de mi vieja tasa a la nueva
         tasa_n = (1 - n/maxit) * tasa_old + n/maxit * tasa;
    } else {
        // Disminuimos el ancho que cubre a los vecinos
        var_n = varianza * exp(-n / tao_1 );
        tasa_n = tasa * exp(-n / tao_2);
    }

}

// Obtengo la distancia entre dos neuronas de la red (Haykin 9.5, p450)
float SOM::distancia_neuronal(unsigned int j, unsigned int i) {

	float pos_x = pow(neuronas[j].get_posx() - neuronas[i].get_posx(), 2),
		  pos_y = pow(neuronas[j].get_posy() - neuronas[i].get_posy(), 2),
		  pos = pos_x + pos_y;

	return pos;
}
