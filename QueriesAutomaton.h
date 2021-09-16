//
// Created by jharw on 9/15/2021.
//

#ifndef PROJECT_1_QUERIESAUTOMATON_H
#define PROJECT_1_QUERIESAUTOMATON_H

#include "Automaton.h"

class QueriesAutomaton : public Automaton
{
private:
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);
    void S4(const std::string& input);
    void S5(const std::string& input);
    void S6(const std::string& input);

public:
    QueriesAutomaton() : Automaton(TokenType::QUERIES) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //PROJECT_1_QUERIESAUTOMATON_H
