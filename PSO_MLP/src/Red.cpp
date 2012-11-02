#include "../include/swarm.h"
#include "../include/Red.h"
/*
aca hay q poner un vector P que va a tener los pesos de cada capa
Esoss pesos se consiguen de la funcion foward pass creo q el de red va a ser un vector de vector de vector
Luego llamamos a backward con el dato q guardamos en red

*/
Red::Red(vector<short> &Capas, float tasa, int N) {

    this->N = N;
    this->cant_neuronas = Capas[0];
    for (unsigned int k = 1; k < Capas.size(); k++) {
        cant_neuronas += Capas[k];
    }

    this->cant_capas = Capas.size();
	srand(time(NULL));

    this->input.resize(N);

	this->capas.resize(cant_capas);
	Capa C(Capas[0], N, tasa, (cant_capas == 1) ? 0 : Capas[1],(cant_capas == 1) ? true : false);
	capas[0] = C;

    //Creamos capas
    for(short i = 1; i < cant_capas - 1; i++) {
        Capa C(Capas[i], Capas[i-1], tasa, Capas[i+1]);
        capas[i] = C;
    }

    //Creamos la ultima capa
    if (cant_capas > 1) {
        Capa ultima(Capas[cant_capas - 1], Capas[cant_capas - 2], tasa, 0, true);
        capas[cant_capas-1] = ultima;
    }

    // Para combinarlo con SWARM
    cant_pesos = 0;
    for (short i = 0 ; i < cant_capas; i ++) {
        for (short j = 0 ; j < capas[i].get_cant_neuronas(); j++) {
            cant_pesos += capas[i].get_pesos()[j].size();
        }
    }
}

vector<float> Red::forward_pass(vector<float> input){
    short cant_capas = this->capas.size();

    this->input = input;

    /*Pasamos un input y la capa siguiente para que pueda sacar de alli los
     pesos para el backward*/
    for(short i=0; i<cant_capas-1; i++) {
        input = capas[i].forward_pass(input, capas[i+1]);
    }
    //Hacemos el fowardpass con la ultima, (no le enviamos ninguna otra capa)
    input = capas[cant_capas-1].forward_pass(input);

    return input;
}

void Red::backward_pass(vector<float> ydeseado){
    short cant_capas = this->capas.size(),
        ultimo = cant_capas - 1;

    vector<float> old_grad;

	old_grad = capas[ultimo].backward_pass(ydeseado, yAnterior(ultimo - 1));

    for (short i = ultimo - 1 ; i >= 0 ; i--) {
        old_grad = capas[i].backward_pass(old_grad, yAnterior(i - 1));
    }

}

/* En base a los indices de las capas, retorna los y correspondientes */
vector<float> Red::yAnterior(short indiceCapa) {

    vector<float> yAnterior;

    if (indiceCapa >= 0) {
        yAnterior = this->capas[indiceCapa].get_output();
    } else {
        yAnterior = this->input;
    }

    yAnterior.push_back(1);

    return yAnterior;
}

/* Actualiza los pesos de cada una de las neuronas yendo por cada capa */
void Red::actualizar_pesos() {

    for(short i = 0; i < cant_capas; i++) {
        this->capas[i].actualizar_pesos();
    }
}

/*Entrena/prueba la red con un solo patron. Se considera que en los
ultimos elementos del patron viene el yDeseado.
Si probar = true entonces prueba la red con los patrones pasados y devuelve
TRUE si el resultado fue el correcto o FALSE si fue incorrecto
Si probar = false, entonces entrena la red actualizando los pesos correspondientes*/
bool Red::entrenarRed(vector<float> P, bool probar){//NO pasar el P por referencia

    vector <float> yDeseado;
    float yDeseadoFloat = P.back(); //Casteo

    P.pop_back();

    yDeseado.resize(capas.back().get_cant_neuronas(), -1);
    vector<float> salida = this->forward_pass(P);
    vector<float> salida2 = salida;
    yDeseado[yDeseadoFloat] = 1;

    bool acerto = false,
        yaSeActivoUna = false;

    if(probar){

        clases.push_back(-1);
/*
        cout << "Prueba: ";
        printVector<float>(P);
        printVector<float>(salida);
*/
       for (unsigned int i=0; i<salida.size(); i++){

            if(salida[i] > 0) {//Si se activo una neurona
                if(yaSeActivoUna){ //Pregunto si ya se habia activado otra
                    acerto = false; //Si ya se activo otra, entonces hay un error y devuelvo false
                    break;
                }

                yaSeActivoUna = true;

                if(i == yDeseadoFloat){ //si la que se activa es la que se tenia q activar
                    acerto = true;
                    clases[clases.size() - 1] = i;
                }
            }

        }

        if (!acerto) {
            clases[clases.size() - 1] = -1;
        }

    }
    else {
        this->backward_pass(yDeseado);
        this->actualizar_pesos();
    }

    return acerto;

}

