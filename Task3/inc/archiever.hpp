#ifndef ARCHIEVER
#define ACHIEVER

#include <fstream>
#include <vector>
#include <stack>

#include "coder.hpp"

class Archiever
{
    
public:
    Archiever(std::istream &input): input(&input) {}
    void zip(std::ostream &output);

private:
    enum {
        BUFFER_LEN = 4096
    };

    std::istream *input;
    uint8_t codingTable[256] = {0};
    char buffer[BUFFER_LEN] = {0};

    std::vector<WordDesc> collectBytesStatistic();
    void createCode();

};

#endif