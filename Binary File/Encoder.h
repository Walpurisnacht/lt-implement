#include <LT.h>
#include <RandomGenerator.h>

double M[K+1];

void ReadData(MB_BLOCK *data)
{
    FILE *read;
    read = fopen(input,readbin);
    for (int i = 0; i < K; i++)
        fread(&data,sizeof(MB_BLOCK),K,read);
    fclose(read);
}

void Encoding_MB_BLOCK(MB_BLOCK &encode, MB_BLOCK *data, int degree, uint32_t seed)
{
    Random pseudo;
    pseudo.getSeed(seed);
    uint32_t temp = pseudo.nextInt() % 101;
    encode = data[temp];
    while(--degree)
    {
        temp = pseudo.nextInt() % 101;
        encode = encode ^ data[i];
    }
}
void Encoding()
{
    uint32_t seed = 2067261;
    int degree;
    InitCDF(M);
    MB_BLOCK *data = new MB_BLOCK[K];
    ReadData(data);
    ENCODING_BLOCK *encode = new ENCODING_BLOCK[K];
    for(int i = 0; i < K; ++i)
    {
        RandomGenerator(M,degree,seed);
        encode[i].d = degree;
        encode[i].seed = seed;
        Encoding_MB_BLOCK(encode[i].DATA,data,degree,seed);
    }
};
