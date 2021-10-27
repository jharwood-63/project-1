//
// Created by jharw on 10/25/2021.
//

#include "Interpreter.h"

Interpreter::Interpreter(DatalogProgram* datalogProgram, Database* database) {
    this->datalogProgram = datalogProgram;
    this->database = database;

    createRelations();
    createTuples();
}

void Interpreter::createRelations() {
    int headerSize;
    Predicate* currScheme;
    Header* newHeader;
    Relation* newRelation;
    //run through the schemes
    for(unsigned int i = 0; i < datalogProgram->schemes.size(); i++) {
        //add attributes to the header
        currScheme = datalogProgram->schemes.at(i);
        newHeader = new Header();
        headerSize = currScheme->getSize();
        for (unsigned int j = 0; j < headerSize; j++) {
            newHeader->addAttribute(currScheme->getParameter(j));
        }
        //create the relation
        newRelation = new Relation(currScheme->getId(), newHeader);
        database->addToMap(newRelation);
    }
    //delete newHeader;
    //delete newRelation;
}

void Interpreter::createTuples() {
    Predicate* currFact;
    std::string currFactName;
    //run through facts and create the tuple
    for (unsigned int i = 0; i < datalogProgram->facts.size(); i++) {
        currFact = datalogProgram->facts.at(i);
        currFactName = currFact->getId();
        Tuple* newTuple = new Tuple();
        for (unsigned int j = 0; j < currFact->getSize(); j++) {
            newTuple->addValue(currFact->getParameter(j));
        }
        //look through relations to find the correct one and add the tuple to it
        for (std::map<std::string, Relation*>::iterator itr = database->dataMap.begin(); itr != database->dataMap.end(); itr++) {
            if (currFactName == itr->second->getName()) {
                itr->second->addTuple(newTuple);
            }
        }
    }
}

Relation* Interpreter::evaluatePredicate(Predicate p) {

}

void Interpreter::evaluateQueries() {

}