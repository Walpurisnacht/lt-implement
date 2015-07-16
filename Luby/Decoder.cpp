#include "Decoder.h"
#include "Encoder.h"
#include "Luby.h"

///uint32_t BoolChk(uint32_t *check)
///{
///    for (uint32_t i = 0; i < block; i++)
///
///}

extern uint32_t block,f_size;
extern const uint32_t SIZE;

bool IntCmpr(const uint32_t& first, const uint32_t& second)
{
    return first < second;
}

std::list<uint32_t>::iterator ListSearch(std::list<uint32_t> ui31_l_blockpos, uint32_t n)
{
    return std::lower_bound(ui31_l_blockpos.begin(),ui31_l_blockpos.end(),n);
}

void ReadES(std::list<ENCODING_BLOCK> &data) ///done
{
    FILE *read;
    read = fopen("encoded.lt","rb");
    ENCODING_BLOCK buffer;
    block = 0;
    while(!feof(read))
    {
        if (!fread(&buffer,sizeof(ENCODING_BLOCK),1,read)) break;
        data.push_back(buffer);
        block++;
    }
    ///debug///
    std::cout << block << std::endl;
    ///debug///
    fclose(read);
}

void ReInitBool(bool* check, Random* pseudo, uint32_t ui32_seed, uint32_t &temp)
{
    for (uint32_t i = 0; i < f_size; i++) check[i] = false;
    pseudo -> setSeed(ui32_seed);
    temp = pseudo -> nextInt() % f_size;
    check[temp] = true;
}

void FormGraph(std::list<ENCODING_BLOCK> data, std::list<uint32_t> *ui31_l_blockpos, DECODING_BLOCK *gdata)
{
    ///for (uint32_t i = 0; i < block; i++)
    std::list<ENCODING_BLOCK>::iterator it;
    uint32_t i;
    for (it = data.begin(), i = 0; it != data.end(); it++, i++)
    {
        gdata[i].EB_encode = *it;
        gdata[i].ui31_l_blockpos = ui31_l_blockpos[i];
        ///ui32_deg from EB_encode;
    }
    extern bool test;
    ///debug
    if (test)
    {
        using namespace std;
        ofstream tr;
        tr.open("readlist.txt");

        for (uint32_t i = 0; i < block; i++)
        {
            cout << "Block: " << i+1 << endl;
            cout << "Degree: " << gdata[i].EB_encode.ui32_deg << endl;
            cout << "Filesize: " << gdata[i].EB_encode.ui64_f_size << endl;
            cout << "Seed: " << gdata[i].EB_encode.ui32_seed << endl;

            tr  << "Block: " << i+1
                << "\nDegree: " << gdata[i].EB_encode.ui32_deg
                << "\nFilesize: " << gdata[i].EB_encode.ui64_f_size
                << "\nSeed: " << gdata[i].EB_encode.ui32_seed
                << "\nPosition: ";

            list<uint32_t>::iterator jt;
            cout << "Position: ";
            for (jt = gdata[i].ui31_l_blockpos.begin(); jt != gdata[i].ui31_l_blockpos.end(); jt++)
            {
                cout << *jt << " ";
                tr << *jt << " ";
            }
            cout << "\n-------------------" << endl;
            tr << "\n-------------------" << endl;

        }
        tr.close();
        exit(1);
    }
    ///debug
    data.clear();
    delete ui31_l_blockpos;

}

