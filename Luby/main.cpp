#include "Encoder.h"
#include "Decoder.h"
#include <bits/stdc++.h>
#include <exception>

int K,k;
bool test = false;

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
    //ENCODING_BLOCK *data = new ENCODING_BLOCK[K];
    ENCODING_BLOCK buffer;
    std::list<ENCODING_BLOCK> data;
    FILE *rf;
    rf = fopen("encoded.lt","rb");
    int i=0;

    FILE *chk;
    chk = fopen("data.bin","rb");
    fseek(chk,0,SEEK_END);
    k = (unsigned int) ftell(chk) / (1024*1024);

    while(!feof(rf))
        {
            if (!fread(&buffer,sizeof(ENCODING_BLOCK),1,rf)) break;
            data.push_back(buffer);
            //std::cout << data[i].d << " " << data[i].seed << " " << data[i].DATA.byte[10] << std::endl;
            printf("%d %u %c %d\n",buffer.d,buffer.seed,buffer.DATA.byte[10],buffer.filesize);
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
    std::list<ENCODING_BLOCK>::iterator it;
    std::ofstream wr;
    wr.open("list.txt", std::ios::out);
    for (it = data.begin(); it != data.end(); it++)
        wr << (*it).d << " " << (*it).seed << " " << (*it).DATA.byte[10] << "\n";
//    for (int j = 0; j < i; j++)
//        wr << data[j].d << " " << data[j].seed << " " << data[j].DATA.byte[10] << "\n";
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
    //TestRead();
//    FILE *chk;
//    chk = fopen("data.bin","rb");
//    fseek(chk,0,SEEK_END);
//    k = (unsigned int) ftell(chk) / (1024*1024);
//    fclose(chk);
//    test = true;
//    Decoding();
//    K = 100;
//    Encoding(123456);




//    exit(9);

    //Main section//
    int n;

    if (argc == 1) return 0;

    if (!strcmp(argv[1],"-help"))
    {
        using namespace std;
        cout << "-make [filesize]" << endl;
        cout << "-encode [seed] [block]" << endl;
        cout << "-debug [tag]" << endl;
        cout << "[tag] : read" << endl;
    }
    else if (!strcmp(argv[1],"-make"))
    {
        MakeFile(k=atoi(argv[2])); // main makefile [filesize]
    }

    else if (!strcmp(argv[1],"-encode")) //main encode [seed] [K]
    {
        n = atoi(argv[2]); //initial seed
        K = atoi(argv[3]);
        FILE *chek;
        chek = fopen("data.bin","rb");
        fseek(chek,0,SEEK_END);
        k = (int) ftell(chek) / (1024*1024);
        fclose(chek);
        std::cout << k << std::endl;
        Encoding(n);
    }

    else if (!strcmp(argv[1],"-decode"))
    {
        FILE *chek;
        chek = fopen("data.bin","rb");
        fseek(chek,0,SEEK_END);
        k = (int) ftell(chek) / (1024*1024);
        fclose(chek);
        Decoding(); //ERROR
    }

    else if (!strcmp(argv[1],"-debug"))
    {
        if (!strcmp(argv[2],"read")) TestRead();
        if (!strcmp(argv[2], "decode")) {test = true; Decoding();}
    }

    return 0;
}
