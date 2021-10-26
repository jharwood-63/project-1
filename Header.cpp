//
// Created by jharw on 10/25/2021.
//

#include "Header.h"

int Header::getSize() {
    return attributes.size();
}

std::string Header::getValue(int index) {
    return attributes.at(index);
}

void Header::addAttribute(std::string attribute) {
    attributes.push_back(attribute);
}