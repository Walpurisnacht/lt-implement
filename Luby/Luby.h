#ifndef LUBY_H_INCLUDED
#define LUBY_H_INCLUDED

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <list>
#include <bits/stdc++.h>

extern int K,k;

#define C 0.1
#define DELTA 0.5
#define SIZE 1024*1024
#define S(x) ((double)C*log((double)(x)/(double)DELTA)*sqrt((double)(x)))



template <class T>
void XOR(char* input1, char* input2, char* output, unsigned int s)
{

    T* in1 = (T*) input1;
    T* in2 = (T*) input2;
    T* out = (T*) output;
    unsigned int n = s/sizeof(T);
    unsigned int d = sizeof(T)*n;
    for (register unsigned int i = 0; i<n; ++i)
        out[i] = in1[i] ^ in2[i];
    if (d<s) XOR<char>(input1+d,input2+d,output+d,s-d);
}


template<class T>
void ReadData(T* data, const char* s)
{
    FILE* read;
    read = fopen(s,"rb");
    for (int i = 0; i < K; i++)
        fread(&data[i],sizeof(T),1,read);
    fclose(read);
}


typedef struct MB_BLOCK
{
    char byte[SIZE];
} MB_BLOCK;


typedef struct ENCODING_BLOCK
{
    int d;
    unsigned int filesize;
    uint32_t seed;
    MB_BLOCK DATA;
} ENCODING_BLOCK;


typedef struct RIPPLE
{
    bool checkin;
    bool checkout;
} RIPPLE;

typedef struct DECODING_BLOCK
{
    std::list<int> _block_pos;
    ENCODING_BLOCK _encode;
    //d from _encode;
} DECODING_BLOCK;

class Random
{
private:
    uint32_t M ;
    uint32_t A ;
    uint32_t state;
    uint32_t MAX_RAND ;
public:
    Random(): M(2147483647UL), A(16807), MAX_RAND(M-1)
    {}
    void setSeed(uint32_t s)
    {
        state = s;
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

#endif // LUBY_H_INCLUDED
