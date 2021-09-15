#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "UndefinedAutomaton.h"
#include "EOFAutomaton.h"
#include <iostream>


Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    // TODO: need to clean up the memory in `automata` and `tokens`
}

void Lexer::CreateAutomata() {
    automata.push_back(new UndefinedAutomaton());
    automata.push_back(new EOFAutomaton());
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    // TODO: Add the other needed automata here
}

void Lexer::Run(std::string& input) {
    // TODO: convert this pseudo-code with the algorithm into actual C++ code
    ///*
    int maxRead;
    int lineNumber = 1;

    std::string tokenString;

    Automaton* end = automata[1];
    Automaton* undefined = automata[0];

    // While there are more characters to tokenize
    while (input.size() > 0) {
        maxRead = 0;
        int inputRead;
        Automaton* maxAutomaton = automata.at(0);

        // TODO: you need to handle whitespace inbetween tokens
        if (isspace(input.at(0))) {
            if (input.at(0) == '\n') {
                lineNumber++;
            }
            input.erase(0, 1);
        }
        else {
            // Here is the "Parallel" part of the algorithm
            //   Each automaton runs with the same input
            for (unsigned int i = 0; i < automata.size(); i++) {
                inputRead = automata[i]->Start(input);
                if (inputRead > maxRead) {
                    maxRead = inputRead;
                    maxAutomaton = automata[i];
                }
            }
            // Here is the "Max" part of the algorithm
            if (maxRead > 0) {
                tokenString = input.substr(0, maxRead);
                Token *newToken = maxAutomaton->CreateToken(tokenString, lineNumber);
                //lineNumber += maxAutomaton->NewLinesRead();
                tokens.push_back(newToken);
            }
                // No automaton accepted input
                // Create single character undefined token
            else {
                maxRead = 1;
                tokenString = input.substr(0, 1);
                Token *newToken = undefined->CreateToken(tokenString, lineNumber);
                //(with first character of input)
                tokens.push_back(newToken);
            }
            // Update `input` by removing characters read to create Token
            input.erase(0, maxRead);
        }
    }
    Token* endToken = end->CreateToken("EOF", lineNumber);
    tokens.push_back(endToken);
    for (int i = 0; i < tokens.size(); i++) {
        std::cout << tokens.at(i)->toString();
    }
    //*/
}
