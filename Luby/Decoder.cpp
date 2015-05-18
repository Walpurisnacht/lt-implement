#include "Decoder.h"

bool IntCmpr(const int& first, const int& second)
{
    return first < second;
}

list<int>::iterator ListSearch(std::list<int> _block_pos, int n)
{
    return std::lower_bound(_block_pos.begin(),_block_pos.end(),n);
}

void ReadES(ENCODING_BLOCK *data)
{
    FILE *read;
    read = fopen("encoded.lt","rb");
    for (int i = 0; i < K; i++)
        fread(&data[i],sizeof(ENCODING_BLOCK),1,read);
    fclose(read);
}

void ReInitBool(bool* check, Random* pseudo, int seed, uint32_t &temp)
{
    for (int i = 0; i < K; i++) check[i] = false;
    pseudo -> setSeed(seed);
    temp = pseudo -> nextInt() % K;
    check[temp] = true;
}

void Decoding_ENCODING_BLOCK(ENCODING_BLOCK *data)
{
    std::list<int> _block_pos[100];

//    bool *check = new bool[K];
//    check = ReInitBool(check);
//
//            //-Test-//
////    for (int i = 0; i < K; i++)
////        std::cout << check[i] << std::endl;
////    system("pause");
//    //------//
//    Random *pseudo = new Random;
//    pseudo -> setSeed(seed);
//    uint32_t temp = pseudo -> nextInt() % K;
//
//    check[temp] = true;
    bool *check = new bool[K];
    Random *pseudo = new Random;
    uint32_t temp;

    clock_t t = clock();

    for (int i = 0; i < K; i++)
    {

        ReInitBool(check,pseudo,data[i].seed,temp);
        int degree = data[i].d;
        _block_pos[i].push_back(temp);
        while (--degree)
        {
            while(check[temp]) temp = pseudo -> nextInt() % K;
            check[temp] = true;

            _block_pos[i].push_back(temp);
        }
        _block_pos[i].sort(IntCmpr);
    }

    //Debug//
    /*std::list<int>::iterator it;
    for (int i = 0; i < K; i++)
    {
        std::cout << _block_pos[i].size() << std::endl;
        for (it = _block_pos[i].begin(); it != _block_pos[i].end(); ++it)
            std::cout << *it << " ";
        system("pause");
    }*/

    t = clock() - t;
    std::cout << (float)t/CLOCKS_PER_SEC <<std::endl;




}
