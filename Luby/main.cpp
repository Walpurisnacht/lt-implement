#include "Encoder.h"
#include "Decoder.h"
#include "Luby.h"
#include <bits/stdc++.h>
#include <exception>

int32_t block,f_size; //f_size by MB
bool test = false;
std::string s_path,o_path,e_path;

int main(int argc, char* argv[])
{
    //IDE debug section//
//    s_path = "f:/YUGIOH.rar";
//    e_path = "f:/YUGIOH.lt";
//    o_path = "f:/res.rar";
//    f_size = GetFileSize(s_path)/SIZE;
//    if (GetFileSize(s_path)%SIZE != 0) f_size++;
//    std::cout << "File size: " << f_size << "MB" << std::endl;
//    Decoding();
//    exit(9);

    //Main section//
    int n;

    if (argc == 1) return 0;

    if (!strcmp(argv[1],"-help"))
    {
        using namespace std;
        cout << "-encode [seed] [block] [source path] [output path]" << endl;
        cout << "-decode [source path] [encoded path] [output path]" << endl;
        cout << "-debug [tag]" << endl;
        cout << "[tag] : decode" << endl;
    }

    else if (!strcmp(argv[1],"-encode")) //main encode [i32_seed] [block]
    {
        n = atoi(argv[2]); //initial i32_seed
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
        s_path = argv[2];
        e_path = argv[3];
        o_path = argv[4];
        f_size = GetFileSize(s_path)/SIZE;
        if (GetFileSize(s_path)%SIZE != 0) f_size++;
        std::cout << "File size: " << f_size << "MB" << std::endl;
        Decoding();

    }

    else if (!strcmp(argv[1],"-debug"))
    {
        if (!strcmp(argv[2], "decode")) {test = true; Decoding();}
    }

    return 0;
}
