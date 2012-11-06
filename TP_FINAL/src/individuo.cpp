#include <sstream>

#include "../include/individuo.h"

Individuo::Individuo(punto origen, vector<punto> &tomas, string cromosoma) {
    this->cromosoma = cromosoma;
    this->origen = origen;
    this->tomas = tomas;

    T.tubo_recto = "a";
    T.codo_izquierdo = "i";
    T.codo_derecho = "d";
    T.tee_izquierdo = "l";
    T.tee_derecho = "r";
    T.cruz = "x";

    T.separador = "+";
}

/*
"Genera un individuo al azar"
Recibe:
Salida:
*/

void Individuo::autocompletar() {

    vector<punto> tomas_libres(tomas);

    short direccion_actual = rand() % 4 + 1;

    // Crear una direccion base al azar para q me de 1..4
    stringstream ss;
    ss << direccion_actual;
    cromosoma += ss.str();

    cromosoma += autocompletar_r(this->origen, tomas_libres, direccion_actual);

    cout << "\n Se ha encontrado camino con " << cromosoma.size() << " tuberias.\n";
}


string Individuo::autocompletar_r(punto base, vector<punto> &tomas_libres, short direccion){

    punto
        punto_toma_libre,
        punto_actual = base;

    short
        menor_dist,
        idx_menor_distancia,
        direccion_actual = direccion;

    bool orientacion;

    string
        retorno,
        nuevo_elemento;

    while(tomas_libres.size()){

        idx_menor_distancia = punto_actual.menor_distancia(tomas_libres,
                                                           menor_dist,
                                                           punto_toma_libre);

        orientacion = calcularOrientacion(convertirOrientacion(direccion_actual),
                                          punto_toma_libre);

        nuevo_elemento = anexarElemento(tomas_libres.size(), orientacion);

        if (es_bifurcacion(nuevo_elemento) == 0) {
            retorno += nuevo_elemento;

            stringstream ss;
        ss << retorno;

        cout << ss.str() << " | " << direccion_actual << "\t Punto actual: ";

            punto_actual = obtenerPuntoPosicion(punto_actual, nuevo_elemento, direccion_actual);

    punto_actual.printPunto();

            if (punto_actual == tomas_libres[0]) {
                break;
            }

        } else {
            stringstream ss; /// PUEDE HABER PROBLEMAAS CON SS y DIRECCION
            ss << direccion << retorno << T.tubo_recto;
            punto_actual = obtenerPuntoPosicion(base, ss.str(), direccion_actual);
            retorno += nuevo_elemento + "(";

            // Flujo principal
            retorno += "(" + autocompletar_r(punto_actual, tomas_libres, direccion_actual) + ")";
            tomas_libres.erase(tomas_libres.begin() + idx_menor_distancia);

            retorno += "(" + autocompletar_r(punto_actual,
                                             tomas_libres,
                                             cambioDeDireccion(direccion_actual,
                                                               orientacion)) + ")";
            tomas_libres.erase(tomas_libres.begin());

            if (nuevo_elemento == T.cruz) {
                retorno += "(" + autocompletar_r(punto_actual,
                                                tomas_libres,
                                                cambioDeDireccion(direccion_actual,
                                                                !orientacion)) + ")";
                tomas_libres.erase(tomas_libres.begin());
            }

            retorno += ")";
        }

    }

    return retorno;

}


unsigned int Individuo::es_bifurcacion(string elemento) {
    unsigned int retorno = 0;

    if (elemento == T.tee_derecho || elemento == T.tee_izquierdo) {
        retorno = 1;
    } else if (elemento == T.cruz) {
        retorno = 2;
    }

    return retorno;
}

/*
"Va a devolver un codo o tubo recto y si llega a haber
mas tomas libres que nodos libres puede
devolver una cruz o una tee"
Recibe: Cantidad de tomas libres - cantidad nodos libres y la orientacion false/true
Salida: Elemento nuevo a conexionar con la tuberia
*/
string Individuo::anexarElemento(short tomas_libres_relativas, bool orientacion){

    string t;
    tomas_libres_relativas = 0; /// ESTO A ARREGLR
    double
        p_bifurcacion = 0.1,   // 10%
        p_codo = 0.35,         // 15%
        p_tee = 0.5;

    if (tomas_libres_relativas && get_rand() < p_bifurcacion) {
        // Existe bifurcacion, vemos si es Tee o Cruz
        if (get_rand() < p_tee) {
            // Si es cero izquierdo, uno derecho
            if (orientacion) {
                t = T.tee_derecho;
            } else {
                t = T.tee_izquierdo;
            }
        // No agregamos cruz si no hay al menos tres tomas libres
        } else if (tomas_libres_relativas > 1) {
            t = T.cruz;
        }
    } else {
    // Sino, agregamos un codo o un tubo recto
        if (get_rand() < p_codo) {
            // Si es cero izquierdo, uno derecho
            if (orientacion) {
                t = T.codo_derecho;
            } else {
                t = T.codo_izquierdo;
            }
        } else {
            t = T.tubo_recto;
        }
    }

    return t;
}

