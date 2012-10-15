/** Incluimos RBF_Network **/
#include "../include/Red_RBF.h"
#include "../include/neurona.h"
#include "../include/neurona_RBF.h"
#include "../include/punto.h"
#include "../../../utils/utils.h"
#include "../../../utils/utils.cpp"

/** Incluimos Perceptron **/
#include "../../../Perceptron/include/Capa.h"
#include "../../../Perceptron/include/perceptron.h"
#include "../../../Perceptron/include/Red.h"
#include "../../../Perceptron/include/Miniptron.h"
#include "../../../Perceptron/include/record.h"

#include "../../../Perceptron/src/Capa.cpp"
#include "../../../Perceptron/src/perceptron.cpp"
#include "../../../Perceptron/src/Red.cpp"
#include "../../../Perceptron/src/Miniptron.cpp"
#include "../../../Perceptron/src/record.cpp"

using namespace std;

int main(int argc, char **argv) {

#if 0 /** Problema XOR **/

    /* ---- Con RBF network ---- */
    /* 2 iteraciones -- 98% de aciertos */

    vector<short> neuronas;
    neuronas.push_back(4);
    neuronas.push_back(2);

    Red_RBF R1(2,neuronas,0.05);
    vector<vector<float> > Ve;
    vector<vector<float> > Vp;
    parseCSV<float>("data/xor600a.csv",Ve);
    parseCSV<float>("data/xor100a.csv",Vp);

    R1.entrenarRed(Ve,10);
    cout<<"Resultados de XOR con RBF: "<<endl;
    cout<<"Porcentaje de aciertos: "<<endl;
    cout<<R1.probarRed(Vp) * 100<<" %";

    getchar();

    /* ---- Con Perceptron multicapa----  */
    /* 6 iteraciones -- 100% aciertos  */

    vector<short> neuronasPorCapa;
    neuronasPorCapa.push_back(2);
    neuronasPorCapa.push_back(2);

    Red R2(neuronasPorCapa,0.01,2);

    cout<<endl;
    cout<<"Resultados de XOR con MLP: "<<endl;
    float aciertos=(1 - R2.entrenar(Ve,Vp,100,0.00001)) *100;

    cout<<endl<<"Porcentaje de aciertos: "<<aciertos<<endl;


#endif

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if 0   /** Problema CONCENT **/
    vector<short> neuronas;
    neuronas.push_back(1);
    neuronas.push_back(2);

    Red_RBF R1(2,neuronas,0.001);

    vector<vector<float> > Ve;
    vector<vector<float> > Vp;
    parseCSV<float>("data/concent2000.csv",Ve);
    parseCSV<float>("data/concent500.csv",Vp);

    R1.entrenarRed(Ve,100);
    cout<<"Porcentaje de aciertos: "<<endl;
    cout<<R1.probarRed(Vp) * 100<<" %";

#endif

#if 0
    getchar();
 /* ---- Con Perceptron multicapa----  */
    vector<short> neuronasPorCapa;
    neuronasPorCapa.push_back(5);
    neuronasPorCapa.push_back(2);

    Red R2(neuronasPorCapa, 0.001, 2);

    cout<<endl;
    cout<<"Resultados de XOR con MLP: "<<endl;
    float aciertos=(1 - R2.entrenar(Ve, Vp, 1000, 0.01)) *100;

    cout<<endl<<"Porcentaje de aciertos: "<<aciertos<<endl;

#endif

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if 0   /** Problema IRIS **/
    /*A veces 91% en 5 iteraciones; desvio = 1*/
    vector<short> neuronas;
    neuronas.push_back(3);
    neuronas.push_back(3);

    Red_RBF R1(4,neuronas,0.01);

    vector<vector<float> > Ve;
    vector<vector<float> > Vp;
    parseCSV<float>("data/iris.csv",Ve);
    parseCSV<float>("data/iris.csv",Vp);

    random_shuffle(Ve.begin(),Ve.end());


//    R1.entrenarRed(Ve, 1000, 0.001, 0.09, 5, 0.5);
//    cout<<"Porcentaje de aciertos: "<<endl;
//    cout<<R1.probarRed(Vp) * 100<<" %";
//    getchar();

#endif

#if 0 /* ---- Con Perceptron multicapa----  */
    /* ---- 112 iteraciones con 95% de aciertos----  */
    vector<short> neuronasPorCapa;
    neuronasPorCapa.push_back(5);
    neuronasPorCapa.push_back(3);

    Red R2(neuronasPorCapa, 0.001, 4);

    cout<<endl;
    cout<<"Resultados de XOR con MLP: "<<endl;
    float aciertos=(1 - R2.entrenar(Ve, Vp, 1000, 0.05)) *100;

    cout<<endl<<"Porcentaje de aciertos: "<<aciertos<<endl;

#endif

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if 0   /** Problema CLOUDS **/
    /*75 % de aciertos con 50 iteraciones, varia dependiendo de como se inicializa */
    vector<short> neuronas;
    neuronas.push_back(3);
    neuronas.push_back(2);

    Red_RBF R1(2, neuronas, 0.001);

    vector<vector<float> > Ve;
    vector<vector<float> > Vp;

    vector<conjuntoDatos> C = particionar("data/clouds.csv",1,80,19,1);
    Ve = C[0].entrenamiento;
    Vp = C[0].prueba;

//    R1.entrenarRed(Ve, 200, 0.001, 0.2, 2, 0);
//    cout<<"Porcentaje de aciertos: "<<endl;
//    cout<<R1.probarRed(Vp) * 100<<" %";

//    getchar();
#endif

#if 0
 /* ---- Con Perceptron multicapa----  */
 /* ----92% de aciertos con 300 iteraciones----  */
    vector<short> neuronasPorCapa;
    neuronasPorCapa.push_back(12);
    neuronasPorCapa.push_back(2);

    Red R2(neuronasPorCapa, 0.001, 2);
    R2.set_alfa(0.0008);

    cout<<endl;
    cout<<"Resultados de XOR con MLP: "<<endl;
    float aciertos=(1 - R2.entrenar(Ve, Vp, 1000, 0.05)) *100;

    cout<<endl<<"Porcentaje de aciertos: "<<aciertos<<endl;

#endif

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


#if 0  /** Problema PHONEME **/
    /* 80% de aciertos en 100 iteraciones*/
    vector<short> neuronas;
    neuronas.push_back(5);
    neuronas.push_back(2);

    Red_RBF R1(5,neuronas,0.01);

    vector<vector<float> > Ve;
    vector<vector<float> > Vp;
    parseCSV<float>("data/phoneme.csv",Ve);

    vector<conjuntoDatos> C = particionar("data/phoneme.csv",1,80,19,1);
    Ve = C[0].entrenamiento;
    Vp = C[0].prueba;


    R1.entrenarRed(Ve, 100, 0.001, 0.2, 1, 0);
    cout<<"Porcentaje de aciertos: "<<endl;
    cout<<R1.probarRed(Vp) * 100<<" %";

    getchar();
#endif

#if 0
 /* ---- Con Perceptron multicapa----  */
 /* 84% de aciertos en 150 iteraciones */
    vector<short> neuronasPorCapa;
    neuronasPorCapa.push_back(6);
    neuronasPorCapa.push_back(3);
    neuronasPorCapa.push_back(2);

    Red R2(neuronasPorCapa, 0.01, 5);
    R2.set_alfa(0.008);
    cout<<endl;
    cout<<"Resultados de XOR con MLP: "<<endl;
    float aciertos=(1 - R2.entrenar(Ve, Vp, 1000, 0.05)) *100;

    cout<<endl<<"Porcentaje de aciertos: "<<aciertos<<endl;

#endif



return 0;
}
