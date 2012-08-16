#ifndef __UTILS_H__
#define __UTILS_H__

#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>

void parseCSV(char *filename, std::vector<std::vector<double> > & X);

template<typename T> void printVector(std::vector<T> &v, char separator = ' ');

template<typename T> void printVectorHelperr(std::vector<std::vector<T> > &v, char separator = ' ', std::string newcase = "\n-------\n");

#endif
