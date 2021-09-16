//
// Created by jharw on 9/15/2021.
//

#include "IdAutomaton.h"

void IdAutomaton::S0(const std::string &input) {
    if (isalpha(input[index])) {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void IdAutomaton::S1(const std::string &input) {
    if(!isalnum(input[index])) {
        //Do nothing, we don't want this to be part of the ID
    }
    else if(isspace(input[index]) || input[index] == EOF) {
        //Do nothing
    }
    else if(isalnum(input[index])) {
        inputRead++;
        index++;
        S1(input);
    }
}