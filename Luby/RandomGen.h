#ifndef RANDOMGEN_H_INCLUDED
#define RANDOMGEN_H_INCLUDED

#include "Luby.h"

extern int K,k;

class RandomGen
{

private:

    double* M = new double[k+1];
    int degree;
    uint32_t seed;


    double ISD(int i)     /// Ideal Soliton Distribution
    {
        if(i==1)
            return 1/(double)k;
        return 1/(double)(i*(i-1));
    }



    double NNF(int i)    /// non-negative function
    {
        if (i < (int)((double)k/(double)S(k)))
            return (double)S(k)/(double)((double)k*(double)i);
        else if ( i == (int)((double)k/(double)S(k)) )
                return (double)S(k)*log(S(k)/DELTA)/(double)k;
        return 0;
    }




    double RSD(int i)    ///  Robust Soliton Distribution
    {
        return ISD(i)+NNF(i);
    }



    int BinarySearch(int , double);



    void InitCDF();   /// Generate Array M



public:


    RandomGen()
    {
        for(int i = 0; i <=k; ++i)
            M[i] = 0;
        InitCDF();
    }


    void RandomGenerator(); /// RandomGenerator d va seed.


    void setSeed(uint32_t s)
    {
        seed = s;
    }



    int getDegree()
    {
        return degree;
    }



    int getSeed()
    {
        return seed;
    }
};


#endif // RANDOMGEN_H_INCLUDED
