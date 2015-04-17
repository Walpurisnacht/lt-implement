#include <iostream>
#include <LT.h>
#include <RandomGenerator.h>

using namespace std;

void MakeFile(int filesize)
{
    MB_BLOCK buffer;
    FILE *output;
    output = fopen(input,writebin);
    for (int i = 0; i < filesize; ++i)
        fwrite(&buffer,sizeof(char),size,output);
    fclose(output);
}

void SplitBlock(int filesize)
{
    MB_BLOCK *data;
    data = new MB_BLOCK[filesize];
    FILE *read;
    read = fopen(input,readbin);
    for (int i = 0; i < filesize; i++)
        fread(&data,sizeof(MB_BLOCK),filesize,read);
    fclose(read);
    //chk
    //for (int i = 0; i < size; i++)
    //    cout << data[2][i];
    //cout << "DONE";
}


int main()
{
    /*int mb;
    cout << "Input file size: ";
    cin >> mb;*/
    //-----Make MB-----//
    //MakeFile(100);
    //system("pause");
    //-----Test random-----//
    Random pseudo;
    pseudo.setSeed(2067261);
    //cout << tmp << " " << (double) tmp/pseudo.getMAX_RAND() << endl;
    //double t = (double)tmp/pseudo.getMAX_RAND();
    //cout << t << endl;
    InitCDF(M);
    //for (int i = 1; i <= K; ++i)
        //cout << M[i] <<endl;
    for (int i = 1; i<= K; ++i)
    {
        uint32_t tmp = pseudo.nextInt();
        double t = (double)tmp/pseudo.getMAX_RAND();
        cout << BinarySearch(M,K,t) << endl;
    }
    //-----Split block-----//
    //SplitBlock(100);
}
