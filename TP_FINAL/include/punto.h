#ifndef PUNTO_H
#define PUNTO_H

#include <vector>
#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;

class punto {
public:
    vector<float> coordenadas;
public:
    punto(int dimension, float desvio, float media);
    punto (float x, float y);
    punto(vector<float> coordenadas);
    punto() {}; /// OJO CONSTRUCTOR VACIO
    punto operator+(const punto& other);
    punto operator-(const punto& other);
    punto operator/(float N);
    float distancia(punto A);
    punto pow2();
    punto raizCuadrada();
    void printPunto();
    float sum();
    /* punto operator=(const punto& other){
     this->coordenadas = other.coordenadas;

     };*/

};

#endif // PUNTO_H
