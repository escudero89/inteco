#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

namespace utilidades {
    float dot(vector<float> V1, vector<float> V2) {

        float sol = 0;

        if (V1.size() == V2.size()) {
            for (unsigned int i = 0; i < V1.size(); i++) {
                sol += V1[i] * V2[i];
            }
        } else {
            cout << "Error haciendo el producto escalar, distinta longitud.";
            exit (1);
        }

        return sol;
    }

    // Esto es para ver el archivo CSV (lo saque de internet, aun no lo vi)
    /*
    std::vector<std::string> getNextLineAndSplitIntoTokens(std::istream& str)
    {
        std::vector<std::string>   result;
        std::string                line;
        std::getline(str,line);

        std::stringstream          lineStream(line);
        std::string                cell;

        while(std::getline(lineStream,cell,','))
        {
            result.push_back(cell);
        }
        return result;
    }*/
}

class Perceptron {
    vector<float> *pesos;	// W(i)
    float umbral;			// w_0
    int N;					// cantidad de elementos
    float tasa; //tasa de aprendizaje

public:

    Perceptron(float umbral, int N, float tasa=1.5, float desvio=0.5, float media=0);
    bool entrenar(vector<float> patrones);
    bool estEntrenamiento(vector<vector<float> > estacion);
    void set_tasa(float tasa) {
        this->tasa = tasa;
    }

};

#endif // PERCEPTRON_H
