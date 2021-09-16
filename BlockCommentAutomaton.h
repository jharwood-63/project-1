//
// Created by jharw on 9/15/2021.
//

#ifndef PROJECT_1_BLOCKCOMMENTAUTOMATON_H
#define PROJECT_1_BLOCKCOMMENTAUTOMATON_H

#include "Automaton.h"

class BlockCommentAutomaton : public Automaton
{
private:
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);
    void SFail(const std::string& input);

public:
    BlockCommentAutomaton() : Automaton(TokenType::COMMENT) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif //PROJECT_1_BLOCKCOMMENTAUTOMATON_H