float Red::estEntrenamiento(vector< vector<float> > &P, bool probar, int cant){

    int tam = P.size();

    if(probar){
        int aciertos = 0;
        for(int i=0; i<tam; i++){
            if(entrenarRed(P[i], true)){
                aciertos += 1;
            }
        }
        return float(float(aciertos)/float(tam));
    }

    else{
        for(int j=0; j<cant; j++){
            for(int i=0; i<tam; i++){
                entrenarRed(P[i]);
            }
        }
        return 123.0;

    } // fin else
} //fin funcion

/* Hace la validacion cruzada usando el leave-k-out */
float Red::validacion_cruzada(string path, short k, unsigned int cant_iteraciones) {
    vector< vector<float> > P;
    parseCSV<float>(path, P);
    return leave_k_out(P, k, cant_iteraciones);
}

/* Leave-Something-Out */
float Red::leave_k_out(vector< vector<float> > &patrones, short k, unsigned int cant_iteraciones) {

    unsigned int indice = 0, contador = 0, N = patrones.size();
    float error = 0;

    while (indice + k - 1 < N) {

        contador++;

        vector< vector<float> > entrenamiento;
        vector< vector<float> > prueba;

        for (unsigned int i = 0; i < N; i++) {
            if (i == indice) {
                vector< vector<float> >::const_iterator inicio = patrones.begin();
                vector< vector<float> >::const_iterator first = patrones.begin() + i;
                vector< vector<float> >::const_iterator last = patrones.begin() + (i + k);
                vector< vector<float> >::const_iterator fin = patrones.end();

                prueba = vector< vector <float> >(first, last);

                entrenamiento = vector< vector <float> >(inicio, first);
                entrenamiento.insert(entrenamiento.end(), last, fin);

                break;
            }
        }

        /// Aca llamo a una funcion que entrene las neuronas
        estEntrenamiento(entrenamiento, false, cant_iteraciones);

        /// Medimos el error
        float suma = 0;
        error = 0;

        for (unsigned int j = 0, eN = entrenamiento.size(); j < eN; j++) {

            //entrenarRed(entrenamiento[j]);

             // Medimos el error cuadratico

            float yDeseado = entrenamiento[j].back();

            entrenamiento[j].pop_back();

            vector<float> salidaRed(forward_pass(entrenamiento[j]));

            for (unsigned int i = 0, N = salidaRed.size(); i < N; i++ ) {
                suma += pow(yDeseado - salidaRed[i], 2);
            }

            error = sqrt(suma) / 2;
            errores.push_back(error);
        }

        reinicializar_red();

        indice += k;
    }

    return error;
}

float Red::entrenar(vector<vector<float> > &E,vector<vector<float> > &P, int maxit, float tol){
    float error = 0;

    cout << "Entrenando..." << endl;

    for(int i = 0;i <maxit; i++) {
        estEntrenamiento(E, false, 1); //Entreno
        error = 1 - estEntrenamiento(P, true); //Pruebo
        cout << "Iteracion: \t" << i << " | Error: \t" << error << "\r";
        cout.flush();

     if(error<tol){
            cout << "\n ... Salio porque el error es menor a la tolerancia [" << tol << "]." << endl;
            return error;
        }

    }

    cout<<"\n... Salio por Maximo de iteraciones "<<endl;
    return error;
}

/// FUNCIONES DE VALIDACION DE ERRORES ///

float Red::get_error() {
    float error = 0;
    unsigned int N = errores.size();

    for (unsigned int i = 0; i < N; i++) {
        error += errores[i];
    }

    return error/N;
}

void Red::get_err_desvio(float &media, float &desvio) {
    desvio = 0;
    media = get_error();

    unsigned int N = errores.size();

    for (unsigned int i = 0; i < N; i++) {
        desvio += pow(media - errores[i], 2);
    }

    desvio = sqrt(desvio/(N - 1));
}

