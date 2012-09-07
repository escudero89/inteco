#include "../include/Red.h"

Red::Red(vector<short> &neuronas, float tasa, int N) {

    short capas = neuronas.size(),
        hidden_cant = capas - 1;

    if (hidden_cant < 1) {
        cout << "No hay capas ocultas, se detiene ejecucion.\n";
        assert(0);
    }

    hidden = new vector<Capa>;
    //hidden->resize(hidden_cant);

    for (short i = 0; i < capas; i++ ) {
        //Capa C(neuronas[i], tasa, N);

        if (i == capas - 1) {
            //output = C;
        } else {
            //hidden->at(i) = C;
        }
    }
}
