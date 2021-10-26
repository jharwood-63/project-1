//
// Created by jharw on 9/27/2021.
//

#ifndef PROJECT_1_PARSER_H
#define PROJECT_1_PARSER_H

#include "Token.h"
#include "DatalogProgram.h"
#include "Predicate.h"
#include "Parameter.h"
#include "Rule.h"
#include <vector>

class Parser {
public:
    void parse(std::vector<Token*> &tokens, DatalogProgram* program);

private:
    void parseDatalogProgram(std::vector<Token*> &tokens, DatalogProgram* &program);
    void parseSchemeList(std::vector<Token*> &tokens, DatalogProgram* &program);
    void parseFactList(std::vector<Token*> &tokens, DatalogProgram* &program);
    void parseRuleList(std::vector<Token*> &tokens, DatalogProgram* &program);
    void parseQueryList(std::vector<Token*> &tokens, DatalogProgram* &program);
    void parseScheme(std::vector<Token*> &tokens, DatalogProgram* &program);
    void parseFact(std::vector<Token*> &tokens, DatalogProgram* &program);
    void parseRule(std::vector<Token*> &tokens, DatalogProgram* &program);
    void parseQuery(std::vector<Token*> &tokens, DatalogProgram* &program);
    void parseHeadPredicate(std::vector<Token*> &tokens, Rule* &newRule);
    void parsePredicate(std::vector<Token*> &tokens, Predicate* &newPredicate);
    void parseRulePredicate(std::vector<Token*> &tokens, Rule* &newRule);
    //void parsePredicateList(std::vector<Token*> &tokens);
    void parsePredicateList(std::vector<Token*> &tokens, Rule* &newRule);
    void parseParameterList(std::vector<Token*> &tokens, Predicate* &newPredicate);
    void parseStringList(std::vector<Token*> &tokens, Predicate* &newPredicate, DatalogProgram* &program);
    void parseIdList(std::vector<Token*> &tokens, Predicate* &newPredicate);
    //void parseRuleIdList(std::vector<Token*> &tokens,);
    void parseParameter(std::vector<Token*> &tokens, Predicate* newPredicate);

    bool Match(TokenType type, TokenType matchingType);
    void checkTerminals(TokenType type, std::vector<Token*> &tokens);
    void filterComments(std::vector<Token*> &tokens);
    bool setIsConstant(Token* token);
};


#endif //PROJECT_1_PARSER_H
