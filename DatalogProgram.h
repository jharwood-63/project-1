//
// Created by jharw on 9/27/2021.
//

#ifndef PROJECT_1_DATALOGPROGRAM_H
#define PROJECT_1_DATALOGPROGRAM_H

#include <vector>
#include <iostream>
#include "Predicate.h"
#include "Rule.h"

class DatalogProgram {
public:
    std::vector<Predicate*> schemes;
    std::vector<Predicate*> facts;
    std::vector<Predicate*> queries;
    std::vector<Rule*> rules;

    void toString();
};


#endif //PROJECT_1_DATALOGPROGRAM_H
