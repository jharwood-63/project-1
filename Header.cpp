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

Header* Header::projectHeader(std::vector<int> indices) {
    //go though this header and copy the attributes that you want into a new header
    Header* newHeader = new Header();
    for (unsigned int i = 0; i < attributes.size(); i++) {
        for (unsigned int j = 0; j < indices.size(); j++) {
            if (i == indices.at(j)) {
                newHeader->addAttribute(attributes.at(i));
            }
        }
    }

    return newHeader;
}