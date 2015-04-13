#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "RandomClass.h"

using namespace std;

class RandomGenerator{
private:
  double ISD(int i)     /// Ideal Soliton Distribution
{
    if(i==1)
        return 1/(double)K;
    return 1/(double)(i*(i-1));
}

double NNF(int i)    /// non-negative function
{
    if (i < (int)((double)K/S))
        return S/(double)((double)K*(double)i);
    else if ( i == (int)((double)K/S) )
            return S*log(S/delta)/(double)K;
    return 0;
}

double RSD(int i)    ///  Robust Soliton Distribution
{
    return ISD(i)+NNF(i);
}

public:
void InitCDF(double M[])   /// Generate Array M
{
    double Z = 1;
    for (int i = 1; i<=K; ++i)
        Z+= NNF(i);
    M[0] = 0;
    for (int i = 1; i<=K; ++i)
        M[i]=M[i-1] + RSD(i)/Z;
}

int BinarySearch(double M[], int n, double u)
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
            if ( M[mid-1] <= u )
                return mid;
            else
                right = mid - 1;
    }
    while(left <= right);
    return mid;
}
};
