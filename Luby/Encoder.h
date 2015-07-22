#ifndef ENCODER_H_INCLUDED
#define ENCODER_H_INCLUDED


#include "RandomGen.h"

void ReadD(MB_BLOCK data); /* Read data from source */



void Encoding_MB_BLOCK(MB_BLOCK &encode, MB_BLOCK *data, int32_t i32_deg, int32_t i32_seed, uint64_t ui64_f_size);



void Encoding(int32_t i32_seed);



void Init_EB(ENCODING_BLOCK &encode);  /* Initialize EB with all NULL char */

#endif // ENCODER_H_INCLUDED