void Decoding_ENCODING_BLOCK(std::list<ENCODING_BLOCK> data, std::list<uint32_t> *ui31_l_blockpos) ///done
{
    {
///    bool *check = new bool[block];
///    check = ReInitBool(check);
///
///            ///-Test-///
//////    for (uint32_t i = 0; i < block; i++)
//////        std::cout << check[i] << std::endl;
//////    system("pause");
///    ///------///
///    Random *pseudo = new Random;
///    pseudo -> setSeed(ui32_seed);
///    uint32_t temp = pseudo -> nextInt() % block;
///
///    check[temp] = true;
    }

    bool *check = new bool[f_size];
    Random *pseudo = new Random;
    uint32_t temp;

    ///clock_t t = clock();
    std::list<ENCODING_BLOCK>::iterator it;
    uint32_t i;
    for (it = data.begin(), i = 0; it != data.end(); it++, i++)
    {
        ReInitBool(check,pseudo,(*it).ui32_seed,temp);
        uint32_t deg = (*it).ui32_deg;

        ui31_l_blockpos[i].push_back(temp);

        while (--deg)
        {
            while (check[temp]) temp = pseudo -> nextInt() % f_size;
            check[temp] = true;

            ui31_l_blockpos[i].push_back(temp);
        }
        ui31_l_blockpos[i].sort(IntCmpr);
    }

{
///    for (uint32_t i = 0; i < block; i++)
///    {
///
///        ReInitBool(check,pseudo,data[i].ui32_seed,temp);
///        uint32_t ui32_deg = data[i].ui32_deg;
///        ui31_l_blockpos[i].push_back(temp);
///        while (--ui32_deg)
///        {
///            while(check[temp]) temp = pseudo -> nextInt() % block;
///            check[temp] = true;
///
///            ui31_l_blockpos[i].push_back(temp);
///        }
///        ui31_l_blockpos[i].sort(IntCmpr);
///    }

    ///Debug///
    /*std::list<uint32_t>::iterator it;
    for (uint32_t i = 0; i < block; i++)
    {
        std::cout << ui31_l_blockpos[i].size() << std::endl;
        for (it = ui31_l_blockpos[i].begin(); it != ui31_l_blockpos[i].end(); ++it)
            std::cout << *it << " ";
        system("pause");
    }*/

    ///t = clock() - t;
    ///std::cout << (float)t/CLOCKS_PER_SEC <<std::endl;
}

//    return ui31_l_blockpos;
}

bool ScanList(uint32_t n, std::list<uint32_t> ripple)
{
    std::list<uint32_t>::iterator it;
    for (it = ripple.begin(); it != ripple.end(); it++)
        if (*it == n) return true;
    return false;
}

void ScanDeg(DECODING_BLOCK *gdata, MB_BLOCK *odata, std::list<uint32_t> &ripple, std::list<uint32_t> offripple)
{
    for (uint32_t i = 0; i < block; i++)
    {
        //std::cout << gdata[i].EB_encode.ui32_deg << "-" << *gdata[i].ui31_l_blockpos.begin() << std::endl;
        if (gdata[i].EB_encode.ui32_deg == 1)
        {
            uint32_t tmp = *gdata[i].ui31_l_blockpos.begin(); ///position of ui32_deg=1 encoding symbol
            ///odata[tmp] = gdata[i].EB_encode.MB_DATA; ///XOR data to original position
            for (uint32_t j = 0; j < SIZE; ++j)
                odata[tmp].c_byte[j] = gdata[i].EB_encode.MB_DATA.c_byte[j];

            ///debug///
//            std::cout << "Block: " << tmp << std::endl;
//            for (uint32_t i = 0; i < 10; i++)
//            std::cout << odata[tmp].c_byte[i] << std::endl;
//            system("pause");
            ///debug///
            gdata[i].EB_encode.ui32_deg--;
            if (!ScanList(tmp,ripple) && !ScanList(tmp,offripple))  ripple.push_back(tmp); ///push position in ripple

            {
            ///debug///
            /*
            using namespace std;
            cout << "Position: " << i << endl;
            cout << "Degree: " << gdata[i].EB_encode.ui32_deg << endl;
            list<uint32_t>::iterator ri,ori;
            cout << "Ripple: ";
            for (ri = ripple.begin(); ri != ripple.end(); ri++)
            {
                cout << *ri << " ";
            }
            cout << "\nOffripple: ";
            for (ori = offripple.begin(); ori != offripple.end(); ori++)
            {
                cout << *ori << " ";
            }
            cout << "\n----------" << endl;
            system("pause");*/
            ///debug///
            }

        }
    }
}



