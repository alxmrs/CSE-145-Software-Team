#include "FFT.h"
#include "error.h"
#include <cmath>
#include <thread>

#define ISPOW2(x) (x && !(x & (x-1)))

template<typename TYPE>
Complex* FFT(TYPE* A, int N)
{
    //If A only contains one element, return but as a complex type
    if (N == 1)
    {
        Complex* A_complex = new Complex[1];
        A_complex[0]       = Complex((double)A[0], 0.0);
        
        return A_complex;
    }
    
    //... proceed with FFT. N must be a power of 2 for logarithmic separation
    else if (ISPOW2(N))
    {
        //Store Nth root of unit
        Complex w  = Complex(1, 0);
        Complex wn = Complex(1, 2*M_PI/N, "polar");
        
        //Sub arrays for even indices and off indices
        TYPE A0[N/2];
        TYPE A1[N/2];
        
        for(int i=0; i<N/2; i++)
        {
            A0[i] = A[i*2];
            A1[i] = A[i*2+1];
        }
        
        //Complex sub arrays returned from FFT using TYPE sub arrays
        Complex* y0 = FFT(A0, N/2);
        Complex* y1 = FFT(A1, N/2);
        
        Complex * y = new Complex[N];
        
        //Merge sub arrays by applying root of unit
        for(int k=0; k<N/2; k++)
        {
            w        = w*wn;
            y[k]     = y0[k] + w*y1[k];
            y[k+N/2] = y0[k] - w*y1[k];
        }
        
        delete[] y0,
        delete[] y1;
        
        return y;
    }
    
    //If N is not a power of 2 then the logarithmic separation is impossible
    //Prevent a seg fault by returning error
    else
    {
        error("Input array to FFT must be of size N where N is a power of 2.", -1);
        return NULL;
    }
}

