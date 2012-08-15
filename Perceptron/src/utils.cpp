#include "utils.h"

/*
Entrada: Path al archivo csv
Salida: Devuelve un vector de vector<double>  con el contenido de un archivo CSV
*/

void parseCSV(char *filename, std::vector<std::vector<double> > & X) {

	std::ifstream file;
	file.open(filename);
	assert(file.is_open()); //muestra error si no se pudo abrir el archivo

	double value;
	std::string s, line;
	std::stringstream ss, iss;
	//Lectura de los datos de entrenamiento
	while(getline(file,line)){ 		//lee una linea entera
		iss<<line;
		X.push_back(std::vector<double>()); 		//agrega un vector vacio

		while(getline(iss,s,',')){ //separa la linea entre las comas
			//transforma de string a double
			ss<<s;
			ss>>value;
			X.back().push_back(value); //agrega el elemento al vector
			ss.clear(); //limpia el stream
		}
		iss.clear();
	}
}

template<typename T>
void printVector(std::vector<T> &v, char separator = ' '){
	for (unsigned int i = 0; i < v.size(); i++){
		std::cout<<v[i];
		if(i < v.size()-1) //Si no es el ultimo caso
			std::cout<<separator;
	}
}


template<typename T>
void printVectorVector(std::vector<std::vector<T> > &v, char separator = ' ',
						std::string newcase = "\n-------\n"){
	for (unsigned int i = 0; i < v.size(); i++){
		printVector(v[i],separator);
		std::cout<<newcase;
	}
}
