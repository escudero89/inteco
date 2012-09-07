#ifndef RED_H
#define RED_H

#include <iostream>
#include <cassert>
#include <vector>

#include "Capa.h"

using namespace std;

class Red {
    vector<Capa> hidden;
    Capa output;

public:
    Red(vector<short> &neuronas, float tasa, int N);
};

#endif // RED_H
