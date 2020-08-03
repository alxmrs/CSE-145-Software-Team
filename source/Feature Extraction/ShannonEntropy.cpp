#include "ShannonEntropy.h"
#include <map>
#include <algorithm>
#include <cmath>

template<typename TYPE>
double shannonEntropy(TYPE* input, int N)
{
    std::map<TYPE, int> frequencies;
    for (int i=0; i<N; i++)
        frequencies[input[i]]++;
    
    double freq, entropy = 0;
    for (std::pair<TYPE, int> p : frequencies)
    {
        freq     = (double)p.second/(double)N;
        entropy -= freq*log(freq)/log(2);
    }
    
    return entropy;
}