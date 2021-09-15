#include "Lexer.h"
#include <iostream>
#include <fstream>
#include <string>

#include <vector>

void testMethod() {
    /*
    std::vector<Token*> tokenVector;
    Token* test1 = new Token(TokenType::COLON, ":", 1);
    Token* test2 = new Token(TokenType::COLON_DASH, ":", 1);
    Token* test3 = new Token(TokenType::COMMA, ":", 1);
    Token* test4 = new Token(TokenType::PERIOD, ":", 1);
    Token* test5 = new Token(TokenType::Q_MARK, ":", 1);
    Token* test6 = new Token(TokenType::LEFT_PAREN, ":", 1);
    Token* test7= new Token(TokenType::RIGHT_PAREN, ":", 1);
    Token* test8 = new Token(TokenType::MULTIPLY, ":", 1);
    Token* test9 = new Token(TokenType::ADD, ":", 1);
    Token* test10 = new Token(TokenType::SCHEMES, ":", 1);
    Token* test11 = new Token(TokenType::FACTS, ":", 1);
    Token* test12 = new Token(TokenType::RULES, ":", 1);
    Token* test13 = new Token(TokenType::QUERIES, ":", 1);
    Token* test14 = new Token(TokenType::ID, ":", 1);
    Token* test15 = new Token(TokenType::STRING, ":", 1);
    Token* test16 = new Token(TokenType::COMMENT, ":", 1);
    Token* test17 = new Token(TokenType::EOF_TYPE, ":", 1);
    Token* test18 = new Token(TokenType::UNDEFINED, ":", 1);

    tokenVector.push_back(test1);
    tokenVector.push_back(test2);
    tokenVector.push_back(test3);
    tokenVector.push_back(test4);
    tokenVector.push_back(test5);
    tokenVector.push_back(test6);
    tokenVector.push_back(test7);
    tokenVector.push_back(test8);
    tokenVector.push_back(test9);
    tokenVector.push_back(test10);
    tokenVector.push_back(test11);
    tokenVector.push_back(test12);
    tokenVector.push_back(test13);
    tokenVector.push_back(test14);
    tokenVector.push_back(test15);
    tokenVector.push_back(test16);
    tokenVector.push_back(test17);
    tokenVector.push_back(test18);

    for (int i = 0; i < tokenVector.size(); i++) {
        std::cout << tokenVector.at(i)->toString() << std::endl;
    }
     */
}

int main(int argc, char** argv) {
    std::string fileName = argv[1];
    std::string input;

    Lexer* lexer = new Lexer();

    std::string nextLine;
    std::ifstream inputFile;
    inputFile.open(fileName);
    if (inputFile.is_open()) {
        std::cout << "Reading from file" << std::endl;
    }
    else {
        std::cout << "Could not open file" << std::endl;
    }

    char currChar = inputFile.peek();

    while (currChar != EOF) {
        char added = inputFile.get();
        input.push_back(added);
        currChar = inputFile.peek();
    }

    lexer->Run(input);

    inputFile.close();

    delete lexer;

    //testMethod();
    return 0;
}