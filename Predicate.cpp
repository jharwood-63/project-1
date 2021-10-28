//
// Created by jharw on 9/27/2021.
//

#include "Predicate.h"

Predicate::Predicate(std::string id) {
    this->id = id;
}

void Predicate::addParameters(Parameter* parameter) {
    parameters.push_back(parameter);
}

std::string Predicate::getId() {
    return id;
}

std::string Predicate::getParameter(int index) {
    return parameters.at(index)->getP();
}

int Predicate::getSize() {
    return parameters.size();
}

std::vector<std::string> Predicate::getParameters() {
    std::vector<std::string> parameterStrings;
    for (unsigned int i = 0; i < parameters.size(); i++) {
        parameterStrings.push_back(parameters.at(i)->getP());
    }

    return parameterStrings;
}

std::string Predicate::toString() {
    std::string predicateString = id + "(";
    for (unsigned int i = 0; i < parameters.size(); i++) {
        if (i != (parameters.size() - 1))
            predicateString += parameters.at(i)->toString() + ",";
        else
            predicateString += parameters.at(i)->toString();
    }
    predicateString += ")?";
    return predicateString;
}