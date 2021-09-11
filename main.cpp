#include "Lexer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main(int argc, char** argv) {

    Lexer* lexer = new Lexer();

    std::ifstream inputFile;
    std::string nextLine;
    inputFile.open("test.txt");
    if (!inputFile.is_open()) {
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