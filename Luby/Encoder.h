#ifndef ENCODER_H_INCLUDED
#define ENCODER_H_INCLUDED


#include "RandomGen.h"


void ReadData(MB_BLOCK *data);



void Encoding_MB_BLOCK(MB_BLOCK &encode, MB_BLOCK *data, int degree, uint32_t seed);



void Encoding(int _tseed);

#endif // ENCODER_H_INCLUDED
