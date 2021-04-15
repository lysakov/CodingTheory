#ifndef DECODER
#define DECODER

#include <fstream>
#include <memory>
#include <set>

#include "CodeGenerator.hpp"
#include "DecodingTable.hpp"

class Decoder
{

public:
    Decoder(std::istream& input): input(&input) {}
    void decode(std::ostream& output);

private:
    enum {
        INP_BUFFER_LEN = 6144,
        OUTP_BUFFER_LEN = 4096
    };

    std::istream *input;
    char bufferInp[INP_BUFFER_LEN] = {0};
    uint8_t bufferOutp[OUTP_BUFFER_LEN] = {0};

    std::vector<WordDesc> deserializeCodingTable();

    inline void readBits(int curByte, int curBit, int n, CodeWord& word)
    {

        int offset = 8 - curBit;
        uint8_t mask = 0xFF >> curBit;
        word.data[0] |= (bufferInp[curByte] >> curBit) & mask;
        word.data[0] |= bufferInp[curByte + 1] << offset;
        word.data[0] &= (0xFF >> (n < 8 ? 8 - n : 0));

        int i = 1;
        int r = 0;
        while ((r = n - (i << 3)) > 0) {
            word.data[i] |= (bufferInp[curByte + i] >> curBit) & mask;
            word.data[i] |= bufferInp[curByte + i + 1] << offset;
            ++i;
        }

        word.data[i] |= (bufferInp[curByte + i] >> (offset < r ? curBit : 8 - r)) & mask;
        word.data[i] |= bufferInp[curByte + i + 1] << (8 - r + offset);
        word.data[i] &= 0xFF >> (8 - r);
        word.size = n;

    }

};

#endif