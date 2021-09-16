//
// Created by jharw on 9/15/2021.
//

#ifndef PROJECT_1_SCHEMESAUTOMATON_H
#define PROJECT_1_SCHEMESAUTOMATON_H

#include "Automaton.h"

class SchemesAutomaton : public Automaton
{
private:
    void S1(const std::string& input);

public:
    SchemesAutomaton() : Automaton(TokenType::SCHEMES) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif //PROJECT_1_SCHEMESAUTOMATON_H
