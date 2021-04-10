#include "CodeGenerator.hpp"

#include <queue>
#include <iostream>

std::shared_ptr<CodeWord> CodeGenerator::createCode()
{

    std::shared_ptr<CodeWord> codingTable(new CodeWord[words.size()]);
    std::priority_queue<WordDesc, std::vector<WordDesc>, std::greater<WordDesc>>
        wordsSet(words.begin(), words.end());
    std::vector<std::shared_ptr<WordDesc>> tmpWords;

    WordDesc tmp;
    do {
        tmp = wordsSet.top();
        if (tmp.freq == 0) {
            wordsSet.pop();
        }
    } while (tmp.freq == 0);
    
    while (wordsSet.size() != 1) {
        auto second = wordsSet.top();
        wordsSet.pop();

        auto first = wordsSet.top();
        wordsSet.pop();

        auto newWord = std::make_shared<WordDesc>(WordDesc::join(first, second));
        wordsSet.push(*newWord);
        tmpWords.push_back(newWord);
    }

    auto final = wordsSet.top();
    computeCodeWord(final, codingTable.get());

    return codingTable;

}

void CodeGenerator::computeCodeWord(WordDesc& word, CodeWord* codeTable)
{
    auto changeCode = [](WordDesc& word, CodeWord prevCode, uint bit) {
        word.code = prevCode;
        word.code.addNextBit(bit);
    };

    std::cout << word.code << " - " << word.code.size << "\n";

    if (word.first) {
        changeCode(*word.first, word.code, 1);
        computeCodeWord(*word.first, codeTable);
    }

    if (word.second) {
        changeCode(*word.second, word.code, 0);
        computeCodeWord(*word.second, codeTable);
    }

    if (!word.first && !word.second) {
        codeTable[word.word] = word.code;
    }

}
