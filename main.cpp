#include "Lexer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main(int argc, char** argv) {
    std::string fileName = argv[1];

    Lexer* lexer = new Lexer();

    std::string nextLine;
    std::ifstream inputFile;
    inputFile.open(fileName);
    //inputFile.open("test.txt");
    if (inputFile.is_open()) {
        std::cout << "Reading from file" << std::endl;
    }
    else {
        std::cout << "Could not open file" << std::endl;
    }

    std::stringstream ss;

    while(getline(inputFile, nextLine)) {
        ss << nextLine;
    }

    std::cout << ss.str() << std::endl;

    inputFile.close();
    // TODO

    delete lexer;

    return 0;
}