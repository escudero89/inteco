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
    bool operator==(punto N);
    float distancia(punto A);
    float distancia_manhattan(punto A, punto &);
    punto pow2();
    punto raizCuadrada();
    void printPunto();
    float sum();
    unsigned int menor_distancia(vector<punto> VP, short &, punto &);
    /* punto operator=(const punto& other){
     this->coordenadas = other.coordenadas;

     };*/

};

#endif // PUNTO_H
