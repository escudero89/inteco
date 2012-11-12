#include <sstream>

#include "../include/individuo.h"

Individuo::Individuo(punto origen,
                      vector<punto> &tomas,
                       string cromosoma,
                        bool completar) {

    this->cromosoma = cromosoma;
    this->origen = origen;
    this->tomas = this-> tomas_sin_cubrir = tomas; // Al iniciar, no hay tomas libres

    esta_siendo_mutado = false;

    T.tubo_recto = "a";
    T.codo_izquierdo = "i";
    T.codo_derecho = "d";
    T.tee_izquierdo = "l";
    T.tee_derecho = "r";
    T.cruz = "x";

    T.separador = "E";
    T.abre_parentesis = "(";
    T.cierra_parentesis = ")";

    p_bifurcacion = get_rand() * .5;      // maxima 50%
    p_codo = get_rand() * .35 + 0.01;     // maxima 35%, minima 1%
    p_tee = get_rand() * .5;              // maxima 50%
    p_orientacion = get_rand() * 0.05;    // maxima 5%

    if(completar) {
        autocompletar();
    }
}

/*
"Genera un individuo al azar"
Recibe:
Salida:
*/

void Individuo::autocompletar() {

    short direccion_actual = rand() % 4 + 1;

    // Crear una direccion base al azar para q me de 1..4
    stringstream ss;
    ss << direccion_actual;
    cromosoma += ss.str();

    // Agrego la direccion a mi vector de direcciones
    // direcciones.push_back(direccion_actual);

    cromosoma += autocompletar_r(this->origen, tomas_sin_cubrir, direccion_actual);

    cout << "\n Se ha encontrado camino con " << cromosoma.size() << " tuberias.\n";

    /// Actualizo mi vector de tuberias
    // @TODO vector de direcciones
    this->tuberias = get_puntos();
}


