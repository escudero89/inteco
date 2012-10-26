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
        c2;     // (para gbest)

    char function_chosen;   // Funcion elegida para comparar

    short Dimension;    // Dimension del hiperespacio

public:

    Particle(short, char = 'a');

    // La mejor posicion personal tambien es la gbest (para cierta particula)
    vector<double> GetBestPosition () { return xpbest; }

    void SetConstantes(double c_1, double c_2) { c1 = c_1; c2 = c_2; };

    /// Funciones complejas

    double EvaluarPbest(bool = false);

    void ChangeVelPos(vector<double>);

};

#endif // PARTICLE_H
