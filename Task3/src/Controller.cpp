#include "Controller.hpp"

#include <exception>
#include "Archiever.hpp"

void Controller::launch(const std::string& flag, const std::string& inputFileName)
{
    std::ifstream input;
    input.open(inputFileName, std::ios::binary | std::ios::in);

    if (!input) {
        throw std::invalid_argument("File "+ inputFileName + " doesn't exist");
    }

    if (flag == "-c") {
        compress(input, inputFileName);
    }

    if (flag == "-x") {
        extract(input, inputFileName);
    }

    if (flag != "-c" && flag != "-x") {
        throw std::invalid_argument("Unknown flag: " + flag);
    }

}

void Controller::compress(std::ifstream& input, const std::string& inputFileName)
{

    std::ofstream output;
    output.open(inputFileName + ".zmh", std::ios::binary | std::ios::out);

    Archiever::zip(input, output);

}

void Controller::extract(std::ifstream& input, const std::string& inputFileName)
{

    std::string outputFileName = inputFileName;
    auto pos = outputFileName.rfind(".zmh");

    if (pos == std::string::npos) {
        throw std::invalid_argument("Unknown extension: compressed file should have .zmh extension");
    }
    outputFileName.resize(pos);

    std::ofstream output;
    output.open(outputFileName, std::ios::binary | std::ios::out);

    Archiever::unzip(input, output);

}
