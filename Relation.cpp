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
    Relation* newRelation = new Relation(this->name, this->header);

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

Relation* Relation::select(int index1, int index2) {
    //this is checking if two columns have the same value so it gives you two column indexes
    //got through all the tuples, check the value of both columns
    //if they are the same, save the row in the new relation
    std::string val1;
    std::string val2;
    Relation* newRelation = new Relation(this->name, this->header);

    for (std::set<Tuple*>::iterator itr = tuples.begin(); itr != tuples.end(); itr++) {
        val1 = (*itr)->getValue(index1);
        val2 = (*itr)->getValue(index2);

        if (val1 == val2) {
            newRelation->addTuple(*itr);
        }
    }

    return newRelation;
}

Relation* Relation::project(std::vector<int> indices) {
    //go through the tuples and keep the values at the indexes that are in the vector
    //need to edit the header, go through the header and copy the attributes that you want into a new header
    Tuple* newTuple;
    Header* newHeader = this->header->projectHeader(indices);
    Relation* newRelation = new Relation(this->name, newHeader);

    for (std::set<Tuple*>::iterator itr = tuples.begin(); itr != tuples.end(); itr++) {
        newTuple = (*itr)->projectTuple(indices);
        newRelation->addTuple(newTuple);
    }

    return newRelation;
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

