#include "../include/Red_RBF.h"
#include "../include/neurona.h"
#include "../include/neurona_RBF.h"
#include "../include/punto.h"
#include "../../../utils/utils.h"

using namespace std;

int main(int argc, char **argv) {
#if 0 /* Problema XOR */
    vector<short> neuronas;
    neuronas.push_back(4);
    neuronas.push_back(2);

    Red_RBF R(2,neuronas,0.05);
    vector<vector<float> > Ve;
    vector<vector<float> > Vp;
    parseCSV<float>("data/xor600a.csv",Ve);
    parseCSV<float>("data/xor100a.csv",Vp);

    R.entrenarRed(Ve,10);
    cout<<"Porcentaje de aciertos: "<<endl;
    cout<<R.probarRed(Vp) * 100<<" %";

#endif

#if 1
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
