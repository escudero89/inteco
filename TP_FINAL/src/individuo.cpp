#include "../include/individuo.h"

Individuo::Individuo(string cromosoma, punto origen) {
    this->cromosoma = cromosoma;
    this->origen = origen;

    T.tubo_recto = "a";
    T.codo_izquierdo = "i";
    T.codo_derecho = "d";
    T.tee_izquierdo = "le+e";
    T.tee_derecho = "re+e";
    T.cruz = "xe+e+e";

    T.separador = "+";

}

/*
"Genera un individuo al azar"
Recibe:
Salida:
*/
void Individuo::autocompletar() {

}

/*
"Va a devolver un codo o tubo recto y si llega a haber
mas tomas libres que nodos libres puede
devolver una cruz o una tee"
Recibe: Cantidad de tomas libres - cantidad nodos libres
Salida: Elemento nuevo a conexionar con la tuberia
*/
string Individuo::anexarElemento(short tomas_libres_relativas) {

    string t;

    double
        p_bifurcacion = 0.1,   // 10%
        p_codo = 0.15,         // 15%
        p_tee = 0.5;

    if (tomas_libres_relativas && get_rand() < p_bifurcacion) {
        // Existe bifurcacion, vemos si es Tee o Cruz
        if (get_rand() < p_tee) {
            // Si es cero izquierdo, uno derecho
            if (calcularOrientacion()) {
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
            if (calcularOrientacion()) {
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
bool Individuo::calcularOrientacion() {
return true;
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
*/
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

/*
"Recibe una seccion del cromosoma base y devuelve la posicion del ultimo
elemento del cromosoma"
Recibe: Seccion de cromosoma base (sin bifurcaciones, solo con codos)
Salida: Devuelve la posicion en la matriz (formato punto)
*/
punto Individuo::obtenerPuntoPosicion(string cromosoma_de_direccion) {

    punto posicion = origen;
    // Siempre empieza con un numero
    string cro(cromosoma_de_direccion.substr(0,1));
    short direccion = atoi(cro.c_str());

    for (unsigned int k = 1, N = cromosoma_de_direccion.size() ; k < N ; k++ ) {

        cro = cromosoma_de_direccion.substr(k, 1);

        posicion = nuevaDireccion_helper(posicion, direccion);

        if (cro == T.codo_izquierdo) {

            direccion = cambioDeDireccion(direccion, false);

        } else if (cro == T.codo_derecho) {

            direccion = cambioDeDireccion(direccion, true);

        }
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
