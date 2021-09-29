//
// Created by jharw on 9/27/2021.
//

#include "Parser.h"
#include <iostream>

void Parser::parse(std::vector<Token *> &tokens) {
    filterComments(tokens);
    try {
        parseDatalogProgram(tokens);
    }
    catch(Token* error) {
        std::cout << "Failure!" << std::endl;
        std::cout << error->toString();
    }
    if (tokens.empty()) {
        std::cout << "Success!" << std::endl;
    }
}

bool Parser::Match(TokenType type, TokenType matchType) {
    if (type == matchType)
        return true;
    else
        return false;
}

void Parser::checkTerminals(TokenType type, std::vector<Token*> &tokens) {
    if (type == TokenType::SCHEMES || type == TokenType::RULES || type == TokenType::QUERIES || type == TokenType::FACTS) {
        if (Match(tokens.at(0)->getType(), type) && Match(tokens.at(1)->getType(), TokenType::COLON)) {
            tokens.erase(tokens.begin() + 0);
            tokens.erase(tokens.begin() + 0);
        }
        else {
            //throw an exception, not an interception
            throw tokens.at(0);
        }
    }
    else {
        if (Match(tokens.at(0)->getType(), type)) {
            tokens.erase(tokens.begin() + 0);
        }
        else {
            //throw an exception, not an interception
            throw tokens.at(0);
        }
    }
}

void Parser::filterComments(std::vector<Token *> &tokens) {
    for (int i = 0; i < tokens.size(); i++) {
        while (tokens.at(i)->getType() == TokenType::COMMENT) {
            tokens.erase(tokens.begin() + i);
        }
    }
}

void Parser::parseDatalogProgram(std::vector<Token *> &tokens) {
    //SCHEMES & COLON
    checkTerminals(TokenType::SCHEMES, tokens);
    //scheme
    parseScheme(tokens);
    //schemeList
    parseSchemeList(tokens);
    //FACTS & COLON
    checkTerminals(TokenType::FACTS, tokens);
    //factList
    parseFactList(tokens);
    //RULES & COLON
    checkTerminals(TokenType::RULES, tokens);
    //ruleList
    parseRuleList(tokens);
    //QUERIES & COLON
    checkTerminals(TokenType::QUERIES, tokens);
    //query
    parseQuery(tokens);
    //queryList
    parseQueryList(tokens);
    //EOF
    checkTerminals(TokenType::EOF_TYPE, tokens);
}

void Parser::parseScheme(std::vector<Token *> &tokens) {
    //ID
    checkTerminals(TokenType::ID, tokens);
    //LEFT_PAREN
    checkTerminals(TokenType::LEFT_PAREN, tokens);
    //ID
    checkTerminals(TokenType::ID, tokens);
    //idList
    parseIdList(tokens);
    //RIGHT_PAREN
    checkTerminals(TokenType::RIGHT_PAREN, tokens);
}

void Parser::parseIdList(std::vector<Token *> &tokens) {
    //COMMA
    checkTerminals(TokenType::COMMA, tokens);
    //ID
    checkTerminals(TokenType::ID, tokens);
    //idList
    if (tokens.at(0)->getType() == TokenType::COMMA) {
        parseIdList(tokens);
    }
    //lambda
}

void Parser::parseSchemeList(std::vector<Token*> &tokens) {
    if (tokens.at(0)->getType() == TokenType::ID) {
        parseScheme(tokens);
        parseSchemeList(tokens);
    }
    //Lambda
}

void Parser::parseFactList(std::vector<Token *> &tokens) {
    if (tokens.at(0)->getType() == TokenType::ID) {
        parseFact(tokens);
        parseFactList(tokens);
    }
    //Lambda
}

void Parser::parseFact(std::vector<Token *> &tokens) {
    //ID
    checkTerminals(TokenType::ID, tokens);
    //LEFT_PAREN
    checkTerminals(TokenType::LEFT_PAREN, tokens);
    //STRING
    checkTerminals(TokenType::STRING, tokens);
    //stringList
    parseStringList(tokens);
    //RIGHT_PAREN
    checkTerminals(TokenType::RIGHT_PAREN, tokens);
    //PERIOD
    checkTerminals(TokenType::PERIOD, tokens);
}

void Parser::parseStringList(std::vector<Token *> &tokens) {
    if (tokens.at(0)->getType() == TokenType::COMMA) {
        //COMMA
        checkTerminals(TokenType::COMMA, tokens);
        //STRING
        checkTerminals(TokenType::STRING, tokens);
        //stringList
        parseStringList(tokens);
    }
    //Lambda
}

void Parser::parseRuleList(std::vector<Token *> &tokens) {
    if (tokens.at(0)->getType() == TokenType::ID) {
        parseRule(tokens);
        parseRuleList(tokens);
    }
    //Lambda
}

void Parser::parseRule(std::vector<Token *> &tokens) {
    //headPredicate
    parseHeadPredicate(tokens);
    //COLON_DASH
    checkTerminals(TokenType::COLON_DASH, tokens);
    //predicate
    parsePredicate(tokens);
    //predicateList
    parsePredicateList(tokens);
    //PERIOD
    checkTerminals(TokenType::PERIOD, tokens);
}

void Parser::parseHeadPredicate(std::vector<Token *> &tokens) {
    //ID
    checkTerminals(TokenType::ID, tokens);
    //LEFT_PAREN
    checkTerminals(TokenType::LEFT_PAREN, tokens);
    //ID
    checkTerminals(TokenType::ID, tokens);
    //idList
    parseIdList(tokens);
    //RIGHT_PAREN
    checkTerminals(TokenType::RIGHT_PAREN, tokens);
}

void Parser::parsePredicate(std::vector<Token *> &tokens) {
    //ID
    checkTerminals(TokenType::ID, tokens);
    //LEFT_PAREN
    checkTerminals(TokenType::LEFT_PAREN, tokens);
    //parameter
    parseParameter(tokens);
    //parameterList
    parseParameterList(tokens);
    //RIGHT_PAREN
    checkTerminals(TokenType::RIGHT_PAREN, tokens);
}

void Parser::parsePredicateList(std::vector<Token *> &tokens) {
    if (tokens.at(0)->getType() == TokenType::COMMA) {
        //COMMA
        checkTerminals(TokenType::COMMA, tokens);
        //predicate
        parsePredicate(tokens);
        //predicateList
        parsePredicateList(tokens);
    }
    //Lambda
}

void Parser::parseParameter(std::vector<Token *> &tokens) {
    if (tokens.at(0)->getType() == TokenType::STRING) {
        checkTerminals(TokenType::STRING, tokens);
    } else if (tokens.at(0)->getType() == TokenType::ID) {
        checkTerminals(TokenType::ID, tokens);
    } else {
        throw tokens.at(0);
    }

}

void Parser::parseParameterList(std::vector<Token *> &tokens) {
    if (tokens.at(0)->getType() == TokenType::COMMA) {
        //COMMA
        checkTerminals(TokenType::COMMA, tokens);
        //parameter
        parseParameter(tokens);
        //parameterList
        parseParameterList(tokens);
    }
    //Lambda
}

void Parser::parseQuery(std::vector<Token *> &tokens) {
    //predicate
    parsePredicate(tokens);
    //Q_MARK
    checkTerminals(TokenType::Q_MARK, tokens);
}

void Parser::parseQueryList(std::vector<Token *> &tokens) {
    if (tokens.at(0)->getType() == TokenType::ID) {
        //query
        parseQuery(tokens);
        //queryList
        parseQueryList(tokens);
    }
    //Lambda
}