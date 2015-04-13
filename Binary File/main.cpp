#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <math.h>
#include "RandomClass.h"
#include "RandomGenerator.h"

using namespace std;

const unsigned long long size = 1024*1024;  //1MB = 1024*1024 byte

typedef char MB_BLOCK[size];

const int K = 100;
const float c = 0.1;
const double delta = 0.5;
const double S = c*log((double)K/delta)*sqrt((double)K);

double M[K+1];

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

int main()
{
    
}
