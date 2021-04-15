#ifndef CODE_GENERATOR
#define CODE_GENERATOR

#include <cstdint>
#include <cstddef>
#include <vector>
#include <memory>
#include <ostream>

struct CodeWord
{

    uint8_t data[32] = {0};
    int size = 0;

    void addNextBit(uint bit)
    {
        data[size / 8] |= bit << (size % 8);
        ++size;
    }

    inline void concat(const CodeWord& codeWord)
    {

        int curByte = this->size / 8;
        int curBit = this->size % 8;

        int offset = 8 - curBit;
        this->data[curByte] &= 0xFF >> offset;
        this->data[curByte] |= codeWord.data[0] << curBit;
        int i = 1;
        while (codeWord.size - offset - (i << 3) > 0) {
            this->data[curByte + i] = (codeWord.data[i - 1] >> offset) | (codeWord.data[i] << curBit);
            ++i;
        }
        this->data[curByte + i] = codeWord.data[i - 1] >> offset;
        this->size += codeWord.size;

    }

    friend std::ostream& operator<<(std::ostream& str, const CodeWord &word)
    {

        int fullBytes = word.size / 8;
        int bits = word.size % 8;

        for (int i = 0; i < fullBytes; ++i) {
            for (int j = 0; j < 8; ++j) {
                str << (word.data[i] & (1 << j)? 1 : 0);
            }
            str << ' ';
        }

        for (int i = 0; i < bits; ++i) {
                str << (word.data[fullBytes] & (1 << i)? 1 : 0);
        }

        return str;
    }

};

struct WordDesc
{

    uint8_t word = 0;
    size_t freq = 0;
    std::shared_ptr<WordDesc> first = nullptr;
    std::shared_ptr<WordDesc> second = nullptr;
    CodeWord code;

    WordDesc() {}
    
    WordDesc(uint8_t word, size_t freq) : word(word), freq(freq){}

    WordDesc(uint8_t word, size_t freq, std::shared_ptr<WordDesc> first, 
        std::shared_ptr<WordDesc> second) : 
            word(word), freq(freq), first(first), second(second){}

    bool operator>(const WordDesc& second) const
    {
        return this->freq > second.freq;
    }

    static WordDesc join(WordDesc &first, WordDesc &second)
    {
        return WordDesc(0, first.freq + second.freq, 
            std::make_shared<WordDesc>(first), std::make_shared<WordDesc>(second));
    }

};

class CodeGenerator
{

public:
    CodeGenerator(std::vector<WordDesc> &words): words(words) {}
    std::shared_ptr<CodeWord> createCode();

private:
    std::vector<WordDesc> words;

    void computeCodeWord(WordDesc &word, CodeWord* codeTable);

};

#endif