#ifndef SWARM_H
#define SWARM_H

#include "particle.h"

#include <iostream>

class Swarm {

    vector<Particle> particulas;

    short gindex;     // Guardo el indice donde esta el mejor

    double gbest;     // Guardo el valor maximo de global performance

    vector<double> fitness_from_net;    // Para guardar el fitness de la red

    char function_chosen;

public:
        Swarm(short, short);

        void set_function(char item) { function_chosen = item; }

        void ChangeVelPos(unsigned int, unsigned int);

        void EvaluarParticulas();

        vector<double> EvaluarSwarm(unsigned int);

        // Para combinarlo con la red
        short GetBestIndex() { return gindex; }

        vector<double> GetPosition (short indx) { return particulas[indx].GetPosition(); }

        vector<double> GetBestPosition() {
            cout << "\nParticula con gbest: " << gindex <<" [fitness: "<< particulas[gindex].get_pbest() << "]\n";
            return GetPosition(gindex);
        }

        void set_fitness_from_net (double fitness, unsigned int idx) {
            particulas[idx].set_fitness_from_net(fitness);
            fitness_from_net[idx] = fitness;
        }
};

#endif // SWARM_H
