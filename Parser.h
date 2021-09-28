//
// Created by jharw on 9/27/2021.
//

#ifndef PROJECT_1_PARSER_H
#define PROJECT_1_PARSER_H

#include "Token.h"
#include "DatalogProgram.h"
#include <vector>

class Parser {
public:
    void parse(std::vector<Token*> &tokens);

private:
    void parseDatalogProgram(std::vector<Token*> &tokens);
    void parseSchemeList(std::vector<Token*> &tokens);
    void parseFactList(std::vector<Token*> &tokens);
    void parseRuleList(std::vector<Token*> &tokens);
    void parseQueryList(std::vector<Token*> &tokens);
    void parseScheme(std::vector<Token*> &tokens);
    void parseFact();
    void parseRule();
    void parseQuery(std::vector<Token*> &tokens);
    void parseHeadPredicate();
    void parsePredicate();
    void parsePredicateList();
    void parseParameterList();
    void parseStringList();
    void parseIdList();
    void parseParameter();

    bool Match(TokenType type, TokenType matchingType);
    void checkTerminals(TokenType type, std::vector<Token*> &tokens);
    void checkComments(std::vector<Token*> &tokens);
};


#endif //PROJECT_1_PARSER_H