/*
"Dado un indice del cromosoma devuelve 0 o 1 indicando si la
posicion optima es hacia la izquierda o hacia la derecha"
Recibe: indice del elemento en el cromosoma
Salida: 0 -> IZQUIERDA || 1 -> DERECHA
*/
bool Individuo::calcularOrientacion(punto direccion_actual, punto direccion_ir) {

    punto Z(0, 0);
    short retorno;

    // Esto quiere decir q son paralelos
    if (direccion_actual - direccion_ir == Z || direccion_actual + direccion_ir == Z) {
        retorno = rand() % 2;
    } else {
        if (direccion_actual.coordenadas[0] == 0) {
            retorno = direccion_actual.coordenadas[1] * direccion_ir.coordenadas[0];
            // Esto porque me devuelve 1 der , -1 izq
            retorno = (retorno == 1) ? true : false;
        } else {
            retorno = direccion_actual.coordenadas[0] * direccion_ir.coordenadas[1];
            // Esto porque me devuelve -1 der , 1 izq
            retorno = (retorno == -1) ? true : false;
        }

    }

    return (bool) retorno;
}

/*
"Le paso un indice de cromosoma y  devuelve la distancia a
la toma libre mas cercana a ese elemento"
Recibe:
Salida:
*/
bool Individuo::calcularDistancia(short){
    return true;
}

/*
"La idea es que a partir de un indice de elemento dentro del cromosoma,
devolver la subrama libre de bifurcaciones de ese elemento"
Recibe: el indice de la posicion del elemento en base 0
Salida: el subramaje en string
*//*
string Individuo::obtenerSubramaje(short posicion) {

    string cromosoma_r = cromosoma.substr(0, posicion), c;
    short k;

    for (k = 0 ; k < posicion ; k++ ) {
        c = cromosoma_r[k];
        if (c == T.tee_derecho || c == T.tee_izquierdo || c == T.cruz) {
            break;
        }
    }

    return cromosoma_r.substr(0, k) + obtenerSubramaje_r(cromosoma_r.substr(k));
}

string Individuo::obtenerSubramaje_r(string cromosoma_r) {
    string subramaje;
    return subramaje;
}
*/
/*
"Recibe una seccion del cromosoma base y devuelve la posicion del ultimo
elemento del cromosoma"
Recibe: Seccion de cromosoma base (sin bifurcaciones, solo con codos)
Salida: Devuelve la posicion en la matriz (formato punto)
*/
punto Individuo::obtenerPuntoPosicion(punto posicion, string cromosoma_de_direccion, short &direccion) {

    string cro;

    for (unsigned int k = 0, N = cromosoma_de_direccion.size() ; k < N ; k++ ) {

        cro = cromosoma_de_direccion.substr(k, 1);

        posicion = obtenerPuntoPosicion_helper(cro, posicion, direccion);

    }

    return posicion;

}

punto Individuo::obtenerPuntoPosicion_helper(string elemento_de_direccion,
                                             punto posicion,
                                             short &direccion) {

    posicion = nuevaDireccion_helper(posicion, direccion);

    if (elemento_de_direccion == T.codo_izquierdo) {

        direccion = cambioDeDireccion(direccion, false);

    } else if (elemento_de_direccion == T.codo_derecho) {

        direccion = cambioDeDireccion(direccion, true);

    }

    return posicion;
}

/*
"Recibe un punto base, y a partir de cierto valor de direccion, devuelve el punto
incrementado un valor hacia arriba, derecha, abajo o izquierda."
Recibe: punto base para incrementar y un 1,2,3,4 para indicar direccion
Salida: punto base con la nueva direccion aplicada
*/
punto Individuo::nuevaDireccion_helper(punto base, short direccion) {

    switch (direccion) {
        case 1:
            base = base + punto(0, 1);
            break;

        case 2:
            base = base + punto(1, 0);
            break;

        case 3:
            base = base + punto(0, -1);
            break;

        case 4:
            base = base + punto(-1, 0);
            break;

        default:
            cout << "\nError al determinar punto nuevo en nuevaDireccion_helper.\n";
            getchar();
    }

    return base;
}

/*
"A partir de la direccion anterior y un tipo de giro (0: izq, 1:der) obtengo
una nueva direccion expresada en valores 1,2,3,4."
Recibe: una direccion anterior y un tipo de giro
Salida: un valor 1,2,3,4 que indica arriba der abajo izq respectivamente
*/
short Individuo::cambioDeDireccion(short direccion_anterior, bool esGiroDerecho) {

    direccion_anterior += (2 * esGiroDerecho - 1);

    if (direccion_anterior < 1) {
        direccion_anterior = 4;
    } else if (direccion_anterior > 4) {
        direccion_anterior = 1;
    }

    return direccion_anterior;
}

/*
"En base a un valor 1,2,3,4, devuelve un vector de posicion en base a eso. Lo
mejor seria hacer esto directamente en la funcion que retorna 1,2,3,4"
Recibe: un valor 1,2,3,4
Salida: un vector (0,1) (1,0) (0, -1) (-1, 0) respectivamente
*/
punto Individuo::convertirOrientacion(short direccion) {

    punto base;

    switch (direccion) {
        case 1:
            base = punto(0, 1);
            break;

        case 2:
            base = punto(1, 0);
            break;

        case 3:
            base = punto(0, -1);
            break;

        case 4:
            base = punto(-1, 0);
            break;

        default:
            cout << "\nError al determinar punto nuevo en convertirOrientacion.\n";
            getchar();
    }

    return base;

}
