//
// Created by jharw on 10/25/2021.
//

#include "Relation.h"

Relation::Relation(std::string name, Header* header) {
    this->name = name;
    this->header = header;
}

void Relation::addTuple(Tuple newTuple) {
    tuples.insert(newTuple);
}

void Relation::addTuple(Tuple newTuple, int &changes) {
    if (tuples.insert(newTuple).second) {
        changes++;
    }
}

std::string Relation::getName() {
     return name;
}

std::string Relation::getAttribute(int index) {
    return this->header->getValue(index);
}

int Relation::getRowSize() {
    return tuples.size();
}

int Relation::getHeaderSize() {
    return header->getSize();
}

std::set<Tuple> Relation::getTuples() {
    return this->tuples;
}

Relation* Relation::select(int index, std::string value) {
    //so the index is the column that you want to look at and the value is the value in that column that you want to look for
    //the attributes shouldn't change right?
    std::string currValue;
    Relation* newRelation = new Relation(this->name, this->header);

    //this is the column that we are looking at
    //the index tells you what index in the tuple to look at
    //look at every tuple, check the value of the column you are looking at
    //if it is the same as the value you are looking for, save the row to the new relation
    for (Tuple t : tuples) {
        currValue = t.getValue(index);
        if (currValue == value) {
            newRelation->addTuple(t);
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

    for (Tuple t : tuples) {
        val1 = t.getValue(index1);
        val2 = t.getValue(index2);

        if (val1 == val2) {
            newRelation->addTuple(t);
        }
    }

    return newRelation;
}

Relation* Relation::project(std::vector<int> indices) {
    //go through the tuples and keep the values at the indexes that are in the vector
    //need to edit the header, go through the header and copy the attributes that you want into a new header
    bool reorder = needsReorder(indices);
    Tuple newTuple;
    Header* newHeader = this->header->projectHeader(indices);
    Relation* newRelation = new Relation(this->name, newHeader);

    for (Tuple t : tuples) {
        newTuple = t.projectTuple(indices, reorder);
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
    for (Tuple t : tuples) {
        newRelation->addTuple(t);
    }
    return newRelation;
}

Relation* Relation::join(Relation* r2, std::string ruleName) {
    //r1 is this->relation, r2 is the parameter
    //make the header for the result of the relation (no duplicate attributes)
    std::vector<std::pair<int, int> > attributeIndices;
    Header* newHeader = combineHeader(r2->header, attributeIndices);
    unsigned int index = 0;
    //make a new empty relation using the new header
    Relation* newRelation = new Relation(ruleName, newHeader);
    for(Tuple t1 : this->tuples) {
        for(Tuple t2 : r2->tuples) {
            //this isnt right, it cant be the attributeIndices size
            //what if we put the loop inside the is joinable
            if (isJoinable(t1, t2, attributeIndices)) {
                //join the tuples
                //add to the relation
                newRelation->addTuple(joinTuple(t1, t2, attributeIndices.at(index).second));
            }
        }
    }

    return newRelation;
}

void Relation::unite(Relation* ruleResult, int &changes) {
    //this->relation is database relation, ruleResult is the result of the rule
    std::set<Tuple> ruleTuples = ruleResult->getTuples();
    for (Tuple t : ruleTuples) {
        this->addTuple(t, changes);
    }
}

bool Relation::needsReorder(std::vector<int> indices) {
    for (unsigned int i = 0; i < indices.size(); i++) {
        if ((i != indices.size() - 1) && indices.at(i) > indices.at(i + 1)) {
            return true;
        }
    }
    return false;
}

Header* Relation::combineHeader(Header* headB, std::vector<std::pair<int, int> > &attributeIndices) {
    Header* newHeader = this->header;
    for (unsigned int i = 0; i < headB->getSize(); i++) {
        //this might need to be newHeader->find
        int headerAIndex = this->header->find(headB->getValue(i));
        if (headerAIndex != -1) {
            std::pair<int, int> newPair(headerAIndex, i);
            attributeIndices.push_back(newPair);
        }
        else {
            newHeader->addAttribute(headB->getValue(i));
        }
    }

    return newHeader;
}

bool Relation::isJoinable(Tuple t1, Tuple t2, std::vector<std::pair<int, int> > attributeIndices) {
    int count = 0;
    for (unsigned int i = 0; i < attributeIndices.size(); i++) {
        if (t1.getValue(attributeIndices.at(i).first) == t2.getValue(attributeIndices.at(i).second))
            count++;
    }

    if (count == attributeIndices.size())
        return true;
    else
        return false;
}

Tuple Relation::joinTuple(Tuple t1, Tuple t2, int index2) {
    Tuple newTuple = t1;
    int size2 = t2.getSize();
    for (unsigned int i = 0; i < size2; i++) {
        if (i != index2)
            newTuple.addValue(t2.getValue(i));
    }

    return newTuple;
}

void Relation::toString() {
    int headerIndex;

    for(Tuple t : tuples) {
        headerIndex = 0;
        while (headerIndex < header->getSize()) {
            if ((headerIndex + 1) != header->getSize()) {
                std::cout << "  " << header->getValue(headerIndex) << "=" << t.getValue(headerIndex) << ", ";
            } else {
                std::cout << "  " << header->getValue(headerIndex) << "=" << t.getValue(headerIndex) << std::endl;
            }
            headerIndex++;
        }
    }
}

