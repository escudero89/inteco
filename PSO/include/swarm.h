#ifndef SWARM_H
#define SWARM_H

#include "particle.h"

#include <iostream>

class Swarm {

    vector<Particle> particulas;

    short gindex;     // Guardo el indice donde esta el mejor

    double gbest;     // Guardo el valor maximo de global performance

    char function_chosen;

public:
        Swarm(short, short, char = 'a');

        void set_function(char item) { function_chosen = item; }

        void ChangeVelPos(unsigned int, unsigned int);

        void EvaluarParticulas();

        vector<double> EvaluarSwarm(unsigned int, double);

};

#endif // SWARM_H