void Decoding()
{
    std::list<ENCODING_BLOCK> data;
    ReadES(data); ///block get!

    uint64_t _size = (*data.begin()).ui64_f_size;

    std::list<uint32_t> *ui31_l_blockpos = new std::list<uint32_t>[block]; ///array of block_pos for each es
    Decoding_ENCODING_BLOCK(data,ui31_l_blockpos);

    ///Test///
///    std::list<uint32_t>::iterator it;
///    for (it = ui31_l_blockpos[0].begin(); it != ui31_l_blockpos[0].end(); ++it)
///        std::cout << *it << " ";
    ///Test///

    DECODING_BLOCK *gdata = new DECODING_BLOCK[block];
    FormGraph(data,ui31_l_blockpos,gdata); ///main is gdata, deleted former

    ///Test///
///    std::list<uint32_t>::iterator it;
///    for (it = gdata[0].ui31_l_blockpos.begin(); it != gdata[0].ui31_l_blockpos.end(); ++it)
///    std::cout << *it << " ";
///    std::cout << gdata[0]._d;
    ///Test///

    ///Main decoder///
    ///uint32_t *check = new uint32_t[block]; /// 0 = out 1 = in 2 = off ripple
    ///for (uint32_t i = 0; i < block; i++) check[i] = 0;

    MB_BLOCK *odata = new MB_BLOCK[block]; ///INIT BLANK ORIGINAL MB_DATA
///    MB_BLOCK *buffer = new MB_BLOCK;
///    std::fill(buffer->c_byte,buffer->c_byte+SIZE,0);
///    std::fill(odata,odata+block,buffer);
    for (uint32_t i = 0; i < block; i++)
        std::fill(odata->c_byte,odata->c_byte+SIZE,0);


    std::list<uint32_t> ripple;
    std::list<uint32_t> offripple;
    clock_t t = clock(); ///offripple.size()!=_size && it != ripple.end()
    while(1) ///stop when ripple is empty
    {
        std::list<uint32_t>::iterator it;
        ScanDeg(gdata,odata,ripple,offripple); ///work

        if (offripple.size() == _size) break;
        if (ripple.size() == 0) {std::cout << "Decode failed!"; return;} ///release ui32_deg = 1 encoding symbols and add them to ripple
        for (it = ripple.begin(); it != ripple.end();) ///process ripple
        {
            ///std::list<uint32_t>::iterator _posit;
            for (uint32_t z  = 0; z < block; z++)///update
            {
                if (!ScanList(*it,gdata[z].ui31_l_blockpos)) continue;
                uint32_t _bget = *it;
                gdata[z].ui31_l_blockpos.remove(*it); ///remove position which is in ripple
                gdata[z].EB_encode.ui32_deg--;

                XOR(gdata[z].EB_encode.MB_DATA.c_byte,odata[_bget].c_byte,gdata[z].EB_encode.MB_DATA.c_byte,SIZE);

//                ScanDeg(gdata,odata,ripple,offripple); ///update ripple + release encoding symbol
            }
            std::list<uint32_t>::iterator tmp;
            tmp = it;
            it++;
            offripple.push_back(*tmp);
            offripple.unique();
            ripple.erase(tmp); ///remove first member of ripple (proccessed)
            {
            ///debug///
            /*
            std::cout << "Ripple: ";
            for (std::list<uint32_t>::iterator ri = ripple.begin(); ri != ripple.end(); ri++)
                std::cout << *ri << " ";
            std::cout << "Offripple: ";
            for (std::list<uint32_t>::iterator ori = offripple.begin(); ori != offripple.end(); ori++)
                std::cout << *ori << " ";
            std::cout << "\n----------" << std::endl;
            system("pause"); */
            ///debug///
            }

        }
    }
    t = clock() - t;
    std::cout << (float)t/CLOCKS_PER_SEC <<std::endl;
    {
    ///debug///
    /*for (uint32_t i = 0; i < f_size; i++)
        {
            for (uint32_t j = 0; j < 26; j++)
                std::cout << odata[i].c_byte[j] << std::endl;
            system("pause");
        }
    */
    ///debug///
    }


    ///write back
    FILE *writebin;
    writebin = fopen("original.bin","wb");
//    fwrite(odata,sizeof(MB_BLOCK),sizeof(odata),writebin);
    for (uint32_t i = 0; i < f_size; i++)
        fwrite(&odata[i],sizeof(MB_BLOCK),1,writebin);
    fclose(writebin);
    std::cout << "Decode completed!";
}
