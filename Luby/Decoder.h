#ifndef DECODER_H_INCLUDED
#define DECODER_H_INCLUDED

#include "RandomGen.h"
#include <bits/stdc++.h>



std::list<int32_t>::iterator ListSearch(std::list<int32_t>, int32_t); /* Search member from list + return list iterator */



void ReadES(std::list<ENCODING_BLOCK>&); /* Read EB from encoded file */



void FormGraph(std::list<ENCODING_BLOCK>, std::list<int32_t>*, DECODING_BLOCK*); /* Form graph of input symbol and encoding symbol */



void Decoding_ENCODING_BLOCK(std::list<ENCODING_BLOCK>, std::list<int32_t>*); /* Random back list of input symbol embeded in encoding symbol*/



bool ScanList(int32_t, std::list<int32_t>); /* Ripple search + return bool value */



void ScanDeg(DECODING_BLOCK*, MB_BLOCK*, std::list<int32_t> &, std::list<int32_t>); /* Scan ripple and release symbol with d = 1*/



void Decoding();


void RestoreOrigin(); /* Restore original file */
#endif // DECODER_H_INCLUDED

