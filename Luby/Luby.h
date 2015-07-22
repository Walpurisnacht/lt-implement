#ifndef LUBY_H_INCLUDED
#define LUBY_H_INCLUDED

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <list>

extern int32_t block,f_size;

/* List of constant using in Random module */
const float C = 0.1;
const float DELTA = 0.5;
const int32_t SIZE = 1 << 20;


/* List of tooltip */
void XOR(char* c_input1, char* c_input2, char* c_output, int32_t i32_size); /* Fast XOR operation */


uint64_t GetFileSize(std::string path); /* Get ui64_f_size in c_byte from path */


/* Declarations */
typedef struct MB_BLOCK
{
    char c_byte[SIZE];
} MB_BLOCK;


typedef struct ENCODING_BLOCK
{
    int32_t i32_deg;
    uint64_t ui64_f_size;
    int32_t i32_seed;
    MB_BLOCK MB_DATA;
} ENCODING_BLOCK;


typedef struct DECODING_BLOCK
{
    std::list<int32_t> i32_l_blockpos;
    ENCODING_BLOCK EB_encode;
} DECODING_BLOCK;

class Random
{
private:
    int32_t _M ;
    int32_t A ;
    int32_t _state;
    int32_t _MAX_RAND ;
public:
    Random(): _M(2147483647UL), A(16807), _MAX_RAND(_M-1)
    {}
    void setSeed(int32_t s)
    {
        _state = s;
    }

    int32_t getState()
    {
        return _state;
    }

    int32_t getMAX_RAND()
    {
        return _MAX_RAND;
    }

    int32_t nextInt()
    {
        int32_t next = (int32_t)(((uint64_t)_state * A) % _M);
        _state = next;
        return next;
    }

    void RandomBack(int32_t,std::list<int32_t>&);

};

#endif // LUBY_H_INCLUDED
