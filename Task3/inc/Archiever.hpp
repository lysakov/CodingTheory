#ifndef ARCHIEVER
#define ARCHIEVER

#include <fstream>

class Archiever
{

public:
    static void zip(std::istream& input, std::ostream& output);
    static void unzip(std::istream& input, std::ostream& output);

};

#endif