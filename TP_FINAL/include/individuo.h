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
    Tubo T;

    vector<punto>
        tomas,
        tuberias;

    vector<short>
        direcciones;

public:
    Individuo(punto, vector<punto>&, string = "", bool = true);

    void autocompletar();
    string autocompletar_r(punto, vector<punto>  &, short);

    unsigned int es_bifurcacion(string);
    unsigned int es_parentesis(string);


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
    vector<short> get_direcciones() { return direcciones; }

    punto convertirOrientacion(short direccion);

    string forzar_completado(punto &, short &, punto &);
    string forzar_completado_helper(punto &,short &,punto &,punto &,bool = false);

    string get_spliced_cromosoma(double, vector<punto>&);
    string get_spliced_cromosoma_r(string, unsigned int &);

    string intercambiarCromosoma(string nuevo_cromosoma);

    punto getPosByIndex(unsigned int idx) { return tuberias[idx]; }
    short getDirByIndex(unsigned int idx) { return direcciones[idx]; }

    vector<punto> getPosDirByIndex(unsigned int, punto &, short &, unsigned int = 0);

    string forzarCromosoma(string cromosoma_base, string cromosoma_reemplazado, vector<punto>);

    double evaluarFitness(vector<vector<double> > &);
    double evaluarFitness_helper();

    vector<vector<double> > get_puntos_double();

    vector<punto> get_puntos();
    vector<punto> get_puntos_r(punto, short, string, vector<short> &);

    vector<string> obtener_bifurcaciones(string);

	void mutarCromosoma();

    void cruzarCromosoma(Individuo &I2, double pos_corte);
};

#endif // INDIVIDUO_H
