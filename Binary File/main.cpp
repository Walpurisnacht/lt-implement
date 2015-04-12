#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <math.h>

using namespace std;

const unsigned long long size = 1024*1024;  //1MB = 1024*1024 byte

typedef char MB_BLOCK[size];

const char* readbin = "rb";
const char* writebin = "wb";
const char* input = "data.bin";
const int K = 100;
const float c = 0.1;
const double delta = 0.5;
const double S = c*log((double)K/delta)*sqrt((double)K);

double M[K+1];

class Random {
private:
    uint32_t M ;
    uint32_t A ;
    uint32_t state;
    uint32_t MAX_RAND ;
public:
    Random(): M(2147483647UL), A(16807), MAX_RAND(M-1)
    {}
    void setSeed(uint32_t S)
    {
        state = S;
    }

    uint32_t getState()
    {
        return state;
    }

    uint32_t getMAX_RAND()
    {
        return MAX_RAND;
    }

    uint32_t nextInt()
    {
        uint32_t next = (uint32_t)(((uint64_t)state * A) % M);
        state = next;
        return next;
    }
};

void MakeFile(int filesize)
{
    MB_BLOCK buffer;
    FILE *output;
    output = fopen(input,writebin);
    for (int i = 0; i < filesize; ++i)
        fwrite(&buffer,sizeof(char),size,output);
    fclose(output);
}

void SplitBlock(int filesize)
{
    MB_BLOCK *data;
    data = new MB_BLOCK[filesize];
    FILE *read;
    read = fopen(input,readbin);
    for (int i = 0; i < filesize; i++)
        fread(&data,sizeof(MB_BLOCK),filesize,read);
    fclose(read);
    //chk
    //for (int i = 0; i < size; i++)
    //    cout << data[2][i];
    //cout << "DONE";
}
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

int main()
{
    /*int mb;
    cout << "Input file size: ";
    cin >> mb;*/
    //-----Make MB-----//
    //MakeFile(100);
    //system("pause");
    //-----Test random-----//
    Random pseudo;
    pseudo.setSeed(2067261);
    //cout << tmp << " " << (double) tmp/pseudo.getMAX_RAND() << endl;
    //double t = (double)tmp/pseudo.getMAX_RAND();
    //cout << t << endl;
    InitCDF(M);
    //for (int i = 1; i <= K; ++i)
        //cout << M[i] <<endl;
    for (int i = 1; i<= K; ++i)
    {
        uint32_t tmp = pseudo.nextInt();
        double t = (double)tmp/pseudo.getMAX_RAND();
        cout << BinarySearch(M,K,t) << endl;
    }
    //-----Split block-----//
    //SplitBlock(100);
}
