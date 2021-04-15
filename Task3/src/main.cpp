#include <iostream>
#include <exception>
#include "Controller.hpp"

int main(int argc, char **argv)
{

    try {
        if (argc < 3) {
            throw std::invalid_argument("Not enought arguments for launch");
        }
        
        Controller controller;
        controller.launch(argv[1], argv[2]);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;

}