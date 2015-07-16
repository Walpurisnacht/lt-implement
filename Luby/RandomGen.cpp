#include "RandomGen.h"





void RandomGen::InitCDF()
{
    double Z = 1;
    for (uint32_t i = 1; i<=f_size; ++i)
        Z+= NNF(i);
    for (uint32_t i = 1; i<=f_size; ++i)
        _M[i]=_M[i-1] + RSD(i)/Z;
}



uint32_t RandomGen::BinarySearch(uint32_t n, double u)
{
    uint32_t left = 0, right = n, mid;
    do
    {
        mid = (left + right)/2;
        if ( _M[mid] < u )
            if ( _M[mid+1] >= u )
                return mid+1;
            else
                left = mid + 1;
        else
        if ( _M[mid] > u )
        {
            if ( _M[mid-1] <= u )
                return mid;
            else
                right = mid - 1;
        }
    }
    while(left <= right);
    return mid;
}



void RandomGen::RandomGenerator() /// RandomGenerator ui32_deg va ui32_seed.
{
    double temp;
    Random *pseudo = new Random;
    pseudo -> setSeed(_ui32_seed);
    temp = (double)pseudo -> nextInt()/(double)pseudo -> getMAX_RAND();
    _degree = BinarySearch(f_size,temp);
    _ui32_seed = pseudo -> getState();
    delete pseudo;
}
