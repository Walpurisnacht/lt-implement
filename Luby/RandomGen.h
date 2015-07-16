#ifndef RANDOMGEN_H_INCLUDED
#define RANDOMGEN_H_INCLUDED

#include "Luby.h"

extern uint32_t block,f_size;
extern const float C;
extern const float DELTA;
extern const uint32_t SIZE;

inline double S(double x)
{
    return ((double)C*log((double)(x)/(double)DELTA)*sqrt((double)(x)));
}

class RandomGen
{

private:

    double* _M = new double[f_size+1];
    uint32_t _degree;
    uint32_t _ui32_seed;


    double ISD(uint32_t i)     /// Ideal Soliton Distribution
    {
        if(i==1)
            return 1/(double)f_size;
        return 1/(double)(i*(i-1));
    }



    double NNF(uint32_t i)    /// non-negative function
    {
        if (i < (uint32_t)((double)f_size/(double)S(f_size)))
            return (double)S(f_size)/(double)((double)f_size*(double)i);
        else if ( i == (uint32_t)((double)f_size/(double)S(f_size)) )
                return (double)S(f_size)*log(S(f_size)/DELTA)/(double)f_size;
        return 0;
    }




    double RSD(uint32_t i)    ///  Robust Soliton Distribution
    {
        return ISD(i)+NNF(i);
    }



    uint32_t BinarySearch(uint32_t , double);



    void InitCDF();   /// Generate Array _M



public:


    RandomGen()
    {
        for(uint32_t i = 0; i <=f_size; ++i)
            _M[i] = 0;
        InitCDF();
    }


    void RandomGenerator(); /// RandomGenerator ui32_deg va _ui32_seed.


    void setSeed(uint32_t s)
    {
        _ui32_seed = s;
    }



    uint32_t getDegree()
    {
        return _degree;
    }



    uint32_t getSeed()
    {
        return _ui32_seed;
    }
};


#endif // RANDOMGEN_H_INCLUDED
