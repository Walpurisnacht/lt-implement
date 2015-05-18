#ifndef DECODER_H_INCLUDED
#define DECODER_H_INCLUDED

#include "RandomGen.h"
#include <bits/stdc++.h>

using namespace std;

void ReadES(ENCODING_BLOCK* data);

void Decoding_ENCODING_BLOCK(ENCODING_BLOCK *data);

void ReInitBool(bool* check, Random* pseudo, int seed, uint32_t &temp);

bool IntCmpr(const int& first, const int& second);

list<int>::iterator ListSearch(std::list<int> _block_pos, int n);

#endif // DECODER_H_INCLUDED

