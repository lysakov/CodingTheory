#ifndef CONTROLLER
#define CONTROLLER

#include <fstream>
#include <string>

class Controller
{

public:
    void launch(const std::string& flag, const std::string& inputFileName);

private:
    void compress(std::ifstream& input, const std::string& inputFileName);
    void extract(std::ifstream& input, const std::string& inputFileName);

};

#endif