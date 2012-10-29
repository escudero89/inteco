#include "../include/particle.h"
#include "../../utils/utils.h"

// Declaramos la funcion que vamos a usar en main
double funciones (vector<double>);

/// INPUT: La dimension D del hiperspacio
Particle::Particle(short D) {

	x.resize(D);
	v.resize(D);
	p.resize(D);

	xpbest.resize(D);

	Dimension = D;

    for (short j = 0; j < D; j++) {

        // Creamos valores iniciales de posicion y velocidad pequenios y aleatorios
		x[j] = ((double) rand() / (RAND_MAX)) * 2 - 1;
		v[j] = ((double) rand() / (RAND_MAX)) * 2 - 1;

    }

    // Para combinarlo con red, lo inicializamos alto
    pbest = fitness_from_net = 99999;
}

/// Obtengo el valor de pbest al evaluar la particula, y lo retorno al swarm
double Particle::EvaluarPbest(bool sin_pbest) {

    // Si no tengo un pbest asignado (primera iteracion), lo asigno
    // O si mi nuevo performance es mejor al anterior
    if (sin_pbest || fitness_from_net < pbest) {
        pbest = fitness_from_net;
        xpbest = x;
    }

    return fitness_from_net;
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
        x[i] = x[i] + v[i];
    }

}
