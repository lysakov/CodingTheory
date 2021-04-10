#ifndef ARCHIEVER
#define ARCHIEVER

#include <fstream>
#include <vector>
#include <memory>

#include "CodeGenerator.hpp"

class Coder
{
    
public:
    Coder(std::istream &input): input(&input) {}
    void zip(std::ostream &output);

private:
    enum {
        INP_BUFFER_LEN = 4096,
        OUTP_BUFFER_LEN = 6144
    };

    std::istream *input;
    char bufferInp[INP_BUFFER_LEN] = {0};
    uint8_t bufferOutp[OUTP_BUFFER_LEN] = {0};

    std::shared_ptr<std::vector<WordDesc>> collectBytesStatistic();
    void serializeCodingTable(std::ostream& output, const CodeWord* codingTable);

    inline void writeToOutpBuffer(int curByte, int curBit, const CodeWord& word) 
    {

        int offset = 8 - curBit;
        bufferOutp[curByte] &= 0xFF >> offset;
        bufferOutp[curByte] |= word.data[0] << curBit;
        int i = 1;
        while (word.size - offset - (i << 3) > 0) {
            bufferOutp[curByte + i] = (word.data[i - 1] >> offset) | (word.data[i] << curBit);
            ++i;
        }
        bufferOutp[curByte + i] = word.data[i - 1] >> offset; 
        
    }

};

#endif