//
// Created by jharw on 9/27/2021.
//

#ifndef PROJECT_1_RULE_H
#define PROJECT_1_RULE_H

#include "Predicate.h"
#include <vector>

class Rule {
public:
    //Rule(Predicate* headPredicate);
    void addBodyPredicates(Predicate* predicate);
    void setHeadPredicate(Predicate* headPredicate);
    std::string toString();
private:
    Predicate* headPredicate;
    std::vector<Predicate*> bodyPredicates;
};


#endif //PROJECT_1_RULE_H
