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

void Tuple::addValue(std::string value) {
    values.push_back(value);
}

Tuple* Tuple::projectTuple(std::vector<int> indices) {
    Tuple* newTuple = new Tuple();
    for (unsigned int i = 0; i < values.size(); i++) {
        for (unsigned int j = 0; j < indices.size(); i++) {
            if (i == indices.at(j)) {
                newTuple->addValue(values.at(i));
            }
        }
    }

    return newTuple;
}