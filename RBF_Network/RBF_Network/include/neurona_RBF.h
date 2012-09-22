#ifndef NEURONA_RBF_H
#define NEURONA_RBF_H

#include <vector>

using namespace std;

class neurona_RBF
{
    private:
        int N;
        vector<float> media;
        vector<float> desvio;

    public:
        neurona_RBF(int N);
        neurona_RBF(){} /// OJO! constructor vacio
};


#endif // NEURONA_RBF_H
