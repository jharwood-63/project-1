//
// Created by jharw on 10/25/2021.
//

#ifndef PROJECT_1_INTERPRETER_H
#define PROJECT_1_INTERPRETER_H

#include "DatalogProgram.h"
#include "Database.h"
#include <string>
#include <

class Interpreter {
private:
    DatalogProgram datalogProgram;
    Database database;

    void createRelations();
public:
    Interpreter(DatalogProgram datalogProgram, Database database);
};


#endif //PROJECT_1_INTERPRETER_H
