#include "Encoder.h"
#include <bits/stdc++.h>

extern int K;

void Encoding_MB_BLOCK(MB_BLOCK &encode, MB_BLOCK *data, int degree, uint32_t seed)
{
    bool *check = new bool[K];
    for (int i = 0; i < K; i++)
        check[i] = false;

    //-Test-//
//    for (int i = 0; i < K; i++)
//        std::cout << check[i] << std::endl;
//    system("pause");
    //------//
    Random *pseudo = new Random;
    pseudo -> setSeed(seed);
    uint32_t temp = pseudo -> nextInt() % K;

    check[temp] = true;

//    std::cout << memcmp(&encode,&data[temp],sizeof(MB_BLOCK));
//    system("pause");

        //encode= data[temp];
    for (register int i = 0; i < SIZE; ++i)
        encode.byte[i] = data[temp].byte[i];

//    std::cout << memcmp(&encode,&data[temp],sizeof(MB_BLOCK));
//    system("pause");

    while(--degree)
    {
        while (check[temp])
        temp = pseudo -> nextInt() % K;
        //std::cout << temp << std::endl;
        //std::cout << data[temp].byte[0] << std::endl;
        check[temp] = true;
        XOR<long long>(encode.byte,data[temp].byte,encode.byte,SIZE);
        /*for (register int i = 0; i < SIZE; ++i)
        encode.byte[i] = encode.byte[i] ^ data[temp].byte[i];*/
    }

    delete pseudo;
    delete check;
}



void Encoding(int _tseed)
{
    MB_BLOCK *data = new MB_BLOCK[K];
    ReadData<MB_BLOCK>(data,"data.bin");
    ENCODING_BLOCK encode ;
    FILE *writebin;
    RandomGen *D = new RandomGen;
    D -> setSeed(_tseed);
    writebin = fopen("encoded.lt","wb");
    clock_t t = clock();
    for(int i = 0; i < K; ++i)
    {
        D -> RandomGenerator();
        encode.d = D -> getDegree();
        encode.seed = D -> getSeed();
        Encoding_MB_BLOCK(encode.DATA,data,encode.d,encode.seed);
        fwrite(&encode,sizeof(ENCODING_BLOCK),1,writebin);
    }
    t = clock() - t;
    std::cout << (float)t/CLOCKS_PER_SEC <<std::endl;
    fclose(writebin);
    delete data;
    delete D;
};
