//
// Created by jharw on 9/15/2021.
//

#ifndef PROJECT_1_IDAUTOMATON_H
#define PROJECT_1_IDAUTOMATON_H

#include "Automaton.h"

class IdAutomaton : public Automaton
{
private:
    void S1(const std::string& input);

public:
    IdAutomaton() : Automaton(TokenType::ID) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //PROJECT_1_IDAUTOMATON_H
