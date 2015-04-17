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

    }

};
