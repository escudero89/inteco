#include "../include/utils.h"
#include <vector>
#include <math.h>
#include <algorithm>
#if 1
using namespace std;
vector<conjuntoDatos> particionar(std::string path, int cantConj,
                 float porEntr,
                 float porPruebas,
                 float porControl){

    // Leemos el archivo csv y lo pasamos al vector V
    vector< vector<float> > V;
    parseCSV(path, V);

    // Buscamos la cantidad de elementos q tendra cada vector longE, longP y longC
    int n = V.size();
    double longE = 0, longP = 0, longC = 0;

    double  fracE = modf( (porEntr * n) / 100, &longE),
            fracP = modf( (porPruebas * n) / 100, &longP),
            fracC = modf( (porControl * n) / 100, &longC);

    double aux = 0;
    while ( (longE + longP + longC) != n)
        {
            aux=max(max(fracE,fracP),fracC);
            if (aux == fracE)
                longE += 1;
                else
                    if(aux == fracP)
                        longP += 1;
                        else
                            longC += 1;

        } // end while

    // Creamos cantConj Conjuntos
    vector< vector<float> > v1,v2,v3;
    vector<conjuntoDatos> particiones;

    for(int i = 0; i<cantConj; i++)
     {
         random_shuffle(V.begin(),V.end()); //revolvemos el vector
         v1.insert(v1.begin(),V.begin(),V.begin()+longE);
         v2.insert(v2.begin(),V.begin()+longE,V.begin()+longE+longP);
         v3.insert(v3.begin(),V.begin()+longE+longP,V.end());
         conjuntoDatos P;
         P.entrenamiento = v1;
         P.control = v2;
         P.prueba = v3;
         particiones.push_back(P);
         v1.clear();
         v2.clear();
         v3.clear();
     }

    return particiones;
                                    }
#endif
