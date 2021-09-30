//
// Created by jharw on 9/27/2021.
//

#include "Parser.h"
#include <iostream>

void Parser::parse(std::vector<Token *> &tokens) {
    filterComments(tokens);
    DatalogProgram* program = new DatalogProgram();
    try {
        parseDatalogProgram(tokens, program);
    }
    catch(Token* error) {
        std::cout << "Failure!\n  " << error->toString();
    }
    if (tokens.empty()) {
        std::cout << "Success!" << std::endl;
        program->toString();
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
    for (unsigned int i = 0; i < tokens.size(); i++) {
        while (tokens.at(i)->getType() == TokenType::COMMENT) {
            tokens.erase(tokens.begin() + i);
        }
    }
}

void Parser::parseDatalogProgram(std::vector<Token *> &tokens, DatalogProgram* &program) {
    //SCHEMES & COLON
    checkTerminals(TokenType::SCHEMES, tokens);
    //scheme
    parseScheme(tokens, program);
    //schemeList
    parseSchemeList(tokens, program);
    //FACTS & COLON
    checkTerminals(TokenType::FACTS, tokens);
    //factList
    parseFactList(tokens, program);
    //RULES & COLON
    checkTerminals(TokenType::RULES, tokens);
    //ruleList
    parseRuleList(tokens, program);
    //QUERIES & COLON
    checkTerminals(TokenType::QUERIES, tokens);
    //query
    parseQuery(tokens, program);
    //queryList
    parseQueryList(tokens, program);
    //EOF
    checkTerminals(TokenType::EOF_TYPE, tokens);
}

void Parser::parseScheme(std::vector<Token *> &tokens, DatalogProgram* &program) {
    //ID
    Predicate* newScheme = new Predicate(tokens.at(0)->getDescription());
    checkTerminals(TokenType::ID, tokens);
    //LEFT_PAREN
    checkTerminals(TokenType::LEFT_PAREN, tokens);
    //ID
    Parameter* newParameter = new Parameter(tokens.at(0)->getDescription());
    newScheme->addParameters(newParameter);
    checkTerminals(TokenType::ID, tokens);
    //idList
    parseIdList(tokens, newScheme);
    //RIGHT_PAREN
    checkTerminals(TokenType::RIGHT_PAREN, tokens);
    program->schemes.push_back(newScheme);
}

void Parser::parseIdList(std::vector<Token *> &tokens, Predicate* &newPredicate) {
    //COMMA
    if (tokens.at(0)->getType() == TokenType::COMMA) {
        checkTerminals(TokenType::COMMA, tokens);
        //ID
        Parameter* newParameter = new Parameter(tokens.at(0)->getDescription());
        newPredicate->addParameters(newParameter);
        checkTerminals(TokenType::ID, tokens);
        //idList
        parseIdList(tokens, newPredicate);
    }
    //lambda
}
/*
void Parser::parseRuleIdList(std::vector<Token *> &tokens) {
    //COMMA
    checkTerminals(TokenType::COMMA, tokens);
    //ID
    checkTerminals(TokenType::ID, tokens);
    //idList
    if (tokens.at(0)->getType() == TokenType::COMMA) {
        parseRuleIdList(tokens);
    }
}
*/
void Parser::parseSchemeList(std::vector<Token*> &tokens, DatalogProgram* &program) {
    if (tokens.at(0)->getType() == TokenType::ID) {
        parseScheme(tokens, program);
        parseSchemeList(tokens, program);
    }
    //Lambda
}

void Parser::parseFactList(std::vector<Token *> &tokens, DatalogProgram* &program) {
    if (tokens.at(0)->getType() == TokenType::ID) {
        parseFact(tokens, program);
        parseFactList(tokens, program);
    }
    //Lambda
}

void Parser::parseFact(std::vector<Token *> &tokens, DatalogProgram* &program) {
    //ID
    Predicate* newFact = new Predicate(tokens.at(0)->getDescription());
    checkTerminals(TokenType::ID, tokens);
    //LEFT_PAREN
    checkTerminals(TokenType::LEFT_PAREN, tokens);
    //STRING
    Parameter* newParameter = new Parameter(tokens.at(0)->getDescription());
    newFact->addParameters(newParameter);
    program->addDomain(newParameter->getP());
    checkTerminals(TokenType::STRING, tokens);
    //stringList
    parseStringList(tokens, newFact, program);
    //RIGHT_PAREN
    checkTerminals(TokenType::RIGHT_PAREN, tokens);
    //PERIOD
    checkTerminals(TokenType::PERIOD, tokens);
    program->facts.push_back(newFact);
}

void Parser::parseStringList(std::vector<Token *> &tokens, Predicate* &newPredicate, DatalogProgram* &program) {
    if (tokens.at(0)->getType() == TokenType::COMMA) {
        //COMMA
        checkTerminals(TokenType::COMMA, tokens);
        //STRING
        Parameter* newParameter = new Parameter(tokens.at(0)->getDescription());
        newPredicate->addParameters(newParameter);
        program->addDomain(newParameter->getP());
        checkTerminals(TokenType::STRING, tokens);
        //stringList
        parseStringList(tokens, newPredicate, program);
    }
    //Lambda
}

void Parser::parseRuleList(std::vector<Token *> &tokens, DatalogProgram* &program) {
    if (tokens.at(0)->getType() == TokenType::ID) {
        parseRule(tokens, program);
        parseRuleList(tokens, program);
    }
    //Lambda
}

void Parser::parseRule(std::vector<Token *> &tokens, DatalogProgram* &program) {
    //headPredicate
    Rule* newRule = new Rule();
    parseHeadPredicate(tokens, newRule);
    //COLON_DASH
    checkTerminals(TokenType::COLON_DASH, tokens);
    //predicate
    parseRulePredicate(tokens, newRule);
    //predicateList
    parsePredicateList(tokens, newRule);
    //PERIOD
    checkTerminals(TokenType::PERIOD, tokens);
    program->rules.push_back(newRule);
}

void Parser::parseHeadPredicate(std::vector<Token *> &tokens, Rule* &newRule) {
    //ID
    Predicate* headPredicate = new Predicate(tokens.at(0)->getDescription());
    newRule->setHeadPredicate(headPredicate);
    checkTerminals(TokenType::ID, tokens);
    //LEFT_PAREN
    checkTerminals(TokenType::LEFT_PAREN, tokens);
    //ID
    Parameter* newParameter = new Parameter(tokens.at(0)->getDescription());
    headPredicate->addParameters(newParameter);
    checkTerminals(TokenType::ID, tokens);
    //idList
    parseIdList(tokens, headPredicate);
    //RIGHT_PAREN
    checkTerminals(TokenType::RIGHT_PAREN, tokens);
}

void Parser::parseRulePredicate(std::vector<Token*> &tokens, Rule* &newRule) {
    //ID
    Predicate* bodyPredicate = new Predicate(tokens.at(0)->getDescription());
    newRule->addBodyPredicates(bodyPredicate);
    checkTerminals(TokenType::ID, tokens);
    //LEFT_PAREN
    checkTerminals(TokenType::LEFT_PAREN, tokens);
    //parameter
    parseParameter(tokens, bodyPredicate);
    //parameterList
    parseParameterList(tokens, bodyPredicate);
    //RIGHT_PAREN
    checkTerminals(TokenType::RIGHT_PAREN, tokens);
}

void Parser::parsePredicate(std::vector<Token *> &tokens, Predicate* &newPredicate) {
    //ID
    checkTerminals(TokenType::ID, tokens);
    //LEFT_PAREN
    checkTerminals(TokenType::LEFT_PAREN, tokens);
    //parameter
    parseParameter(tokens, newPredicate);
    //parameterList
    parseParameterList(tokens, newPredicate);
    //RIGHT_PAREN
    checkTerminals(TokenType::RIGHT_PAREN, tokens);
}

void Parser::parsePredicateList(std::vector<Token*> &tokens, Rule* &newRule) {
    if (tokens.at(0)->getType() == TokenType::COMMA) {
        //COMMA
        checkTerminals(TokenType::COMMA, tokens);
        //predicate
        parseRulePredicate(tokens, newRule);
        //predicateList
        parsePredicateList(tokens, newRule);
    }
    //Lambda
}
/*
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
*/
void Parser::parseParameter(std::vector<Token *> &tokens, Predicate* newPredicate) {
    Parameter* newParameter = new Parameter(tokens.at(0)->getDescription());
    if (tokens.at(0)->getType() == TokenType::STRING) {
        newPredicate->addParameters(newParameter);
        checkTerminals(TokenType::STRING, tokens);
    } else if (tokens.at(0)->getType() == TokenType::ID) {
        newPredicate->addParameters(newParameter);
        checkTerminals(TokenType::ID, tokens);
    } else {
        throw tokens.at(0);
    }
}

void Parser::parseParameterList(std::vector<Token *> &tokens, Predicate* &newPredicate) {
    if (tokens.at(0)->getType() == TokenType::COMMA) {
        //COMMA
        checkTerminals(TokenType::COMMA, tokens);
        //parameter
        parseParameter(tokens, newPredicate);
        //parameterList
        parseParameterList(tokens, newPredicate);
    }
    //Lambda
}

void Parser::parseQuery(std::vector<Token *> &tokens, DatalogProgram* &program) {
    //predicate
    Predicate* newQuery = new Predicate(tokens.at(0)->getDescription());
    parsePredicate(tokens, newQuery);
    //Q_MARK
    checkTerminals(TokenType::Q_MARK, tokens);
    program->queries.push_back(newQuery);
}

void Parser::parseQueryList(std::vector<Token *> &tokens, DatalogProgram* &program) {
    if (tokens.at(0)->getType() == TokenType::ID) {
        //query
        parseQuery(tokens, program);
        //queryList
        parseQueryList(tokens, program);
    }
    //Lambda
}