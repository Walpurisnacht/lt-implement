#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define K 100
#define c 0.1
#define delta 0.5

using namespace std;

const unsigned long long size = 1024*1024;  //1MB = 1024*1024 byte

typedef char MB_BLOCK[size];

const char* readbin = "rb";
const char* writebin = "wb";
const char* input = "data.bin";

double S = (double)c*log((double)K/(double)delta)*sqrt((double)K);

typedef struct ENCODING_BLOCK
{
    int d;
    uint32_t seed;
    MB_BLOCK DATA;
} ENCODING_BLOCK;

class Random{
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
