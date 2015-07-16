#ifndef DECODER_H_INCLUDED
#define DECODER_H_INCLUDED

#include "RandomGen.h"
#include <bits/stdc++.h>

bool IntCmpr(const uint32_t& first, const uint32_t& second);



std::list<uint32_t>::iterator ListSearch(std::list<uint32_t> ui31_l_blockpos, uint32_t n);



void ReadES(std::list<ENCODING_BLOCK> &data);



void ReInitBool(bool* check, Random* pseudo, uint32_t ui32_seed, uint32_t &temp);



void FormGraph(std::list<ENCODING_BLOCK> data, std::list<uint32_t> *ui31_l_blockpos, DECODING_BLOCK *gdata);



void Decoding_ENCODING_BLOCK(std::list<ENCODING_BLOCK> data, std::list<uint32_t> *ui31_l_blockpos);



bool ScanList(uint32_t n, std::list<uint32_t> ripple);



void ScanDeg(DECODING_BLOCK *gdata, MB_BLOCK *odata, std::list<uint32_t> &ripple, std::list<uint32_t> offripple);



void Decoding();



#endif // DECODER_H_INCLUDED

