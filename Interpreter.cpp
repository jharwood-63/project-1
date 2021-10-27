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
        headerSize = currScheme->getSize(); //get size refers to the number of parameters, may need to rename it
        for (unsigned int j = 0; j < headerSize; j++) {
            newHeader->addAttribute(currScheme->getParameter(j));
        }
        //create the relation
        newRelation = new Relation(currScheme->getId(), newHeader);
        database->addToMap(newRelation);
    }
    //if we put this inside the loop after the add to database would that work?
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

Relation* Interpreter::evaluatePredicate(Predicate* predicate) {
    //TODO
    std::string currParameter;
    int index1;
    int index2;
    bool isConstant;
    bool isDuplicate;
    std::vector<std::string> newAttributes;
    std::vector<std::string> parameterStrings = predicate->getParameters();

    //grab the relation with the same name as the query
    Relation* relation = findRelation(predicate);
    Relation* newRelation;
    //look through the parameters
    for (unsigned int i = 0; i < predicate->getSize(); i++) {
        currParameter = predicate->getParameter(i);
        isConstant = setConstant(currParameter);
        if (isConstant) {
            //constant -> select type 1
            index1 = findIndex1(parameterStrings, currParameter);
            newRelation = relation->select(index1, currParameter);
        }
        else {
            //duplicate variables -> select type 2
            isDuplicate = checkDuplicates(parameterStrings, currParameter);
            if (isDuplicate) {
                index1 = findIndex1(predicate->getParameters(), currParameter);
                index2 = findIndex2(predicate->getParameters(), currParameter);
                newRelation->select(index1, index2);
            }

            //singular variable -> save for project and rename
        }

    }

    //project all to a new relation
    //rename the attributes
}

void Interpreter::evaluateQueries() {
    //TODO
    //FIXME: for testing
    for (unsigned int i = 0; i < datalogProgram->queries.size(); i++) {
        evaluatePredicate(datalogProgram->queries.at(i));
    }
}

Relation* Interpreter::findRelation(Predicate* p) {
    for (std::map<std::string, Relation*>::iterator itr = database->dataMap.begin(); itr != database->dataMap.end(); itr++) {
        if (p->getId() == itr->second->getName()) {
            return itr->second;
        }
    }
}

bool Interpreter::setConstant(std::string parameterId) {
    if (parameterId.substr(0, 1) == "\'")
        return true;
    else
        return false;
}

int Interpreter::findIndex1(std::vector<std::string> parameterStrings, std::string parameterId) {
    //look through the list
    for (unsigned int i = 0; i < parameterStrings.size(); i++) {
        if (parameterStrings.at(i) == parameterId) {
            return i;
        }
    }
}

int Interpreter::findIndex2(std::vector<std::string> parameterStrings, std::string parameterId) {
    bool second = false;
    for (unsigned int i = 0; i < parameterStrings.size(); i++) {
        if((parameterStrings.at(i) == parameterId) && second) {
            return i;
        }
        else if ((parameterStrings.at(i) == parameterId) && !second) {
            second = true;
        }
    }
}

bool Interpreter::checkDuplicates(std::vector<std::string> parameterStrings, std::string parameterId) {
    //checks if there is a duplicate variable
    int count = 0;
    for (unsigned int i = 0; i < parameterStrings.size(); i++) {
        if (parameterStrings.at(i) == parameterId) {
            count++;
        }
    }

    if (count > 1)
        return true;
    else
        return false;
}
