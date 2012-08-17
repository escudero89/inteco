#include "../include/utils.h"
/*
Entrada: Path al archivo csv
Salida: Devuelve un vector de vector<double>  con el contenido de un archivo CSV
*/

void parseCSV(std::string filename, std::vector<std::vector<float> > & X) {

	std::ifstream file;
	file.open(filename.c_str());

	assert(file.is_open()); //muestra error si no se pudo abrir el archivo

	float value;
	std::string s, line;
	std::stringstream ss, iss;
	//Lectura de los datos de entrenamiento
	while(getline(file,line)){ 		//lee una linea entera
		iss<<line;
		X.push_back(std::vector<float>()); 		//agrega un vector vacio

		while(getline(iss,s,',')){ //separa la linea entre las comas
			//transforma de string a double
			ss<<s;
			ss>>value;
			X.back().push_back(value); //agrega el elemento al vector
			ss.clear(); //limpia el stream
		}
		iss.clear();
	}
    file.close();
}
