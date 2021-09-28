//
// Created by jharw on 9/27/2021.
//

#include "Parser.h"
#include <iostream>

void Parser::parse(std::vector<Token *> &tokens) {
    checkComments(tokens);
    try {
        parseDatalogProgram(tokens);
    }
    catch(Token error) {
        std::cerr << "Failure" << std::endl;
    }
}

bool Parser::Match(TokenType type, TokenType matchType) {
    if (type == matchType)
        return true;
    else
        return false;
}

void Parser::checkTerminals(TokenType type, std::vector<Token*> &tokens) {
    if (type != TokenType::EOF_TYPE) {
        if (Match(tokens.at(0)->getType(), type) && Match(tokens.at(1)->getType(), TokenType::COLON)) {
            tokens.erase(tokens.begin() + 0);
            tokens.erase(tokens.begin() + 0);
        }
        else {
            //throw an exception, not an interception
        }
    }
    else {
        if (Match(tokens.at(0)->getType(), TokenType::EOF_TYPE)) {
            tokens.erase(tokens.begin() + 0);
            tokens.erase(tokens.begin() + 0);
        }
        else {
            //throw an exception, not an interception
        }
    }
}

void Parser::checkComments(std::vector<Token *> &tokens) {
    //when they are at the beginning weird things happen so you need to fix that
    for (int i = 0; i < tokens.size(); i++) {
        if (tokens.at(i)->getType() == TokenType::COMMENT) {
            tokens.erase(tokens.begin() + i);
        }
    }
}

void Parser::parseDatalogProgram(std::vector<Token *> &tokens) {
    //SCHEMES & COLON
    checkTerminals(TokenType::SCHEMES, tokens);
    //checkComments(tokens);
    //scheme
    //parseScheme(tokens);
    //checkComments(tokens);
    //schemeList
    //parseSchemeList(tokens);
    //checkComments(tokens);
    //FACTS & COLON
    //checkTerminals(TokenType::FACTS, tokens);
    //checkComments(tokens);
    //factList
    //parseFactList(tokens);
    //checkComments(tokens);
    //RULES & COLON
    //checkTerminals(TokenType::RULES, tokens);
    //checkComments(tokens);
    //ruleList
    //parseRuleList(tokens);
    //checkComments(tokens);
    //QUERIES & COLON
    //checkTerminals(TokenType::QUERIES, tokens);
    //checkComments(tokens);
    //query
    //parseQuery(tokens);
    //checkComments(tokens);
    //queryList
    //parseQueryList(tokens);
    //checkComments(tokens);
    //EOF
    //checkTerminals(TokenType::EOF_TYPE, tokens);
}

