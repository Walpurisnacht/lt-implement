#include "Decoder.h"
#include "Encoder.h"
#include "Luby.h"

extern int32_t block,f_size;
extern std::string s_path;
//extern std::string e_path;
extern std::string o_path;

std::list<int32_t>::iterator ListSearch(std::list<int32_t> i32_l_blockpos, int32_t n) /* Search member from list + return list iterator */
{
    return std::lower_bound(i32_l_blockpos.begin(),i32_l_blockpos.end(),n);
}

void ReadES(std::list<ENCODING_BLOCK> &data) /* Read EB from encoded file */
{
    FILE *read;
    read = fopen(/*e_path*/s_path.c_str(),"rb");
    ENCODING_BLOCK buffer;
    block = 0;
    while(!feof(read))
    {
        if (!fread(&buffer,sizeof(ENCODING_BLOCK),1,read)) break;
        data.push_back(buffer);
        block++;
    }

    fclose(read);
}

void ReInitBool(bool* check, Random* pseudo, int32_t i32_seed, int32_t &temp) /* Re-init random assets */
{
    for (int32_t i = 0; i < f_size; i++) check[i] = false;
    pseudo -> setSeed(i32_seed);
    temp = pseudo -> nextInt() % f_size;
    check[temp] = true;
}

void RestoreOrigin() /* Restore original file */
{
    /* Read section */
    FILE* read;
    read = fopen("tmp.bin","rb");
    FILE* write;
    write = fopen(o_path.c_str(),"ab");

    int32_t _tmp_size;
    fread(&_tmp_size,sizeof(int32_t),1,read);  /* Original size from tmp */
    //std::cout << _tmp_size << std::endl;

    int32_t _d = _tmp_size/SIZE;
    //std::cout << _d << std::endl;

    for(int32_t i = 0; i < _d; i++) /* Rewrite with buffer in SIZE */
    {
        char* buffer = new char[SIZE];
        fread(&buffer,sizeof(buffer),1,read);
        fwrite(&buffer,sizeof(buffer),1,write);
    }

    for(; _d < _tmp_size; _d++) /* Rewrite left over bits */
    {
        char c_buffer;
        fread(&c_buffer,sizeof(char),1,read);
        fwrite(&c_buffer,sizeof(char),1,write);
    }

    fclose(read);

    fclose(write);

    if( remove( "tmp.bin" ) != 0 ) /* Delete temp file */
        perror( "Error deleting file" );
}

