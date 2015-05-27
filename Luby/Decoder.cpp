#include "Decoder.h"
#include "Encoder.h"
#include "Luby.h"

//int BoolChk(int *check)
//{
//    for (int i = 0; i < K; i++)
//
//}

extern int K;

bool IntCmpr(const int& first, const int& second)
{
    return first < second;
}

std::list<int>::iterator ListSearch(std::list<int> _block_pos, int n)
{
    return std::lower_bound(_block_pos.begin(),_block_pos.end(),n);
}

void ReadES(std::list<ENCODING_BLOCK> &data) //done
{
    FILE *read;
    read = fopen("encoded.lt","rb");
    ENCODING_BLOCK buffer;
    K = 0;
    while(!feof(read))
    {
        if (!fread(&buffer,sizeof(ENCODING_BLOCK),1,read)) break;
        data.push_back(buffer);
        K++;
    }
    //debug//
    std::cout << K << std::endl;
    //debug//
    fclose(read);
}

void ReInitBool(bool* check, Random* pseudo, int seed, uint32_t &temp)
{
    for (int i = 0; i < K; i++) check[i] = false;
    pseudo -> setSeed(seed);
    temp = pseudo -> nextInt() % K;
    check[temp] = true;
}

void FormGraph(std::list<ENCODING_BLOCK> data, std::list<int> *_block_pos, DECODING_BLOCK *gdata)
{
    //for (int i = 0; i < K; i++)
    std::list<ENCODING_BLOCK>::iterator it;
    int i;
    for (it = data.begin(), i = 0; it != data.end(); it++, i++)
    {
        gdata[i]._encode = *it;
        gdata[i]._block_pos = _block_pos[i];
        //d from _encode;
    }
    data.clear();
    delete _block_pos;
}

std::list<int>* Decoding_ENCODING_BLOCK(std::list<ENCODING_BLOCK> data, std::list<int> *_block_pos) //done
{
//    bool *check = new bool[K];
//    check = ReInitBool(check);
//
//            //-Test-//
////    for (int i = 0; i < K; i++)
////        std::cout << check[i] << std::endl;
////    system("pause");
//    //------//
//    Random *pseudo = new Random;
//    pseudo -> setSeed(seed);
//    uint32_t temp = pseudo -> nextInt() % K;
//
//    check[temp] = true;
    bool *check = new bool[K];
    Random *pseudo = new Random;
    uint32_t temp;

    //clock_t t = clock();
    std::list<ENCODING_BLOCK>::iterator it;
    int i;
    for (it = data.begin(), i = 0; it != data.end(); it++, i++)
    {
        ReInitBool(check,pseudo,(*it).seed,temp);
        int deg = (*it).d;

        _block_pos[i].push_back(temp);

        while (--deg)
        {
            while (check[temp]) temp = pseudo -> nextInt() % K;
            check[temp] = true;

            _block_pos[i].push_back(temp);
        }
        _block_pos[i].sort(IntCmpr);
    }

//    for (int i = 0; i < K; i++)
//    {
//
//        ReInitBool(check,pseudo,data[i].seed,temp);
//        int degree = data[i].d;
//        _block_pos[i].push_back(temp);
//        while (--degree)
//        {
//            while(check[temp]) temp = pseudo -> nextInt() % K;
//            check[temp] = true;
//
//            _block_pos[i].push_back(temp);
//        }
//        _block_pos[i].sort(IntCmpr);
//    }

    //Debug//
    /*std::list<int>::iterator it;
    for (int i = 0; i < K; i++)
    {
        std::cout << _block_pos[i].size() << std::endl;
        for (it = _block_pos[i].begin(); it != _block_pos[i].end(); ++it)
            std::cout << *it << " ";
        system("pause");
    }*/

    //t = clock() - t;
    //std::cout << (float)t/CLOCKS_PER_SEC <<std::endl;
    return _block_pos;
}

bool ScanList(int n, std::list<int> ripple)
{
    std::list<int>::iterator it;
    for (it = ripple.begin(); it != ripple.end(); it++)
        if (*it == n) return true;
    return false;
}

void ScanDeg(DECODING_BLOCK *gdata, MB_BLOCK *odata, std::list<int> &ripple, std::list<int> offripple)
{
    for (int i = 0; i < K; i++)
    {
        if (gdata[i]._encode.d == 1)
        {
            int tmp = *gdata[i]._block_pos.begin(); //position of d=1 encoding symbol
            //odata[tmp] = gdata[i]._encode.DATA; //XOR data to original position
            XOR<long long>(odata[tmp].byte,gdata[i]._encode.DATA.byte,odata[tmp].byte,SIZE);
            gdata[i]._encode.d--;
            if (!ScanList(tmp,ripple) && !ScanList(tmp,offripple))  ripple.push_back(tmp); //push position in ripple
        }
    }
}



void Decoding()
{
    std::list<ENCODING_BLOCK> data;
    ReadES(data); //K get!

    unsigned int _size = (*data.begin()).filesize;

    std::list<int> *_block_pos = new std::list<int>[K]; //array of block_pos for each es
    Decoding_ENCODING_BLOCK(data,_block_pos);

    //Test//
//    std::list<int>::iterator it;
//    for (it = _block_pos[0].begin(); it != _block_pos[0].end(); ++it)
//        std::cout << *it << " ";
    //Test//

    DECODING_BLOCK *gdata = new DECODING_BLOCK[K];
    FormGraph(data,_block_pos,gdata); //main is gdata, deleted former

    //Test//
//    std::list<int>::iterator it;
//    for (it = gdata[0]._block_pos.begin(); it != gdata[0]._block_pos.end(); ++it)
//    std::cout << *it << " ";
//    std::cout << gdata[0]._d;
    //Test//

    //Main decoder//
    //int *check = new int[K]; // 0 = out 1 = in 2 = off ripple
    //for (int i = 0; i < K; i++) check[i] = 0;

    MB_BLOCK *odata = new MB_BLOCK[K]; //INIT BLANK ORIGINAL DATA
//    MB_BLOCK *buffer = new MB_BLOCK;
//    std::fill(buffer->byte,buffer->byte+SIZE,0);
//    std::fill(odata,odata+K,buffer);
    for (int i = 0; i < K; i++)
        std::fill(odata->byte,odata->byte+SIZE,0);


    std::list<int> ripple;
    std::list<int> offripple;
    clock_t t = clock();
    while(offripple.size()!=_size) //stop when ripple is empty
    {
        std::list<int>::iterator it;
        ScanDeg(gdata,odata,ripple,offripple); //release d = 1 encoding symbols and add them to ripple
        for (it = ripple.begin(); it != ripple.end();) //process ripple
        {
            //std::list<int>::iterator _posit;
            for (int z  = 0; z < K; z++)
            {
                gdata[z]._block_pos.remove(*it); //remove position which is in ripple
                gdata[z]._encode.d--;
                ScanDeg(gdata,odata,ripple,offripple); //update ripple + release encoding symbol
            }
            std::list<int>::iterator tmp;
            tmp = it;
            it++;
            offripple.push_back(*tmp);
            offripple.unique();
            ripple.erase(tmp); //remove first member of ripple (proccessed)
        }
    }
    t = clock() - t;
    std::cout << (float)t/CLOCKS_PER_SEC <<std::endl;
    //write back
    FILE *writebin;
    writebin = fopen("original.bin","wb");
    fwrite(odata,sizeof(MB_BLOCK),SIZE,writebin);
    fclose(writebin);
}
