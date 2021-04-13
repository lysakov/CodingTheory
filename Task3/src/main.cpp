#include <iostream>
#include <sstream>
#include "Coder.hpp"
#include "Decoder.hpp"
#include "CodeGenerator.hpp"

int main()
{

    //std::ifstream input;
    //input.open("resources/file.txt", std::ios::binary | std::ios::in);
    //std::ofstream output;
    //output.open("resources/output.txt");
    //std::stringstream str;
    //str << "euweouew[por3029902idpw;ll;llmekcmouewoux";
    //Coder archiever = Coder(input);
    //archiever.encode(output);
    std::ifstream input;
    input.open("resources/output.txt");

    std::ofstream output;
    output.open("resources/output1.txt");

    Decoder decoder(input);
    decoder.decode(output);

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