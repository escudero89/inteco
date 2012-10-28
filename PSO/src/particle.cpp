#include <cmath>

#include "../include/particle.h"
#include "../../utils/utils.h"

// Declaramos la funcion que vamos a usar en main
double funciones (vector<double>, char);

/// INPUT: La dimension D del hiperspacio
Particle::Particle(short D, char item, double range_min, double range_max) {

	x.resize(D);
	v.resize(D);
	p.resize(D);

	xpbest.resize(D);

    function_chosen = item;

    p_range_min = range_min;
    p_range_max = range_max;

	Dimension = D;

    for (short j = 0; j < D; j++) {

        // Creamos valores iniciales de posicion y velocidad pequenios y aleatorios
        v[j] = ((double) rand() / (RAND_MAX)) * 2 - 1;

        // Pero los valores de X van a estar a mitad del rango
		x[j] = (p_range_max + p_range_min) / 2
               + ((double) rand() / (RAND_MAX)) * 2 - 1;

    }

}

/// Obtengo el valor de pbest al evaluar la particula, y lo retorno al swarm
double Particle::EvaluarPbest(bool sin_pbest) {

    double F = funciones(x, function_chosen);
    // Si no tengo un pbest asignado (primera iteracion), lo asigno
    // O si mi nuevo performance es mejor al anterior
    if (sin_pbest || F < pbest) {
        pbest = F;
        xpbest = x;
    }

    return F;
}

/// Cambio el valor de velocidad y posicion de la particula
void Particle::ChangeVelPos(vector<double> xgbest) {

    double
        r1 = ((double) rand() / (RAND_MAX)),    // valores entre 0 y 1
        r2 = ((double) rand() / (RAND_MAX)),

        p1 = r1 * c1,
        p2 = r2 * c2,
        inertia = 1;

    for (short i = 0; i < Dimension; i++) {
        v[i] = inertia * v[i] + p1 * (xpbest[i] - x[i]) + p2 * (xgbest[i] - x[i]);

        double new_position = x[i] + v[i];

        if (new_position >= p_range_min && new_position <= p_range_max) {
            x[i] = new_position;
        }
    }

}
