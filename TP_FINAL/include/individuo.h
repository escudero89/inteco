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
    Individuo(string, punto);

    void autocompletar();

    string anexarElemento(short);
    bool calcularOrientacion();
    bool calcularDistancia(short);

    string obtenerSubramaje(short);
    string obtenerSubramaje_r(string);

    punto obtenerPuntoPosicion(string cromosoma_de_direccion);
    punto nuevaDireccion_helper(punto base, short direccion);
    short cambioDeDireccion(short direccion_anterior, bool esGiroDerecho);
};

#endif // INDIVIDUO_H
