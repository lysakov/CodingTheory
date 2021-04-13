#include "Decoder.hpp"

#include <cstring>
#include <vector>
#include <cmath>
#include <iostream>

/* TODO: Improve error with 000 and decode padding */

void Decoder::decode(std::ostream &output)
{

    auto table = deserializeCodingTable();
    for (auto x : table) {
        std::cout << x.code << '\n';
    }
    DecodingTable decodingTable(table);

    int outputPos = 0;
    int minLen = decodingTable.getMinCodeWordLen();
    int bytesRead = 0;
    int pos = 0;

    do {

        input->read(bufferInp + pos / 8, INP_BUFFER_LEN - pos / 8);
        bytesRead = input->gcount();

        while (!((pos / 8 < INP_BUFFER_LEN) && (pos / 8 > OUTP_BUFFER_LEN) && (pos % 8 == 0)) && (pos / 8 < bytesRead)) {
            int len = minLen;
            uint8_t word = 0;
            while (len != 0) {
                CodeWord codeWord;
                //std::memset(codeWord.data, 0, 32);
                readBits(pos / 8, pos % 8, len, codeWord);
                pos += len;
                word = decodingTable.decode(codeWord, len);
            }
            bufferOutp[outputPos] = word;
            ++outputPos;

            if (outputPos == OUTP_BUFFER_LEN) {
                output.write(reinterpret_cast<char*>(bufferOutp), OUTP_BUFFER_LEN);
                outputPos = 0;
            }
        }

        std::memcpy(bufferInp, bufferInp + pos / 8, INP_BUFFER_LEN - pos / 8);
        pos = 8 * (INP_BUFFER_LEN - pos / 8);

    } while (bytesRead != 0);

    output.write(reinterpret_cast<char*>(bufferOutp), outputPos);

}

std::vector<WordDesc> Decoder::deserializeCodingTable()
{

    decltype(deserializeCodingTable()) table;
    int len = 0;
    input->read(reinterpret_cast<char *>(&len), sizeof(int));

    std::unique_ptr<char> serializedTable(new char[len]);
    char *serializedTablePtr = serializedTable.get();
    input->read(serializedTable.get(), len);

    int pos = 0;
    while (pos < len) {
        WordDesc word;
        word.word = serializedTablePtr[pos];
        word.code.size = serializedTablePtr[pos + 1];
        std::memcpy(word.code.data, serializedTablePtr + pos + 2, word.code.size / 8 + 1);
        table.push_back(word);
        pos += 2 + word.code.size / 8 + 1;
    }

    return table;
}