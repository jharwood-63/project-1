//
// Created by jharw on 10/25/2021.
//

#ifndef PROJECT_1_INTERPRETER_H
#define PROJECT_1_INTERPRETER_H

#include "DatalogProgram.h"
#include "Database.h"
#include <string>
#include <vector>

class Interpreter {
private:
    DatalogProgram* datalogProgram;
    Database* database;

    void createRelations();
    void createTuples();
    Relation* evaluatePredicate(Predicate* predicate);

    Relation* findRelation(Predicate* p);
    bool setConstant(std::string parameterId);
    int findIndex1(std::vector<std::string> parameterStrings, std::string parameterId);
    int findIndex2(std::vector<std::string> parameterStrings, std::string parameterId);
    bool checkDuplicates(std::vector<std::string> parameterStrings, std::string parameterId);
public:
    Interpreter(DatalogProgram* datalogProgram, Database* database);

    void evaluateQueries();
};


#endif //PROJECT_1_INTERPRETER_H