string Individuo::autocompletar_r(punto punto_actual, vector<punto> &tomas_asignadas, short direccion){

    punto punto_toma_libre;

    short
        menor_dist,
        idx_menor_distancia,
        direccion_actual = direccion,
        radio_absorcion = (esta_siendo_mutado) ? rand()%10 : rand()%5;

    bool orientacion;

    string
        retorno,
        nuevo_elemento;

    cout << "\nPartiendo de origen: "; punto_actual.printPunto();
    cout << "Con direccion: " << direccion << endl;

    while(tomas_asignadas.size()){

        idx_menor_distancia = punto_actual.menor_distancia(tomas_asignadas,
                                                           menor_dist,
                                                           punto_toma_libre);

        orientacion = calcularOrientacion(convertirOrientacion(direccion_actual),
                                          punto_toma_libre);

        nuevo_elemento = anexarElemento(tomas_asignadas.size(), orientacion);

        if (es_bifurcacion(nuevo_elemento) == 0) {

            if (menor_dist < radio_absorcion){
                string retorno_forzar_completado;
                cout << "Toma destino en forzar: "; tomas_asignadas[idx_menor_distancia].printPunto();
                retorno_forzar_completado = forzar_completado(punto_actual,
                                                              direccion_actual,
                                                              tomas_asignadas[idx_menor_distancia]);

                cout << "Nuevas tuberias de forzar_completado: " << retorno_forzar_completado << endl;
                retorno += retorno_forzar_completado;

                tomas_asignadas.erase(tomas_asignadas.begin() + idx_menor_distancia);
                cout << "Alcanzado! -----------------------------------\n";

            } else {
                retorno += nuevo_elemento;

                stringstream ss;
                ss << retorno;
                punto_actual = obtenerPuntoPosicion(punto_actual, nuevo_elemento, direccion_actual);

                cout << nuevo_elemento << " (dir: " << direccion_actual << ")"; punto_actual.printPunto();

                for (unsigned int kTomas = 0 ; kTomas < tomas_asignadas.size(); kTomas++) {
                    if (punto_actual == tomas_asignadas[kTomas]) {
                        tomas_asignadas.erase(tomas_asignadas.begin() + kTomas);
                        cout << "Alcanzado! -------------------------------\n";
                    }
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

            toma_flujo_principal.push_back(tomas_asignadas[idx_menor_distancia]);

            // Borro la ya "asignada"
            tomas_asignadas.erase(tomas_asignadas.begin() + idx_menor_distancia);

            // Asigno ya el flujo secundario, y si hay, el terciario
            toma_flujo_secundario.push_back(tomas_asignadas[0]);
            tomas_asignadas.erase(tomas_asignadas.begin());

            if (tomas_asignadas.size()) {
                if (nuevo_elemento == T.cruz) {
                    toma_flujo_terciario.push_back(tomas_asignadas[0]);
                    tomas_asignadas.erase(tomas_asignadas.begin());
                }

                // Y ahora asigno el resto de tomas al azar (si hay)
                for (unsigned int k = 0, kSize = tomas_asignadas.size(); k < kSize ; k++) {
                    // Si es verdadero, el switch es de 3
                    switch (rand() % ( 2 + (nuevo_elemento == T.cruz))) {
                        case 0:
                            toma_flujo_principal.push_back(tomas_asignadas[0]);
                            break;
                        case 1:
                            toma_flujo_secundario.push_back(tomas_asignadas[0]);
                            break;
                        case 2:
                            if (nuevo_elemento == T.cruz) {
                                toma_flujo_terciario.push_back(tomas_asignadas[0]);
                            }
                            break;
                        default:
                            cout << "Exploto todo vieja en la funcion recursiva \n";
                    }
                    tomas_asignadas.erase(tomas_asignadas.begin());
                }
            }

            // El tema era que cuando accedia recursivamente, la funcion usaba las tomas libres
            // (la primera) y no dejaba con tomas libres a las otras que se llamaban

            /// FIN MANIPULACION

            // Flujo principal
            retorno += "(" + autocompletar_r(punto_actual, toma_flujo_principal, direccion_actual) + ")";

            if (nuevo_elemento == T.cruz) {
                retorno += "(" + autocompletar_r(punto_actual,
                                                 toma_flujo_secundario,
                                                 cambioDeDireccion(direccion_actual, 0)) + ")";

                retorno += "(" + autocompletar_r(punto_actual,
                                                toma_flujo_terciario,
                                                cambioDeDireccion(direccion_actual, 1)) + ")";
            } else { // Es una tee?
                retorno += "(" + autocompletar_r(punto_actual,
                                                toma_flujo_secundario,
                                                cambioDeDireccion(direccion_actual,
                                                orientacion)) + ")";
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

unsigned int Individuo::es_parentesis(string elemento){
    unsigned int retorno = 0;

    if(elemento == T.abre_parentesis) {
        retorno = 1;
    }else if(elemento == T.cierra_parentesis){
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

    orientacion = (get_rand() < p_orientacion) ? !orientacion : orientacion;

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
    //direcciones.push_back(direccion);

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
            cout << "Direccion recibida: " << direccion << endl;

            cout << "\nCromosoma: " << cromosoma << endl;
            cout << "Tam tuberias y  direcciones: " << tuberias.size() << ", " << direcciones.size() << endl;
            cout << "Vector de direcciones: "; printVector<short>(direcciones);

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
"Fuerza a un cromosoma a llegar a un toma especificado"
Recibe: un punto origen, una direccion actual y el punto donde esta el toma
Salida: devuelve un string con el cromosoma modificado que llega al toma
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


        cout << "Nuevo elemento [" << nuevo_elemento << "], direccion: "
             << direccion_actual << " posicion: "; base.printPunto();

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

string Individuo::get_spliced_cromosoma(double idx_percentage, vector<punto> &puntos_borrados) {

    unsigned int
        idx = (idx_percentage * cromosoma.size()),
        pos_corte = 0;

    // Si es la primera posicion
    if (idx == 0) {
        idx++;

    // O la ultima
    } else if (idx == cromosoma.size()) {
        idx--;
    }


    // Evito trabajar en un parentesis
    while (cromosoma[idx] == '(' || cromosoma[idx] == ')') {
        if (cromosoma[idx] == '(') {
            idx++;
        } else if (cromosoma[idx] == ')') {
            idx--;
        }
    }

    // Si caigo en una l, r o cruz, me muevo un lugar hacia atras
    string cro_c; cro_c = cromosoma[idx];
    if ( es_bifurcacion(cro_c) ) {
        idx--;
    }

    string
        cromosoma_base = this->cromosoma.substr(idx),
        cromosoma_spliceado = get_spliced_cromosoma_r(cromosoma_base, pos_corte),
        cromosoma_spliceado_sin_parentesis = cromosoma_spliceado;

    cout << "Indice inicial: "<< idx<< endl;
    idx += pos_corte;
    cout << "Indice mas posicion de corte: "<< idx << endl;
    cout << "Tamanio tuberia inicial: " << tuberias.size() << endl;

    cout << "Normal: " <<cromosoma <<endl;
    cout << "Base: " <<cromosoma_base <<endl;
    cout << "Spliced: " <<cromosoma_spliceado <<endl;

    cromosoma.erase(idx, cromosoma_spliceado.size());

    cout << "Cromosoma borrado: " << cromosoma << endl;

    cromosoma.insert(idx, "E");

    // Guardo la posicion de E
    this->insercion = idx;

    cout << "Cromosoma con E:" << cromosoma << endl;

    /// Reviso las tuberias

    unsigned int idx_sin_parentesis = idx,
        hasta_sin;

    for (unsigned int k = 0; k <= idx; k++) {
        if (cromosoma[k] == '(' || cromosoma[k] == ')') {
            idx_sin_parentesis--;
        }
    }
    cout << "Cromosoma spliceado sin parentesis: " << cromosoma_spliceado_sin_parentesis << endl;
    /// Voy a obtener un cromosoma sin parentesis
    for (unsigned int k = 0; k < cromosoma_spliceado_sin_parentesis.size(); k++) {
        if (cromosoma_spliceado_sin_parentesis[k] == '(' ||
            cromosoma_spliceado_sin_parentesis[k] == ')') {
            cromosoma_spliceado_sin_parentesis.erase(k, 1);
            k = 0;
            cout << "Cr splic: " << cromosoma_spliceado_sin_parentesis << endl;
        }
    }
    cout << "Cromosoma spliceado sin parentesis: " << cromosoma_spliceado_sin_parentesis << endl;
    cout << "END" << endl;
    cout << endl;

    hasta_sin = idx_sin_parentesis + cromosoma_spliceado_sin_parentesis.size();

    cout << "idx_sin_parentesis: " << idx_sin_parentesis << endl;
    cout << "hasta_sin: " << hasta_sin << endl;
    cout << "tuberias size: " << tuberias.size() << endl;


    vector<punto> puntos_reemplazados(tuberias.begin() + idx_sin_parentesis,
                                      tuberias.begin() + hasta_sin);

    puntos_borrados = puntos_reemplazados;
cout << "Saliendo de get_spliced" << endl;
cout << endl;
    /// Fin

    return cromosoma_spliceado;

}

string Individuo::get_spliced_cromosoma_r(string cromosoma_base, unsigned int &pos_corte) {

    string retorno = cromosoma_base;
    cout << "\nget_spliced_cromosoma_r: " << cromosoma_base << endl;

#if 1
    int parentesis_abiertos = 0;
    // Si caigo en un parentesis cerrado, me voy al proximo caso
    if (cromosoma_base[0] == ')') {
        pos_corte++;
        retorno = get_spliced_cromosoma_r(cromosoma_base.substr(1), pos_corte);
    } else {
        for (unsigned int k = 0, N = cromosoma_base.size() ; k < N ; k++) {

            if (cromosoma_base[k] == '(') {
                parentesis_abiertos++;
            } else if (cromosoma_base[k] == ')') {
                parentesis_abiertos--;
                if (parentesis_abiertos < 0) {
                    retorno = cromosoma_base.substr(0, k);
                    break;
                }
            }

        }
    }

/*
    // Si caigo en un parentesis cerrado, me voy al proximo caso
    if (cromosoma_base[0] == ')') {
        pos_corte++;
        retorno = get_spliced_cromosoma_r(cromosoma_base.substr(1), pos_corte);
    } else {
        for (unsigned int k = 0, N = cromosoma_base.size() ; k < N ; k++) {
            // Si encuentro un (, corto
            if (cromosoma_base[k] == '(') {
                retorno = cromosoma_base.substr(0, k - 1);
                break;
            } else if (cromosoma_base[k] == ')') {
                retorno = cromosoma_base.substr(0, k);
                break;
            }

        }
    }
*/
    cout << "get_spliced_cromosoma_r salida: " << retorno << endl;

#endif
#if 0
    // Si caigo en un parentesis cerrado, me voy al proximo caso
    if (cromosoma_base[0] == ')') {
        pos_corte++;
        retorno = get_spliced_cromosoma_r(cromosoma_base.substr(1), pos_corte);
    } else {
        for (unsigned int k = 0, N = cromosoma_base.size() ; k < N ; k++) {
            // Avanzo hasta encontrar un ), si encuentro un ( recursion time
            if (cromosoma_base[k] == '(') {
                pos_corte += k + 1;
                retorno = get_spliced_cromosoma_r(cromosoma_base.substr(k + 1), pos_corte);
                break;
            } else if (cromosoma_base[k] == ')') {
                retorno = cromosoma_base.substr(0, k);
                break;
            }
        }
    }
#endif
    return retorno;
}
/*
"Coloca el contenido genetico del nuevo cromosoma en el interior
del cromosoma base, donde tenga un separador"
Recibe: un nuevo cromosoma a insertar
Salida: el cromosoma modificado con el nuevo cromosoma
*/

string Individuo::intercambiarCromosoma(string nuevo_cromosoma) {

    unsigned int pos_separador = this->cromosoma.find(T.separador);

    if (pos_separador >= 0) {
        this->cromosoma.erase(pos_separador, 1);
        this->cromosoma.insert(pos_separador, nuevo_cromosoma);
    } else {
        cout << "Error en el intercambiarCromosoma, no hay separador\n";
        getchar();
    }

    return this->cromosoma;

}
/*
"Dado un indice del cromosoma, me devuelve la posicion y la direccion de este"
Recibe: un indice del 0 al tamanio del cromosoma y si queres un pre-idx (por default 0) para
las tuberias libres (desde donde empezar a tomarlas)
Salida: la posicion y direccion en esa posicion del eleemnto, y las tomas libres hasta ese punto
*/
void Individuo::getPosDirByIndex(unsigned int idx,
                                  punto &pos_actual,
                                  short &direccion,
                                  unsigned int pre_idx) {

    unsigned int real_idx = idx;

    cout << "\nIniciando getPosDirByIndex..." << endl;
    cout << "Cromosoma: " << cromosoma << endl;

    cout << "Idx: " << idx << " | tubsize: " << tuberias.size() << endl;
    // Voy recorriendo el indice, si encuentro algun ( lo resto
    for (unsigned int i = 0; i <= idx; i++) {
        if (cromosoma[i] == '(' || cromosoma[i] == ')') {
            real_idx--;
        }
    }

    cout << "Idx: " << idx << "\t| Real idx: "<< real_idx << " | " << tuberias.size() << endl;

    pos_actual = tuberias[real_idx];
    direccion = direcciones[real_idx];
}

/*
"Recibe un nuevo cromosoma, a partir de este y una posicion,
fuerza el completado"
Recibe: cromosoma base (this->cromosoma), cromosoma_reemplazado (lo que quitamos)
Salida: el cromosoma base modificado
*/

void Individuo::forzarCromosoma(string &cromosoma_base,
                                  unsigned int tam_cromosoma_reemplazado,
                                  vector<punto> tuberias_reemplazadas) {

    cout << "\n\n----------------------------------------------------------\n";
    cout << " INICIANDO FORZAR CROMOSOMA \n\n";

    // Devuelve la posicion de insercion
    unsigned int
        pos_separador = this->insercion,
        pos_con_reemplazo = pos_separador + tam_cromosoma_reemplazado - 1;

    punto punto_actual;
    short direccion_actual;
    vector<punto> nuevas_tuberias;

    cout << "Posicion separador: " << pos_separador << endl;
    cout << "Posicion con reemplazo: " << pos_con_reemplazo << endl;

    // El -1 es porque contaba la posicion de E
    getPosDirByIndex(pos_con_reemplazo,
                     punto_actual,
                     direccion_actual,
                     pos_separador);

    cout << "Posicion separador: " << pos_con_reemplazo << endl;
    cout << "Punto actual: "; punto_actual.printPunto();
    cout << "Direccion actual: " << direccion_actual << endl;
    cout << "____________________\n";
    cout << "Tomas destino:\n";
    for (unsigned int k = 0; k < tomas_sin_cubrir.size(); k++) {
        cout << "[" << k << "] ";
        tomas_sin_cubrir[k].printPunto();
    }
    cout << "____________________\n";
    cout << "Punto Origen: "; punto_actual.printPunto();
    cout << "Direccion Origen: " << direccion_actual << endl;
    cout << "Tomas cant liberadas? " << tomas_sin_cubrir.size() << endl;

    // Si me quedaron sin cubrir
    if (tomas_sin_cubrir.size()) {
        cout << "\n\nAUTOCOMPLETANDO...\n\n";
        /// TRABAJAMOS CON LA AUTOCOMPLETACION
        // Le anexo la autocompletacion
        string autocompletado;
        autocompletado = autocompletar_r(punto_actual, tomas_sin_cubrir, direccion_actual);

        cout << "Cromosoma sin autocompletado: " << cromosoma << endl;
        cout << "Autocompletado: " << autocompletado << endl;

        // El +1 es porque ya no esta la "E"

        unsigned int posicion_nueva = pos_con_reemplazo + 1;
        cout << "Tamanio cromosoma: " << cromosoma.size() << endl;
        cout << "Posicion de reemplazo: " << posicion_nueva << endl;

        // Quiero evitar que agregue en cualquier lado
        while (cromosoma[posicion_nueva] == ')' || posicion_nueva == cromosoma.size()) {
            posicion_nueva--;
        }

        cout << "Valor en reemplazo nueva: " << cromosoma[posicion_nueva] << endl;
        cout << "Posicion de reemplazo nueva: " << posicion_nueva << endl;

        cromosoma.insert(posicion_nueva + 1, autocompletado);

        cout << "Cromosoma con autocompletado: " << cromosoma << endl;

        /// FIN AUTOCOMPLETAR
    }

    cout << "\nACTUALIZANDO INDIVIDUO (Fase 2)\n";
    cout << cromosoma << endl;
    cout << endl;
    actualizarIndividuo();
    cout << "Actualizado con exito!\n\n";

    cout << "Cromsoma luego de forzarlo:  " << cromosoma;

}
/*
"Evalua el fitness de un individuo, en base a los bloques, al costo de las tuberias
y el largo de ella"
Recibe: la matriz de bloques
Salida: el valor de fitness
*/
double Individuo::evaluarFitness(vector<vector<double> > &Field) {

    // Voy recorriendo cada posicion que ocupa mi tuberia
    vector<punto> puntosObtenidos = tuberias;


    double
        fitness = 0,    // Mi valor de fitness
        fitness_bloqueado = 10000;    // Esto es que tan caro hago el pasar sobre un bloque

    // Voy a suponer que todos mis puntos obtenidos son enteros
    int x, y,
        cant_rows = Field.size(),
        cant_cols = (Field[0]).size(); // Notese la diferencia

//    cout << "Tenemos un Field de [" << cant_rows << " x " << cant_cols << "]\n";

    for (unsigned int k = 0, kCant = puntosObtenidos.size() ; k < kCant ; k++) {
        // Obtengo la coordenada de una tuberia
        x = puntosObtenidos[k].coordenadas[0];
        y = cant_rows - puntosObtenidos[k].coordenadas[1] - 1;

        if (x < 0  || y < 0 || x >= cant_cols || y >= cant_rows) {
            //cout << "Error, la matriz no alcanza a cubrir todos los puntos\n";
            //getchar();
            /// Si me salgo del area, penalizo al fitness
            // fitness += 1000;
        } else {
            // Hay un bloque coincidiendo? Yo lo sumo total
            fitness += Field[y][x] * fitness_bloqueado;
        }
    }

    // Ademas voy viendo en mi cromosoma que costo tiene cada pieza
    fitness += evaluarFitness_helper();

    /// Otra cosa extra, y es que si no cubre todas las tuberias, lo penalizo copado
    unsigned int tomas_libres = actualizarTomasLibres();

    // Y se lo agrego al fitness con mucha penalizacion
    fitness += 100000 * tomas_libres;

    cout << "Tomas libres en fitness: " <<  tomas_libres << endl;
    if (tomas_libres) {
        cout << cromosoma << endl;
     //   getchar();
    }

    // Y le sumo la longitud del cromosoma al cuadrado por x
    // fitness += tuberias.size() * tuberias.size() * 10;

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

    //cout << "\nCromosoma libre: " << cromosoma_libre << endl;

    /// Precios:

    double
        precio_total = 0,
        precio_base = 0.1;        // Esto es una medida para ajustar cuanto pesa el precio

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
            cout << "\nHubo un error en evaluarFitness_helper (precios)" << endl;
            cout << "Parte del error: [" << cro_k << "]." << endl;
            cout << "Cromosoma del error:\n" << cromosoma;
            getchar();
        }

      //  cout << "Pieza: " << cro_k <<" (precio $" << precio_total << ")"<<  endl;
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


/*
"Mapea un cromosoma a los puntos de la matriz correspondiente"
Salida: vector con los puntos ocupados por la tuberia
*/
vector<punto> Individuo::get_puntos() {

    // Borramos lo que estaba antes
    this->tuberias.clear();
    this->direcciones.clear();

    vector<short> nuevas_direcciones,
                    nuevas_dir_0,
                    nuevas_dir_1,
                    nuevas_dir_2;

    string cromo = this->cromosoma,
        tipo_tubo;

    vector<punto> VP, VP_r1, VP_r2, VP_r3;

    bool orientacion;

    //char ca = cromo[0];
    string ca; ca = cromo[0];
    short direccion_actual = atoi(ca.c_str());
    cromo = cromo.substr(1);

    nuevas_direcciones.push_back(direccion_actual);

    punto base = this->origen;

    while(cromo.size()){

        if(es_parentesis(tipo_tubo) == 0){
            tipo_tubo = cromo[0];
            cromo = cromo.substr(1);

            //Actualizo punto base y direccion (si viene un codo)
            base = obtenerPuntoPosicion(base, tipo_tubo, direccion_actual);
            nuevas_direcciones.push_back(direccion_actual);

            VP.push_back(base);
        }
        else{
            //Vino un parentesis
            break;
        }

    }

    if(es_parentesis(tipo_tubo) == 1){
        //Actualizo el tipo tubo
        tipo_tubo = cromo[0];

        // si viene un parentesis, lo saco
        cromo = cromo.substr(1);

        //Tambien saco el ultimo parentesis
        cromo.erase(cromo.size() - 1, 1);


    }


    if(es_bifurcacion(tipo_tubo)){

        //base = obtenerPuntoPosicion(base, T.tubo_recto, direccion_actual);

        vector<string> biff = obtener_bifurcaciones(tipo_tubo + cromo);

        VP_r1 = get_puntos_r(base, direccion_actual, biff[0], nuevas_dir_0);

        nuevas_direcciones.insert(nuevas_direcciones.end(),
                                  nuevas_dir_0.begin(), nuevas_dir_0.end());

        VP.insert(VP.end(), VP_r1.begin(), VP_r1.end());

        if(es_bifurcacion(tipo_tubo) == 1){

            if(tipo_tubo == T.tee_izquierdo){
                orientacion = false;
            } else {
                orientacion = true;
            }

            //Obtengo nueva direccion para flujo secundario
            short direccion_flujo_secundario = cambioDeDireccion(direccion_actual, orientacion);

            VP_r2 = get_puntos_r(base, direccion_flujo_secundario, biff[1], nuevas_dir_1);

             nuevas_direcciones.insert(nuevas_direcciones.end(),
                                  nuevas_dir_1.begin(), nuevas_dir_1.end());

            VP.insert(VP.end(), VP_r2.begin(), VP_r2.end());

        }else{

            short direccion_flujo_secundario = cambioDeDireccion(direccion_actual, 0);
            short direccion_flujo_terciario = cambioDeDireccion(direccion_actual, 1);

            VP_r2 = get_puntos_r(base, direccion_flujo_secundario, biff[1], nuevas_dir_1);
            VP_r3 = get_puntos_r(base, direccion_flujo_terciario, biff[2], nuevas_dir_2);

             nuevas_direcciones.insert(nuevas_direcciones.end(),
                                  nuevas_dir_1.begin(), nuevas_dir_1.end());

            nuevas_direcciones.insert(nuevas_direcciones.end(),
                                  nuevas_dir_2.begin(), nuevas_dir_2.end());


            VP.insert(VP.end(), VP_r2.begin(), VP_r2.end());
            VP.insert(VP.end(), VP_r3.begin(), VP_r3.end());

        }

    }

    // Inserto el origen
    VP.insert(VP.begin(), origen);

    this->tuberias = VP;
    this->direcciones = nuevas_direcciones;
    return VP;

}

/*
Version recursiva de la funcion anterior
*/
vector<punto> Individuo::get_puntos_r(punto base, short direccion_actual,
                                       string cromo_recibido,
                                        vector<short> &nuevas_direcciones){

    string cromo = cromo_recibido,
        tipo_tubo;

    vector<punto> VP, VP_r1, VP_r2, VP_r3;

    vector<short>  nuevas_dir_0,
                    nuevas_dir_1,
                    nuevas_dir_2;

    bool orientacion;

    while(cromo.size()){

        if(es_parentesis(tipo_tubo) == 0){
            tipo_tubo = cromo[0];
            cromo = cromo.substr(1);

            //Actualizo punto base y direccion (si viene un codo)
            base = obtenerPuntoPosicion(base, tipo_tubo, direccion_actual);

            nuevas_direcciones.push_back(direccion_actual);
            VP.push_back(base);
        }
        else{
            //Vino un parentesis
            break;
        }

    }

    if(es_parentesis(tipo_tubo) == 1){
        //Actualizo el tipo tubo
        tipo_tubo = cromo[0];

        // si viene un parentesis, lo saco
        cromo = cromo.substr(1);

        //Tambien saco el ultimo parentesis
        cromo.erase(cromo.size() - 1, 1);


    }

    if(es_bifurcacion(tipo_tubo)){
        //Agrego un tubo recto xq deo actualizar la posicion
        //base = obtenerPuntoPosicion(base, T.tubo_recto, direccion_actual);

        vector<string> biff = obtener_bifurcaciones(tipo_tubo + cromo);

        VP_r1 = get_puntos_r(base, direccion_actual, biff[0], nuevas_dir_0);

        nuevas_direcciones.insert(nuevas_direcciones.end(),
                                   nuevas_dir_0.begin(), nuevas_dir_0.end());

        VP.insert(VP.end(), VP_r1.begin(), VP_r1.end());

        if(es_bifurcacion(tipo_tubo) == 1){

            if(tipo_tubo == T.tee_izquierdo){
                orientacion = false;
            } else {
                orientacion = true;
            }

            //Obtengo nueva direccion para flujo secundario
            short direccion_flujo_secundario = cambioDeDireccion(direccion_actual, orientacion);

            VP_r2 = get_puntos_r(base, direccion_flujo_secundario, biff[1], nuevas_dir_1);

            nuevas_direcciones.insert(nuevas_direcciones.end(),
                                   nuevas_dir_1.begin(), nuevas_dir_1.end());

            VP.insert(VP.end(), VP_r2.begin(), VP_r2.end());

        }else{

            short direccion_flujo_secundario = cambioDeDireccion(direccion_actual, 0);
            short direccion_flujo_terciario = cambioDeDireccion(direccion_actual, 1);

            VP_r2 = get_puntos_r(base, direccion_flujo_secundario, biff[1], nuevas_dir_1);
            VP_r3 = get_puntos_r(base, direccion_flujo_terciario, biff[2], nuevas_dir_2);

            nuevas_direcciones.insert(nuevas_direcciones.end(),
                                   nuevas_dir_1.begin(), nuevas_dir_1.end());

            nuevas_direcciones.insert(nuevas_direcciones.end(),
                                   nuevas_dir_2.begin(), nuevas_dir_2.end());

            VP.insert(VP.end(), VP_r2.begin(), VP_r2.end());
            VP.insert(VP.end(), VP_r3.begin(), VP_r3.end());

        }

    }

    return VP;


}

/*
"Recibe parte de un cromosoma con bifurcacion del tipo [x(aaaa)(aa(l(a)(a))a)(aaa)] y
devuelve un vector con los sub string correspondientes ej: aaaa; aa(l(a)(a))a; aaa"
Salida: string en el formato indicado
Salida: vector de string con los substring correspondientes
*/
vector<string> Individuo :: obtener_bifurcaciones(string entrada){

    string ca(&entrada[0],1);
    unsigned int max;

    if(es_bifurcacion(ca) == 1){
        max = 2;
    } else{

        max = 3;
    }
    vector<string>ret;
    string ret_1;
    entrada = entrada.substr(2);

    // contador de parentesis
    int kparentesis = 1;
    unsigned int i = 0;

    for(unsigned int j = 0; j < max; j++){
        ret_1.clear();
        for(i = 0; i < entrada.size(); i++){

            if(string(&entrada[i],1) == T.abre_parentesis){
                kparentesis++;
            }

            if(string(&entrada[i],1) == T.cierra_parentesis){
                kparentesis--;
            }

            if(kparentesis == 0){
                break;
            }

            ret_1 += entrada[i];

        }

        ret.push_back(ret_1);

        if(j != max-1){
            kparentesis = 1;
            entrada = entrada.substr(i+2);
        }
    }

    return ret;
}

/*
"Muta una seccion random del cromosoma"
Recibe: el cromosoma a editar (normalmente dentro de la clase)
Salida: el cromosoma mutado
*/
void Individuo::mutarCromosoma() {

    insercion = 0;

    cout << "\n\nMUTACION EN PROCESO....\n\n";

    esta_siendo_mutado = true;

    double pos_corte = get_rand();

    // SI DA LA CASUALIDAD DE SALIR EL PRIMER ELEMENTO MUTAMOS DE FORMA COPADA
    if ((int) (pos_corte * cromosoma.size()) == 0) {
        short direccion_actual = rand() % 4 + 1;

        stringstream ss;
        ss << direccion_actual;

        string cro; cro = ss.str();
        cromosoma.replace(0, 1, cro);

        actualizarIndividuo();

    } else {

        vector<punto> puntos_eliminados;

        string
            h_mutado = this->get_spliced_cromosoma(pos_corte, puntos_eliminados),
            cromosoma_mutado = "";

        // La mutacion intercambio el cromosoma por uno vacio
        cout << "Cromosoma mutado: " << this->intercambiarCromosoma(cromosoma_mutado) << endl;

        cout << "\nTRABAJANDO CON MUTACION\n\n";
        // Antes elimino si hay cosas asi 2aa() lo paso a 2aa y muevo la insercion
        size_t
            posicion_parentesis = this->cromosoma.find("()"),
            posicion_parentesis_cruzados = this->cromosoma.find(")(");

        // Si encuentro uno pero no el otro, lo reemplazo (evito algo como 2(r()(..)))
        while (posicion_parentesis != string::npos && posicion_parentesis_cruzados == string::npos) {
            cout << cromosoma.find("()") << endl ;
            this->cromosoma.erase(this->cromosoma.find("()"), 2);
            this->insercion--;
            posicion_parentesis = this->cromosoma.find("()");
        }

        cout << "Cromosoma mutado 2: " << cromosoma << endl;


        this->cruzarCromosoma_helper(0, puntos_eliminados);

    }

    esta_siendo_mutado = false;
}

void Individuo::cruzarCromosoma(Individuo &I2, double pos_corte) {

    vector<punto> pos1_r, pos2_r;

    string
        h1 = this->get_spliced_cromosoma(pos_corte, pos1_r),
        h2 = I2.get_spliced_cromosoma(pos_corte, pos2_r);

    cout << "Cromosoma hijo 1: " << this->intercambiarCromosoma(h2) << endl;
    cout << "Cromosoma hijo 2: " << I2.intercambiarCromosoma(h1) << endl;

    /// Hijo 1
    cout << "\nTRABAJANDO CON HIJO 1\n\n";
    this->cruzarCromosoma_helper(h2.size(), pos1_r);

    /// Hijo 2

    cout << "\nTRABAJANDO CON HIJO 2\n\n";
    I2.cruzarCromosoma_helper(h1.size(), pos2_r);

}

void Individuo::cruzarCromosoma_helper(unsigned int tam_cromosoma_reemplazado,
                                       vector<punto> tuberias_reemplazadas) {
    cout << "Fase 0" << endl;
    cout << cromosoma << endl;

    // Si agrego una nueva tanda de cromosomas (en otras palabras, CRUZA)
    //if (tam_cromosoma_reemplazado > 0) {
        this->actualizarIndividuo();
   // }

    cout << "Fase 1" << endl;

    this->forzarCromosoma(this->cromosoma,
                          tam_cromosoma_reemplazado,
                          tuberias_reemplazadas);

    cout << "\nFase 2" << endl;
    cout << "Tomas sin cubrir: " << tomas_sin_cubrir.size() << endl;

    cout << "Cromosoma final: "<< this->get_cromosoma() << endl;
    cout << "Tomas sin cubrir: " << tomas_sin_cubrir.size() << endl;
    cout << "\n\n------------------------------------------------------------------\n\n";
}

/*
"Recorre el vector de tuberias, y va eliminando el vector de tomas cubiertas."
Recibe: Vector de tuberias y tomas
Salida: Cantidad de tomas cubiertas actualizado en el cromosoma.
*/
unsigned int Individuo::actualizarTomasLibres() {

    tomas_sin_cubrir = tomas;   // Reactualizamos el vector de tomas

    for (unsigned int i = 0, N = tuberias.size() ; i < N ; i++) {
        for (unsigned int j = 0 ; j < tomas_sin_cubrir.size() ; j++) {
            if (tuberias[i] == tomas_sin_cubrir[j]) {
                // Borro la ya analizada
                tomas_sin_cubrir.erase(tomas_sin_cubrir.begin() + j);
            }
        }
    }

    for (unsigned int j = 0, N = tomas_sin_cubrir.size() ; j < N ; j++ ) {
        cout << "Toma sin cubrir: "; tomas_sin_cubrir[j].printPunto();
    }

    return tomas_sin_cubrir.size();

}
