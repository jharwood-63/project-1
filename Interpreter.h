//
// Created by jharw on 10/25/2021.
//

#ifndef PROJECT_1_INTERPRETER_H
#define PROJECT_1_INTERPRETER_H

#include "DatalogProgram.h"
#include "Database.h"
#include <string>

class Interpreter {
private:
    DatalogProgram* datalogProgram;
    Database* database;

    void createRelations();
    void createTuples();
    Relation* evaluatePredicate(Predicate p);
public:
    Interpreter(DatalogProgram* datalogProgram, Database* database);

    void evaluateQueries();
};


#endif //PROJECT_1_INTERPRETER_H
