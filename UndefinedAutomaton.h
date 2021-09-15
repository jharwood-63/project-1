//
// Created by jharw on 9/15/2021.
//

#ifndef PROJECT_1_UNDEFINEDAUTOMATON_H
#define PROJECT_1_UNDEFINEDAUTOMATON_H

#include "Automaton.h"

class UndefinedAutomaton : public Automaton{
public:
    UndefinedAutomaton() : Automaton(TokenType::UNDEFINED) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //PROJECT_1_UNDEFINEDAUTOMATON_H
