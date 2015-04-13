#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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
