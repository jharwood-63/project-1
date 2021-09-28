#include "Lexer.h"
#include "Parser.h"
#include <iostream>
#include <fstream>
#include <string>

#include <vector>

int main(int argc, char** argv) {
    std::string fileName = argv[1];
    std::string input;

    Lexer* lexer = new Lexer();
    Parser* parser = new Parser();

    std::vector<Token*> tokens;

    std::string nextLine;
    std::ifstream inputFile;
    inputFile.open(fileName);
    if (!inputFile.is_open()) {
        std::cout << "Could not open file" << std::endl;
    }

    char currChar = inputFile.peek();

    while (currChar != EOF) {
        char added = inputFile.get();
        input.push_back(added);
        currChar = inputFile.peek();
    }

    lexer->Run(input);

    tokens = lexer->getTokens();
    parser->parse(tokens);

    inputFile.close();

    delete lexer;
    delete parser;

    return 0;
}