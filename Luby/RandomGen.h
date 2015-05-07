#ifndef RANDOMGEN_H_INCLUDED
#define RANDOMGEN_H_INCLUDED

#include "Luby.h"

class RandomGen
{

private:

    static double M[K+1];
    int degree;
    uint32_t seed;


    static double ISD(int i)     /// Ideal Soliton Distribution
    {
        if(i==1)
            return 1/(double)K;
        return 1/(double)(i*(i-1));
    }



    static double NNF(int i)    /// non-negative function
    {
        if (i < (int)((double)K/(double)S))
            return (double)S/(double)((double)K*(double)i);
        else if ( i == (int)((double)K/(double)S) )
                return (double)S*log(S/DELTA)/(double)K;
        return 0;
    }




    static double RSD(int i)    ///  Robust Soliton Distribution
    {
        return ISD(i)+NNF(i);
    }



    int BinarySearch(int , double);


public:


    static void InitCDF();   /// Generate Array M


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