/// FUNCION PARA EL SWARM ///

// Esta funcion se encarga de recibir un vector de pesos de cant_neuronas * N,
// y ordenarlos en subconjuntos de pesos para cada capa
vector<vector<float> > Red::transmutar_pesos(vector<float> &pesos) {
    vector<float> temp_pesos;
    vector<vector<float> > nuevos_pesos;

    short contador_pesos_convertidos = 0;

    for (short i = 0; i < cant_capas; i++ ) {

        for (short j = 0, cant = capas[i].get_cant_neuronas() * capas[i].get_pesos()[0].size(); j < cant; j++ ) {
            temp_pesos.push_back(pesos[j]);
            contador_pesos_convertidos++;
        }

        nuevos_pesos.push_back(temp_pesos);
        temp_pesos.clear();

        // Si no es el ultimo, borramos
        if (i < cant_capas - 1) {
            pesos.erase(pesos.begin(), pesos.begin() + contador_pesos_convertidos);
        }
    }

    return nuevos_pesos;
}

// Fuerzas los pesos de la red, en vez de usar backpropagation
void Red::forzar_pesos(vector<float> &pesos) {

    vector<vector<float> > nuevos_pesos = transmutar_pesos(pesos);

    for (short i = 0; i < cant_capas; i++ ) {
        vector<vector<float> > pesos_por_capa;
        vector<float> aux_pesos_por_capa;

        short pesos_a_explorar = capas[i].get_pesos()[0].size();

        for (unsigned int k = 0, kCant = nuevos_pesos[i].size(); k <= kCant; k++ ) {
            if (k > 0 && k % pesos_a_explorar == 0) {
                pesos_por_capa.push_back(aux_pesos_por_capa);
                aux_pesos_por_capa.clear();
            }

            aux_pesos_por_capa.push_back(nuevos_pesos[i][k]);
        }

        capas[i].forzar_pesos(pesos_por_capa);

    }
}


float Red::swarmEntrenar(
                         vector<vector<float> > &E,
                         vector<vector<float> > &P,
                         vector<vector<float> > &V,
                         int maxit, float tol) {

    // Creo mi enjambre, cuya dimension va a ser cant_neuronas * cant_pesos_por_capa
    short
        dimension = cant_pesos,
        particulas = 50;

    double
        error = 0,
        best_value = 1;

    vector <double> particlePosition;

    cout << "\nCreando enjambre de [" << particulas
         << "] particulas y de dimension [" << dimension << "]:\n"
         << "Entrenando con enjambre...\n";

    Swarm S(particulas, dimension);

    for(int iteration = 0; iteration < maxit; iteration++) {

        for (short kParticulas = 0; kParticulas < particulas; kParticulas++) {
            particlePosition = S.GetPosition(kParticulas);

            // Convierto mi vector<double> a vector<float>
            vector<float> fParticlePosition(particlePosition.begin(), particlePosition.end());
            // Fuerzo los pesos de la red a los nuevos obtenidos por el Swarm
            forzar_pesos(fParticlePosition);

            // "Entreno" la red, sin usar le backpropagation
            error = 1 - estEntrenamiento(E, true);
            S.set_fitness_from_net(error, kParticulas);
        }

        /// Ahora fuerzo los pesos con la mejor particula y verifico
        particlePosition = S.GetBestPosition();
        vector<float> fParticlePosition(particlePosition.begin(), particlePosition.end());
        forzar_pesos(fParticlePosition);

        /// Es momento de verificar si los nuevos pesos son buenos
        error = 1 - estEntrenamiento(P, true);

        if (error < best_value) {
            best_value = error;
        }

        cout << "Iteracion: \t" << iteration << " | Error: \t" << error
             << " | Menor Error:\t" << best_value << endl;
        //cout.flush();

        if(error<tol){
            cout << "\n ... Salio porque el error es menor a la tolerancia [" << tol << "]." << endl;
            return error;
        }

        // Evaluo las particulas con sus nuevos pesos/posiciones y fitness
        S.EvaluarParticulas();
        S.ChangeVelPos(iteration, maxit);

    }

    cout<<"\n... Salio por Maximo de iteraciones "<<endl;
    return error;
}
