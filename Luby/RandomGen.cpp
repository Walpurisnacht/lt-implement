#include "RandomGen.h"





void RandomGen::InitCDF()
{
    double Z = 1;
    for (int i = 1; i<=K; ++i)
        Z+= NNF(i);
    for (int i = 1; i<=K; ++i)
        M[i]=M[i-1] + RSD(i)/Z;
}



int RandomGen::BinarySearch(int n, double u)
{
    int left = 0, right = n, mid;
    do
    {
        mid = (left + right)/2;
        if ( M[mid] < u )
            if ( M[mid+1] >= u )
                return mid+1;
            else
                left = mid + 1;
        else
        if ( M[mid] > u )
        {
            if ( M[mid-1] <= u )
                return mid;
            else
                right = mid - 1;
        }
    }
    while(left <= right);
    return mid;
}



void RandomGen::RandomGenerator() /// RandomGenerator d va seed.
{
    double temp;
    Random *pseudo = new Random;
    pseudo -> setSeed(seed);
    temp = (double)pseudo -> nextInt()/(double)pseudo -> getMAX_RAND();
    degree = BinarySearch(K,temp);
    seed = pseudo -> getState();
    delete pseudo;
}
