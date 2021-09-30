//
// Created by jharw on 9/27/2021.
//

#include "Parameter.h"
Parameter::Parameter(std::string p) {
    this->p = p;
}

std::string Parameter::toString() {
    std::string parameterString = p;
    return parameterString;
}