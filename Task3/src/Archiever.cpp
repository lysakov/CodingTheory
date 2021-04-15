#include "Archiever.hpp"

#include "Coder.hpp"
#include "Decoder.hpp"

void Archiever::zip(std::istream& input, std::ostream& output)
{

    Coder coder(input);
    coder.encode(output);

}

void Archiever::unzip(std::istream& input, std::ostream& output)
{

    Decoder decoder(input);
    decoder.decode(output);

}