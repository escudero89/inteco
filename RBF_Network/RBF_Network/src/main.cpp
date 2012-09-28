/** Incluimos RBF_Network **/
#include "../include/Red_RBF.h"
#include "../include/neurona.h"
#include "../include/neurona_RBF.h"
#include "../include/punto.h"
#include "../../../utils/utils.h"

/** Incluimos Perceptron **/
#include "../../../Perceptron/include/Capa.h"
#include "../../../Perceptron/include/perceptron.h"
#include "../../../Perceptron/include/Red.h"
#include "../../../Perceptron/include/Miniptron.h"
#include "../../../Perceptron/include/Record.h"

#include "../../../Perceptron/src/Capa.cpp"
#include "../../../Perceptron/src/perceptron.cpp"
#include "../../../Perceptron/src/Red.cpp"
#include "../../../Perceptron/src/Miniptron.cpp"
#include "../../../Perceptron/src/Record.cpp"

using namespace std;

int main(int argc, char **argv) {

#if 1 /** Problema XOR **/

    /* ---- Con RBF network ---- */
    vector<short> neuronas;
    neuronas.push_back(4);
    neuronas.push_back(2);

    Red_RBF R1(2,neuronas,0.05);
    vector<vector<float> > Ve;
    vector<vector<float> > Vp;
    parseCSV<float>("data/xor600a.csv",Ve);
    parseCSV<float>("data/xor100a.csv",Vp);

    R1.entrenarRed(Ve,10);
    cout<<"Porcentaje de aciertos: "<<endl;
    cout<<R1.probarRed(Vp) * 100<<" %";

    getchar();

    /* ---- Con Perceptron multicapa----  */
    vector<short> neuronasPorCapa;
    neuronasPorCapa.push_back(2);
    neuronasPorCapa.push_back(2);

    Red R2(neuronasPorCapa,0.01,2);
    R2.entrenar(Ve,Vp,500,0.01);


#endif

#if 0
    vector<short> neuronas;
    neuronas.push_back(1);
    neuronas.push_back(2);

    Red_RBF R(2,neuronas,0.05);

    vector<vector<float> > Ve;
    vector<vector<float> > Vp;
    parseCSV<float>("data/concent2000.csv",Ve);
    parseCSV<float>("data/concent500.csv",Vp);

    R.entrenarRed(Ve,10);
    cout<<"Porcentaje de aciertos: "<<endl;
    cout<<R.probarRed(Vp) * 100<<" %";

#endif
return 0;
}
