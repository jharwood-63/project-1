//
// Created by jharw on 9/15/2021.
//

#ifndef PROJECT_1_EOFAUTOMATON_H
#define PROJECT_1_EOFAUTOMATON_H

#include "Automaton.h"

class EOFAutomaton : public Automaton {
public:
    EOFAutomaton() : Automaton(TokenType::EOF_TYPE) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //PROJECT_1_EOFAUTOMATON_H
