#include "Encoder.h"
#include <bits/stdc++.h>

extern uint32_t block,f_size;
extern std::string s_path;
extern std::string o_path;

void Init_EB(ENCODING_BLOCK &encode) /* Initialize EB with all NULL char */
{
    for (uint32_t i = 0; i < SIZE; i++)
        encode.MB_DATA.c_byte[i] = '\0';
}

void ReadD(MB_BLOCK* data)  /* Read data from source */
{
    FILE* read;
    read = fopen(s_path.c_str(),"rb");
    for (uint32_t i = 0; i < block; i++)
        fread(&data[i],sizeof(MB_BLOCK),1,read);
    fclose(read);
}

void Encoding_MB_BLOCK(MB_BLOCK &encode, MB_BLOCK *data, uint32_t ui32_deg, uint32_t ui32_seed, uint64_t ui64_f_size)
{
    bool *check = new bool[f_size]; /* Improve randomness by reducing random redundancy */
    for (uint32_t i = 0; i < f_size; i++) /* Initialize flag array */
        check[i] = false;

    //-Test-//
/*
    for (uint32_t i = 0; i < block; i++)
    std::cout << check[i] << std::endl;
    system("pause");
*/
    //------//

    Random *pseudo = new Random; /* Initialize base number */
    pseudo -> setSeed(ui32_seed);
    uint32_t _tmp = pseudo -> nextInt() % f_size;

    check[_tmp] = true;

//    std::cout << memcmp(&encode,&data[_tmp],sizeof(MB_BLOCK));
//    system("pause");

//    encode= data[_tmp];
    for ( uint32_t i = 0; i < SIZE; ++i) /* Copy data to encode buffer */
        encode.c_byte[i] = data[_tmp].c_byte[i];

//    std::cout << memcmp(&encode,&data[_tmp],sizeof(MB_BLOCK));
//    system("pause");

    while(--ui32_deg) /* Implement of encoding process */
    {
        while (check[_tmp])
            _tmp = pseudo -> nextInt() % f_size;
        //std::cout << _tmp << std::endl;
        //std::cout << data[_tmp].c_byte[0] << std::endl;
        check[_tmp] = true;
        XOR(encode.c_byte,data[_tmp].c_byte,encode.c_byte,SIZE);
        //for (register uint32_t i = 0; i < SIZE; ++i)
        //encode.c_byte[i] = encode.c_byte[i] ^ data[_tmp].c_byte[i];
    }

    delete pseudo;
    delete check;
}



void Encoding(uint32_t ui32_seed)
{
    //-File size-//
    /*
    uint32_t _filesize = 0;
    _filesize = GetFileSize(s_path);
    std::cout << "File size data.bin in MB: " << _filesize/SIZE << std::endl;
    */
    //-----------//

    MB_BLOCK *data = new MB_BLOCK[f_size];
    ReadD(data);
    ENCODING_BLOCK encode ;
    Init_EB(encode);

    FILE *write;
    RandomGen *D = new RandomGen;
    D -> setSeed(ui32_seed);



    write = fopen(o_path.c_str(),"wb");
    clock_t t = clock();
    for(uint32_t i = 0; i < block; ++i)
    {
        D -> RandomGenerator();
        encode.ui32_deg = D -> getDegree();
        encode.ui32_seed = D -> getSeed();
        encode.ui64_f_size = (uint64_t) f_size;

        Encoding_MB_BLOCK(encode.MB_DATA,data,encode.ui32_deg,encode.ui32_seed,encode.ui64_f_size);
        fwrite(&encode,sizeof(ENCODING_BLOCK),1,write);
        Init_EB(encode);
    }
    t = clock() - t;
    std::cout << "Encoding time: " << (float)t/CLOCKS_PER_SEC <<std::endl;
    fclose(write);
    delete data;
    delete D;
};
