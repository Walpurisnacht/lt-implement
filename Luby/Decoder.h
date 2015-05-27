#ifndef DECODER_H_INCLUDED
#define DECODER_H_INCLUDED

#include "RandomGen.h"
#include <bits/stdc++.h>

bool IntCmpr(const int& first, const int& second);

std::list<int>::iterator ListSearch(std::list<int> _block_pos, int n);

void ReadES(std::list<ENCODING_BLOCK> &data);

void ReInitBool(bool* check, Random* pseudo, int seed, uint32_t &temp);

void FormGraph(std::list<ENCODING_BLOCK> data, std::list<int> *_block_pos, DECODING_BLOCK *gdata);

std::list<int>* Decoding_ENCODING_BLOCK(std::list<ENCODING_BLOCK> data, std::list<int> *_block_pos);

bool ScanList(int n, std::list<int> ripple);

void ScanDeg(DECODING_BLOCK *gdata, MB_BLOCK *odata, std::list<int> &ripple, std::list<int> offripple);

void Decoding();



#endif // DECODER_H_INCLUDED

