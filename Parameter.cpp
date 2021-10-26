//
// Created by jharw on 9/27/2021.
//

#include "Parameter.h"
Parameter::Parameter(std::string p, bool isConstant) {
    this->p = p;
    this->isConstant = isConstant;
}

std::string Parameter::toString() {
    std::string parameterString = p;
    return parameterString;
}

std::string Parameter::getP() {
    return p;
}

void Parameter::setConstant(bool isConstant) {
    this->isConstant = isConstant;
}