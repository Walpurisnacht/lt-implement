#ifndef RANDOMGEN_H_INCLUDED
#define RANDOMGEN_H_INCLUDED

#include "Luby.h"

extern int32_t block,f_size;
extern const float C;
extern const float DELTA;
extern const int32_t SIZE;

inline double S(double x)
{
    return ((double)C*log((double)(x)/(double)DELTA)*sqrt((double)(x)));
}

class RandomGen
{

private:

    double* _M = new double[f_size+1];
    int32_t _degree;
    int32_t _i32_seed;


    double ISD(int32_t i)     /// Ideal Soliton Distribution
    {
        if(i==1)
            return 1/(double)f_size;
        return 1/(double)(i*(i-1));
    }



    double NNF(int32_t i)    /// non-negative function
    {
        if (i < (int32_t)((double)f_size/(double)S(f_size)))
            return (double)S(f_size)/(double)((double)f_size*(double)i);
        else if ( i == (int32_t)((double)f_size/(double)S(f_size)) )
                return (double)S(f_size)*log(S(f_size)/DELTA)/(double)f_size;
        return 0;
    }




    double RSD(int32_t i)    ///  Robust Soliton Distribution
    {
        return ISD(i)+NNF(i);
    }



    int32_t BinarySearch(int32_t , double);



    void InitCDF();   /// Generate Array _M



public:


    RandomGen()
    {
        for(int32_t i = 0; i <=f_size; ++i)
            _M[i] = 0;
        InitCDF();
    }


    void RandomGenerator(); /// RandomGenerator i32_deg va _i32_seed.


    void setSeed(int32_t s)
    {
        _i32_seed = s;
    }



    int32_t getDegree()
    {
        return _degree;
    }



    int32_t getSeed()
    {
        return _i32_seed;
    }
};


#endif // RANDOMGEN_H_INCLUDED
