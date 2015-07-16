#include "Encoder.h"
#include "Decoder.h"
#include "Luby.h"
#include <bits/stdc++.h>
#include <exception>

uint32_t block,f_size; //f_size by MB
bool test = false;
std::string s_path,o_path;

int main(int argc, char* argv[])
{
    //IDE debug section//
//    s_path = "f:/wrong.png";
//    f_size = (GetFileSize(s_path)/SIZE);
//    if (GetFileSize(s_path)%SIZE != 0) f_size++;
//    o_path = "out.lt";
//    block = 100;
//    Encoding(123456);
//
//
//
//
//    exit(9);

    //Main section//
    int n;

    if (argc == 1) return 0;

    if (!strcmp(argv[1],"-help"))
    {
        using namespace std;
        cout << "-encode [ui32_seed] [block] [source path] [output path]" << endl;
        cout << "-decode [source path] [output path]" << endl;
        cout << "-debug [tag]" << endl;
        cout << "[tag] : decode" << endl;
    }

    else if (!strcmp(argv[1],"-encode")) //main encode [ui32_seed] [block]
    {
        n = atoi(argv[2]); //initial ui32_seed
        block = atoi(argv[3]);
        s_path = argv[4];
        o_path = argv[5];
        f_size = GetFileSize(s_path)/SIZE;
        if (GetFileSize(s_path)%SIZE != 0) f_size++;
        std::cout << "File size: " << f_size << "MB" << std::endl;
        Encoding(n);
    }

    else if (!strcmp(argv[1],"-decode"))
    {
        FILE *chek;
        chek = fopen("data.bin","rb");
        fseek(chek,0,SEEK_END);
        f_size = (int) ftell(chek) / (1024*1024);
        fclose(chek);
        Decoding(); //ERROR
    }

    else if (!strcmp(argv[1],"-debug"))
    {
        if (!strcmp(argv[2], "decode")) {test = true; Decoding();}
    }

    return 0;
}
