#ifndef PUNTO_H
#define PUNTO_H

#include <vector>
#include <cstdlib>
#include <math.h>

using namespace std;

class punto
{
    private:
        vector<float> coordenadas;
    public:
        punto(int dimension, float desvio = 0.5, float media = 0);
        punto(vector<float> coordenadas);
        punto(){}; /// OJO CONSTRUCTOR VACIO
        punto operator+(const punto& other);
        punto operator-(const punto& other);
        punto operator/(float N);
        float distancia(punto A);
        punto pow2();
        punto raizCuadrada();

       /* punto operator=(const punto& other){
        this->coordenadas = other.coordenadas;

        };*/

};

#endif // PUNTO_H
