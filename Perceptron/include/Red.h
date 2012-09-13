#ifndef RED_H
#define RED_H

#include <iostream>
#include <cassert>
#include <vector>

#include "Capa.h"

using namespace std;

class Red {
    vector<Capa> capas;

public:
    Red(vector<short> &Capas, float tasa, int N);
    vector<float> forward_pass(vector<float> input);
    void backward_pass(vector<float> ydeseado);
};

#endif // RED_H
