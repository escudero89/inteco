#include "../include/swarm.h"

using namespace std;

Swarm::Swarm(short cantParticulas, short Dimension, char item) {

    double F;  // Almaceno performance

    /// Creo el enjambre de particulas

    for (short kCant = 0; kCant < cantParticulas; kCant++) {
        Particle P(Dimension, item);
        F = P.EvaluarPbest(true); // Lo evaluo por primera vez para asignar pbest

        if (kCant == 0 || F < gbest) { // es el primer elemento? o el mejor valor de gbest?
            gbest = F;
            gindex = kCant;
        }

        particulas.push_back(P);
    }

}

/// Voy recorriendo cada particula y cambiando su velocidad y posicion
void Swarm::ChangeVelPos(unsigned int iteration, unsigned int maxit) {

    double
        alfa = iteration/maxit,
        c_max = 2.5,
        c_min = 0.5,
        c1 = c_max * (1 - alfa) + c_min * alfa,   // Lo voy reduciendo linealmente
        c2 = c_max * alfa + c_min * (1 - alfa);   // Lo voy aumentando linealmente

    for (unsigned int i = 0, N = particulas.size(); i < N; i++ ) {
        particulas[i].SetConstantes(c1, c2);
        particulas[i].ChangeVelPos(particulas[gindex].GetBestPosition());
    }
}

/// Re-evaluo las particulas luego de haber modificado su vel/pos
void Swarm::EvaluarParticulas() {

    double F;  // Almaceno performance

    for (unsigned int i = 0, N = particulas.size(); i < N; i++ ) {

        F = particulas[i].EvaluarPbest();

        if (F < gbest) { // es el mejor valor de gbest?
            gbest = F;
            gindex = i;
        }

    }

}

/// Voy a ir moviendo mi enjambre por la 'sabana'
vector<double> Swarm::EvaluarSwarm(unsigned int maxit, double tolerancia) {

    vector<double> retorno;

    for (unsigned int iteration = 0; iteration < maxit; iteration++) {
        if (iteration > 0) {    // Luego de la primera iteracion, voy evaluando
            EvaluarParticulas();
        }
        ChangeVelPos(iteration, maxit); // Actualizo la pos/vel

        cout << "Gbest: " << gbest << endl;
        retorno = particulas[gindex].GetBestPosition();
/*
        if (gbest < tolerancia) {
            // Obtengo el mejor valor de x
            cout << "Salgo por gbest [" << gbest << "] < tolerancia \n";
            break;
        }*/
    }

    return retorno;

}
