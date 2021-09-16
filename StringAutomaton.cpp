//
// Created by jharw on 9/15/2021.
//

#include "StringAutomaton.h"

void StringAutomaton::S0(const std::string& input) {
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void StringAutomaton::S1(const std::string& input) {
    int stringSize = input.size();
    if (input[index] == '\n') {
        newLines++;
    }
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S2(input);
    }
    else if (index == stringSize) {
        SFail(input);
    }
    else {
        inputRead++;
        index++;
        S1(input);
    }
}

void StringAutomaton::S2(const std::string& input) {
    if (input[index] != '\'') {
        //do nothing its a string
    }
    else if (input[index] == EOF) {
        inputRead++;
    }
    else {
        inputRead++;
        index++;
        S1(input);
    }
}

void StringAutomaton::SFail(const std::string& input) {
    type = TokenType::UNDEFINED;
}