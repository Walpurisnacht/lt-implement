#ifndef ENCODER_H_INCLUDED
#define ENCODER_H_INCLUDED

#include "Luby.h"
#include "RandomGen.h"


void ReadData(MB_BLOCK *data);



void Encoding_MB_BLOCK(MB_BLOCK &encode, MB_BLOCK *data, int degree, uint32_t seed);



void Encoding();

#endif // ENCODER_H_INCLUDED
