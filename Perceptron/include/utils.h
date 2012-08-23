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
void genPlot2D(std::vector< std::vector<T> > &pesos, std::vector< std::vector<T> > &padrones, std::string filename_o = "log.dat") {

	unsigned int PLOT_ARGS = 2; // debido a que es un ploteo 2D, solo quiero dos argumentos de los padrones

	std::string filename = "logs/" + filename_o;

	std::ofstream file;
	file.open(filename.c_str());

	assert(file.is_open()); //muestra error si no se pudo abrir el archivo

	// Guardo los pesos y todos los padrones separados por comas
	for (unsigned int i = 0, N = padrones.size(); i < N; i++){
		for (unsigned int j = 0, step = PLOT_ARGS; j < step ; j++) {
			file << padrones[i][j];
			if (j < step - 1) { // si no es el ultimo elemento, agrego la coma
				file << ",";
			}
		}
		file << std::endl;
	}

	file << "#END#" << std::endl; // para avisar hasta donde llegan los patrones

	for (unsigned int i = 0, N = pesos.size(); i < N; i++){
		for (unsigned int j = 0, step = pesos[i].size(); j < step ; j++) {
			file << pesos[i][j] ;
			if (j < step - 1) { // si no es el ultimo elemento, agrego la coma
				file << ",";
			}
		}
		file << std::endl;
	}

	file.close();
}

// Funcion para particionar vector de datos
#if 0
bool particionar(string path,
                 vector< vector<float> > &Ventrenamiento,
                 vector< vector<float> > &Vcontrol,
                 vector< vector<float> > &Vpruebas,
                 float porEntr = 70,
                 float porControl = 20,
                 float porPruebas = 10);
#endif

#endif
