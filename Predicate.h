//
// Created by jharw on 9/27/2021.
//

#ifndef PROJECT_1_PREDICATE_H
#define PROJECT_1_PREDICATE_H

#include "Parameter.h"
#include <string>
#include <vector>

class Predicate {
public:
    Predicate(std::string id);
    void addParameters(Parameter* parameter);
    int getSize();
    std::vector<std::string> getParameters();
    std::string getParameter(int index);
    std::string getId();
    std::string toString();
private:
    std::string id;
    std::vector<Parameter*> parameters;
};


#endif //PROJECT_1_PREDICATE_H
