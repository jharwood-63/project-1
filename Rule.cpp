//
// Created by jharw on 9/27/2021.
//

#include "Rule.h"
/*
Rule::Rule(Predicate* headPredicate) {
    this->headPredicate = headPredicate;
}
*/
void Rule::addBodyPredicates(Predicate* predicate) {
    bodyPredicates.push_back(predicate);
}

void Rule::setHeadPredicate(Predicate* headPredicate) {
    this->headPredicate = headPredicate;
}

Predicate* Rule::getHeadPredicate() {
    return headPredicate;
}

Predicate* Rule::getBodyPredicate(int index) {
    return bodyPredicates.at(index);
}

int Rule::getBodyPredicateSize() {
    return bodyPredicates.size();
}

std::string Rule::toString() {
    std::string ruleString = headPredicate->toString() + " :- ";
    for (unsigned int i = 0; i < bodyPredicates.size(); i++) {
        if (i != (bodyPredicates.size() - 1))
            ruleString += bodyPredicates.at(i)->toString() + ",";
        else
            ruleString += bodyPredicates.at(i)->toString() + ".";
    }
    return ruleString;
}