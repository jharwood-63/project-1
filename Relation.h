//
// Created by jharw on 10/25/2021.
//

#ifndef PROJECT_1_RELATION_H
#define PROJECT_1_RELATION_H

#include "Tuple.h"
#include "Header.h"
#include <set>
#include <map>
#include <string>
#include <iostream>

class Relation {
private:
    std::set<Tuple> tuples;
    std::string name;
    Header* header;

    Header* combineHeader(Header* headB, std::vector<std::pair<int, int> > &attributeIndices);
    bool isJoinable(Tuple t1, Tuple t2, int index1, int index2);
    Tuple joinTuple(Tuple t1, Tuple t2, int index2);
public:
    Relation(std::string name, Header* header);
    void addTuple(Tuple newTuple);
    std::string getName();
    std::string getAttribute(int index);
    int getRowSize();

    Relation* select(int index, std::string);
    Relation* select(int index1, int index2);
    Relation* project(std::vector<int> indices);
    Relation* rename(std::vector<std::string> newAttributes);
    Relation* join(Relation* r2, std::string ruleName);
    Relation* unite(Relation* ruleResult);

    void toString();
};


#endif //PROJECT_1_RELATION_H
