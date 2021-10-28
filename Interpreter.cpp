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
        Tuple newTuple = Tuple();
        for (unsigned int j = 0; j < currFact->getSize(); j++) {
            newTuple.addValue(currFact->getParameter(j));
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
    std::string currParameter;
    int index;
    bool isConstant;
    bool isDuplicate;
    std::vector<std::string> allAttributes;
    std::vector<std::string> renameAttributes;
    std::vector<int> indices;
    std::vector<std::string> parameterStrings = predicate->getParameters();
    std::map<int, std::string> saveVars;

    //grab the relation with the same name as the query
    Relation* relation = findRelation(predicate);
    //Relation* newRelation = relation;
    //look through the parameters
    for (unsigned int i = 0; i < predicate->getSize(); i++) {
        currParameter = parameterStrings.at(i);
        isConstant = setConstant(currParameter);
        if (isConstant) {
            //constant -> select type 1
            index = findIndex(parameterStrings, currParameter, false);
            relation = relation->select(index, currParameter);
            allAttributes.push_back(relation->getAttribute(index));
        }
        else {
            //variable -> check if it is a duplicate, if yes run select type 2
            isDuplicate = checkVector(allAttributes, currParameter);
            index = findIndex(parameterStrings, currParameter, isDuplicate);
            saveVars.insert({index, currParameter});
            if (isDuplicate) {
                int index2 = searchMap(saveVars, currParameter, index);
                relation = relation->select(index, index2);
            }
            else {
                indices.push_back(index);
                renameAttributes.push_back(currParameter);
            }
            //save the attribute in the order we saw it
            allAttributes.push_back(currParameter);
        }
    }
    //project all to a new relation
    relation = relation->project(indices);
    //rename the attributes
    relation = relation->rename(renameAttributes);
    return relation;
}

void Interpreter::evaluateQueries() {
    Relation* output;
    std::vector<Predicate*> queries = datalogProgram->queries;
    for (unsigned int i = 0; i < queries.size(); i++) {
        Predicate* query = queries.at(i);
        output = evaluatePredicate(query);
        //add to string stuff
        toString(query, output);
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

int Interpreter::findIndex(std::vector<std::string> parameterStrings, std::string parameterId, bool isDuplicate) {
    //look through the list
    for (unsigned int i = 0; i < parameterStrings.size(); i++) {
        if (parameterStrings.at(i) == parameterId && !isDuplicate) {
            return i;
        }
        else if (parameterStrings.at(i) == parameterId && isDuplicate) {
            isDuplicate = false;
        }
    }
}

bool Interpreter::checkVector(std::vector<std::string> saveVars, std::string var) {
    //checks if there is a duplicate variable
    for (unsigned int i = 0; i < saveVars.size(); i++) {
        if (saveVars.at(i) == var) {
            return true;
        }
    }

    return false;
}

int Interpreter::searchMap(std::map<int, std::string> saveVars, std::string var, int index) {
    for(std::map<int, std::string>::iterator itr = saveVars.begin(); itr != saveVars.end(); itr++) {
        if (itr->second == var && itr->first != index) {
            return itr->first;
        }
    }
}

bool Interpreter::checkAllConst(Predicate* query) {
    int count = 0;
    for (unsigned int i = 0; i < query->getSize(); i++) {
        if (query->getParameters().at(i).substr(0, 1) == "\'") {
            count++;
        }
    }

    if(count == query->getSize())
        return true;
    else
        return false;
}

void Interpreter::toString(Predicate *query, Relation *relation) {
    //print everything out
    int numRows = relation->getRowSize();
    bool bothConstant;
    if (numRows != 0) {
        std::cout << query->toString() << " Yes(" << numRows << ")\n";
        if (!checkAllConst(query)) {
            relation->toString();
        }
    }
    else {
        std::cout << query->toString() << " No\n";
    }

}


