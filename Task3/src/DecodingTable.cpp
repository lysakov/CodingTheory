#include "DecodingTable.hpp"

#include <algorithm>
#include <exception>
#include <set>

DecodingTable::DecodingTable(const std::vector<WordDesc>& code)
{

    initDeltas(code);

    for (const auto &codeWord: code) {
        initTableNode(0, codeWord.word, reinterpret_cast<const char*>(codeWord.code.data), 
            codeWord.code.size, table);
    }

}

void DecodingTable::initDeltas(const std::vector<WordDesc>& code)
{

    std::set<int> lensSet;
    std::for_each(code.begin(), code.end(), 
        [&lensSet](const WordDesc& word) mutable {lensSet.insert(word.code.size);});

    std::vector<int> lensVector(lensSet.size());
    std::copy(lensSet.begin(), lensSet.end(), lensVector.begin());

    int j = 0;
    int prevLen = 0;
    for (size_t i = 0; i < lensVector.size(); ++i) {
        int delta = lensVector[i] - prevLen;
        while (delta > PREFIX_LEN) {
            deltas[j] = PREFIX_LEN;
            ++j;
            delta -= PREFIX_LEN;
        }
        deltas[j] = delta;
        ++j;
        prevLen = lensVector[i];
    }
}

void DecodingTable::initTableNode(int pos, uint8_t symb, const char *codeData, 
    int size, DecodingTableNode *table)
{

    int intCodeData = *(reinterpret_cast<const int*>(codeData + pos));
    auto &node = table[intCodeData];

    if (!node.initialized) {
        node.initialized = true;
        node.symb = symb;
        node.size = size > PREFIX_LEN ? PREFIX_LEN : size;
        if (size > PREFIX_LEN) {
            node.ref = new DecodingTableNode[TABLE_LEVEL_LEN];
            initTableNode(pos + PREFIX_LEN / 8, symb, codeData + PREFIX_LEN / 8, 
                size - PREFIX_LEN, node.ref);
        }
    }
    else {
        throw std::invalid_argument("Code is not prefix");
    }

}

void DecodingTable::deleteNode(DecodingTableNode *node)
{

    for (int i = 0; i < TABLE_LEVEL_LEN; ++i) {
        if ((node + i)->ref != nullptr) {
            deleteNode(node + i);
        }
    }

    if (node != curTable) {
        delete[] node;
    }

}


DecodingTable::~DecodingTable()
{

    deleteNode(table);

}