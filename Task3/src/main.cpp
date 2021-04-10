#include <iostream>
#include <sstream>
#include "Coder.hpp"
#include "CodeGenerator.hpp"

int main()
{

    std::ifstream input;
    input.open("resources/file1.txt", std::ios::binary | std::ios::in);
    std::ofstream output;
    output.open("resources/output.txt");
    //std::stringstream str;
    //str << "euweouew[por3029902idpw;ll;llmekcmouewoux";
    Coder archiever = Coder(input);
    archiever.zip(output);

    CodeWord code;
    code.addNextBit(1);
    std::cout << code << " - " << code.size << "\n";

    /*std::vector<WordDesc> v;
    for (int i = 0; i < 256; ++i) {
        v.push_back(WordDesc(i, i*i));
    }
    CodeGenerator coder(v);
    auto arr = coder.createCode();

    for (int i = 0; i < 256; ++i) {
        std::cout << (int)i << " - " << arr.get()[i] << "\n";
    }*/

    return 0;

}