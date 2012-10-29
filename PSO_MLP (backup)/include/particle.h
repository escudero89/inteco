#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>

using namespace std;

class Particle {

    vector<double>
        x,	// Current position
        v,	// Velocity
        p,	// Previous position
        xpbest; // Position of best performance

    double
        pbest,  // Best performance
        c1,     // Constantes de aceleracion (para pbest)
        c2,     // (para gbest)
        fitness_from_net;   // Para trabajar con la red

    short Dimension;    // Dimension del hiperespacio

public:

    Particle(short);

    // La mejor posicion personal tambien es la gbest (para cierta particula)
    vector<double> GetBestPosition () { return xpbest; }

    // Necesito los pesos para la red
    vector<double> GetPosition () { return x; }

    void SetConstantes(double c_1, double c_2) { c1 = c_1; c2 = c_2; };

    /// Funciones complejas

    double EvaluarPbest(bool = false);

    void ChangeVelPos(vector<double>);

    /// Para trabajar con la red

    double get_pbest() { return pbest; }

    void set_fitness_from_net (double fitness) { fitness_from_net = fitness; }

};

#endif // PARTICLE_H
