#include <iostream>
#include <LT.h>
#include <RandomGenerator.h>
#include <Encoder.h>

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




int main()
{
   Encoding();
}
