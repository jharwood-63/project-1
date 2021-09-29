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
    void parseFact(std::vector<Token*> &tokens);
    void parseRule(std::vector<Token*> &tokens);
    void parseQuery(std::vector<Token*> &tokens);
    void parseHeadPredicate(std::vector<Token*> &tokens);
    void parsePredicate(std::vector<Token*> &tokens);
    void parsePredicateList(std::vector<Token*> &tokens);
    void parseParameterList(std::vector<Token*> &tokens);
    void parseStringList(std::vector<Token*> &tokens);
    void parseIdList(std::vector<Token*> &tokens);
    void parseParameter(std::vector<Token*> &tokens);

    bool Match(TokenType type, TokenType matchingType);
    void checkTerminals(TokenType type, std::vector<Token*> &tokens);
    void filterComments(std::vector<Token*> &tokens);
};


#endif //PROJECT_1_PARSER_H
