//
// Created by jharw on 9/15/2021.
//

#include "PeriodAutomaton.h"

void PeriodAutomaton::S0(const std::string& input) {
    if (input[index] == '.') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}