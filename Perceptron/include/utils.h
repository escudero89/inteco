#ifndef __UTILS_H__
#define __UTILS_H__

#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>

void parseCSV(std::string filename, std::vector<std::vector<double> > & X);

// Debo definir las funciones con templates en los headers porque sino no linkea

template<class T> void printVector(std::vector<T> &v, char separator = ' ') {
	for (unsigned int i = 0; i < v.size(); i++){
		std::cout << v[i];
		if(i < v.size() - 1) //Si no es el ultimo caso
			std::cout << separator;
	}
}

template<class S> void printVectorVector(std::vector< std::vector<S> > &v, char separator = ' ', std::string newcase = "\n-------\n"){
    for (unsigned int i = 0; i < v.size(); i++){
		printVector(v[i],separator);
		std::cout<<newcase;
	}
}
#endif
