#include "Luby.h"

void XOR(char* c_input1, char* c_input2, char* c_output, int32_t i32_size)
{

    uint64_t* ui64_tmpin1 = (uint64_t*) c_input1;
    uint64_t* ui64_tmpin2 = (uint64_t*) c_input2;
    uint64_t* ui64_tmpout = (uint64_t*) c_output;

    uint64_t ui64_n = i32_size/sizeof(uint64_t);
    uint64_t ui64_d = sizeof(uint64_t)*ui64_n; /* Left over bits*/

    for (uint64_t i = 0; i<ui64_n; ++i) /* XOR bit by 64B */
        ui64_tmpout[i] = ui64_tmpin1[i] ^ ui64_tmpin2[i];

    if (ui64_d<(uint32_t)i32_size) /* XOR left over bit by char */
    {
        char* c_tmpin1 = (char*) c_input1+ui64_d;
        char* c_tmpin2 = (char*) c_input2+ui64_d;
        char* c_tmpout = (char*) c_output+ui64_d;
        uint64_t ui64_c_n = (i32_size-ui64_d)/sizeof(char);
        for (uint64_t i = 0; i<ui64_c_n; ++i)
            c_tmpout[i] = c_tmpin1[i] ^ c_tmpin2[i];
    }
}

uint64_t GetFileSize(std::string path)
{
    FILE *f_chk;
    f_chk = fopen(path.c_str(),"rb");
    fseek(f_chk,0,SEEK_END);
    uint64_t ui64_f_size = (uint64_t) ftell(f_chk);
    fclose(f_chk);
    return ui64_f_size;
}

bool IntCmpr(const int32_t& first, const int32_t& second)
{
    return first < second;
}

void Random::RandomBack(int32_t _deg, std::list<int32_t> &_block_pos)
{
    bool *check = new bool[f_size];
    for (int32_t i = 0; i < f_size; i++)
        check[i] = false;


    int32_t temp;
    temp = nextInt() % f_size;
    check[temp] = true;
    _block_pos.push_back(temp);

    while(--_deg)
    {
        while (check[temp])
            temp = nextInt() % f_size;
        check[temp] = true;
        _block_pos.push_back(temp);
    }

    _block_pos.sort(IntCmpr);


    delete check;
}
