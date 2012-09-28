#include "../include/Red_RBF.h"
#include "../include/neurona.h"
#include "../include/neurona_RBF.h"
#include "../include/punto.h"
#include "../../../utils/utils.h"

using namespace std;

int main(int argc, char **argv) {
    vector<short> neuronas;
    neuronas.push_back(4);
    neuronas.push_back(2);

    Red_RBF R(4,neuronas,0.05);
    vector<vector<float> > V;
    parseCSV<float>("data/or700.csv",V);
    vector<punto> in;
    vector<vector<punto> >out;
    in.resize(V.size());
    vector<float> yDeseado;
    for(unsigned int i=0; i< V.size(); i++){
        yDeseado.push_back(V[i].back());
        V[i].pop_back();
        punto P(V[i]);
        in[i] = P;
    }


        R.entrenarCapa0(in,4);
        R.entrenarCapa1(in, yDeseado);

//
//    out = R.k_means(in,4,0.0001);
//    //Anda bastante bien, por ahi tira nan, hay q ver si es xq chupa basura o xq arranca mal
//    //Ver tambien el tema de la varianza
//    for(int i=0; i<4;i++){
//        for(int j = 0; j<2; j++){
//        cout<<"Coordenada: "<<endl;
//        cout<<out[0][i].coordenadas[j]<<endl;
//        cout<<"Desvio: "<<endl;
//        cout<<out[1][i].coordenadas[j]<<endl;
//        }
//        cout<<endl;
//    }

return 0;
}