void FormGraph(std::list<ENCODING_BLOCK> data, std::list<int32_t> *i32_l_blockpos, DECODING_BLOCK *gdata) /* Form graph of input symbol and encoding symbol */
{
    ///for (int32_t i = 0; i < block; i++)
    std::list<ENCODING_BLOCK>::iterator it;
    int32_t i;
    for (it = data.begin(), i = 0; it != data.end(); it++, i++)
    {
        gdata[i].EB_encode = *it;
        gdata[i].i32_l_blockpos = i32_l_blockpos[i];
        ///i32_deg from EB_encode;
    }
    extern bool test;

    /* Debug */
    if (test)
    {
        using namespace std;
        ofstream tr;
        tr.open("readlist.txt");

        for (int32_t i = 0; i < block; i++)
        {
            cout << "Block: " << i+1 << endl;
            cout << "Degree: " << gdata[i].EB_encode.i32_deg << endl;
            cout << "Filesize: " << gdata[i].EB_encode.ui64_f_size << endl;
            cout << "Seed: " << gdata[i].EB_encode.i32_seed << endl;

            tr  << "Block: " << i+1
                << "\nDegree: " << gdata[i].EB_encode.i32_deg
                << "\nFilesize: " << gdata[i].EB_encode.ui64_f_size
                << "\nSeed: " << gdata[i].EB_encode.i32_seed
                << "\nPosition: ";

            list<int32_t>::iterator jt;
            cout << "Position: ";
            for (jt = gdata[i].i32_l_blockpos.begin(); jt != gdata[i].i32_l_blockpos.end(); jt++)
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
    //------//

    data.clear();
    delete i32_l_blockpos;

}

std::list<int32_t>* Decoding_ENCODING_BLOCK(std::list<ENCODING_BLOCK> data, std::list<int32_t> *i32_l_blockpos) /* Random back list of input symbol embeded in encoding symbol*/
{
    {
///    bool *check = new bool[block];
///    check = ReInitBool(check);
///
///            ///-Test-///
//////    for (int32_t i = 0; i < block; i++)
//////        std::cout << check[i] << std::endl;
//////    system("pause");
///    ///------///
///    Random *pseudo = new Random;
///    pseudo -> setSeed(i32_seed);
///    int32_t temp = pseudo -> nextInt() % block;
///
///    check[temp] = true;
    }

    ///bool *check = new bool[f_size];
    Random *pseudo = new Random;
    ///int32_t temp;

    ///clock_t t = clock();
    std::list<ENCODING_BLOCK>::iterator it;
    int32_t i;
    for (it = data.begin(), i = 0; it != data.end(); it++, i++)
    {
        /*ReInitBool(check,pseudo,(*it).i32_seed,temp);
        int32_t deg = (*it).i32_deg;

        i32_l_blockpos[i].push_back(temp);

        while (--deg)
        {
            while (check[temp]) temp = pseudo -> nextInt() % f_size;
            check[temp] = true;

            i32_l_blockpos[i].push_back(temp);
        }
        i32_l_blockpos[i].sort(IntCmpr);*/
        pseudo -> setSeed((*it).i32_seed);
        pseudo -> RandomBack((*it).i32_deg,i32_l_blockpos[i]);
    }

{
///    for (int32_t i = 0; i < block; i++)
///    {
///
///        ReInitBool(check,pseudo,data[i].i32_seed,temp);
///        int32_t degree = data[i].i32_deg;
///        i32_l_blockpos[i].push_back(temp);
///        while (--degree)
///        {
///            while(check[temp]) temp = pseudo -> nextInt() % block;
///            check[temp] = true;
///
///            i32_l_blockpos[i].push_back(temp);
///        }
///        i32_l_blockpos[i].sort(IntCmpr);
///    }

    ///Debug///
    /*std::list<int32_t>::iterator it;
    for (int32_t i = 0; i < block; i++)
    {
        std::cout << i32_l_blockpos[i].size() << std::endl;
        for (it = i32_l_blockpos[i].begin(); it != i32_l_blockpos[i].end(); ++it)
            std::cout << *it << " ";
        system("pause");
    }*/

    ///t = clock() - t;
    ///std::cout << (float)t/CLOCKS_PER_SEC <<std::endl;
}

    return i32_l_blockpos;
}

bool ScanList(int32_t n, std::list<int32_t> ripple) /* Ripple search + return bool value */
{
    std::list<int32_t>::iterator it;
    for (it = ripple.begin(); it != ripple.end(); it++)
        if (*it == n) return true;
    return false;
}

void ScanDeg(DECODING_BLOCK *gdata, MB_BLOCK *odata, std::list<int32_t> &ripple, std::list<int32_t> offripple) /* Check encoding symbol with d = 1 + release it */
{
    for (int32_t i = 0; i < block; i++)
    {
        //std::cout << gdata[i].EB_encode.i32_deg << "-" << *gdata[i].i32_l_blockpos.begin() << std::endl;
        if (gdata[i].EB_encode.i32_deg == 1)
        {
            int32_t tmp = *gdata[i].i32_l_blockpos.begin(); ///position of i32_deg=1 encoding symbol
            ///odata[tmp] = gdata[i].EB_encode.DATA; ///XOR data to original position
            for (register int32_t j = 0; j < SIZE; ++j)
                odata[tmp].c_byte[j] = gdata[i].EB_encode.MB_DATA.c_byte[j];

            ///debug///
//            std::cout << "Block: " << tmp << std::endl;
//            for (int32_t i = 0; i < 10; i++)
//            std::cout << odata[tmp].c_byte[i] << std::endl;
//            system("pause");
            ///debug///
            gdata[i].EB_encode.i32_deg--;
            if (!ScanList(tmp,ripple) && !ScanList(tmp,offripple))  ripple.push_back(tmp); ///push position in ripple

            {
            ///debug///
            /*
            using namespace std;
            cout << "Position: " << i << endl;
            cout << "Degree: " << gdata[i].EB_encode.i32_deg << endl;
            list<int32_t>::iterator ri,ori;
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

void Decoding() /* Implement of decoding process */
{
    std::list<ENCODING_BLOCK> data;
    ReadES(data); ///block get!

    int32_t _size = (int32_t)(*data.begin()).ui64_f_size; //Original size in bytes
    //TMP//
    std::cout << _size << std::endl;

    f_size = _size/SIZE;
    if (_size%SIZE != 0) f_size++; //MB blocks

    std::list<int32_t> *i32_l_blockpos = new std::list<int32_t>[block]; ///array of block_pos for each es
    Decoding_ENCODING_BLOCK(data,i32_l_blockpos); ///form list of input symbol

    ///Test///
///    std::list<int32_t>::iterator it;
///    for (it = i32_l_blockpos[0].begin(); it != i32_l_blockpos[0].end(); ++it)
///        std::cout << *it << " ";
    ///Test///

    DECODING_BLOCK *gdata = new DECODING_BLOCK[block];
    FormGraph(data,i32_l_blockpos,gdata); ///main is gdata, deleted former

    ///Test///
///    std::list<int32_t>::iterator it;
///    for (it = gdata[0].i32_l_blockpos.begin(); it != gdata[0].i32_l_blockpos.end(); ++it)
///    std::cout << *it << " ";
///    std::cout << gdata[0]._d;
    ///Test///

    ///Main decoder///
    ///int32_t *check = new int32_t[block]; /// 0 = out 1 = in 2 = off ripple
    ///for (int32_t i = 0; i < block; i++) check[i] = 0;

    MB_BLOCK *odata = new MB_BLOCK[block]; ///INIT BLANK ORIGINAL DATA
///    MB_BLOCK *buffer = new MB_BLOCK;
///    std::fill(buffer->c_byte,buffer->c_byte+SIZE,0);
///    std::fill(odata,odata+block,buffer);
    for (int32_t i = 0; i < block; i++)
        std::fill(odata->c_byte,odata->c_byte+SIZE,0);


    std::list<int32_t> ripple;
    std::list<int32_t> offripple;
    clock_t t = clock(); ///offripple.size()!=_size && it != ripple.end()
    while(1) ///stop when ripple is empty
    {
        std::list<int32_t>::iterator it;
        ScanDeg(gdata,odata,ripple,offripple); ///work

        if (offripple.size() == f_size) break;
        if (ripple.size() == 0) {std::cout << "Decode failed!"; return;} ///release i32_deg = 1 encoding symbols and add them to ripple
        for (it = ripple.begin(); it != ripple.end();) ///process ripple
        {
            ///std::list<int32_t>::iterator _posit;
            for (int32_t z  = 0; z < block; z++)///update
            {
                if (!ScanList(*it,gdata[z].i32_l_blockpos)) continue;
                int32_t _bget = *it;
                gdata[z].i32_l_blockpos.remove(*it); ///remove position which is in ripple
                gdata[z].EB_encode.i32_deg--;

                XOR(gdata[z].EB_encode.MB_DATA.c_byte,odata[_bget].c_byte,gdata[z].EB_encode.MB_DATA.c_byte,SIZE);

//                ScanDeg(gdata,odata,ripple,offripple); ///update ripple + release encoding symbol
            }
            std::list<int32_t>::iterator tmp;
            tmp = it;
            it++;
            offripple.push_back(*tmp);
            offripple.unique();
            ripple.erase(tmp); ///remove first member of ripple (proccessed)
            {
            ///debug///
            /*
            std::cout << "Ripple: ";
            for (std::list<int32_t>::iterator ri = ripple.begin(); ri != ripple.end(); ri++)
                std::cout << *ri << " ";
            std::cout << "Offripple: ";
            for (std::list<int32_t>::iterator ori = offripple.begin(); ori != offripple.end(); ori++)
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
    /*for (int32_t i = 0; i < f_size; i++)
        {
            for (int32_t j = 0; j < 26; j++)
                std::cout << odata[i].c_byte[j] << std::endl;
            system("pause");
        }
    */
    ///debug///
    }


    ///write back to tmp file
    FILE *writebin;
    writebin = fopen("tmp.bin","wb");
    fwrite(&_size,sizeof(int32_t),1,writebin);

    for (int32_t i = 0; i < f_size; i++)
        fwrite(&odata[i],sizeof(MB_BLOCK),1,writebin);
    fclose(writebin);
    std::cout << "Decode completed!";
    system("pause");
    delete(odata);
    RestoreOrigin();
}





