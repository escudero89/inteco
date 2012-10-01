#ifndef SOM_H
#define SOM_H

#include <cassert>
#include <iostream>
#include <vector>

#include "neurona.h"
#include "../../utils/utils.h"

using namespace std;

/* Al crear el SOM, una tasa_0 = 0.1 es lo recomendado, y una varianza inicial
 * de magnitud igual al "radio" de la red. Como regla general, el numero de
 * iteraciones para la convergencia debe ser 500 veces el numero de neuronas en
 * la red. */

class SOM {

    bool tasa_fija,        // La tasa cambia por epoca?
         is_printingCSV;        // Imprimo CSV por buffer?

	unsigned int cant,
				 cant_x,
				 cant_y,
				 N,
				 cant_clases;

	float tasa,				// tasa de aprendizaje
		  tasa_n,			// tasa de aprendizaje variable
		  tasa_old,         // tasa de aprendizaje en la que termino
		  varianza,
		  var_n,			// varianza variable
		  tao_1,
		  tao_2;

	vector<Neurona> neuronas;

	vector<float> clases;

	public:

	// Cantidad de neuronas a lo largo del eje x/y, cantidad de inputs, tasa de
	// aprendizaje, y varianza
	SOM(unsigned int cant_x, unsigned int cant_y, unsigned int N, unsigned int cant_clases):
		cant_x(cant_x), cant_y(cant_y), N(N), cant_clases(cant_clases) {
		    srand(time(NULL));
			cant = cant_x * cant_y;
			neuronas.resize(cant);
			is_printingCSV = false;
			inicializar_som();
		};

	void inicializar_som();

    void adaptation(const vector<vector<float> > &samples, float tasa, float var,
                   unsigned int maxit, bool tasa_fija = false);

	void sampling(const vector<vector<float> > &samples, unsigned int maxit);

	void sampling(const vector<vector<float> > &samples, float it, float maxit);
	void updating(const vector<float> &samples, unsigned int idx, unsigned int muestra, float it, float maxit);

    // Modificaciones con respecto al otro

    void save_labels(vector<vector<float> > &samples);
    float set_labels(const vector<vector<float> > &samples);

    // Funcionalidades extras

	void updating_som(unsigned int iteration, float maxit);

	float distancia_neuronal(unsigned int j, unsigned int i);

	float topologic_neigh(unsigned int j, unsigned int i) {
		return exp(-distancia_neuronal(j, i)/(2 * pow(var_n, 2)));
	}

	vector<vector<float> > get_pesos() {
		vector<vector<float> > pesos(cant);
		for (unsigned int j = 0; j < cant; j++) {
			pesos[j] = neuronas[j].get_pesos();
		}
		return pesos;
	}

    void set_print(bool print) {
        if (!remove("logs/buffer.csv")) {
            cout << "Borrado antiguo 'buffer.csv'!\n";
        }
        is_printingCSV = print;
    }

};

#endif // SOM_H
