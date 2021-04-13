#include "Coder.hpp"

#include <algorithm>
#include <iostream>

void Coder::encode(std::ostream &output)
{

    auto res = collectBytesStatistic();
    auto codeGenerator = CodeGenerator(*res);
    auto codeTable = codeGenerator.createCode();
    auto codeTablrPtr = codeTable.get();
    unsigned long bytesRead = 0;

    for (int i = 0; i < 256; ++i) {
        std::cout << i << " - " << codeTablrPtr[i] << " - " << codeTablrPtr[i].size << '\n';
    }

    serializeCodingTable(output, codeTablrPtr);

    int size = 0;
    do {
        input->read(bufferInp, INP_BUFFER_LEN);
        bytesRead = input->gcount();

        for (int i = 0; i < INP_BUFFER_LEN; ++i) {
            CodeWord &word = codeTablrPtr[static_cast<int>(bufferInp[i])];
            writeToOutpBuffer(size / 8, size % 8, word);
            size += word.size;
            
            if (size/8 > INP_BUFFER_LEN && size/8 <= OUTP_BUFFER_LEN && size%8 == 0) {
                output.write(reinterpret_cast<char*>(bufferOutp), size/8);
                size = 0;
            }
        } 
    } while (bytesRead != 0);
    
    char paddingLen = 8 - size % 8;
    CodeWord zeroPadding;
    zeroPadding.size = paddingLen;
    writeToOutpBuffer(size / 8, size % 8, zeroPadding);
    size += paddingLen + 8;
    output.write(reinterpret_cast<char*>(bufferOutp), size/8);
    output.write(&paddingLen, 1);

}

std::shared_ptr<std::vector<WordDesc>> Coder::collectBytesStatistic() 
{

    uint8_t i = 0;
    std::vector<WordDesc> res = decltype(res)(256);
    std::for_each(res.begin(), res.end(), [i](WordDesc &word) mutable {word.word = i; ++i;});

    do {
        input->read(bufferInp, INP_BUFFER_LEN);
        for (long int i = 0; i < input->gcount(); ++i) {
            res[static_cast<uint8_t>(bufferInp[i])].freq += 1;
        }
    } while (input->gcount() != 0);

    input->clear();
    input->seekg(std::ios_base::beg);

    return std::make_shared<decltype(res)>(res);

}

void Coder::serializeCodingTable(std::ostream& output, const CodeWord* codingTable)
{

    uint serializedLen = 0;
    for (int i = 0; i < 256; ++i) {
        if (codingTable[i].size != 0) {
            serializedLen += 2 + codingTable[i].size / 8 + 1;
        }
    }

    output.write(reinterpret_cast<char*>(&serializedLen), sizeof(int));
    for (int i = 0; i < 256; ++i) {
        if (codingTable[i].size != 0) {
            output.write(reinterpret_cast<char*>(&i), sizeof(char));
            output.write(reinterpret_cast<const char*>(&(codingTable[i].size)), sizeof(char));
            output.write(reinterpret_cast<const char*>(codingTable[i].data), codingTable[i].size / 8 + 1);
        }
    }

}