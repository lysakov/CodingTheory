#include "Decoder.hpp"

#include <cstring>
#include <vector>

void Decoder::decode(std::ostream &output)
{

    auto table = deserializeCodingTable();
    DecodingTable decodingTable(table);

    int outputPos = 0;
    int minLen = decodingTable.getMinCodeWordLen();
    int bytesInBuf = 0;
    int bytesRead = 0;
    int pos = 0;
    int offset = 0;

    do {

        input->read(bufferInp + offset, INP_BUFFER_LEN - offset);
        bytesRead = input->gcount();
        bytesInBuf = bytesRead + offset;
        pos %= 8;

        int finalBitPos = INP_BUFFER_LEN * 8;
        if (bytesInBuf < INP_BUFFER_LEN) {
            uint8_t paddedBitsNum = bufferInp[bytesInBuf - 1];
            finalBitPos = (bytesInBuf - 1) * 8 - paddedBitsNum;
        }

        while (pos < finalBitPos && pos < 8 * OUTP_BUFFER_LEN) {

            int len = minLen;
            uint8_t word = 0;
            CodeWord codeWord;

            while (len != 0) {
                CodeWord tmp;
                readBits(pos / 8, pos % 8, len, tmp);
                codeWord.concat(tmp);
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

        offset = bytesInBuf - pos / 8;
        char tmpBuf[INP_BUFFER_LEN - OUTP_BUFFER_LEN] = {0};

        if (pos != finalBitPos) {
            std::memcpy(tmpBuf, bufferInp + pos / 8, offset);
            std::memset(bufferInp, 0, INP_BUFFER_LEN);
            std::memcpy(bufferInp, tmpBuf, offset);
        }

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