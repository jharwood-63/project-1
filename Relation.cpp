//
// Created by jharw on 10/25/2021.
//

#include "Relation.h"

Relation::Relation(std::string name, Header* header) {
    this->name = name;
    this->header = header;
}

void Relation::addTuple(Tuple* newTuple) {
    tuples.insert(newTuple);
}

std::string Relation::getName() {
     return name;
}

Relation* Relation::select(int index, std::string value) {
    //TODO
    //the attributes shouldn't change right?
    Header* newHeader = this->header;
}

Relation* Relation::select(int index, int index1) {
    //TODO
}

Relation* Relation::project(std::vector<int> indices) {
    //TODO
}

Relation* Relation::rename(std::vector<std::string> newAttributes) {
    //create the new header with the new attribute names
    Header* newHeader = new Header();
    for (unsigned int i = 0; i < newAttributes.size(); i++) {
        newHeader->addAttribute(newAttributes.at(i));
    }
    //create the new relation
    Relation* newRelation = new Relation(this->name, newHeader);
    //take the tuples from this relation and add them to the new one
    for (std::set<Tuple*>::iterator itr = tuples.begin(); itr != tuples.end(); itr++) {
        newRelation->addTuple(*itr);
    }
    return newRelation;
}

void Relation::toString() {
    int headerIndex;

    for(Tuple* t : tuples) {
        headerIndex = 0;
        while (headerIndex < header->getSize()) {
            if ((headerIndex + 1) != header->getSize()) {
                std::cout << header->getValue(headerIndex) << "=" << t->getValue(headerIndex) << ", ";
            } else {
                std::cout << header->getValue(headerIndex) << "=" << t->getValue(headerIndex) << std::endl;
            }
            headerIndex++;
        }
    }
}

