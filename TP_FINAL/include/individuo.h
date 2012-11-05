#ifndef INDIVIDUO_H
#define INDIVIDUO_H
#include <string>
#include <vector>

#include "punto.h"
#include "../../utils/utils.h"

using namespace std;

class Individuo {
    string cromosoma;
    punto origen;
    vector<punto> tomas;
    Tubo T;

public:
    Individuo(punto, vector<punto>&, string = "");

    void autocompletar();
    string autocompletar_r(punto, vector<punto> &, short);

    unsigned int es_bifurcacion(string);

    string anexarElemento(short, bool);
    bool calcularOrientacion(punto, punto);
    bool calcularDistancia(short);

    string obtenerSubramaje(short);
    string obtenerSubramaje_r(string);

    punto obtenerPuntoPosicion(punto, string, short&);
    punto obtenerPuntoPosicion_helper(string, punto, short&);
    punto nuevaDireccion_helper(punto base, short direccion);
    short cambioDeDireccion(short direccion_anterior, bool esGiroDerecho);

    string get_cromosoma() { return cromosoma; }
};

#endif // INDIVIDUO_H
