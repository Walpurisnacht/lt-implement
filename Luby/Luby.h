#ifndef LUBY_H_INCLUDED
#define LUBY_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define K 100
#define C 0.1
#define DELTA 0.5
#define SIZE 1024*1024
#define S (double)C*log((double)K/(double)DELTA)*sqrt((double)K)


typedef struct MB_BLOCK
{
    char byte[SIZE];
} MB_BLOCK;


typedef struct ENCODING_BLOCK
{
    int d;
    uint32_t seed;
    MB_BLOCK DATA;
} ENCODING_BLOCK;


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
