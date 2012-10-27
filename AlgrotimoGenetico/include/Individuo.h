#ifndef INDIVIDUO_H
#define INDIVIDUO_H


class Individuo
{
    private:
        string cromosoma;
        vector<float> fenotipo;
        float fitness;


    public:
        Individuo(int tam_cromosoma);

        /* Estas funciones variaran segun el problema */
        float evaluarFitness(int fitness_function);
        void actualizarFenotipo(int tipo_codificacion);




};

#endif // INDIVIDUO_H
