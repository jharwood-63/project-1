//
// Created by jharw on 10/25/2021.
//

#include "Relation.h"

Relation::Relation(std::string name, Header* header) {
    this->name = name;
    this->header = header;
}

void Relation::addTuple(Tuple* newTuple) {
    tuples.insert(*newTuple);
}

std::string Relation::getName() {
     return name;
}

Relation* Relation::select(int index, std::string value) {
    //TODO
    
}

Relation* Relation::select(int index, int index1) {
    //TODO
}

Relation* Relation::project(std::vector<int> indices) {
    //TODO
}

Relation* Relation::rename(std::vector<std::string> newAttributes) {
    //TODO
}

void Relation::toString() {
    int headerIndex;

    for(Tuple t : tuples) {
        headerIndex = 0;
        while (headerIndex < header->getSize()) {
            if ((headerIndex + 1) != header->getSize()) {
                std::cout << header->getValue(headerIndex) << "=" << t.getValue(headerIndex) << ", ";
            } else {
                std::cout << header->getValue(headerIndex) << "=" << t.getValue(headerIndex) << std::endl;
            }
            headerIndex++;
        }
    }
}

