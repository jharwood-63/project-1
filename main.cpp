#include "Lexer.h"
#include "Parser.h"
#include "DatalogProgram.h"
#include "Database.h"
#include "Interpreter.h"
#include <iostream>
#include <fstream>
#include <string>

#include <vector>

int main(int argc, char** argv) {
    std::string fileName = argv[1];
    std::string input;

    Lexer* lexer = new Lexer();
    Parser* parser = new Parser();
    DatalogProgram* program = new DatalogProgram();
    Database* database = new Database();
    Interpreter* interpreter;

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
    parser->parse(tokens, program);
    interpreter = new Interpreter(program, database);
    interpreter->evaluateRules();
    interpreter->evaluateQueries();

    inputFile.close();

    delete lexer;
    delete parser;
    delete program;
    delete database;
    delete interpreter;

    return 0;
}