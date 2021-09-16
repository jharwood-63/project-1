//
// Created by jharw on 9/15/2021.
//

#include "BlockCommentAutomaton.h"

void BlockCommentAutomaton::S0(const std::string &input) {
    if (input[index] == '#') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void BlockCommentAutomaton::S1(const std::string &input) {
    if (input[index] == '|') {
        inputRead++;
        index++;
        S2(input);
    }
    else {
        Serr();
    }
}

void BlockCommentAutomaton::S2(const std::string &input) {
    int stringSize = input.size();
    if (input[index] == '|') {
        inputRead++;
        index++;
        S3(input);
    }
    else if (index == stringSize) {
        SFail(input);
    }
    else {
        inputRead++;
        index++;
        S2(input);
    }
}

void BlockCommentAutomaton::S3(const std::string &input) {
    int stringSize = input.size();
    if (input[index] == '#') {
        inputRead++;
    }
    else if (input[index] == '|') {
        inputRead++;
        index++;
        S3(input);
    }
    else if (index == stringSize) {
        SFail(input);
    }
    else {
        inputRead++;
        index++;
        S2(input);
    }
}

void BlockCommentAutomaton::SFail(const std::string& input) {
    type = TokenType::UNDEFINED;
}
