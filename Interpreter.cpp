//
// Created by jharw on 10/25/2021.
//

#include "Interpreter.h"

Interpreter::Interpreter(DatalogProgram datalogProgram, Database database) {
    this->datalogProgram = datalogProgram;
    this->database = database;

    createRelations();
}

void Interpreter::createRelations() {
    int headerSize;
    //run through the schemes
    for(unsigned int i = 0; i < datalogProgram.schemes.size(); i++) {
        //add attributes to the header
        Header* newHeader = new Header();
        headerSize = datalogProgram.schemes.at(i)->getId().size();
        for (unsigned int j = 0; j < headerSize; j++) {
            std::string* currChar = (std::string*)(datalogProgram.schemes.at(i)->getId()[j]);
            newHeader->addAttribute(*currChar);
        }
        Relation* newRelation = new Relation(datalogProgram.schemes.at(i)->getId(), newHeader);
        //add parameters as a tuple
        Tuple* newTuple = new Tuple();
        for (unsigned int k = 0; k < datalogProgram.schemes.at(i)->getSize(); k++) {
            newTuple->addValue(datalogProgram.schemes.at(i)->getParameter(k));
        }
        database.addToMap(newRelation);
    }
}