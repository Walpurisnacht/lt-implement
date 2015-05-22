#ifndef DECODER_H_INCLUDED
#define DECODER_H_INCLUDED

#include "RandomGen.h"
#include <bits/stdc++.h>


void ReadES(ENCODING_BLOCK* data);



std::list<int>* Decoding_ENCODING_BLOCK(ENCODING_BLOCK *data, std::list<int> _block_pos[100]);



void ReInitBool(bool* check, Random* pseudo, int seed, uint32_t &temp);



bool IntCmpr(const int& first, const int& second);



std::list<int>::iterator ListSearch(std::list<int> _block_pos, int n);


void Decoding();

void FormGraph(ENCODING_BLOCK *data, std::list<int> *_block_pos, DECODING_BLOCK *gdata);

int BoolChk(int *check);

#endif // DECODER_H_INCLUDED

