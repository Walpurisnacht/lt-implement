#include "RandomGen.h"





void RandomGen::InitCDF()
{
    double Z = 1;
    for (int32_t i = 1; i<=i32_f_size; ++i)
        Z+= NNF(i);
    for (int32_t i = 1; i<=i32_f_size; ++i)
        _M[i]=_M[i-1] + RSD(i)/Z;
}



int32_t RandomGen::BinarySearch(int32_t n, double u)
{
    int32_t left = 0, right = n, mid;
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



void RandomGen::RandomGenerator() /// RandomGenerator i32_deg va i32_seed.
{
    double temp;
    Random *pseudo = new Random;
    pseudo -> setSeed(_i32_seed);
    temp = (double)pseudo -> nextInt()/(double)pseudo -> getMAX_RAND();
    _degree = BinarySearch(i32_f_size,temp);
    _i32_seed = pseudo -> getState();
    delete pseudo;
}
