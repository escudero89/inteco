#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

namespace utilidades {
    float dot(vector<float> V1, vector<float> V2) {

        float sol = 0;

        if (V1.size() == V2.size()) {
            for (unsigned int i = 0; i < V1.size(); i++) {
                sol += V1[i] * V2[i];
            }
        } else {
            cout << "Error haciendo el producto escalar, distinta longitud.";
            exit (1);
        }

        return sol;
    }

    // Esto es para ver el archivo CSV (lo saque de internet, aun no lo vi)
    /*
    std::vector<std::string> getNextLineAndSplitIntoTokens(std::istream& str)
    {
        std::vector<std::string>   result;
        std::string                line;
        std::getline(str,line);

        std::stringstream          lineStream(line);
        std::string                cell;

        while(std::getline(lineStream,cell,','))
        {
            result.push_back(cell);
        }
        return result;
    }*/
}
