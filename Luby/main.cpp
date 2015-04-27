#include <iostream>
#include "Luby.h"
#include "RandomGen.h"
#include "Encoder.h"
using namespace std;

//Test function
void MakeFile(int filesize)
{
    MB_BLOCK buffer;
    for (int i = 0; i < SIZE; i++)
        buffer.byte[i]='a';
    FILE *output;
    output = fopen("data.bin","wb");
    for (int i = 0; i < filesize; ++i)
        fwrite(&buffer,sizeof(char),SIZE,output);
    fclose(output);
}

int main()
{
    //MakeFile(100);
    Encoding();
    return 0;
}
