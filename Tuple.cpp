//
// Created by jharw on 10/25/2021.
//

#include "Tuple.h"

bool Tuple::operator<(const Tuple &rhs) const {
    return values < rhs.values;
}

std::string Tuple::getValue(int index) {
    return values.at(index);
}