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

Tuple Tuple::projectTuple(std::vector<int> indices, bool reorder) {
    Tuple newTuple = Tuple();
    int valueSize = values.size();
    int indexSize = indices.size();

    if (!reorder) {
        for (int i = 0; i < valueSize; i++) {
            for (int j = 0; j < indexSize; j++) {
                if (i == indices.at(j)) {
                    newTuple.addValue(values.at(i));
                }
            }
        }
    }
    else {
        int index = 0;
        while (index < indexSize) {
            newTuple.addValue(values.at(indices.at(index)));
            index++;
        }
    }

    return newTuple;
}

int Tuple::getSize() {
    return values.size();
}

void Tuple::switchTuple(int switchIndex, int next, std::vector<int> indices) {
    std::string temp = values.at(indices.at(switchIndex));
    values.at(indices.at(switchIndex)) = values.at(indices.at(next));
    values.at(indices.at(next)) = temp;
}