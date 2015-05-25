#include "Encoder.h"
#include "Decoder.h"
#include <bits/stdc++.h>

int K;

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
    std::cout << "Make file completed";
}

void TestRead()
{
    ENCODING_BLOCK *data = new ENCODING_BLOCK[K];
    FILE *rf;
    rf = fopen("encoded.lt","rb");
    int i=0;

    while(!feof(rf))
        {
            if (!fread(&data[i],sizeof(ENCODING_BLOCK),1,rf)) break;
            //std::cout << data[i].d << " " << data[i].seed << " " << data[i].DATA.byte[10] << std::endl;
            printf("%d %u %c\n",data[i].d,data[i].seed,data[i].DATA.byte[10]);
            //wr <<data[i].d << " "<< data[i].seed << "\n";
            i++;
        }
    std::cout << "Total blocks: " << i << std::endl;
    system("pause");
    fclose(rf);

//    FILE *wr;
//    wr = fopen("list.txt","w");
//    for (int j = 0; j < i; j++)
//    {
//        fscanf(wr,"%d %u %c",&data[i].d,&data[i].seed,&data[i].DATA.byte[10]);
//    }
    std::ofstream wr;
    wr.open("list.txt", std::ios::out);
    for (int j = 0; j < i; j++)
        wr << data[j].d << " " << data[j].seed << " " << data[j].DATA.byte[10] << "\n";
    std::cout << "Output completed!" << std::endl;
    wr.close();
}

//void TestList()
//{
//    ENCODING_BLOCK *data = new ENCODING_BLOCK[K];
//    ReadES(data);
//    //Decoding_ENCODING_BLOCK(data);
//}

int main(int argc, char* argv[])
{
    //IDE debug section//








    //Main section//
    int n;

    if (argc == 1) return 0;

    if (!strcmp(argv[1],"makefile"))
    {
        MakeFile(atoi(argv[2])); // main makefile [filesize]
    }

    else if (!strcmp(argv[1],"encode")) //main encode [seed] [K]
    {
        n = atoi(argv[2]); //initial seed
        K = atoi(argv[3]);
        std::cout << K;
        Encoding(n);
    }

    else if (!strcmp(argv[1],"debug"))
    {
        if (!strcmp(argv[2],"read")) TestRead();
    }

    return 0;
}
