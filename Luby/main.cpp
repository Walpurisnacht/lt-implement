#include "Encoder.h"
#include "Decoder.h"
#include <bits/stdc++.h>

//Test function
void MakeFile(int filesize)
{
    MB_BLOCK buffer;
    for (int i = 0; i < SIZE; i++)
        buffer.byte[i]= 97 + i%26;
    FILE *output;
    output = fopen("data.bin","wb");
    for (int i = 0; i < filesize; ++i)
        fwrite(&buffer,sizeof(char),SIZE,output);
    fclose(output);
}

void TestRead()
{
    ENCODING_BLOCK *data = new ENCODING_BLOCK[K];
    FILE *rf;
    rf = fopen("encoded.lt","rb");
    std::ofstream wr;
    wr.open("list.txt");
    for (int i = 0; i < K; i++)
        {
            fread(&data[i],sizeof(ENCODING_BLOCK),1,rf);
            std::cout << data[i].d << " " << data[i].seed << " " << data[i].DATA.byte[10] << std::endl;
            wr <<data[i].d << " "<< data[i].seed << "\n";
        }
    fclose(rf);
    wr.close();
}

void TestList()
{
    ENCODING_BLOCK *data = new ENCODING_BLOCK[K];
    ReadES(data);
    Decoding_ENCODING_BLOCK(data);
}

int main()
{
    //MakeFile(100);
    //Encoding();
    //TestRead();
    //TestList();
    return 0;
}
