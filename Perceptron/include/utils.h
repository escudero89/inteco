#ifndef __UTILS_H__
#define __UTILS_H__

#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>

/*
Entrada: Path al archivo csv
Salida: Devuelve un vector de vector<double>  con el contenido de un archivo CSV
*/
template <class T>
void parseCSV(std::string filename, std::vector<std::vector<T> > & X) {
	std::ifstream file;
	file.open(filename.c_str());

	assert(file.is_open()); //muestra error si no se pudo abrir el archivo

    // creamos una variable en el que almacenar los strings del cvs
	T value;

	std::string s, line;
	std::stringstream ss, iss;
	//Lectura de los datos de entrenamiento
	while(getline(file,line)){ 		//lee una linea entera
		iss << line;
		X.push_back(std::vector<T>()); 		//agrega un vector vacio

		while(getline(iss,s,',')){ //separa la linea entre las comas
			//transforma de string a double
			ss << s;
			ss >> value;
			X.back().push_back(value); //agrega el elemento al vector
			ss.clear(); //limpia el stream
		}
		iss.clear();
	}
    file.close();
}

// Debo definir las funciones con templates en los headers porque sino no linkea

template <class T>
void printVector(std::vector<T> &v, char separator = ' ') {
	for (unsigned int i = 0; i < v.size(); i++){
		std::cout << v[i];
		if(i < v.size() - 1) //Si no es el ultimo caso
			std::cout << separator;
	}
}

template <class S>
void printVectorVector(std::vector< std::vector<S> > &v, char separator = ' ', std::string newcase = "\n-------\n"){
    for (unsigned int i = 0; i < v.size(); i++){
		printVector(v[i],separator);
		std::cout<<newcase;
	}
}

/* La idea es que exporte archivos para plotearlo luego con otro programa */
/* El formato es:
	padrones
	...
	#END#
	pesos
*/
template <class T>
void genPlot2D(std::vector< std::vector<T> > &pesos, std::vector< std::vector<T> > &padrones, std::string padrones_o = "padrones.log", std::string pesos_o = "pesos.log") {

	unsigned int PLOT_ARGS = 2; // debido a que es un ploteo 2D, solo quiero dos argumentos de los padrones

    std::string file_padron = "logs/" + padrones_o;
    std::string file_pesos = "logs/" + pesos_o;

    genPlot2D_helper(padrones, file_padron, PLOT_ARGS);
    genPlot2D_helper(pesos, file_pesos);
}

// Se encarga de crear y guardar los archivos de log.
template <class T>
void genPlot2D_helper(std::vector< std::vector<T> > &array, std::string filename_o, unsigned int PLOT_ARGS = 0) {

	std::ofstream file;
	file.open(filename_o.c_str());

	assert(file.is_open()); //muestra error si no se pudo abrir el archivo

    // Si no hay PLOT_ARGS, el defaul es el tamanio del vector de largo
    if (PLOT_ARGS == 0) {
        PLOT_ARGS = array[0].size();
    }

	// Guardo los pesos en "filename_o.log"
	for (unsigned int i = 0, N = array.size(); i < N; i++){
		for (unsigned int j = 0, step = PLOT_ARGS; j < step ; j++) {
			file << array[i][j];
			if (j < step - 1) { // si no es el ultimo elemento, agrego la coma
				file << ",";
			}
		}
		file << std::endl;
	}

    file.close();
}

// Es para hacer productos puntos entre vectores
template <class T>
T dot(std::vector<T> &V1, std::vector<T> &V2) {
    T sol = 0;

    if (V1.size() == V2.size()) {
        for (unsigned int i = 0; i < V1.size(); i++) {
            sol += V1[i] * V2[i];
        }
    } else {
        std::cout << "Error haciendo el producto escalar, distinta longitud.\n";
        std::cout << "V1: " << V1.size() << std::endl;
        printVector(V1);
        std::cout << "\nV2: "<< V2.size() << std::endl;
        printVector(V2);
        exit (1);
    }

    return sol;
}

/*
Struc conjunto de datos. Tiene 3 elementos. Ellos son: una particion con datos de
entrenamiento, una particion con datos de pruebas y una particion con datos de control
*/
struct conjuntoDatos {
std::vector< std::vector<float> > entrenamiento;
std::vector< std::vector<float> > prueba;
std::vector< std::vector<float> > control;
};
/*
Dados una ruta de archivo, una cantidad de Conjunto de datos (cantConj) y los
porcentajes deseados para cada particion; la funcion devuelve un vector que contiene
cantConj conjuntos DISTINTOS de datos.
*/
std::vector<conjuntoDatos> particionar(std::string path, int cantConj = 1,
                    float porEntr = 70,
                    float porPruebas = 20,
                    float porControl = 10);


#endif
