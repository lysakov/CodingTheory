#ifndef DECODING_TABLE
#define DECODING_TABLE

#include <vector>
#include <cmath>

#include "CodeGenerator.hpp"

class DecodingTable
{

public:
    enum {
        PREFIX_LEN = 16
    };
    
    DecodingTable(const std::vector<WordDesc>& code);

    inline uint8_t decode(const CodeWord& word, int& nextWordSize)
    {

        uint16_t intData = *(reinterpret_cast<const int*>(word.data));

        if (!curTable[intData].initialized || curTable[intData].size != word.size) {
            nextWordSize = deltas[curDeltaPos];
            ++curDeltaPos;
            return 0;
        }

        if (curTable[intData].ref) {
            curTable = curTable[intData].ref;
            nextWordSize = deltas[curDeltaPos];
            ++curDeltaPos;
            return 0;
        }

        auto &decodedWord = curTable[intData];
        curTable = table;
        curDeltaPos = 1;
        nextWordSize = 0;

        return decodedWord.symb;

    }

    int getMinCodeWordLen() { return deltas[0]; }

    ~DecodingTable();

private:
    struct DecodingTableNode
    {
        bool initialized = false;
        uint8_t symb = 0;
        uint8_t size = 0;
        DecodingTableNode *ref = nullptr;
    };

    enum {
        TABLE_LEVEL_LEN = 65536
    };

    DecodingTableNode table[TABLE_LEVEL_LEN];
    DecodingTableNode *curTable = table;
    int deltas[256] = {0};
    int curDeltaPos = 1;

    void initDeltas(const std::vector<WordDesc>& code);
    void initTableNode(int pos, uint8_t symb, const char *codeData, 
        int size, DecodingTableNode *table);
    void deleteNode(DecodingTableNode *node);
    
};

#endif