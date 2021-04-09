#include <iostream>
#include <sstream>
#include "archiever.hpp"
#include "coder.hpp"

int main()
{

    /*std::ifstream input;
    input.open("resources/file.txt", std::ios::binary | std::ios::in);
    std::stringstream str;
    str << "euweouew[por3029902idpw;ll;llmekcmouewoux";
    Archiever archiever = Archiever(str);
    archiever.zip(std::cout);
    */

    std::vector<WordDesc> v;
    for (int i = 0; i < 256; ++i) {
        v.push_back(WordDesc(i, i*i));
    }
    Coder coder(v);
    auto arr = coder.createCode();

    for (int i = 0; i < 256; ++i) {
        std::cout << (int)i << " - " << arr.get()[i] << "\n";
    }

    return 0;

}