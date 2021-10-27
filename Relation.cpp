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
    //so the index is the column that you want to look at and the value is the value in that column that you want to look for
    //the attributes shouldn't change right?
    std::string currValue;
    Header* newHeader = this->header;
    Relation* newRelation = new Relation(this->name, newHeader);

    //this is the column that we are looking at
    //std::string attribute = this->header->getValue(index);
    //the index tells you what index in the tuple to look at
    //look at every tuple, check the value of the column you are looking at
    //if it is the same as the value you are looking for, save the row to the new relation
    for (std::set<Tuple*>::iterator itr = tuples.begin(); itr != tuples.end(); itr++) {
        currValue = (*itr)->getValue(index);
        if (currValue == value) {
            newRelation->addTuple(*itr);
        }
    }

    return newRelation;
}

Relation* Relation::select(int index, int index1) {
    //TODO
    //this is checking if two columns have the same value so it gives you two column indexes
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

