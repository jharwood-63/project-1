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
        for (int j = 0; j < headerSize; j++) {
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
        for (int j = 0; j < currFact->getSize(); j++) {
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
    int prevIndex = -1;
    bool isConstant;
    bool isDuplicate;
    std::vector<std::string> allAttributes;
    std::vector<std::string> renameAttributes;
    std::vector<int> indices;
    std::vector<std::string> parameterStrings = predicate->getParameters();
    std::map<int, std::string> saveVars;

    //grab the relation with the same name as the query
    Relation* relation = findRelation(predicate);
    //look through the parameters
    for (int i = 0; i < predicate->getSize(); i++) {
        currParameter = parameterStrings.at(i);
        isConstant = setConstant(currParameter);
        if (isConstant) {
            //constant -> select type 1
            index = findIndex(parameterStrings, currParameter, -1);
            relation = relation->select(index, currParameter);
            allAttributes.push_back(relation->getAttribute(index));
        }
        else {
            //variable -> check if it is a duplicate, if yes run select type 2
            isDuplicate = checkVector(allAttributes, currParameter);
            index = findIndex(parameterStrings, currParameter, prevIndex);
            prevIndex = index;
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
    std::cout << "Query Evaluation" << std::endl;
    std::vector<Predicate*> queries = datalogProgram->queries;
    for (unsigned int i = 0; i < queries.size(); i++) {
        Predicate* query = queries.at(i);
        output = evaluatePredicate(query);
        //add to string stuff
        toString(query, output);
    }
}

void Interpreter::evaluateRules() {
    /*
     * Evaluate the predicates on the right-hand side of the rule
     * Join the relations that result
     * Project the columns that appear in the head predicate
     * Rename the relation to make it union-compatible
     * Union with the relation in the database
     */
    Relation* result;
    int changes;
    int iterations = 0;
    std::vector<Rule*> rules = datalogProgram->rules;
    std::vector<Predicate*> schemes = datalogProgram->schemes;
    std::vector<Relation*> interResults;
    do {
        for (unsigned int i = 0; i < rules.size(); i++) {
            changes = 0;
            unsigned int size = rules.at(i)->getBodyPredicateSize();
            std::string ruleName = rules.at(i)->getHeadPredicate()->getId();
            //evaluate predicates on the right side of the rule
            for (unsigned int j = 0; j < size; j++) {
                Relation *newRelation = evaluatePredicate(rules.at(i)->getBodyPredicate(j));
                interResults.push_back(newRelation);
            }
            //join the relations that result
            result = interResults.at(0);
            for (unsigned int j = 1; j < size; j++) {
                result = result->join(interResults.at(j), ruleName);
            }
            interResults.clear();
            //project using the head predicate parameters
            std::vector<int> indexList = createIndexList(result, rules.at(i)->getHeadPredicate());
            result = result->project(indexList);
            //rename to the orignal parameter names from the scheme
            Predicate *scheme;
            for (unsigned int i = 0; i < schemes.size(); i++) {
                if (schemes.at(i)->getId() == ruleName) {
                    scheme = schemes.at(i);
                    break;
                }
            }
            result = result->rename(scheme->getParameters());
            //union the result with the fact in the database
            std::map<std::string, Relation *>::iterator it;
            Relation *dataRelation;
            for (it = database->dataMap.begin(); it != database->dataMap.end(); it++) {
                if (it->first == ruleName) {
                    dataRelation = it->second;
                    break;
                }
            }
            dataRelation->unite(result, changes);
            iterations++;
        }
    } while (changes != 0);
}

Relation* Interpreter::findRelation(Predicate* p) {
    for (std::map<std::string, Relation*>::iterator itr = database->dataMap.begin(); itr != database->dataMap.end(); itr++) {
        if (p->getId() == itr->second->getName()) {
            return itr->second;
        }
    }
    return nullptr;
}

bool Interpreter::setConstant(std::string parameterId) {
    if (parameterId.substr(0, 1) == "\'")
        return true;
    else
        return false;
}

int Interpreter::findIndex(std::vector<std::string> parameterStrings, std::string parameterId, int prevIndex) {
    //look through the list
    int parameterSize = parameterStrings.size();
    for (int i = 0; i < parameterSize; i++) {
        if (parameterStrings.at(i) == parameterId && (i > prevIndex)) {
            return i;
        }
    }
    return -1;
}

std::vector<int> Interpreter::createIndexList(Relation *joinedRelation, Predicate* headPredicate) {
    std::vector<int> indices;
    for (unsigned int i = 0; i < headPredicate->getSize(); i++) {
        std::string attribute = headPredicate->getParameter(i);
        for (unsigned int j = 0; j < joinedRelation->getHeaderSize(); j++) {
            if (joinedRelation->getAttribute(j) == attribute) {
                indices.push_back(j);
                break;
            }
        }
    }
    return indices;
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

    return -1;
}

bool Interpreter::checkAllConst(Predicate* query) {
    int count = 0;
    for (int i = 0; i < query->getSize(); i++) {
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

void Interpreter::toString(Rule* rule) {
    std::cout << rule->getHeadPredicate()->getId() << "(";
    for (unsigned int i = 0; i < rule->getHeadPredicate()->getSize(); i++) {
        
    }
}


