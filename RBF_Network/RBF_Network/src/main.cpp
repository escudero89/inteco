#include "../include/Red_RBF.h"
#include "../include/neurona.h"
#include "../include/neurona_RBF.h"
#include "../include/punto.h"
#include "../../../utils/utils.h"

using namespace std;

int main(int argc, char **argv) {
    vector<short> neuronas;
    neuronas.push_back(2);
    neuronas.push_back(2);

    Red_RBF R(2,neuronas,0.05);
    vector<vector<float> > V;
    parseCSV<float>("data/or700.csv",V);
    vector<punto> in;
    vector<vector<punto> >out;
    in.resize(V.size());

    for(int i=0; i< V.size(); i++){
        V[i].pop_back();
        punto P(V[i]);
        in[i] = P;
    }


    out = R.k_means(in,4,0.1);

return 0;
}
