#include <sstream>

#include "../include/individuo.h"

Individuo::Individuo(punto origen, vector<punto> &tomas, string cromosoma) {
    this->cromosoma = cromosoma;
    this->origen = origen;
    this->tomas = tomas;

    // El primer punto es el origen
    tuberias.push_back(origen);

    T.tubo_recto = "a";
    T.codo_izquierdo = "i";
    T.codo_derecho = "d";
    T.tee_izquierdo = "l";
    T.tee_derecho = "r";
    T.cruz = "x";

    T.separador = "E";
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

    // Agrego la direccion a mi vector de direcciones
    direcciones.push_back(direccion_actual);

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
        direccion_actual = direccion,
        radio_absorcion = 5;

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

            if (menor_dist < radio_absorcion){
                tomas_libres[idx_menor_distancia].printPunto();
                retorno += forzar_completado(punto_actual, direccion_actual, tomas_libres[idx_menor_distancia]);

                tomas_libres.erase(tomas_libres.begin() + idx_menor_distancia);
                cout << "Alcanzado! -----------------------------------\n";

            } else {
                retorno += nuevo_elemento;

                stringstream ss;
                ss << retorno;
                punto_actual = obtenerPuntoPosicion(punto_actual, nuevo_elemento, direccion_actual);

                cout << ss.str() << " | " << direccion_actual << "\t Punto actual: ";
                punto_actual.printPunto();

                if (punto_actual == tomas_libres[idx_menor_distancia]) {
                    tomas_libres.erase(tomas_libres.begin() + idx_menor_distancia);
                    cout << "Alcanzado! -----------------------------------\n";
                }

            }

        } else {
            // Calculo el punto actual en base a mi punto anterior, la direccion, y el flujo principal
            punto_actual = obtenerPuntoPosicion(punto_actual, T.tubo_recto, direccion_actual);

            retorno += "(" + nuevo_elemento;

            /// MANIPULACION DE TOMAS LIBRES

            /// Borro las tomas libres antes de asignarlas, asi recursivamente no me jode.
            //Esto podria joder si ya saco una toma porque ya paso por ahi//
            vector<punto>
                toma_flujo_principal,
                toma_flujo_secundario,
                toma_flujo_terciario;

            toma_flujo_principal.push_back(tomas_libres[idx_menor_distancia]);

            // Borro la ya "asignada"
            tomas_libres.erase(tomas_libres.begin() + idx_menor_distancia);

            // Asigno ya el flujo secundario, y si hay, el terciario
            toma_flujo_secundario.push_back(tomas_libres[0]);
            tomas_libres.erase(tomas_libres.begin());

            if (tomas_libres.size()) {
                if (nuevo_elemento == T.cruz) {
                    toma_flujo_terciario.push_back(tomas_libres[0]);
                    tomas_libres.erase(tomas_libres.begin());
                }

                // Y ahora asigno el resto de tomas al azar (si hay)
                for (unsigned int k = 0, kSize = tomas_libres.size(); k < kSize ; k++) {
                    // Si es verdadero, el switch es de 3
                    switch (rand() % ( 2 + (nuevo_elemento == T.cruz))) {
                        case 0:
                            toma_flujo_principal.push_back(tomas_libres[0]);
                            break;
                        case 1:
                            toma_flujo_secundario.push_back(tomas_libres[0]);
                            break;
                        case 2:
                            if (nuevo_elemento == T.cruz) {
                                toma_flujo_terciario.push_back(tomas_libres[0]);
                            }
                            break;
                        default:
                            cout << "Exploto todo vieja en la funcion recursiva \n";
                    }
                    tomas_libres.erase(tomas_libres.begin());
                }
            }

            // El tema era que cuando accedia recursivamente, la funcion usaba las tomas libres
            // (la primera) y no dejaba con tomas libres a las otras que se llamaban

            /// FIN MANIPULACION

            // Flujo principal
            retorno += "(" + autocompletar_r(punto_actual, toma_flujo_principal, direccion_actual) + ")";

            retorno += "(" + autocompletar_r(punto_actual,
                                             toma_flujo_secundario,
                                             cambioDeDireccion(direccion_actual,
                                                               orientacion)) + ")";

            if (nuevo_elemento == T.cruz) {
                retorno += "(" + autocompletar_r(punto_actual,
                                                toma_flujo_terciario,
                                                cambioDeDireccion(direccion_actual,
                                                                !orientacion)) + ")";
            }

            retorno += ")";

            // Y ahora rompo el while, ya que no necesito seguir agregando
            break;
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
Recibe: Cantidad de tomas libres y la orientacion false/true
Salida: Elemento nuevo a conexionar con la tuberia
*/
string Individuo::anexarElemento(short tomas_libres, bool orientacion){

    string t;

    double
        p_bifurcacion = 0.1,   // 10%
        p_codo = 0.35,         // 15%
        p_tee = 0.5;

    if (tomas_libres > 1 && get_rand() < p_bifurcacion) {
        // Existe bifurcacion, vemos si es Tee o Cruz
        if (get_rand() < p_tee) {
            // Si es cero izquierdo, uno derecho
            if (orientacion) {
                t = T.tee_derecho;
            } else {
                t = T.tee_izquierdo;
            }
        // No agregamos cruz si no hay al menos tres tomas libres
        } else if (tomas_libres > 2) {
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
string Individuo::anexarElemento(short tomas_libres_relativas, bool orientacion){

    string t;

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
*/
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

    // Agrego mi posicion a mi vector de posiciones
    tuberias.push_back(posicion);
    direcciones.push_back(direccion);

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

/*
"MARCO COMPLETA"
Recibe: un valor 1,2,3,4
Salida: un vector (0,1) (1,0) (0, -1) (-1, 0) respectivamente
*/
string Individuo::forzar_completado(punto &base,
                                    short &direccion_actual,
                                    punto &punto_toma_libre){

    string nuevo_elemento,
           retorno;

    punto
        Z(0, 0),
        dir_toma(0,0);

    bool orientacion,
         girar = true;

    punto direccion_actual_convertida = convertirOrientacion(direccion_actual);

    base.distancia_manhattan(punto_toma_libre, dir_toma, true);

    if (direccion_actual_convertida - dir_toma == Z) {
        girar = false;
    }

    while(girar) {

        orientacion = calcularOrientacion(direccion_actual_convertida, dir_toma);

        if (orientacion) {
            nuevo_elemento = T.codo_derecho;
        } else {
            nuevo_elemento = T.codo_izquierdo;
        }

        retorno += nuevo_elemento;
        base = obtenerPuntoPosicion(base, nuevo_elemento, direccion_actual);

        direccion_actual_convertida = convertirOrientacion(direccion_actual);

        base.distancia_manhattan(punto_toma_libre, dir_toma, true);

        if (direccion_actual_convertida - dir_toma == Z) {
            girar = false;
        }

    }

    /// hasta aca anda todo bien

    if (direccion_actual == 2 || direccion_actual == 4){
        //Nos movemos en x
        retorno += forzar_completado_helper(base, direccion_actual, punto_toma_libre, dir_toma, false);
    } else {
        retorno += forzar_completado_helper(base, direccion_actual, punto_toma_libre, dir_toma, true);
    }

    ///ESTO ME PA Q NO VA
    base.distancia_manhattan(punto_toma_libre, dir_toma);
    ///FINESTO


    if (!(base - punto_toma_libre == Z)){
        cout<<"El forzar_completar no esta funcionando bien"<<endl;
        cout<<"Punto Base: "<<endl;
        base.printPunto();
        cout<<endl;
        cout<<"Punto toma: "<<endl;
        dir_toma.printPunto();

        getchar();
    }

    return retorno;

}

string Individuo::forzar_completado_helper(punto &base,
                                           short &direccion_actual,
                                           punto &punto_toma_libre,
                                           punto &dir_toma,
                                           bool trabajando_con_y) {

    string retorno,
        nuevo_elemento;

    short dist_x = (base - punto_toma_libre).coordenadas[trabajando_con_y],
          dist_y = (base - punto_toma_libre).coordenadas[!trabajando_con_y];

    while (abs(dist_x) > 1) { //dejo un lugar para poner el codo
        retorno += T.tubo_recto;

       // getchar();
        base = obtenerPuntoPosicion(base, T.tubo_recto, direccion_actual);
        dist_x = (base - punto_toma_libre).coordenadas[trabajando_con_y];
    }
    ///NO TOCAR ESE FALSE!!!
    base.distancia_manhattan(punto_toma_libre, dir_toma, false);

    bool orientacion = calcularOrientacion(convertirOrientacion(direccion_actual),
                                      dir_toma);
    //Ponemos un codo solo si la distancia y es mayor que cero
    if (dist_y != 0) {
        if (orientacion) {
            nuevo_elemento = T.codo_derecho;
        } else {
            nuevo_elemento = T.codo_izquierdo;
        }
    } else {
        nuevo_elemento = T.tubo_recto;
    }

    retorno += nuevo_elemento;

    base = obtenerPuntoPosicion(base, nuevo_elemento, direccion_actual);
    dist_y = (base - punto_toma_libre).coordenadas[!trabajando_con_y];

    dist_x = (base - punto_toma_libre).coordenadas[trabajando_con_y];

    if(dist_x != 0){cout<< "Problema en forzar_completado (X) linea 556 o por ahi"<<endl;}
    //Nos movemos en y
     while(dist_y != 0){
        retorno += T.tubo_recto;
        base = obtenerPuntoPosicion(base, T.tubo_recto, direccion_actual);
        dist_y = (base - punto_toma_libre).coordenadas[!trabajando_con_y];
    }
    return retorno;

}

/*
"Le paso un indice, y me devuelve el cromosoma spliceado desde ese indice hasta
la subrama mas proxima. Ejemplo: [2 a a (l (a a)(a d a)], indx = "2" (en % realmente)
=> salida:[a a]"
Recibe: un valor entre 0 y 1
Salida: cromosoma spliceado, el cromosoma borrado, y el vector de puntos q pertenece a ese cromosoma
*/

string Individuo::get_spliced_cromosoma(double idx_percentage, string &cromosoma_borrado, vector<punto> &puntos_borrados) {

    unsigned int idx = (idx_percentage * cromosoma.size());

    cout << "Posicion en cromosoma: " << idx << endl;

    string
        cromosoma_base = this->cromosoma.substr(idx),
        cromosoma_spliceado = get_spliced_cromosoma_r(cromosoma_base);

    unsigned int pos_borrado = cromosoma.find(cromosoma_spliceado, idx);

    cout << "Viejo cromosoma:\n" << cromosoma << endl;

    string cromosoma_borrado_aux(cromosoma.begin() + pos_borrado,
                                 cromosoma.begin() + pos_borrado + cromosoma_spliceado.size());

    cromosoma_borrado = cromosoma_borrado_aux;

    /// Para pasar los puntos borrados
    unsigned int fin_idx = pos_borrado;
    for (unsigned int k = pos_borrado; k < pos_borrado + cromosoma_spliceado.size(); k++) {
        string cro;
        cro = cromosoma[k];
        if (cro != "(" && cro != ")") {
            fin_idx ++;
        }
    }

    vector<punto> puntos_reemplazados(tuberias.begin() + pos_borrado, tuberias.begin() + fin_idx);

    for (unsigned int j = 0; j < puntos_reemplazados.size(); j++) {
        cout << "Reemplazado: "; puntos_reemplazados[j].printPunto();
    }

    puntos_borrados = puntos_reemplazados;

    /// Fin

    cout << "Cromosoma borrado: " << cromosoma_borrado_aux << endl;

    cromosoma.replace(pos_borrado, cromosoma_spliceado.size(), T.separador);

    cout << "\nNuevo cromosoma:\n" << cromosoma << endl;

    cout << "-------------------------" << endl;

    return cromosoma_spliceado;

}

string Individuo::get_spliced_cromosoma_r(string cromosoma_base) {

    string retorno = cromosoma_base;

    // Si caigo en un parentesis cerrado, me voy al proximo caso
    if (cromosoma_base[0] == ')') {
        retorno = get_spliced_cromosoma_r(cromosoma_base.substr(1));
    } else {
        for (unsigned int k = 0, N = cromosoma_base.size() ; k < N ; k++) {

            // Avanzo hasta encontrar un ), si encuentro un ( recursion time
            if (cromosoma_base[k] == '(') {
                retorno = get_spliced_cromosoma_r(cromosoma_base.substr(k + 1));
                break;
            } else if (cromosoma_base[k] == ')') {
                retorno = cromosoma_base.substr(0, k);
                break;
            }
        }
    }

    return retorno;
}
/*
"Coloca el contenido genetico del nuevo cromosoma en el interior
del cromosoma base, donde tenga un separador"
Recibe: un nuevo cromosoma a insertar
Salida: el cromosoma modificado con el nuevo cromosoma
*/

string Individuo::intercambiarCromosoma(string nuevo_cromosoma) {

    unsigned int pos_separador = cromosoma.find(T.separador);

    if (pos_separador >= 0) {
        cromosoma.erase(pos_separador, 1);
        cromosoma.insert(pos_separador, nuevo_cromosoma);
    } else {
        cout << "Error en el intercambiarCromosoma, no hay separador\n";
        getchar();
    }

    return cromosoma;

}
/*
"Dado un indice del cromosoma, me devuelve la posicion y la direccion de este"
Recibe: un indice del 0 al tamanio del cromosoma y si queres un pre-idx (por default 0) para
las tuberias libres (desde donde empezar a tomarlas)
Salida: la posicion y direccion en esa posicion del eleemnto, y las tomas libres hasta ese punto
*/
vector<punto> Individuo::getPosDirByIndex(unsigned int idx,
                                          punto &pos,
                                          short &direccion,
                                          unsigned int pre_idx) {

    unsigned int real_idx = idx;

    // Voy recorriendo el indice, si encuentro algun ( lo resto
    for (unsigned int i = 0; i <= idx; i++) {
        if (cromosoma[i] == '(' || cromosoma[i] == ')') {
            real_idx--;
        }
    }

    // Obtengo las tomas libres
    vector<punto> tomas_libres_cubiertas;
    cout << cromosoma << endl;
    // Evita que me vaya. Revisar
    if (real_idx >= tuberias.size()) {
        real_idx = tuberias.size() - 1;
    }

    for (unsigned int k = pre_idx ; k <= real_idx ; k++) {
        for (unsigned int j = 0; j < tomas.size(); j++) {
            cout << "Tuberias analizadas: "; tuberias[k].printPunto();

            if (tuberias[k] == tomas[j]) { // Encontro tuberia
                tomas_libres_cubiertas.push_back(tomas[j]);
                cout << "Tuberia cubierta!"; tomas[j].printPunto();
            }
        }
    }

    pos = tuberias[real_idx];
    direccion = direcciones[real_idx];

    return tomas_libres_cubiertas;
}

/*
"Recibe un nuevo cromosoma, a partir de este y una posicion,
fuerza el completado"
Recibe: un nuevo cromosoma a insertar
Salida: el cromosoma base modificado
*/

string Individuo::forzarCromosoma(string cromosoma_base,
                                  string cromosoma_reemplazado,
                                  vector<punto> tuberias_reemplazadas,
                                  string nuevo_cromosoma) {

    cout << "\n\n----------------------------------------------------------\n\n";

    // Devuelve la posicion de insercion
    unsigned int pos_separador = cromosoma_base.find(T.separador);

    punto punto_actual;
    short direccion_actual;
    vector<punto> nuevas_tuberias;

    cout << "Pos separador: " << pos_separador << endl;
    cout << "Cromosoma_reemplazado tamanio: " << cromosoma_reemplazado.size() << endl;

    /// Anexo a mi vector de tuberias, mis tuberias que vinieron con el cromosoma reemplazado
    nuevas_tuberias.insert(nuevas_tuberias.end(), tuberias_reemplazadas.begin(), tuberias_reemplazadas.end());

    vector<punto> tomas_liberadas = getPosDirByIndex(pos_separador + cromosoma_reemplazado.size(),
                                                     punto_actual,
                                                     direccion_actual,
                                                     pos_separador);


    for (unsigned int j = 0; j < tomas_liberadas.size(); j++) {
        cout << "toma: "; tomas_liberadas[j].printPunto();
    }

    // Voy recorriendo con el nuevo cromosoma, y elimino tomas si ya pase por ahi
    for (unsigned int k = 0 ; k < nuevo_cromosoma.size(); k++) {
        string nuevo_elemento;
        nuevo_elemento = nuevo_cromosoma[k];

        punto_actual = obtenerPuntoPosicion(punto_actual, nuevo_elemento, direccion_actual);

        // Agregado nuevo punto
        nuevas_tuberias.push_back(punto_actual);

        for (unsigned int j = 0; j < tomas_liberadas.size(); j++) {
            if (punto_actual == tomas_liberadas[j]) {
                tomas_liberadas.erase(tomas_liberadas.begin() + j);
            }
        }
    }

    /// TRABAJAMOS CON LA AUTOCOMPLETACION
    // Le anexo la autocompletacion
    short
        cant_tuberias_antes_de_autocompletar = tuberias.size();

    nuevo_cromosoma += autocompletar_r(punto_actual, tomas_liberadas, direccion_actual);

    vector<punto> puntos_nuevos_dps_de_autocompletar(tuberias.begin() + cant_tuberias_antes_de_autocompletar,
                                                     tuberias.end());

    vector<short> direcciones_nuevas_dps_autocompletar(direcciones.begin() + cant_tuberias_antes_de_autocompletar,
                                                       direcciones.end());

    nuevas_tuberias.insert(nuevas_tuberias.end(),
                           puntos_nuevos_dps_de_autocompletar.begin(),
                           puntos_nuevos_dps_de_autocompletar.end());

    if (pos_separador >= 0) {
        cromosoma.erase(pos_separador, 1);
        cromosoma.insert(pos_separador, nuevo_cromosoma);
    } else {
        cout << "Error en el intercambiarCromosoma, no hay separador\n";
        getchar();
    }

    return cromosoma;

}
/*
"Evalua el fitness de un individuo, en base a los bloques, al costo de las tuberias
y el largo de ella"
Recibe: la matriz de bloques
Salida: el valor de fitness
*/
double Individuo::evaluarFitness(vector<vector<double> > &Field) {

    // Voy recorriendo cada posicion que ocupa mi tuberia
    /// CONVOCO ACA LA MEGA FUNCION DE MARCOS QUE OBTIENE PUNTOS
    /// megaFuncionObtenedora de puntos
    vector<punto> puntosObtenidos = tuberias;


    double
        fitness = 0,    // Mi valor de fitness
        fitness_bloqueado = 500;    // Esto es que tan caro hago el pasar sobre un bloque

    // Voy a suponer que todos mis puntos obtenidos son enteros
    int x, y,
        cant_rows = Field.size(),
        cant_cols = (Field[0]).size(); // Notese la diferencia

    cout << "Tenemos un Field de [" << cant_rows << " x " << cant_cols << "]\n";

    for (unsigned int k = 0, kCant = puntosObtenidos.size() ; k < kCant ; k++) {
        // Obtengo la coordenada de una tuberia
        x = (int) puntosObtenidos[k].coordenadas[0] + cant_cols / 2;
        y = (int) puntosObtenidos[k].coordenadas[1] + cant_rows / 2;

        cout << x << " # " << y <<  " (bloqueado? " << Field[x][y] << ")" << endl;

        if (x < 0  || y < 0) {
            cout << "Error, la matriz no alcanza a cubrir todos los puntos\n";
            getchar();
        }

        // Hay un bloque coincidiendo? Yo lo sumo total
        fitness += Field[x][y] * fitness_bloqueado;
    }

    // Ademas voy viendo en mi cromosoma que costo tiene cada pieza
    fitness += evaluarFitness_helper();

    return fitness;
}

/*
"La onda es que te da, en base al cromosoma, el costo total de este"
Recibe: el cromosoma
Salida: el valor de las componentes del cromosoma
*/
double Individuo::evaluarFitness_helper() {

    // Creo un cromosoma sin punto de origen
    string cromosoma_libre(cromosoma.begin() + 1, cromosoma.end());

    cout << "\nCromosoma libre: " << cromosoma_libre << endl;

    /// Precios:

    double
        precio_total = 0,
        precio_base = 1;        // Esto es una medida para ajustar cuanto pesa el precio

    // Voy a tomar tubos de 1''. Por lo que las medidas (segun planos)
    // de cada cuadrado son 0.118 x 0.118 m

    for (unsigned int k = 0, kCant = cromosoma_libre.size(); k < kCant ; k++) {
        string cro_k;
        cro_k = cromosoma_libre[k];

        // Si encuentro un separador, salto al proximo for
        if (cro_k == "(" || cro_k == ")") {
            continue;
        }

        /// Por cada tuberia, cuento el precio

        // Tubo simple de 1 metro sale 120$, entonces uno de 0.118m saldria
        // 120 * 0.118 = 14$
        if (cro_k == T.tubo_recto) {
            precio_total += precio_base * 14;

        //  Codo 90º (89$).
        } else if (cro_k == T.codo_izquierdo || cro_k == T.codo_derecho) {
            precio_total += precio_base * 89;

        //  Tee (120$).
        } else if (cro_k == T.tee_izquierdo || cro_k == T.tee_derecho) {
            precio_total += precio_base * 120;

        //  Cruz galvanizada (300$).
        } else if (cro_k == T.cruz) {
            precio_total += precio_base * 300;

        // Sino se da ninguna, es porque hubo un error
        } else {
            cout << "\nHubo un error en evaluarFitness_helper (precios)";
            getchar();
        }

        cout << "Pieza: " << cro_k <<" (precio $" << precio_total << ")"<<  endl;
    }

    return precio_total;

}

/*
"Recorro las posiciones actuales, pero retorno estas en forma de puntos double"
Salida: el vector de vectores de doubles de la posicion
*/
vector<vector<double> > Individuo::get_puntos_double() {

    vector<vector<double> > retorno;
    vector<double> aux;

    for (unsigned int k = 0, kCant = tuberias.size(); k < kCant; k++ ) {
        aux.push_back(tuberias[k].coordenadas[0]);
        aux.push_back(tuberias[k].coordenadas[1]);

        retorno.push_back(aux);
        aux.clear();
    }

    return retorno;
}
